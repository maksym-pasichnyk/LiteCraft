#pragma once

#include <world/gen/feature/structure/StructurePiece.hpp>

struct MineshaftPieces {
    struct Piece;
    struct Room;
    struct Cross;
    struct Stairs;
    struct Corridor;

    static Piece* createRandomShaftPiece(std::span<StructurePiece *> pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex, MineshaftType type);
    static Piece* generateAndAddPiece(Piece* start, std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex);
};