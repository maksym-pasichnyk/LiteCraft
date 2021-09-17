#pragma once

#include "JigsawPiece.hpp"

struct ListJigsawPiece : JigsawPiece {
    std::vector<JigsawPiece*> elements;

    ListJigsawPiece(std::vector<JigsawPiece*> pieces, JigsawProjection projection)
        : JigsawPiece(projection)
        , elements(std::move(pieces)) {}

    auto to_json() -> Json override;
};