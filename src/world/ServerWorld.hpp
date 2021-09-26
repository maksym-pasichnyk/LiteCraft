#pragma once

#include "ChunkManager.hpp"
#include "gen/NoiseChunkGenerator.hpp"
#include "gen/feature/structure/TemplateManager.hpp"

#include <memory>

struct Biome;
struct CraftServer;
struct ChunkManager;
struct NoiseChunkGenerator;
struct ServerWorld {
    CraftServer* server;
    std::unique_ptr<ChunkManager> manager;
    std::unique_ptr<TemplateManager> templates;
    std::unique_ptr<NoiseChunkGenerator> generator;
    int64_t seed = 1;

    int viewDistance = -1;

    explicit ServerWorld(CraftServer* server, int viewDistance);
    ~ServerWorld() {
        manager.reset();
        generator.reset();
    }

    Biome* getNoiseBiomeRaw(int x, int y, int z);

    auto getChunk(int32_t x, int32_t z) const -> Chunk* {
        return manager->getChunk(x, z).get();
    }

    auto getLightFor(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
        static constexpr std::array getLight {
            &Chunk::getSkyLight,
            &Chunk::getBlockLight,
        };
        auto chunk = getChunk(x >> 4, z >> 4);
        if (chunk == nullptr) {
            return 0;
        }
        return (chunk->*getLight[channel])(x, y, z);
    }

    void setLightFor(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) const {
        static constexpr std::array setLight {
            &Chunk::setSkyLight,
            &Chunk::setBlockLight,
        };
        (getChunk(x >> 4, z >> 4)->*setLight[channel])(x, y, z, val);
    }

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
        if (y < 0 || y > 255) {
            return {};
        }
        return getChunk(x >> 4, z >> 4)->getData(x, y, z);
    }

    bool setData(int32_t x, int32_t y, int32_t z, BlockData data) {
        if (y < 0 || y > 255) {
            return false;
        }
        return getChunk(x >> 4, z >> 4)->setData(x, y, z, data);
    }
    int getHeight(HeightmapType type, int x, int z) {
        return getChunk(x >> 4, z >> 4)->getHeight(type, x & 15, z & 15);
    }
};