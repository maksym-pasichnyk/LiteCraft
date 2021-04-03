#include "ForestFlowerBlockStateProvider.hpp"
#include "../../biome/Biome.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

ForestFlowerBlockStateProvider::ForestFlowerBlockStateProvider() {
    STATES = {
        Blocks::DANDELION->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::POPPY->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::ALLIUM->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::AZURE_BLUET->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::RED_TULIP->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::ORANGE_TULIP->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::WHITE_TULIP->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::PINK_TULIP->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::OXEYE_DAISY->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::CORNFLOWER->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::LILY_OF_THE_VALLEY->getDefaultState()
    };
}

BlockData ForestFlowerBlockStateProvider::getBlockState(Random &random, glm::ivec3 pos) {
    const double noise = (1.0 + Biome::INFO_NOISE.noiseAt(static_cast<double>(pos.x) / 48.0, static_cast<double>(pos.z) / 48.0, false)) / 2.0;
    return STATES[static_cast<int>(std::clamp(noise, 0.0, 0.9999) * static_cast<double>(STATES.size()))];
}