#pragma once

#include "MineshaftStructure.hpp"
#include "StructureStart.hpp"

struct MineshaftStructure::Start : StructureStart {
    Start(Structure *structure, int chunkx, int chunkz, BoundingBox bounds, int references, int64_t seed)
        : StructureStart(structure, chunkx, chunkz, bounds, references, seed) {}

    void createComponents(ChunkGenerator &generator, TemplateManager &templateManager, int chunkx, int chunkz, Biome &biome, const StructureConfig &config) override;
};
