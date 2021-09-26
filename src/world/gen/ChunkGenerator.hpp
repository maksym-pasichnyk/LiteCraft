#pragma once

#include "GenerationStage.hpp"
#include "../biome/provider/BiomeProvider.hpp"

#include <memory>
#include <mutex>

struct Chunk;
struct ChunkPos;
struct WorldGenRegion;
struct TemplateManager;
struct StructureFeature;
struct ChunkGenerator {
    std::unique_ptr<BiomeProvider> biomeProvider;

    explicit ChunkGenerator(std::unique_ptr<BiomeProvider>&& biomeProvider);
    virtual ~ChunkGenerator() = default;

    virtual void generateStructures(WorldGenRegion& region, Chunk& chunk, TemplateManager& templates);
    virtual void getStructureReferences(WorldGenRegion& region, Chunk& chunk);
    virtual void generateTerrain(Chunk& chunk) = 0;
    virtual void generateCarvers(WorldGenRegion& region, int64_t seed, Chunk& chunk/*, GenerationStage::Carving carving*/);
    virtual void generateSurface(WorldGenRegion& region, Chunk& chunk) = 0;
    virtual void generateFeatures(WorldGenRegion& region, Chunk& chunk, TemplateManager& templates);

    auto getNoiseBiome(int x, int y, int z) -> Biome *;

    void createStarts(StructureFeature* feature, Chunk& chunk, TemplateManager& templates, int64_t seed, const ChunkPos& chunkPos, Biome& biome);
};
