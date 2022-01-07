#pragma once

#include "JigsawElement.hpp"

struct EmptyJigsawPiece : JigsawElement {
    EmptyJigsawPiece() : JigsawElement(JigsawProjection::TERRAIN_MATCHING) {}

    auto to_json() -> Json override;
    static auto from_json(const Json& o) -> std::unique_ptr<JigsawElement>;
};