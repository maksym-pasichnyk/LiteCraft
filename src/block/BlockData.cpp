#include "BlockData.hpp"
#include "Blocks.hpp"
#include "Block.hpp"

#include <algorithm>

auto BlockData::getBlock() const -> Block* {
    return Blocks::blocks[static_cast<size_t>(id)];
}
auto BlockData::isOpaque() const -> bool {
    return getBlock()->getMaterial()->isOpaque;
}
auto BlockData::getLightLevel() const -> int32_t {
    return getBlock()->getLightLevel(*this);
}
auto BlockData::isValidPosition(WorldReader &reader, const glm::vec3 &pos) const -> bool {
    return getBlock()->isValidPosition(*this, reader, pos);
}
auto BlockData::hasProperty(BlockStateProperties property) const -> bool {
    auto properties = getBlock()->getBlockStateProperties();
    return std::ranges::find(properties, property) != properties.end();
}
