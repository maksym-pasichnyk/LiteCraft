#pragma once

#include "../tags/BlockTags.hpp"
#include "../util/math/BlockPos.hpp"

#include <cstdint>
#include <compare>

enum class BlockStateProperty;

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
    auto hasProperty(BlockStateProperty property) const -> bool;
};