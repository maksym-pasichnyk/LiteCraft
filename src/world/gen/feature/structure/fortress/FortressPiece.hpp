#pragma once

#include <world/gen/feature/structure/StructurePiece.hpp>

struct FortressPiece : StructurePiece {
    FortressPiece(Random& random, int x, int z) : StructurePiece(0) {}

    bool addComponentParts(WorldGenRegion& region, StructureManager& structureManager, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;
};