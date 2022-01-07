#pragma once

#include <compare>
#include <cstdint>
#include <util/Mirror.hpp>
#include <tags/BlockTags.hpp>
#include <util/math/BlockPos.hpp>
#include <state/util/PropertyUtil.hpp>

struct Block;
struct BlockMaterial;
struct WorldReader;
struct BlockData {
    uint16_t id = 0;
    uint16_t dv = 0;

    constexpr auto operator<=>(const BlockData&) const noexcept = default;

    bool is(Block* block) const {
        return block == getBlock();
    }
    bool in(const BlockTag& tag) const;

    bool isAir() const;
    auto getBlock() const -> Block*;
    auto getMaterial() const -> BlockMaterial *;
    auto isOpaque() const -> bool;
    auto isSolid() const -> bool;
    auto getLightLevel() const -> int32_t;
    auto isValidPosition(WorldReader& reader, const glm::vec3& pos) const -> bool;

    auto has(Property property) const -> bool;

    auto get(Property prop) const -> PropertyValue;
    auto set(Property prop, const PropertyValue & property) const -> BlockData;

    auto get(const std::string& prop) const -> PropertyValue;

    template<Property prop>
    auto get() const -> typename TypeFrom<prop>::type {
        return std::get<typename TypeFrom<prop>::type>(get(prop));
    }
    template<Property prop>
    auto set(typename TypeFrom<prop>::type property) const -> BlockData {
        return set(prop, property);
    }

    auto rotate(Rotation rotation) const -> BlockData;
    auto mirror(Mirror mirror) const -> BlockData;
};