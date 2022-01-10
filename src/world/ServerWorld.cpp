#include "ServerWorld.hpp"
#include "ChunkManager.hpp"
#include "world/gen/feature/structure/Structure.hpp"
#include "world/gen/feature/structure/StructureStart.hpp"
#include "world/gen/feature/structure/StructurePieces.hpp"
#include "world/gen/feature/structure/StructureGenerateContext.hpp"

#include <CraftServer.hpp>

#include <world/biome/Biomes.hpp>
#include <world/biome/provider/SingleBiomeProvider.hpp>
#include <world/biome/provider/OverworldBiomeProvider.hpp>

#include <world/gen/NoiseChunkGenerator.hpp>
#include <world/gen/feature/structure/TemplateManager.hpp>
#include <world/gen/feature/structure/StructureFeatures.hpp>

#include <memory>
#include <Json.hpp>

auto TemplateManager::readStructure(Nbt::Compound const& nbt) -> tl::optional<std::unique_ptr<Template>> {
    try {
        const auto AIR = Blocks::AIR->getDefaultState();

        auto palette = std::vector<BlockData>{};
        if (nbt.contains("palette")) {
            for (auto &&item : nbt.at("palette").get<Nbt::List>()) {
                palette.emplace_back([&nbt = item.get<Nbt::Compound>()] {
                    const auto location = ResourceLocation::from(nbt.at("Name").get<Nbt::String>());
                    const auto block = Blocks::blocks.get(location.get_location()).value();
                    auto state = block->getDefaultState();

                    if (nbt.contains("Properties")) {
                        auto&& properties = nbt.at("Properties").get<Nbt::Compound>();

                        for (auto&& [k, v] : properties) {
                            if (!block->properties.contains(k)) {
        //                            spdlog::info("Missing property: {}", k);
                                continue;
                            }
                            const auto property = block->properties.at(k);
                            state = state.set(property, PropertyUtil::parse(property, v).value());
                        }
                    }
                    return state;
                }());
            }
        }
        else {
            for (auto &&item : nbt.at("palettes").get<Nbt::List>().at(0).get<Nbt::List>()) {
                palette.emplace_back([&nbt = item.get<Nbt::Compound>()] {
                    const auto location = ResourceLocation::from(nbt.at("Name").get<Nbt::String>());
                    const auto block = Blocks::blocks.get(location.get_location()).value();
                    auto state = block->getDefaultState();

                    if (nbt.contains("Properties")) {
                        auto&& properties = nbt.at("Properties").get<Nbt::Compound>();

                        for (auto&& [k, v] : properties) {
                            if (!block->properties.contains(k)) {
//                                spdlog::info("Missing property: {}", k);
                                continue;
                            }
                            const auto property = block->properties.at(k);
                            state = state.set(property, PropertyUtil::parse(property, v).value());
                        }
                    }
                    return state;
                }());
            }
        }

        auto tmpl = std::make_unique<Template>();
        tmpl->size = [&nbt = nbt.at("size").get<Nbt::List>()] {
            return glm::ivec3{
                nbt.at(0).get<Nbt::Int>(),
                nbt.at(1).get<Nbt::Int>(),
                nbt.at(2).get<Nbt::Int>()
            };
        }();

        for (auto&& item : nbt.at("blocks").get<Nbt::List>()) {
            tmpl->blocks.emplace_back([&, &nbt = item.get<Nbt::Compound>()] {
                return BlockInfo{
                    .pos = [&nbt = nbt.at("pos").get<Nbt::List>()] {
                        return glm::ivec3{
                            nbt.at(0).get<Nbt::Int>(),
                            nbt.at(1).get<Nbt::Int>(),
                            nbt.at(2).get<Nbt::Int>()
                        };
                    }(),
                    .state = palette.at(nbt.at("state").get<Nbt::Int>()),
                    .nbt = nbt.contains("nbt") ? tl::optional(nbt.at("nbt").get<Nbt::Compound>()) : tl::nullopt
                };
            }());
        }
        return tmpl;
    } catch (const std::exception& e) {
        spdlog::error("TemplateManager::readStructure: {}", e.what());
    }
    return tl::nullopt;
}

struct DebugChunkGeneratorBase {
    explicit DebugChunkGeneratorBase() {
        for (auto&& [name, block] : Blocks::blocks.objects) {
            for (auto state : block->validStates) {
                states.emplace_back(state);
            }
        }

        spdlog::info("States: {}", states.size());

        grid.x = std::ceil(std::sqrt(states.size()));
        grid.y = (states.size() - 1) / grid.x;
    }

