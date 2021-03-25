#include "BlockData.hpp"
#include "Blocks.hpp"
#include "Block.hpp"

Block *BlockData::getBlock() const {
    return Blocks::blocks[static_cast<size_t>(id)];
}
bool BlockData::isOpaque() const {
    return getBlock()->getMaterial()->isOpaque;
}
int32_t BlockData::getLightLevel() const{
    return getBlock()->getLightLevel(*this);
}
