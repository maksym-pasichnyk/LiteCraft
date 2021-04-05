#include "MushroomBlock.hpp"
#include "../world/WorldReader.hpp"

bool MushroomBlock::isValidGround(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    return data.isOpaque(); // data.isOpaqueCube(reader, pos);
}

bool MushroomBlock::isValidPosition(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    const auto blockpos = pos - glm::ivec3(0, 1, 0);
    const auto state = reader.getData(blockpos);
    if (state.isIn(BlockTags::MUSHROOM_GROW_BLOCK)) {
        return true;
    }
    return /*reader.getLightSubtracted(pos, 0) < 13 &&*/ isValidGround(state, reader, blockpos);
}
