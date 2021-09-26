#pragma once

#include <world/gen/feature/structure/StructurePiece.hpp>

struct BuriedTreasurePiece : StructurePiece {
    explicit BuriedTreasurePiece(const BlockPos& pos) : StructurePiece(0, BoundingBox::from(pos)) {}

    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;
};