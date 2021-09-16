#pragma once

#include "JigsawPiece.hpp"

struct EmptyJigsawPiece : JigsawPiece {
    EmptyJigsawPiece() : JigsawPiece(JigsawProjection::TERRAIN_MATCHING) {}
};