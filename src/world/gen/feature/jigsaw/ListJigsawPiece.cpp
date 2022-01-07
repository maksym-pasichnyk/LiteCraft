#include "ListJigsawPiece.hpp"
#include <range/v3/all.hpp>

auto ListJigsawPiece::to_json() -> Json {
	return {
        {"type", "list"},
        {"projection", projection},
        {"elements", cpp_iter(elements).map(std::mem_fn(&JigsawElement::to_json)).collect()}
    };
}
auto ListJigsawPiece::from_json(const Json &o) -> std::unique_ptr<JigsawElement> {
    return std::make_unique<ListJigsawPiece>(
        cpp_iter(o.at("elements").as_array().value()).map(&JigsawElement::from_json).collect(),
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
