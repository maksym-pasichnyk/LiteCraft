#pragma once

#include "MineshaftPiece.hpp"

struct MineshaftPieces::Stairs : Piece {
    Stairs(int componentIndex, const BoundingBox& bb, Direction direction, MineshaftType type) : Piece(componentIndex, type) {
        setCoordBaseMode(direction);
        bounds = bb;
    }

    static std::optional<BoundingBox> findStairs(std::span<StructurePiece *> pieces, Random& random, int x, int y, int z, Direction facing);

    void buildComponent(StructurePiece* start, std::vector<StructurePiece*>& pieces, Random& random) override;
    bool addComponentParts(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) override;
};