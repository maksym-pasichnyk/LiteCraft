#include "ListJigsawPiece.hpp"
#include <range/v3/all.hpp>

auto ListJigsawPiece::to_json() -> Json {
	return {
        {"type", "list"},
        {"projection", projection},
        {"elements", elements | ranges::views::transform(std::mem_fn(&JigsawElement::to_json)) | ranges::to_vector}
    };
}
auto ListJigsawPiece::from_json(const Json &o) -> std::unique_ptr<JigsawElement> {
    return std::make_unique<ListJigsawPiece>(
        o.at("elements").as_array().value() | ranges::views::transform(&JigsawElement::from_json) | ranges::to_vector,
        o.at("projection")
    );
}
auto ListJigsawPiece::getBoundingBox(TemplateManager &manager, const BlockPos &pos, Rotation rotation) -> BoundingBox {
	auto bounds = BoundingBox::getNewBoundingBox();
	for (auto&& element : elements) {
		bounds.expandTo(element->getBoundingBox(manager, pos, rotation));
	}
	return bounds;
}
