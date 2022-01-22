#include "BlockStates.hpp"
#include "Blocks.hpp"
#include "Block.hpp"

#include <TextureAtlas.hpp>
#include <ResourceManager.hpp>
#include <client/render/model/Definition.hpp>

DynamicRegistry<Block*, BlockState> BlockStates::states;

void BlockStates::init() {
    for (auto&& [name, block] : Blocks::blocks.objects) {
        const auto location = ResourceLocation::from(name);

        states.add(block, std::make_unique<BlockState>(
            Resources::open(fmt::format("assets/{}/blockstates/{}.json", location.get_namespace(), location.get_location()))
                .and_then([](auto&& resource) { return Json::Read::read(*resource); })
                .and_then(Json::Into<BlockState>::into)
                .value()
        ));
    }
}