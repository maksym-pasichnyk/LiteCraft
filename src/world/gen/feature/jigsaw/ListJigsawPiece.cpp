#include "ListJigsawPiece.hpp"
#include <range/v3/all.hpp>

auto ListJigsawPiece::to_json() -> Json {
	return {
        {"type", "list"},
        {"projection", projection},
        {"elements", elements | ranges::views::transform(std::mem_fn(&JigsawPiece::to_json)) | ranges::to_vector}
    };
}
auto ListJigsawPiece::from_json(const Json &o) -> std::unique_ptr<JigsawPiece> {
    return std::make_unique<ListJigsawPiece>(
        o.at("elements").as_array().value() | ranges::views::transform(&JigsawPiece::from_json) | ranges::to_vector,
        o.at("projection")
    );
}
