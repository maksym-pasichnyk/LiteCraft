#pragma once

#include <util/math/ChunkPos.hpp>
#include "config/StructureConfig.hpp"

struct Biome;
struct ChunkGenerator;
struct TemplateManager;
struct StructureGenerateContext {
    ChunkGenerator& generator;
    TemplateManager& templateManager;
    ChunkPos pos;
    Biome& biome;
    int64_t seed;
};