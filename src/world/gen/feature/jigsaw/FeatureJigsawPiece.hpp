#pragma once

#include "JigsawPiece.hpp"

struct FeatureJigsawPiece : JigsawPiece {
    ConfiguredFeature *feature;

    FeatureJigsawPiece(ConfiguredFeature *feature, JigsawProjection projection) : JigsawPiece(projection), feature(feature) {}

    auto to_json() -> Json override;
    static auto from_json(const Json& o) -> std::unique_ptr<JigsawPiece>;
};