#pragma once

#include "Block.hpp"

struct SnowBlock : Block {
    using Block::Block;

    bool isValidPosition(const BlockData& data, WorldReader &reader, const glm::vec3 &pos) override;
};