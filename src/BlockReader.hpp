#pragma once

#include <stdint.hpp>
#include <concepts>

#include "Block.hpp"
#include "BlockTable.hpp"

template <typename T>
concept IBlockReader = requires(T& self, BlockLayers blockLayers, int32 x, int32 y, int32 z) {
    { self.getBlock(x, y, z)} -> std::same_as<BlockLayers>;
    { self.setBlock(x, y, z, blockLayers)} -> std::same_as<void>;
//    { self.getChunk(x, z)} -> std::same_as<Chunk*>;
};