#pragma once

#include "StructurePiece.hpp"

struct Template;
struct TemplateManager;
struct TemplateStructurePiece : StructurePiece {
    std::string location;
    Template* structure_template;
    BlockPos structure_position;

    TemplateStructurePiece(int componentIndex, TemplateManager& templates, std::string location, const BlockPos& position)
        : StructurePiece(componentIndex, BoundingBox{})
        , location(std::move(location))
        , structure_position(position) {}

};