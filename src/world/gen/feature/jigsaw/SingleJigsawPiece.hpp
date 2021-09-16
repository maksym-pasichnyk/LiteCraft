#pragma once

#include "JigsawPiece.hpp"

struct SingleJigsawPiece : JigsawPiece {
    std::string location;
    StructureProcessorList* processors;

    SingleJigsawPiece(std::string location, StructureProcessorList* processors, JigsawProjection projection)
        : JigsawPiece(projection)
        , location(std::move(location))
        , processors(processors) {}
};