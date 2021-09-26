#pragma once

#include "MineshaftPieces.hpp"
#include <block/BlockData.hpp>

struct MineshaftPieces::Piece : StructurePiece {
    MineshaftType mineShaftType;
    BlockData planks;
    BlockData fence;

    Piece(int componentIndex, MineshaftType type, const BoundingBox& bounds);

    auto getPlanksBlock() const -> BlockData {
        return planks;
    }

    auto getFenceBlock() const -> BlockData {
        return fence;
    }

    bool isSupportingBox(WorldReader& reader, const BoundingBox& bb, int xmin, int xmax, int y, int z) const;
};
