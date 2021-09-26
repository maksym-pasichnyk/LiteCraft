#include "MineshaftPieces.hpp"
#include "MineshaftCross.hpp"
#include "MineshaftStairs.hpp"
#include "MineshaftCorridor.hpp"

MineshaftPieces::Piece* MineshaftPieces::createRandomShaftPiece(std::span<StructurePiece *> pieces, Random &random, int x, int y, int z, Direction facing, int componentIndex, MineshaftType type) {
    const auto i = random.nextInt(100);
    if (i >= 80) {
        if (const auto bb = Cross::findCrossing(pieces, random, x, y, z, facing)) {
            return new Cross(componentIndex, *bb, facing, type);
        }
    } else if (i >= 70) {
        if (const auto bb = Stairs::findStairs(pieces, random, x, y, z, facing)) {
            return new Stairs(componentIndex, *bb, facing, type);
        }
    } else {
        if (const auto bb = Corridor::findCorridor(pieces, random, x, y, z, facing)) {
            return new Corridor(componentIndex, random, *bb, facing, type);
        }
    }
    return nullptr;
}

MineshaftPieces::Piece* MineshaftPieces::generateAndAddPiece(Piece *start, std::vector<StructurePiece *> &pieces, Random &random, int x, int y, int z, Direction facing, int componentIndex) {
    if (componentIndex > 8) {
        return nullptr;
    }

    const auto bounds = start->getBoundingBox();
    if (std::abs(x - bounds.minX) <= 80 && std::abs(z - bounds.minZ) <= 80) {
        if (auto piece = createRandomShaftPiece(pieces, random, x, y, z, facing, componentIndex + 1, start->mineShaftType)) {
            pieces.emplace_back(piece);
            piece->buildComponent(start, pieces, random);
            return piece;
        }
    }
    return nullptr;
}