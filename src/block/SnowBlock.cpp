#include "SnowBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"

bool SnowBlock::isValidPosition(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    const auto down = reader.getData(pos.down());
    if (!down.is(Blocks::ICE) && !down.is(Blocks::PACKED_ICE) && !down.is(Blocks::BARRIER)) {
        if (!down.is(Blocks::HONEY_BLOCK) && !down.is(Blocks::SOUL_SAND)) {
//            return Block.doesSideFillSquare(down.getCollisionShape(worldIn, pos.down()), Direction.UP) || down.getBlock() == this && down.get(LAYERS) == 8;
        }
        return true;
    }
    return false;
}
