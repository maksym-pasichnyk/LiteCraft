#pragma once

#include <cstdint>
#include <compare>
#include <glm/vec3.hpp>

enum class BlockStateProperties;

struct Block;
struct WorldReader;
struct BlockData {
    uint16_t id = 0;
    uint16_t dv = 0;

    constexpr auto operator<=>(const BlockData&) const noexcept = default;

    bool isAir() const {
        return id == 0;
    }

    bool isIn(Block* block) const {
        return block == getBlock();
    }

    auto getBlock() const -> Block*;
    auto isOpaque() const -> bool;
    auto getLightLevel() const -> int32_t;
    auto isValidPosition(WorldReader& reader, const glm::vec3& pos) const -> bool;
    auto hasProperty(BlockStateProperties property) const -> bool;
};