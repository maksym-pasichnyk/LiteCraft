#include "LilyPadBlock.hpp"
#include "material/Materials.hpp"
#include "../world/WorldReader.hpp"

bool LilyPadBlock::isValidGround(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    return (reader.hasWater(pos) || data.getMaterial() == Materials::ICE) && !reader.hasWater(pos.up());
}
