#pragma once

#include <concepts>
#include <glm/vec3.hpp>

#include "BlockData.hpp"

template <typename T>
concept IBlockReader = requires(T& self, BlockData blockData, int32_t x, int32_t y, int32_t z, BlockPos pos) {
    { self.getData(x, y, z)} -> std::same_as<BlockData>;
    { self.getData(pos)} -> std::same_as<BlockData>;
};

template <typename T>
concept IBlockWriter = requires(T& self, BlockData blockData, int32_t x, int32_t y, int32_t z, BlockPos pos) {
    { self.setData(x, y, z, blockData)} -> std::same_as<void>;
    { self.setData(pos, blockData)} -> std::same_as<void>;
};