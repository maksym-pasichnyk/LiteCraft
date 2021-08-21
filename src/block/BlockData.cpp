#include "BlockData.hpp"
#include "Blocks.hpp"
#include "Block.hpp"

#include <range/v3/algorithm.hpp>

bool BlockData::in(const BlockTag &tag) const {
    return getBlock()->in(tag);
}

bool BlockData::isAir() const {
    return getBlock()->properties.isAir;
}
auto BlockData::getBlock() const -> Block* {
    return Blocks::blocks[static_cast<size_t>(id)];
}
auto BlockData::getMaterial() const -> Material * {
    return getBlock()->getMaterial();
}
auto BlockData::isOpaque() const -> bool {
    return getMaterial()->isOpaque;
}
auto BlockData::isSolid() const -> bool {
    return getBlock()->properties.isSolid;
}
auto BlockData::getLightLevel() const -> int32_t {
    return getBlock()->getLightLevel(*this);
}
auto BlockData::isValidPosition(WorldReader &reader, const glm::vec3 &pos) const -> bool {
    return getBlock()->isValidPosition(*this, reader, pos);
}
auto BlockData::hasProperty(BlockStateProperty property) const -> bool {
    auto properties = getBlock()->getBlockStateProperties();
    return ranges::find(properties, property) != properties.end();
}