#include "PlainFlowerBlockStateProvider.hpp"

#include <block/States.hpp>
#include <world/biome/Biome.hpp>

PlainFlowerBlockStateProvider::PlainFlowerBlockStateProvider() {
    RARE_FLOWERS = {
        States::ORANGE_TULIP,
        States::RED_TULIP,
        States::PINK_TULIP,
        States::WHITE_TULIP,
    };
    COMMON_FLOWERS = {
        States::POPPY,
        States::AZURE_BLUET,
        States::OXEYE_DAISY,
        States::CORNFLOWER,
    };
}

BlockData PlainFlowerBlockStateProvider::getBlockState(Random &random, BlockPos pos) {
    const double noise = Biome::INFO_NOISE.noiseAt((double)pos.x / 200.0, (double)pos.z / 200.0, false);
    if (noise < -0.8) {
        return RARE_FLOWERS[random.nextInt(RARE_FLOWERS.size())];
    }
    return random.nextInt(3) > 0
        ? COMMON_FLOWERS[random.nextInt(COMMON_FLOWERS.size())]
        : States::DANDELION;
}