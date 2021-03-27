#include "PlainFlowerBlockStateProvider.hpp"
#include "../../biome/Biome.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

PlainFlowerBlockStateProvider::PlainFlowerBlockStateProvider() {
    RARE_FLOWERS = {
        Blocks::DANDELION->getDefaultState(), //Blocks::ORANGE_TULIP->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::RED_TULIP->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::PINK_TULIP->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::WHITE_TULIP->getDefaultState()
    };
    COMMON_FLOWERS = {
        Blocks::DANDELION->getDefaultState(), //Blocks::POPPY->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::AZURE_BLUET->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::OXEYE_DAISY->getDefaultState(),
        Blocks::DANDELION->getDefaultState(), //Blocks::CORNFLOWER->getDefaultState()
    };
}

BlockData PlainFlowerBlockStateProvider::getBlockState(Random &random, glm::ivec3 pos) {
    const double noise = Biome::INFO_NOISE.noiseAt((double)pos.x / 200.0, (double)pos.z / 200.0, false);
    if (noise < -0.8) {
        return RARE_FLOWERS[random.nextInt(RARE_FLOWERS.size())];
    }
    return random.nextInt(3) > 0
        ? COMMON_FLOWERS[random.nextInt(COMMON_FLOWERS.size())]
        : Blocks::DANDELION->getDefaultState();
}