    auto createBiome() -> std::unique_ptr<Biome> {
        return std::make_unique<Biome>(Biome {
            .climate = BiomeClimate{},
            .biomeGenerationSettings = BiomeGenerationSettings{},
            .mobSpawnInfo = MobSpawnInfo{},
            .depth = 0.0f,
            .scale = 0.0f,
            .category = BiomeCategory::NONE,
            .effects = BiomeAmbience{}
        });
    }

    auto getBlockStateFor(int x, int z) -> tl::optional<BlockData> {
        //        if (x > 0 && z > 0 && x % 2 != 0 && z % 2 != 0) {
        //            x = x / 2;
        //            z = z / 2;
        //            if (x <= grid.x && z <= grid.y) {
        //                const auto i = std::abs(x * grid.x + z);
        //                if (i < states.size()) {
        //                    return states[i];
        //                }
        //            }
        //        }
        return tl::nullopt;
    }

    auto createBiomeSource() -> std::unique_ptr<SingleBiomeProvider> {
        return std::make_unique<SingleBiomeProvider>(biome.get());
    }
private:
    std::unique_ptr<Biome> biome = createBiome();
    std::vector<BlockData> states{};
    glm::ivec2 grid{};
};

struct DebugChunkGenerator : private DebugChunkGeneratorBase, public ChunkGenerator {
    explicit DebugChunkGenerator() : DebugChunkGeneratorBase{}, ChunkGenerator(createBiomeSource()) {}

    void generateStructures(WorldGenRegion& region, Chunk& chunk, TemplateManager& templates) override {
        if (chunk.coords == ChunkPos::from(0, 0)) {
            auto feature = StructureFeatures::registry.get("shipwreck").value();

            auto pieces = StructurePieces{};
            auto context = StructureGenerateContext{
                *this,
                templates,
                chunk.coords,
                *getNoiseBiome(0, 0, 0),
                region.getSeed()
            };
            feature->structure->generatePieces(pieces, context, feature->config);

            if (!pieces.empty()) {
                auto bounds = pieces.getBoundingBox().value();
                auto start = new StructureStart(
                    std::move(pieces.components),
                    feature->structure,
                    context.pos.x,
                    context.pos.z,
                    bounds,
                    1,
                    context.seed
                );
                chunk.addStructureStart(feature->structure, start);
            }
        }
    }

    void generateTerrain(Chunk &chunk) override {}

    void generateSurface(WorldGenRegion &region, Chunk& chunk) override {
        for (int x = 0; x < 16; ++x) {
            for (int z = 0; z < 16; ++z) {
                const auto pos = chunk.coords.getBlockPos(x, 0, z);

                const auto state = getBlockStateFor(pos.x, pos.z);
                if (state.has_value()) {
                    region.setData(pos, *state);
                }
            }
        }
    }
};

ServerWorld::ServerWorld(CraftServer *server, int viewDistance) : server(server), viewDistance(viewDistance) {
    std::default_random_engine engine{};
    engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    seed = engine();

    auto dimensionSettings = DimensionSettings{
        .noise{
            .sampling{
                .xz_scale = 0.9999999814507745,
                .y_scale = 0.9999999814507745,
                .xz_factor = 80,
                .y_factor = 160
            },
            .topSlide{
                .target = -10,
                .size = 3,
                .offset = 0
            },
            .bottomSlide{
                .target = -30,
                .size = 0,
                .offset = 0
            },
            .height = 256,
            .sizeVertical = 2,
            .sizeHorizontal = 1,
            .destinyFactor = 1.0,
            .densityOffset = -0.46875,
            .randomDensityOffset = true,
            .islandNoiseOverride = false,
            .amplified = false
        },
        .layer = Blocks::STONE->getDefaultState(),
        .fluid = Blocks::WATER->getDefaultState(),
        .bedrockRoofPosition = -1,
        .bedrockFloorPosition = 0,
        .seaLevel = 63,
        .disableMobGeneration = false
    };

    templates = std::make_unique<TemplateManager>();
    generator = std::make_unique<NoiseChunkGenerator>(seed, dimensionSettings, std::make_unique<OverworldBiomeProvider>(seed, false, false));
//    generator = std::make_unique<DebugChunkGenerator>();
//        generator = std::make_unique<NoiseChunkGenerator>(seed, std::make_unique<SingleBiomeProvider>(Biomes::SWAMP));
    manager = std::make_unique<ChunkManager>(this, generator.get(), templates.get());
}

Biome *ServerWorld::getNoiseBiomeRaw(int x, int y, int z) {
    return generator->biomeProvider->getNoiseBiome(x, y, z);
}
