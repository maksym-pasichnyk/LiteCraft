#pragma once

#include "StructurePiece.hpp"
#include "TemplateManager.hpp"

struct Template;
struct TemplateStructurePiece : StructurePiece {
    Template* structure_template;
    BlockPos structure_position;
    PlacementSettings structure_settings;

    TemplateStructurePiece(int componentIndex, const BlockPos& position)
        : StructurePiece(componentIndex, BoundingBox{})
        , structure_position(position) {}
};