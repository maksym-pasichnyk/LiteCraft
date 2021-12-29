#pragma once

#include <vector>
#include <tl/optional.hpp>
#include <util/Random.hpp>
#include <util/math/BoundingBox.hpp>

struct StructurePiece;
struct StructurePieces {
    std::vector<StructurePiece*> components;

    auto empty() const -> bool {
        return components.empty();
    }

    void emplace(StructurePiece* piece) {
        components.emplace_back(piece);
    }

    auto getBoundingBox() const -> tl::optional<BoundingBox>;
    void markAvailableHeight(int seaLevel, int minY, Random& random, int offset);
    void moveVertically(int y);
};