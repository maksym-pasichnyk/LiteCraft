#pragma once

#include "Feature.hpp"
#include <util/math/ChunkPos.hpp>

struct VoidStartPlatformFeature : Feature {
    static constexpr auto VOID_SPAWN_POS = BlockPos::from(8, 3, 8);
    static constexpr auto VOID_SPAWN_CHUNK_POS = ChunkPos::from(VOID_SPAWN_POS);

    bool generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) override;
};