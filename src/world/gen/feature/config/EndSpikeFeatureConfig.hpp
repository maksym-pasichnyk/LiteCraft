#pragma once

#include <util/math/BlockPos.hpp>
#include <util/math/ChunkPos.hpp>
#include <util/math/BoundingBox.hpp>

struct AxisAlignedBB {
    double minX;
    double minY;
    double minZ;
    double maxX;
    double maxY;
    double maxZ;
};

struct EndSpike {
    int centerX;
    int centerZ;
    int radius;
    int height;
    bool guarded;

    auto getTopBoundingBox() const -> AxisAlignedBB {
        return {
            static_cast<double>(centerX - radius),
            0.0,
            static_cast<double>(centerZ - radius),
            static_cast<double>(centerX + radius),
            256.0,
            static_cast<double>(centerZ + radius)
        };
    }

    bool doesStartInChunk(const BlockPos& pos) const {
        return ChunkPos::from(pos) == ChunkPos::from(centerX >> 4, centerZ >> 4);
    }
};

struct EndSpikeFeatureConfig {
    bool crystalInvulnerable;
    std::vector<EndSpike> spikes;
    std::optional<BlockPos> crystalBeamTarget;
};