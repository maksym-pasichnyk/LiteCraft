#pragma once

#include "../../block/BlockTable.hpp"

#include <memory>

struct Chunk;
struct BlockTable;
struct BiomeProvider;
struct WorldGenRegion;

struct ChunkGenerator {
    std::unique_ptr<BiomeProvider> biomeProvider;

    explicit ChunkGenerator(std::unique_ptr<BiomeProvider>&& biomeProvider);
    virtual ~ChunkGenerator() = default;

    virtual void generateStructures(WorldGenRegion& region, Chunk& chunk);
    virtual void getStructureReferences(WorldGenRegion& region, Chunk& chunk);
    virtual void generateTerrain(Chunk& chunk) = 0;
    virtual void generateSurface(WorldGenRegion& region, Chunk& chunk) = 0;
    virtual void generateFeatures(WorldGenRegion& region, Chunk& chunk);
};
