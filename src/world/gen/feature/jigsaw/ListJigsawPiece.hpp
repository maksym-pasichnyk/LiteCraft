#pragma once

#include "JigsawPiece.hpp"

struct ListJigsawPiece : JigsawPiece {
    std::vector<std::unique_ptr<JigsawPiece>> elements;

    ListJigsawPiece(std::vector<std::unique_ptr<JigsawPiece>> pieces, JigsawProjection projection)
        : JigsawPiece(projection)
        , elements(std::move(pieces)) {}

    auto to_json() -> Json override;
    static auto from_json(const Json& o) -> std::unique_ptr<JigsawPiece>;
};