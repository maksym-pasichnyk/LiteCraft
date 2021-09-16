#pragma once

#include "JigsawPiece.hpp"

struct ListJigsawPiece : JigsawPiece {
    std::vector<JigsawPiece*> pieces;

    ListJigsawPiece(std::vector<JigsawPiece*> pieces, JigsawProjection projection)
        : JigsawPiece(projection)
        , pieces(std::move(pieces)) {}
};