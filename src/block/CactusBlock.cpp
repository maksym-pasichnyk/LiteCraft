#include "CactusBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"
#include "../util/Direction.hpp"

bool CactusBlock::isValidPosition(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    for (Direction direction : Directions::Plane::HORIZONTAL) {
        const auto material = reader.getData(Directions::offset(pos, direction)).getMaterial();
        if (material->isSolid/* || worldIn.getFluidState(pos.offset(direction)).isTagged(FluidTags.LAVA)*/) {
            return false;
        }
    }

    const auto block = reader.getData(pos - glm::ivec3(0, 1, 0)).getBlock();
    return ((block == Blocks::CACTUS) || (block == Blocks::SAND) || (block == Blocks::RED_SAND))
        && !reader.getData(pos + glm::ivec3(0, 1, 0)).getMaterial()->isLiquid;
}
