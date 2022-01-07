#pragma once

#include "JigsawElement.hpp"

struct FeatureJigsawPiece : JigsawElement {
    ConfiguredFeature *feature;

    FeatureJigsawPiece(ConfiguredFeature *feature, JigsawProjection projection) : JigsawElement(projection), feature(feature) {}

    auto to_json() -> Json override;
    static auto from_json(const Json& o) -> std::unique_ptr<JigsawElement>;
};