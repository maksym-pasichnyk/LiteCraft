#pragma once

#include "ClientChunkProvider.h"
#include "../../block/Block.hpp"

#include <memory>

struct ClientWorld {
    std::unique_ptr<ClientChunkProvider> provider;

    ClientWorld() {
        provider = std::make_unique<ClientChunkProvider>(8);
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

    auto getData(glm::ivec3 pos) const -> BlockData {
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

    void setData(glm::ivec3 pos, BlockData blockData) {
        setData(pos.x, pos.y, pos.z, blockData);
    }

    void setData(int32_t x, int32_t y, int32_t z, BlockData blockData) {
        if (y >= 0 && y < 256) {
            if (auto chunk = getChunk(x >> 4, z >> 4)) {
                chunk->setData(x, y, z, blockData);
            }
        }
    }

    auto getBlock(glm::ivec3 pos) const -> Block* {
        return getBlock(pos.x, pos.y, pos.z);
    }

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return Block::id_to_block[(int) getData(x, y, z).id];
    }
};
