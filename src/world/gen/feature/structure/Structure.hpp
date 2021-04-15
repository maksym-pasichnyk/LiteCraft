#pragma once

#include "StructureFeature.hpp"
#include "../../settings/StructureSeparation.hpp"
#include "../../../../util/math/ChunkPos.hpp"
#include "../../../../util/math/BoundingBox.hpp"

struct Biome;
struct Random;
struct BoundingBox;
struct BiomeProvider;
struct StructureStart;
struct ChunkGenerator;
struct TemplateManager;
struct Structure {
    virtual ~Structure() = default;

    virtual StructureStart* createStart(int x, int z, const BoundingBox& bounds, int refCount, int64_t seed) = 0;
    virtual bool canGenerate(ChunkGenerator& generator, BiomeProvider& biomes, int64_t seed, Random& random, int x, int z, Biome& biome, const ChunkPos& pos, const StructureConfig& config) {
        return true;
    }
    virtual bool func_230365_b_() {
        return true;
    }

    StructureFeature* withConfiguration(StructureConfig config) {
        return new StructureFeature{
            .structure = this,
            .config = std::move(config)
        };
    }

    StructureStart* generate(ChunkGenerator& generator, BiomeProvider& provider, TemplateManager& templateManager, int64_t seed, const ChunkPos& pos, Biome& biome, int refCount, Random& random, const StructureSeparation& settings, const StructureConfig& config);

    ChunkPos getChunkPosForStructure(const StructureSeparation& settings, int64_t seed, Random& random, int x, int z);
};