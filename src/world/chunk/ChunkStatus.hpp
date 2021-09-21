#pragma once

#include <util/Registry.hpp>

#include <span>
#include <array>
#include <vector>
#include <memory>
#include <cstdint>

struct Chunk;
struct ServerWorld;
struct ChunkGenerator;
struct WorldLightManager;

struct ChunkStatus {
    static Registry<ChunkStatus> all;

    static ChunkStatus* Empty;
    static ChunkStatus* StructureStart;
    static ChunkStatus* StructureReferences;
    static ChunkStatus* Biome;
    static ChunkStatus* Noise;
    static ChunkStatus* Surface;
    static ChunkStatus* Carvers;
//    static const ChunkStatus Carver;
//    static const ChunkStatus LiquidCarver;
    static ChunkStatus* Features;
    static ChunkStatus* Light;
    static ChunkStatus* Full;

    using Fn = void(*)(ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int range);

    int32_t ordinal;
    int32_t range;
    Fn on_generate;
    Fn on_load;

    void generate(ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed) {
        on_generate(world, lightManager, generator, x, z, chunk, chunks, seed, range);
    }

    static auto getByName(const std::string& name) -> ChunkStatus* {
        return all.objects.at(name);
    }

    static auto getById(int32_t ordinal) -> ChunkStatus* {
        return all.entries.at(ordinal).get();
    }

    static void init();
};