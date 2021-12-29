#pragma once

#include "MineshaftPiece.hpp"

struct MineshaftPieces::Cross : Piece {
    Direction corridorDirection;
    bool isMultipleFloors;

    Cross(int componentIndex, const BoundingBox& bounds, Direction direction, MineshaftType type)
        : Piece(componentIndex, type, bounds), corridorDirection(direction), isMultipleFloors(bounds.getYSize() > 3) {}

    static tl::optional<BoundingBox> findCrossing(std::span<StructurePiece *> pieces, Random& random, int x, int y, int z, Direction facing);

    void buildComponent(StructurePiece *start, std::vector<StructurePiece *> &pieces, Random &random) override;
    bool addComponentParts(WorldGenRegion &region, TemplateManager& templates, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) override;
    void placeSupportPillar(WorldGenRegion& region, const BoundingBox& bb, int x, int minY, int z, int maxY);
};