#pragma once

#include <world/gen/feature/structure/TemplateManager.hpp>
#include <world/gen/feature/structure/TemplateStructurePiece.hpp>

struct ShipwreckPiece : TemplateStructurePiece {
    ShipwreckPiece(TemplateManager& templates, std::string location, const BlockPos& pos, Rotation rotation, bool is_beached)
    : TemplateStructurePiece(0, pos)
    , location(std::move(location))
    , is_beached(is_beached) {
        _setup(templates);
    }

    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;

private:
    void _setup(TemplateManager& templates) {
        structure_settings = PlacementSettings{
            .pivot = BlockPos::from(4, 0, 15),
            .rotation = rotation,
        };
        structure_template = templates.get(location);
        bounds = structure_template->getBoundingBox(structure_settings, structure_position);
    }

    std::string location;
    bool is_beached;
};