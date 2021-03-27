#include "SnowBlock.hpp"
#include "Blocks.hpp"
#include "../world/WorldReader.hpp"

bool SnowBlock::isValidPosition(const BlockData &data, WorldReader &reader, const glm::ivec3 &pos) {
    const auto down = reader.getData(pos - glm::ivec3(0, 1, 0));
    if (!down.isIn(Blocks::ICE) && !down.isIn(Blocks::PACKED_ICE) && !down.isIn(Blocks::BARRIER)) {
        if (!down.isIn(Blocks::HONEY_BLOCK) && !down.isIn(Blocks::SOUL_SAND)) {
//            return Block.doesSideFillSquare(down.getCollisionShape(worldIn, pos.down()), Direction.UP) || down.getBlock() == this && down.get(LAYERS) == 8;
        }
        return true;
    }
    return false;
}
