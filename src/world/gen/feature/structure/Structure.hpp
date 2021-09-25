#pragma once

#include "StructureFeature.hpp"
#include "config/StructureConfig.hpp"
#include "../../settings/StructureSeparation.hpp"
#include <util/math/ChunkPos.hpp>
#include <util/math/BoundingBox.hpp>

#include <map>
#include <vector>
#include <json/json.hpp>

struct Biome;
struct Random;
struct BoundingBox;
struct BiomeProvider;
struct StructureStart;
struct ChunkGenerator;
struct TemplateManager;

struct Structure {
    auto(*deserialize)(const Json& obj) -> std::optional<StructureConfig>;

    Structure(decltype(deserialize) deserialize) : deserialize(deserialize) {}

    virtual ~Structure() = default;

    virtual auto createStart(int x, int z, const BoundingBox& bounds, int refCount, int64_t seed) -> StructureStart* = 0;
    virtual auto canGenerate(ChunkGenerator& generator, BiomeProvider& biomes, int64_t seed, Random& random, int x, int z, Biome& biome, const ChunkPos& pos, const StructureConfig& config) -> bool {
        return true;
    }
    virtual auto hasSimpleSeparation() const -> bool {
        return true;
    }

    auto generate(ChunkGenerator& generator, BiomeProvider& provider, TemplateManager& templateManager, int64_t seed, const ChunkPos& pos, Biome& biome, int refCount, Random& random, const StructureSeparation& settings, const StructureConfig& config) -> StructureStart*;

    ChunkPos getChunkPosForStructure(const StructureSeparation& settings, int64_t seed, Random& random, int x, int z);
};

template<typename Config = NoFeatureConfig>
struct CfgStructure : Structure {
    CfgStructure() : Structure(deserialize) {}

    static auto deserialize(const Json& obj) -> std::optional<StructureConfig> {
        return Json::Deserialize<std::decay_t<Config>>::from_json(obj);
    }
};