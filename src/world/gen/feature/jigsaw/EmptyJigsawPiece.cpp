#include "EmptyJigsawPiece.hpp"

auto EmptyJigsawPiece::to_json() -> Json {
    return {
        {"type", "empty"}
    };
}
auto EmptyJigsawPiece::from_json(const Json &o) -> std::unique_ptr<JigsawElement> {
    return std::make_unique<EmptyJigsawPiece>();
}
