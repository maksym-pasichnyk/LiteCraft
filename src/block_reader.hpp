#pragma once

#include <stdint.hpp>
#include <concepts>

#include "block.hpp"

template <typename T>
concept IBlockReader = requires(T& self, BlockState blockState, int32 x, int32 y, int32 z) {
    { self.getBlock(x, y, z)} -> std::same_as<BlockState>;
    { self.setBlock(x, y, z, blockState)} -> std::same_as<void>;
};