#include "StructurePieces.hpp"
#include "StructurePiece.hpp"

auto StructurePieces::getBoundingBox() const -> std::optional<BoundingBox> {
    if (components.empty()) {
        return std::nullopt;
    }

    auto bounds = BoundingBox::getNewBoundingBox();
    for (auto& piece : components) {
        bounds.expandTo(piece->getBoundingBox());
    }
    return bounds;
}

void StructurePieces::markAvailableHeight(int seaLevel, int minY, Random &random, int offset) {
    const auto bounds = getBoundingBox().value();
    const auto lowest_y = seaLevel - offset;
    auto upper_y = bounds.getYSize() + minY + 1;
    if (upper_y < lowest_y) {
        upper_y += random.nextInt(lowest_y - upper_y);
    }
    moveVertically(upper_y - bounds.maxY);
}

void StructurePieces::moveVertically(int y) {
    for (auto piece : components) {
        piece->offset(0, y, 0);
    }
}
