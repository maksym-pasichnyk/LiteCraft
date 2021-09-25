#pragma once

#include "JigsawPiece.hpp"

struct EmptyJigsawPiece : JigsawPiece {
    EmptyJigsawPiece() : JigsawPiece(JigsawProjection::TERRAIN_MATCHING) {}

    auto to_json() -> Json override;
    static auto from_json(const Json& o) -> std::unique_ptr<JigsawPiece>;
};