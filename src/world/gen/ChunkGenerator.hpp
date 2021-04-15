#pragma once

#include "GenerationStage.hpp"
#include "../biome/provider/BiomeProvider.hpp"

#include <memory>

struct Chunk;
struct ChunkPos;
struct WorldGenRegion;
struct TemplateManager;
struct StructureManager;
struct StructureFeature;
struct ChunkGenerator {
    std::unique_ptr<BiomeProvider> biomeProvider;

    explicit ChunkGenerator(std::unique_ptr<BiomeProvider>&& biomeProvider);
    virtual ~ChunkGenerator() = default;

    virtual void generateStructures(WorldGenRegion& region, Chunk& chunk);
    virtual void getStructureReferences(WorldGenRegion& region, Chunk& chunk);
    virtual void generateTerrain(Chunk& chunk) = 0;
    virtual void generateCarvers(WorldGenRegion& region, int64_t seed, Chunk& chunk/*, GenerationStage::Carving carving*/);
    virtual void generateSurface(WorldGenRegion& region, Chunk& chunk) = 0;
    virtual void generateFeatures(WorldGenRegion& region, Chunk& chunk);

    void createStarts(StructureFeature* feature, /*DynamicRegistries registries,*/ StructureManager& structureManager, Chunk& chunk, TemplateManager& templateManager, int64_t seed, const ChunkPos& chunkPos, Biome& biome);
};
