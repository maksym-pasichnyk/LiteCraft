#include "WorldReader.hpp"
#include "../block/Block.hpp"
#include "../block/material/Materials.hpp"

bool WorldReader::hasWater(const BlockPos &pos) {
//        return getFluidState(pos).isTagged(FluidTags.WATER);
    return getData(pos).getBlock()->getMaterial() == Materials::WATER;
}

bool WorldReader::isAirBlock(const BlockPos &pos) {
    return getData(pos).isAir();
}
