#pragma once

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
    static const ChunkStatus Empty;
    static const ChunkStatus StructureStart;
    static const ChunkStatus StructureReferences;
//    static const ChunkStatus Biome;
//    static const ChunkStatus Noise;
    static const ChunkStatus Surface;
//    static const ChunkStatus Carver;
//    static const ChunkStatus LiquidCarver;
    static const ChunkStatus Features;
    static const ChunkStatus Light;
    static const ChunkStatus Full;

    static constexpr std::array ALL {
        &ChunkStatus::Empty,
        &ChunkStatus::StructureStart,
        &ChunkStatus::StructureReferences,
//        &ChunkStatus::Biome,
//        &ChunkStatus::Noise,
        &ChunkStatus::Surface,
//        &ChunkStatus::Carver,
//        &ChunkStatus::LiquidCarver,
        &ChunkStatus::Features,
        &ChunkStatus::Light,
        &ChunkStatus::Full
    };

    using Fn = void(*)(ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed);

    int32_t ordinal;
    int32_t range;
    Fn generate;

    static ChunkStatus create(ChunkStatus const* parent, int32_t range, Fn generate) noexcept;
    static ChunkStatus const* getById(int32_t ordinal);
};