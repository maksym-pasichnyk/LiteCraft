#include "FeatureJigsawPiece.hpp"
#include <configs.hpp>

auto FeatureJigsawPiece::to_json() -> Json {
	return {
        {"type", "feature"},
        {"projection", projection},
        {"feature", feature}
    };
}
