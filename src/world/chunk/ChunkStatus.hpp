#pragma once

#include <span>
#include <cstdint>
#include <vector>

struct Chunk;
struct ServerWorld;
struct ChunkGenerator;
struct WorldLightManager;

struct ChunkStatus {
    static const ChunkStatus Empty;
    static const ChunkStatus StructureStart;
    static const ChunkStatus StructureReferences;
    static const ChunkStatus Biome;
    static const ChunkStatus Noise;
    static const ChunkStatus Surface;
    static const ChunkStatus Features;
    static const ChunkStatus Light;
    static const ChunkStatus Full;

    using Fn = void(*)(ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed);

    int range;
    Fn generate;

    static ChunkStatus create(int id, int range, Fn generate) noexcept;
    static ChunkStatus const* getById(int id);
};