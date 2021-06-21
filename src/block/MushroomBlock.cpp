#include "MushroomBlock.hpp"
#include "../world/WorldReader.hpp"

bool MushroomBlock::isValidGround(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    return data.isOpaque(); // data.isOpaqueCube(reader, pos);
}

bool MushroomBlock::isValidPosition(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    const auto blockpos = pos.down();
    const auto state = reader.getData(blockpos);
    if (state.in(BlockTags::MUSHROOM_GROW_BLOCK)) {
        return true;
    }
    return /*reader.getLightSubtracted(pos, 0) < 13 &&*/ isValidGround(state, reader, blockpos);
}
