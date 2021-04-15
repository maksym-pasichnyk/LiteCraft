#include "MineshaftPiece.hpp"
#include "../../../../block/Block.hpp"
#include "../../../../block/Blocks.hpp"

MineshaftPieces::Piece::Piece(int componentIndex, MineshaftType type) : StructurePiece(componentIndex), mineShaftType(type) {
    switch (mineShaftType) {
        case MineshaftType::MESA:
            planks = Blocks::DARK_OAK_PLANKS->getDefaultState();
            fence = Blocks::DARK_OAK_FENCE->getDefaultState();
            break;
        default:
            planks = Blocks::OAK_PLANKS->getDefaultState();
            fence = Blocks::OAK_FENCE->getDefaultState();
            break;
    }
}

bool MineshaftPieces::Piece::isSupportingBox(WorldReader &reader, const BoundingBox &bb, int xmin, int xmax, int y, int z) const {
    for (int x = xmin; x <= xmax; ++x) {
        if (getBlockStateFromPos(reader, x, y + 1, z, bb).isAir()) {
            return false;
        }
    }

    return true;
}
