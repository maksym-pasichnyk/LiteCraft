#include "ListJigsawPiece.hpp"
#include <range/v3/all.hpp>
#include <configs.hpp>

auto ListJigsawPiece::to_json() -> Json {
	return {
        {"type", "list"},
        {"projection", projection},
        {"elements", elements | ranges::views::transform(std::mem_fn(&JigsawPiece::to_json)) | ranges::to_vector}
    };
}
