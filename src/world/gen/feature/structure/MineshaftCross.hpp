#pragma once

#include "MineshaftPiece.hpp"

struct MineshaftPieces::Cross : Piece {
    Direction corridorDirection;
    bool isMultipleFloors;

    Cross(int componentIndex, const BoundingBox& bb, Direction direction, MineshaftType type)
        : Piece(componentIndex, type)
        , corridorDirection(direction)
        , isMultipleFloors(bb.getYSize() > 3) {
        bounds = bb;
    }

    static std::optional<BoundingBox> findCrossing(std::span<StructurePiece *> pieces, Random& random, int x, int y, int z, Direction facing);

    void buildComponent(StructurePiece *start, std::vector<StructurePiece *> &pieces, Random &random) override;
    bool addComponentParts(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) override;
    void placeSupportPillar(WorldGenRegion& region, const BoundingBox& bb, int x, int minY, int z, int maxY);
};