#include "BlockData.hpp"
#include "Blocks.hpp"
#include "Block.hpp"

#include <range/v3/algorithm.hpp>

bool BlockData::in(const BlockTag &tag) const {
    return getBlock()->in(tag);
}

bool BlockData::isAir() const {
    return getBlock()->behaviour.isAir;
}
auto BlockData::getBlock() const -> Block* {
    return Blocks::blocks.entries[static_cast<size_t>(id)].get();
}
auto BlockData::getMaterial() const -> BlockMaterial * {
    return getBlock()->getMaterial();
}
auto BlockData::isOpaque() const -> bool {
    return getMaterial()->isOpaque;
}
auto BlockData::isSolid() const -> bool {
    return getBlock()->behaviour.isSolid;
}
auto BlockData::getLightLevel() const -> int32_t {
    return getBlock()->getLightLevel(*this);
}
auto BlockData::isValidPosition(WorldReader &reader, const glm::vec3 &pos) const -> bool {
    return getBlock()->isValidPosition(*this, reader, pos);
}
auto BlockData::has(Property property) const -> bool {
    return getBlock()->binds.contains(property);
}
auto BlockData::get(Property prop) const -> PropertyValue {
    return getBlock()->binds.at(prop).first(*this);
}
auto BlockData::set(Property prop, const PropertyValue &property) const -> BlockData {
    return getBlock()->binds.at(prop).second(*this, property);
}

auto BlockData::rotate(Rotation rotation) const -> BlockData {
    return getBlock()->rotate(*this, rotation);
}

auto BlockData::mirror(Mirror mirror) const -> BlockData {
    return getBlock()->mirror(*this, mirror);
}
