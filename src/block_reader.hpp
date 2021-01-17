#pragma once

#include <stdint.hpp>
#include <concepts>

struct Tile;

template <typename T>
concept IBlockReader = requires(T& self, Tile* tile, int32 x, int32 y, int32 z) {
    {self.getTile(x, y, z)} -> std::same_as<Tile*>;
    {self.setTile(x, y, z, tile)} -> std::same_as<void>;
};