#pragma once

#include "JigsawPiece.hpp"

struct FeatureJigsawPiece : JigsawPiece {
    FeatureJigsawPiece(ConfiguredFeature *feature, JigsawProjection projection) : JigsawPiece(projection) {}
};