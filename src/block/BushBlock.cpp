#include "BushBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"

bool BushBlock::isValidGround(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    return data.isIn(Blocks::GRASS_BLOCK)
        || data.isIn(Blocks::DIRT)
//        || data.isIn(Blocks::COARSE_DIRT)
        || data.isIn(Blocks::PODZOL)
        || data.isIn(Blocks::FARMLAND);
}

bool BushBlock::isValidPosition(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    const auto down = pos - glm::ivec3(0, 1, 0);
    return isValidGround(reader.getData(down), reader, down);
}
