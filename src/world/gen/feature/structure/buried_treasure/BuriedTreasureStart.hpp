#pragma once

#include "BuriedTreasureStructure.hpp"
#include <world/gen/feature/structure/StructureStart.hpp>

struct BuriedTreasureStructure::Start : StructureStart {
    Start(Structure *structure, int chunkx, int chunkz, BoundingBox bounds, int references, int64_t seed)
        : StructureStart(structure, chunkx, chunkz, bounds, references, seed) {}

    void createComponents(ChunkGenerator &generator, TemplateManager &templateManager, int chunkx, int chunkz, Biome &biome, const StructureConfig &config, int64_t seed) override;
};
