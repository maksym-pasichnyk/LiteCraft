#include "WorldReader.hpp"
#include "../block/Block.hpp"
#include "../block/material/Materials.hpp"

bool WorldReader::hasWater(const glm::ivec3 &pos) {
//        return getFluidState(pos).isTagged(FluidTags.WATER);
    return getData(pos).getBlock()->getMaterial() == Materials::WATER;
}

bool WorldReader::isAirBlock(const glm::ivec3 &pos) {
    return getData(pos).isAir();
}
