#include "FeatureJigsawPiece.hpp"

auto FeatureJigsawPiece::to_json() -> Json {
	return {
        {"type", "feature"},
        {"projection", projection},
        {"feature", feature}
    };
}
auto FeatureJigsawPiece::from_json(const Json &o) -> std::unique_ptr<JigsawPiece> {
    return std::make_unique<FeatureJigsawPiece>(o.at("feature"), o.at("projection"));
}
