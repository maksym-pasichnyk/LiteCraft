#include "CactusBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"
#include "../util/Direction.hpp"

bool CactusBlock::isValidPosition(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    for (Direction direction : Directions::Plane::HORIZONTAL) {
        const auto material = reader.getData(Directions::offset(pos, direction)).getMaterial();
        if (material->isSolid/* || worldIn.getFluidState(pos.offset(direction)).isTagged(FluidTags.LAVA)*/) {
            return false;
        }
    }

    const auto block = reader.getData(pos.down()).getBlock();
    return ((block == Blocks::CACTUS) || (block == Blocks::SAND) || (block == Blocks::RED_SAND))
        && !reader.getData(pos.up()).getMaterial()->isLiquid;
}
