#include "ForestFlowerBlockStateProvider.hpp"

#include <block/States.hpp>
#include <world/biome/Biome.hpp>

ForestFlowerBlockStateProvider::ForestFlowerBlockStateProvider() {
    STATES = {
        States::DANDELION,
        States::POPPY,
        States::ALLIUM,
        States::AZURE_BLUET,
        States::RED_TULIP,
        States::ORANGE_TULIP,
        States::WHITE_TULIP,
        States::PINK_TULIP,
        States::OXEYE_DAISY,
        States::CORNFLOWER,
        States::LILY_OF_THE_VALLEY
    };
}

BlockData ForestFlowerBlockStateProvider::getBlockState(Random &random, BlockPos pos) {
    const double noise = (1.0 + Biome::INFO_NOISE.noiseAt(static_cast<double>(pos.x) / 48.0, static_cast<double>(pos.z) / 48.0, false)) / 2.0;
    return STATES[static_cast<int>(std::clamp(noise, 0.0, 0.9999) * static_cast<double>(STATES.size()))];
}