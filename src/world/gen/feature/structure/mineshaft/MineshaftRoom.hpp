#pragma once

#include "MineshaftPiece.hpp"

struct MineshaftPieces::Room : Piece {
    std::vector<BoundingBox> connectedRooms{};

    Room(int componentIndex, Random& random, int x, int z, MineshaftType type);

    void buildComponent(StructurePiece* start, std::vector<StructurePiece*>& pieces, Random& random) override;
    bool addComponentParts(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) override;
};
