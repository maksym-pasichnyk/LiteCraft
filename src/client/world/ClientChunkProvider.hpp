#pragma once

#include "chunk/ChunkArray.hpp"

struct ClientChunkProvider {
    ChunkArray chunkArray;

    explicit ClientChunkProvider(int viewDistance)
        : chunkArray{adjustViewDistance(viewDistance)} {}

    void loadChunk(int32_t x, int32_t z, Chunk* chunk) {
        if (chunkArray.inView(x, z)) {
            chunkArray.set(chunkArray.getIndex(x, z), chunk);
        }
    }

    void unloadChunk(int32_t x, int32_t z) {
        if (chunkArray.inView(x, z)) {
            const auto i = chunkArray.getIndex(x, z);
            auto chunk = chunkArray.get(i);
            if (isValid(chunk, x, z)) {
                chunkArray.set(i, nullptr);
            }
        }
    }

    auto getChunk(int32_t x, int32_t z) const -> Chunk* {
        if (chunkArray.inView(x, z)) {
            auto chunk = chunkArray.get(chunkArray.getIndex(x, z));
            if (isValid(chunk, x, z)) {
                return chunk;
            }
        }
        return nullptr;
    }

    static auto isValid(Chunk* chunk, int32_t x, int32_t z) -> bool {
        return chunk != nullptr && chunk->pos.x == x && chunk->pos.z == z;
    }

    static auto adjustViewDistance(int viewDistance) -> int {
        return std::max(2, viewDistance) + 3;
    }
};
