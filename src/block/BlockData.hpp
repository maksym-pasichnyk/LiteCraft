#pragma once

#include "../tags/BlockTags.hpp"
#include "../util/math/BlockPos.hpp"
#include <state/BlockStateProperties.hpp>

#include <cstdint>
#include <compare>

struct Block;
struct Material;
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
    auto getMaterial() const -> Material*;
    auto isOpaque() const -> bool;
    auto isSolid() const -> bool;
    auto getLightLevel() const -> int32_t;
    auto isValidPosition(WorldReader& reader, const glm::vec3& pos) const -> bool;

    auto has(BlockStateProperty property) const -> bool;

    auto get(BlockStateProperty prop) -> Property;
    auto set(BlockStateProperty prop, const Property& property) -> BlockData;

    template<BlockStateProperty prop>
    auto get() -> typename BlockStatePropertyType<prop>::type {
        return std::get<typename BlockStatePropertyType<prop>::type>(get(prop));
    }
    template<BlockStateProperty prop>
    auto set(typename BlockStatePropertyType<prop>::type property) -> BlockData {
        return set(prop, property);
    }
};