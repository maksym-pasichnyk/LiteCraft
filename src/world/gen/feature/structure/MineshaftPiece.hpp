#pragma once

#include "MineshaftPieces.hpp"
#include "../../../../block/BlockData.hpp"

struct MineshaftPieces::Piece : StructurePiece {
    MineshaftType mineShaftType;
    BlockData planks;
    BlockData fence;

    Piece(int componentIndex, MineshaftType type);

    BlockData getPlanksBlock() const {
        return planks;
    }

    BlockData getFenceBlock() const {
        return fence;
    }

    bool isSupportingBox(WorldReader& reader, const BoundingBox& bb, int xmin, int xmax, int y, int z) const;
};
