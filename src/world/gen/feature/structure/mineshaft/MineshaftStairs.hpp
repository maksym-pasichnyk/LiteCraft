#pragma once

#include "MineshaftPiece.hpp"

struct MineshaftPieces::Stairs : Piece {
    Stairs(int componentIndex, const BoundingBox& bounds, Direction direction, MineshaftType type) : Piece(componentIndex, type, bounds) {
        setCoordBaseMode(direction);
    }

    static std::optional<BoundingBox> findStairs(std::span<StructurePiece *> pieces, Random& random, int x, int y, int z, Direction facing);

    void buildComponent(StructurePiece* start, std::vector<StructurePiece*>& pieces, Random& random) override;
    bool addComponentParts(WorldGenRegion &region, TemplateManager& templates, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) override;
};