#include "SingleJigsawPiece.hpp"

#include <block/Blocks.hpp>
#include <world/gen/feature/processor/ProcessorLists.hpp>

auto SingleJigsawPiece::to_json() -> Json {
	return {
        {"type", "single"},
        {"location", location},
        {"projection", projection},
        {"processors", ProcessorLists::processors.name(processors).value()}
    };
}

auto SingleJigsawPiece::from_json(const Json &o) -> std::unique_ptr<JigsawElement> {
    auto processors = ProcessorLists::processors.get(o.at("processors").as_string().value()).value();
    return std::make_unique<SingleJigsawPiece>(o.at("location").as_string().value(), processors, o.at("projection"));
}

void SingleJigsawPiece::place(WorldGenRegion &region, TemplateManager &manager, ChunkGenerator &generator, Random &random, const BoundingBox &box, const BlockPos &pos, const PlacementSettings& settings) {
    auto templ = manager.get(location);

    for (auto&& info : templ->blocks) {
        if (info.state.isAir()) {
            continue;
        }

        const auto new_pos = settings.calculateConnectedPosition(info.pos).add(pos);
        const auto new_state = info.state.rotate(settings.rotation);//.mirror(settings.mirror)

//        if (!settings.boundingBox.isVecInside(new_pos)) {
//            continue;
//        }

        region.setData(new_pos, new_state);
    }
}
auto SingleJigsawPiece::getJigsawBlocks(TemplateManager &manager, const BlockPos &pos, Rotation rotation, Random &random) -> std::vector<BlockInfo> {
    auto templ = manager.get(location);

    const auto settings = PlacementSettings{.rotation = rotation};
    auto blocks = templ->blocks | ranges::views::filter([](auto&& info) { return info.state.is(Blocks::JIGSAW); });
    return blocks | ranges::views::transform([&settings, &pos](auto&& info) {
        return BlockInfo {
            .pos = settings.calculateConnectedPosition(info.pos).add(pos),
            .state = info.state.rotate(settings.rotation),
            .nbt = info.nbt,
        };
    }) | ranges::to_vector;
}

auto SingleJigsawPiece::getBoundingBox(TemplateManager &manager, const BlockPos &pos, Rotation rotation) -> BoundingBox {
    return manager.get(location)->getBoundingBox(PlacementSettings{.rotation = rotation}, pos);
}
