#pragma once

#include "world/chunk/Chunk.hpp"

struct ChunkRenderCache {
    ChunkPos coords;
    glm::ivec2 bounds_min;
    glm::ivec2 bounds_max;
    std::array<Chunk*, 9> chunks{};

    ChunkRenderCache(int32_t x, int32_t z) :
        coords{x, z},
        bounds_min{x - 1, z - 1},
        bounds_max{x + 1, z + 1} {}

    auto toIndex(int32_t x, int32_t z) const -> size_t {
        return (x - bounds_min.x) + (z - bounds_min.y) * 3;
    }

    auto chunkExists(int32_t x, int32_t z) const -> bool {
        return bounds_min.x <= x && x <= bounds_max.x && bounds_min.y <= z && z <= bounds_max.y;
    }

    auto getChunk(int32_t x, int32_t z) const -> Chunk* {
        if (chunkExists(x, z)) {
            return chunks[toIndex(x, z)];
        }
        return nullptr;
    }

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return getData(x, y, z).getBlock();
    }

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
        if (y < 0 || y > 255) {
            return {};
        }
        return getChunk(x >> 4, z >> 4)->getData(x, y, z);
    }

    auto getData(const glm::ivec3& pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t {
        auto chunk = getChunk(x >> 4, z >> 4);
        auto bl = chunk->getBlockLight(x, y, z);
        auto sl = chunk->getSkyLight(x, y, z);
        return (sl << 4) | bl;
    }

    auto getLightPacked(const glm::ivec3& pos) const -> int32_t {
        return getLightPacked(pos.x, pos.y, pos.z);
    }
};
