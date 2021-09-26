#pragma once

#include <world/gen/feature/structure/ScatteredStructurePiece.hpp>

struct JunglePyramidPiece : ScatteredStructurePiece {
    bool placedMainChest = false;
    bool placedHiddenChest = false;
    bool placedTrap1 = false;
    bool placedTrap2 = false;
//    private static final JunglePyramidPiece.Selector MOSS_STONE_SELECTOR = new JunglePyramidPiece.Selector();

    JunglePyramidPiece(Random& random, int x, int z)
        : ScatteredStructurePiece(random, x, 64, z, 12, 10, 15, random.nextElement(std::span(DirectionUtil::Plane::HORIZONTAL))) {}

    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;
};