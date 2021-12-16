#pragma once

#include "ClientChunkProvider.hpp"
#include "block/BlockData.hpp"

#include <memory>

struct Biome;

struct ClientWorld {
    std::unique_ptr<ClientChunkProvider> provider;

    ClientWorld(int viewDistance) {
        provider = std::make_unique<ClientChunkProvider>(viewDistance);
    }

    void loadChunk(int32_t x, int32_t z, Chunk* chunk) {
        provider->loadChunk(x, z, chunk);
    }

    void unloadChunk(int32_t x, int32_t z) {
        provider->unloadChunk(x, z);
    }

    auto getChunk(int32_t x, int32_t z) const -> Chunk* {
        return provider->getChunk(x, z);
    }

    auto getData(const glm::ivec3& pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
        if (y >= 0 && y < 256) {
            if (auto chunk = getChunk(x >> 4, z >> 4)) {
                return chunk->getData(x, y, z);
            }
        }
        return {};
    }

    auto getBlock(const glm::ivec3& pos) const -> Block* {
        return getBlock(pos.x, pos.y, pos.z);
    }

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return getData(x, y, z).getBlock();
    }

    auto getBiome(const glm::ivec3& pos) const -> Biome* {
        return getBiome(pos.x, pos.y, pos.z);
    }

    auto getBiome(int32_t x, int32_t y, int32_t z) const -> Biome* {
        return nullptr;
    }
};
