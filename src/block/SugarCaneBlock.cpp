#include "SugarCaneBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"
#include "../util/Direction.hpp"

bool SugarCaneBlock::isValidPosition(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    const auto blockpos = pos - glm::ivec3(0, 1, 0);
    auto block = reader.getData(blockpos).getBlock();
    if (block == this) {
        return true;
    }
    if (block->isIn(BlockTags::SAND) ||
        (block == Blocks::GRASS_BLOCK) ||
        (block == Blocks::DIRT) ||
        (block == Blocks::COARSE_DIRT) ||
        (block == Blocks::PODZOL)) {

        for (Direction direction : Directions::Plane::HORIZONTAL) {
            const auto state = reader.getData(Directions::offset(blockpos, direction));
//            const auto fluid = reader.getFluidState(blockpos.offset(direction));
            if (/*fluid.isTagged(FluidTags.WATER) ||*/ state.isIn(Blocks::FROSTED_ICE) || state.isIn(Blocks::WATER)) {
                return true;
            }
        }
    }

    return false;
}
