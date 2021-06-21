#include "BushBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"

bool BushBlock::isValidGround(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    return data.is(Blocks::GRASS_BLOCK)
        || data.is(Blocks::DIRT)
//        || data.is(Blocks::COARSE_DIRT)
        || data.is(Blocks::PODZOL)
        || data.is(Blocks::FARMLAND);
}

bool BushBlock::isValidPosition(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    const auto down = pos.down();
    return isValidGround(reader.getData(down), reader, down);
}
