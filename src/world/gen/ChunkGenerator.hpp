#pragma once

#include "src/BlockTable.hpp"

struct Chunk;
struct BlockTable;
struct WorldGenRegion;

struct ChunkGenerator {
    virtual ~ChunkGenerator() = default;

    virtual void generateStructures(WorldGenRegion& region, Chunk* chunk);
    virtual void getStructureReferences(WorldGenRegion& region, Chunk* chunk);
    virtual void generateTerrain(Chunk* chunk, BlockTable& pallete) = 0;
    virtual void generateSurface(WorldGenRegion& region, Chunk* chunk, BlockTable& pallete) = 0;
    virtual void generateFeatures(WorldGenRegion& region, Chunk* chunk, BlockTable& pallete);
};
