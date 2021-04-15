#include "WorldReader.hpp"
#include "../block/Block.hpp"
#include "../block/material/Materials.hpp"

bool WorldReader::hasWater(const BlockPos &pos) const {
//        return getFluidState(pos).isTagged(FluidTags.WATER);
    return getData(pos).getBlock()->getMaterial() == Materials::WATER;
}

bool WorldReader::isAirBlock(const BlockPos &pos) const {
    return getData(pos).isAir();
}

bool WorldReader::isLiquidBlock(const BlockPos &pos) const {
    return getData(pos).getMaterial()->isLiquid;
}
