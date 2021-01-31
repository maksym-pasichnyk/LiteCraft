#pragma once

#include <stdint.hpp>
#include <concepts>

#include "Block.hpp"
#include "BlockTable.hpp"

template <typename T>
concept IBlockReader = requires(T& self, BlockData blockData, int32 x, int32 y, int32 z) {
    { self.getBlock(x, y, z)} -> std::same_as<BlockData>;
    { self.setBlock(x, y, z, blockData)} -> std::same_as<void>;
};