#pragma once

#include "MineshaftPiece.hpp"

struct MineshaftPieces::Corridor : Piece {
    bool hasRails;
    bool hasSpiders;
    bool spawnerPlaced;
    int sectionCount;

    Corridor(int componentIndex, Random& random, const BoundingBox& bounds, Direction facing, MineshaftType type) : Piece(componentIndex, type, bounds) {
        setCoordBaseMode(facing);
        hasRails = random.nextInt(3) == 0;
        hasSpiders = !hasRails && random.nextInt(23) == 0;
        sectionCount = (DirectionUtil::getAxis(facing) == DirectionUtil::Axis::Z ? bounds.getZSize() : bounds.getXSize()) / 5;
    }

    static std::optional<BoundingBox> findCorridor(std::span<StructurePiece*> pieces, Random& random, int x, int y, int z, Direction facing);

    void buildComponent(StructurePiece* start, std::vector<StructurePiece *> &pieces, Random& random) override;
    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;

    void placeSupport(WorldGenRegion& region, const BoundingBox& bb, int xmin, int ymin, int z, int ymax, int xmax, Random& random);
    void placeCobWeb(WorldGenRegion& region, const BoundingBox& bb, Random& random, float chance, int x, int y, int z);
};