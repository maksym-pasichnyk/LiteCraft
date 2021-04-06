#include "BushBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"

bool BushBlock::isValidGround(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    return data.isIn(Blocks::GRASS_BLOCK)
        || data.isIn(Blocks::DIRT)
//        || data.isIn(Blocks::COARSE_DIRT)
        || data.isIn(Blocks::PODZOL)
        || data.isIn(Blocks::FARMLAND);
}

bool BushBlock::isValidPosition(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    const auto down = pos.down();
    return isValidGround(reader.getData(down), reader, down);
}
