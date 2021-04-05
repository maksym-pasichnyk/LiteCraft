#include "Feature.hpp"
#include "../../../block/Blocks.hpp"

bool Feature::isDirt(Block* block) {
    return block == Blocks::DIRT
        || block == Blocks::GRASS_BLOCK
        || block == Blocks::PODZOL
        || block == Blocks::COARSE_DIRT
        || block == Blocks::MYCELIUM;
}
