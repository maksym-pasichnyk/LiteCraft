#include "EmptyJigsawPiece.hpp"

auto EmptyJigsawPiece::to_json() -> Json {
    return {
        {"type", "empty"}
    };
}