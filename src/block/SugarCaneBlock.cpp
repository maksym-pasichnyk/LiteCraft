#include "SugarCaneBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"
#include "../util/Direction.hpp"

bool SugarCaneBlock::isValidPosition(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    const auto blockpos = pos.down();
    auto block = reader.getData(blockpos).getBlock();
    if (block == this) {
        return true;
    }
    if (block->isIn(BlockTags::SAND) ||
        (block == Blocks::GRASS_BLOCK) ||
        (block == Blocks::DIRT) ||
        (block == Blocks::COARSE_DIRT) ||
        (block == Blocks::PODZOL)) {

        for (Direction direction : DirectionUtil::Plane::HORIZONTAL) {
            const auto state = reader.getData(blockpos.offset(direction));
//            const auto fluid = reader.getFluidState(blockpos.offset(direction));
            if (/*fluid.isTagged(FluidTags.WATER) ||*/ state.isIn(Blocks::FROSTED_ICE) || state.isIn(Blocks::WATER)) {
                return true;
            }
        }
    }

    return false;
}
