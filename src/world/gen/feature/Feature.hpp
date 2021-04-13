#pragma once

#include "ConfiguredFeature.hpp"

#include <glm/vec3.hpp>

struct Block;
struct Random;
struct WorldReader;
struct WorldWriter;
struct WorldGenRegion;
struct ChunkGenerator;

struct Feature {
    virtual ~Feature() = default;
    virtual bool generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) = 0;

    auto withConfiguration(FeatureConfig config) -> ConfiguredFeature* {
        return new ConfiguredFeature {
            .feature = this,
            .config = std::move(config)
        };
    }

    static bool isStone(Block* block);
    static bool isDirt(Block* block);
    static bool isDirtAt(WorldReader& reader, const BlockPos& pos);
    static bool isAirAt(WorldReader& reader, const BlockPos& pos);
    static void setBlockState(WorldWriter& world, const BlockPos& pos, BlockData state);
};