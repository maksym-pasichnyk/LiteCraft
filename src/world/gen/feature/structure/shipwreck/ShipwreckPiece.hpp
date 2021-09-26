#pragma once

#include <world/gen/feature/structure/TemplateStructurePiece.hpp>

struct ShipwreckPiece : TemplateStructurePiece {
    ShipwreckPiece(TemplateManager& templates, std::string location, const BlockPos& pos, Rotation rotation, bool is_beached)
        : TemplateStructurePiece(0, templates, std::move(location), pos)
        , is_beached(is_beached) {}

    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;

private:
    bool is_beached;
};