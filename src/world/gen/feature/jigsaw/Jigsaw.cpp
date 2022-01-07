#include "Jigsaw.hpp"

#include <queue>
#include <range/v3/algorithm.hpp>

#include <block/JigsawBlock.hpp>
#include <world/gen/pools/JigsawPools.hpp>
#include <world/gen/feature/jigsaw/JigsawElement.hpp>
#include <world/gen/feature/jigsaw/JigsawPattern.hpp>
#include <world/gen/feature/jigsaw/EmptyJigsawPiece.hpp>
#include <world/gen/feature/structure/StructurePiece.hpp>

struct JigsawPiece : StructurePiece {
    BlockPos position;
    Rotation rotation;
    JigsawElement* element;

    explicit JigsawPiece(JigsawElement* element, const BlockPos& position, Rotation rotation, BoundingBox shape)
        : StructurePiece(0, shape)
        , position(position)
        , rotation(rotation)
        , element(element) {}

    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox&box, const ChunkPos& chunkPos, const BlockPos&pos) override {
        try {
            const auto settings = PlacementSettings{.rotation = rotation, .boundingBox = box};
            element->place(region, templates, generator, random, box, position, settings);
        } catch (std::exception const& e) {
            spdlog::error("{}", e.what());
        }
        return true;
    }
};

struct JigsawNode {
    JigsawPiece* piece;
    size_t depth = 0;
};

struct Shape {
    float minX = 0;
    float minY = 0;
    float minZ = 0;
    float maxX = 0;
    float maxY = 0;
    float maxZ = 0;

    static constexpr auto from(const BoundingBox& box) -> Shape {
        return Shape{
                .minX = static_cast<float>(box.minX),
                .minY = static_cast<float>(box.minY),
                .minZ = static_cast<float>(box.minZ),
                .maxX = static_cast<float>(box.maxX),
                .maxY = static_cast<float>(box.maxY),
                .maxZ = static_cast<float>(box.maxZ)
        };
    }

    constexpr void set(float x0, float y0, float z0, float x1, float y1, float z1) {
        minX = x0;
        minY = y0;
        minZ = z0;
        maxX = x1;
        maxY = y1;
        maxZ = z1;
    }

    constexpr auto deflate(float offset) const -> Shape {
        return inflate(-offset);
    }

    constexpr auto inflate(float offset) const -> Shape {
        return Shape{
                .minX = minX - offset,
                .minY = minY - offset,
                .minZ = minZ - offset,
                .maxX = maxX + offset,
                .maxY = maxY + offset,
                .maxZ = maxZ + offset
        };
    }

    constexpr auto intersect(const Shape& aabb) const noexcept -> bool {
        return maxX >= aabb.minX && minX <= aabb.maxX && maxZ >= aabb.minZ && minZ <= aabb.maxZ && maxY >= aabb.minY && minY <= aabb.maxY;
    }
};

static auto joinIsNotEmpty(std::span<const Shape> shapes, const Shape& aabb) -> bool {
    return cpp_iter(shapes).any([&aabb](const auto& element) -> bool {
        return aabb.intersect(element);
    });
}

void Jigsaw::createComponents(StructurePieces &pieces, StructureGenerateContext &context, const StructureConfig &config) {
    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);

    auto&& cfg = std::get<JigsawConfig>(config);
    const auto rotation = Rotation::NONE;
    const auto position = context.pos.getStartBlock();
    const auto start = random.nextElement(std::span(cfg.pool->pieces));
    const auto bounds = start->getBoundingBox(context.templateManager, position, rotation);

    const auto piece = new JigsawPiece(start, position, rotation, bounds);
    pieces.emplace(piece);

    auto shapes = std::vector<Shape>{};
    shapes.emplace_back(Shape::from(bounds));

    auto queue = std::queue<JigsawNode>{};
    queue.emplace(JigsawNode{.piece = piece, .depth = 0});

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        for (auto&& info_a : node.piece->element->getJigsawBlocks(context.templateManager, BlockPos{}, node.piece->rotation, random)) {
            const auto pool = [&info_a] {
                const auto location = ResourceLocation::from(info_a.nbt.value().at("pool").get<std::string>());
                return JigsawPools::pools.get(location.get_location()).value_or(nullptr);
            }();
            if (pool == nullptr) {
                spdlog::info("missing pool {}", info_a.nbt.value().at("pool").get<std::string>());
                continue;
            }
            const auto fallback = [pool] {
                const auto location = ResourceLocation::from(pool->fallback);
                return JigsawPools::pools.get(location.get_location()).value_or(nullptr);
            }();
            if (fallback == nullptr) {
                spdlog::info("missing fallback {}", pool->fallback);
                continue;
            }
            auto elements = std::vector<JigsawElement*>{};
            if (node.depth != cfg.size) {
                auto items = pool->getJigsawPieces(random);
                elements.insert(elements.end(), items.begin(), items.end());
            }
            {
                auto items = fallback->getJigsawPieces(random);
                elements.insert(elements.end(), items.begin(), items.end());
            }

            auto flag = false;
            for (auto element : elements) {
                if (dynamic_cast<EmptyJigsawPiece*>(element) != nullptr) {
                    break;
                }

                auto rotations = RotationUtil::VALUES;
                random.shuffle(std::span(rotations));

                for (auto new_rotation : rotations) {
                    for (auto&& info_b : element->getJigsawBlocks(context.templateManager, BlockPos{}, new_rotation, random)) {
                        const auto front_a = JigsawBlock::getFrontFacing(info_a.state);
                        const auto front_b = JigsawBlock::getFrontFacing(info_b.state);
                        const auto top_a = JigsawBlock::getTopFacing(info_a.state);
                        const auto top_b = JigsawBlock::getTopFacing(info_b.state);

                        if (front_a != DirectionUtil::getOpposite(front_b)) {
                            continue;
                        }

                        const auto joint = info_a.nbt.value().contains("joint")
                            ? info_a.nbt.value().at("joint").get<std::string>()
                            : DirectionUtil::getAxis(front_a) == DirectionAxis::Y
                                ? "rollable"
                                : "aligned";

                        if (joint != "rollable" && top_a != top_b) {
                            continue;
                        }

                        auto&& target = info_a.nbt.value().at("target").get<std::string>();
                        auto&& name = info_b.nbt.value().at("name").get<std::string>();

                        if (target != name) {
                            continue;
                        }

                        const auto new_position = node.piece->position - info_b.pos + info_a.pos + DirectionUtil::getOffset(JigsawBlock::getFrontFacing(info_a.state));

                        auto old_bounds = node.piece->bounds;
                        auto new_bounds = element->getBoundingBox(context.templateManager, new_position, new_rotation);
                        if (element->projection == JigsawProjection::RIGID) {
                            new_bounds.offset(0, old_bounds.maxY + 1 - new_bounds.minY, 0);
                        }

                        if (joinIsNotEmpty(shapes, Shape::from(new_bounds)/*.deflate(0.25f)*/)) {
                            continue;
                        }
                        shapes.emplace_back(Shape::from(new_bounds));

                        auto new_piece = new JigsawPiece(element, new_position, new_rotation, new_bounds);
                        pieces.emplace(new_piece);

                        if (node.depth < cfg.size) {
                            queue.emplace(JigsawNode{.piece = new_piece, .depth = node.depth + 1});
                        }

                        flag = true;
                        break;
                    }

                    if (flag) {
                        break;
                    }
                }

                if (flag) {
                    break;
                }
            }
        }
    }
}
