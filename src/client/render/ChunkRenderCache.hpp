#pragma once

#include "../../world/chunk/Chunk.hpp"

struct ChunkRenderCache {
    int32_t chunk_x;
    int32_t chunk_z;
    glm::ivec2 bounds_min;
    glm::ivec2 bounds_max;
    std::array<Chunk*, 9> chunks{};

    ChunkRenderCache(int32_t chunk_x, int32_t chunk_z) :
        chunk_x(chunk_x),
        chunk_z(chunk_z),
        bounds_min{chunk_x - 1, chunk_z - 1},
        bounds_max{chunk_x + 1, chunk_z + 1}
    {}

    auto toIndex(int32_t x, int32_t z) const -> size_t {
        return (x - bounds_min.x) + (z - bounds_min.y) * 3;
    }

    auto chunkExists(int32_t x, int32_t z) const -> bool {
        return bounds_min.x <= x && x <= bounds_max.x && bounds_min.y <= z && z <= bounds_max.y;
    }

    auto getMainChunkPos() const -> ChunkPos {
        return {chunk_x, chunk_z};
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

    auto getData(glm::ivec3 pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    auto getLight(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
        return getChunk(x >> 4, z >> 4)->getLight(x, y, z, channel);
    }

    auto getLight(glm::ivec3 pos, int32_t channel) const -> int32_t {
        return getLight(pos.x, pos.y, pos.z, channel);
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t {
        return getChunk(x >> 4, z >> 4)->getLightPacked(x, y, z);
    }

    auto getLightPacked(glm::ivec3 pos) const -> int32_t {
        return getLightPacked(pos.x, pos.y, pos.z);
    }

    auto getMainChunk() const -> Chunk* {
        return chunks[4];
    }
};
