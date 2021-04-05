#pragma once

#include "../tags/BlockTags.hpp"

#include <cstdint>
#include <compare>
#include <glm/vec3.hpp>

enum class BlockStateProperties;

struct Block;
struct Material;
struct WorldReader;
struct BlockData {
    uint16_t id = 0;
    uint16_t dv = 0;

    constexpr auto operator<=>(const BlockData&) const noexcept = default;

    bool isIn(Block* block) const {
        return block == getBlock();
    }
    bool isIn(const BlockTag& tag) const;

    bool isAir() const;
    auto getBlock() const -> Block*;
    auto getMaterial() const -> Material*;
    auto isOpaque() const -> bool;
    auto isSolid() const -> bool;
    auto getLightLevel() const -> int32_t;
    auto isValidPosition(WorldReader& reader, const glm::vec3& pos) const -> bool;
    auto hasProperty(BlockStateProperties property) const -> bool;
};