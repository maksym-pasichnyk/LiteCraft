#pragma once

#include "../../settings/StructureSeparation.hpp"
#include "PieceGenerator.hpp"
#include "StructureFeature.hpp"
#include "config/StructureConfig.hpp"
#include <util/math/BoundingBox.hpp>
#include <util/math/ChunkPos.hpp>

#include <map>
#include <vector>
#include <Json.hpp>

struct Biome;
struct Random;
struct BoundingBox;
struct BiomeProvider;
struct StructureStart;
struct ChunkGenerator;
struct TemplateManager;

struct Structure final {
    bool hasSimpleSeparation = true;
    auto(*configFromJson)(const Json& obj) -> tl::optional<StructureConfig> = [](auto...) -> tl::optional<StructureConfig> {
        return NoFeatureConfig{};
    };
    auto(*canGenerate)(ChunkGenerator& generator, BiomeProvider& biomes, int64_t seed, Random& random, int x, int z, Biome& biome, const ChunkPos& pos, const StructureConfig& config) -> bool = [](auto...) -> bool {
        return true;
    };
    void(*generatePieces)(StructurePieces&, StructureGenerateContext& context, const StructureConfig& config) = [](auto...) {};

    auto getChunkPosForStructure(const StructureSeparation& settings, int64_t seed, Random& random, int x, int z) -> ChunkPos;
    auto generate(ChunkGenerator& generator, BiomeProvider& provider, TemplateManager& templateManager, int64_t seed, const ChunkPos& pos, Biome& biome, int refCount, Random& random, const StructureSeparation& settings, const StructureConfig& config) -> StructureStart*;
};