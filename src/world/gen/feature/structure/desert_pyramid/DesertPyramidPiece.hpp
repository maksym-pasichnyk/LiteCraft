#pragma once

#include <world/gen/feature/structure/ScatteredStructurePiece.hpp>

struct DesertPyramidPiece : ScatteredStructurePiece {
    std::array<bool, 4> hasPlacedChest{};

    DesertPyramidPiece(Random& random, int x, int z)
        : ScatteredStructurePiece(random, x, 64, z, 21, 15, 21, random.nextElement(std::span(DirectionUtil::Plane::HORIZONTAL))) {}

    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;
};