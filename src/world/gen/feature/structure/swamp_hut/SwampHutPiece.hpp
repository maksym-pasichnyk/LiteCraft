#pragma once

#include <world/gen/feature/structure/ScatteredStructurePiece.hpp>

struct SwampHutPiece : ScatteredStructurePiece {
    bool witch = false;
    bool cat = false;

    SwampHutPiece(Random& random, int x, int z)
        : ScatteredStructurePiece(random, x, 64, z, 7, 7, 9, random.nextElement(std::span(DirectionUtil::Plane::HORIZONTAL))) {}

    bool addComponentParts(WorldGenRegion& region, StructureManager& structureManager, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;

    void spawnWitch(WorldGenRegion& region, const BoundingBox& bb);
    void spawnCat(WorldGenRegion& region, const BoundingBox& bb);
};