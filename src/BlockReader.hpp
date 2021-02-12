#pragma once

#include <stdint.hpp>
#include <concepts>
#include <glm/vec3.hpp>

#include "Block.hpp"
#include "BlockTable.hpp"

template <typename T>
concept IBlockReader = requires(T& self, BlockData blockData, int32 x, int32 y, int32 z, glm::ivec3 pos) {
    { self.getData(x, y, z)} -> std::same_as<BlockData>;
    { self.setData(x, y, z, blockData)} -> std::same_as<void>;
    { self.getData(pos)} -> std::same_as<BlockData>;
    { self.setData(pos, blockData)} -> std::same_as<void>;
};