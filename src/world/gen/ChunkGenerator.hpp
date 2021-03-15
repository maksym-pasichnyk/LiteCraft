#pragma once

#include "GenerationStage.hpp"

#include <memory>

struct Chunk;
struct BiomeProvider;
struct WorldGenRegion;

struct ChunkGenerator {
    std::unique_ptr<BiomeProvider> biomeProvider;

    explicit ChunkGenerator(std::unique_ptr<BiomeProvider>&& biomeProvider);
    virtual ~ChunkGenerator() = default;

    virtual void generateStructures(WorldGenRegion& region, Chunk& chunk);
    virtual void getStructureReferences(WorldGenRegion& region, Chunk& chunk);
    virtual void generateTerrain(Chunk& chunk) = 0;
    virtual void generateCarvers(WorldGenRegion& region, int64_t seed, Chunk& chunk, GenerationStage::Carving carving);
    virtual void generateSurface(WorldGenRegion& region, Chunk& chunk) = 0;
    virtual void generateFeatures(WorldGenRegion& region, Chunk& chunk);
};
