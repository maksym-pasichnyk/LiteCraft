#include "BambooBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"

bool BambooBlock::isValidPosition(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    auto block = reader.getData(pos - glm::ivec3(0, 1, 0)).getBlock();
    return block == Blocks::SAND
        || block == Blocks::RED_SAND
        || block == Blocks::BAMBOO_SAPLING
        || block == Blocks::GRAVEL
        || block == Blocks::DIRT
        || block == Blocks::GRASS_BLOCK
        || block == Blocks::PODZOL
        || block == Blocks::COARSE_DIRT
        || block == Blocks::MYCELIUM;
}
