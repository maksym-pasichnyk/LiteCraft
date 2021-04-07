#include "Feature.hpp"
#include "../../WorldReader.hpp"
#include "../../../block/Blocks.hpp"

bool Feature::isStone(Block* block) {
    return block == Blocks::STONE
        || block == Blocks::GRANITE
        || block == Blocks::DIORITE
        || block == Blocks::ANDESITE;
}

bool Feature::isDirt(Block* block) {
    return block == Blocks::DIRT
        || block == Blocks::GRASS_BLOCK
        || block == Blocks::PODZOL
        || block == Blocks::COARSE_DIRT
        || block == Blocks::MYCELIUM;
}

bool Feature::isDirtAt(WorldReader &reader, const BlockPos& pos) {
    return isDirt(reader.getData(pos).getBlock());
}

bool Feature::isAirAt(WorldReader &reader, const BlockPos &pos) {
    return reader.getData(pos).isAir();
}