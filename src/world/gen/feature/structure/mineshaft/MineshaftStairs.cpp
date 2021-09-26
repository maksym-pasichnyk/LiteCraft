#include "MineshaftStairs.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

std::optional<BoundingBox> MineshaftPieces::Stairs::findStairs(std::span<StructurePiece *> pieces, Random &random, int x, int y, int z, Direction facing) {
    BoundingBox bounds{x, y - 5, z, x, y + 3 - 1, z};
    switch (facing) {
        case Direction::NORTH:
        default:
            bounds.maxX = x + 3 - 1;
            bounds.minZ = z - 8;
            break;
        case Direction::SOUTH:
            bounds.maxX = x + 3 - 1;
            bounds.maxZ = z + 8;
            break;
        case Direction::WEST:
            bounds.minX = x - 8;
            bounds.maxZ = z + 3 - 1;
            break;
        case Direction::EAST:
            bounds.maxX = x + 8;
            bounds.maxZ = z + 3 - 1;
            break;
    }

    if (hasIntersecting(pieces, bounds)) {
        return std::nullopt;
    }
    return bounds;
}

void MineshaftPieces::Stairs::buildComponent(StructurePiece *start, std::vector<StructurePiece *> &pieces, Random &random) {
    const int i = getComponentType();
    if (coordBaseMode.has_value()) {
        auto dyn_start = dynamic_cast<Piece*>(start);

        switch (*coordBaseMode) {
            case Direction::NORTH:
            default:
                generateAndAddPiece(dyn_start, pieces, random, bounds.minX, bounds.minY, bounds.minZ - 1, Direction::NORTH, i);
                break;
            case Direction::SOUTH:
                generateAndAddPiece(dyn_start, pieces, random, bounds.minX, bounds.minY, bounds.maxZ + 1, Direction::SOUTH, i);
                break;
            case Direction::WEST:
                generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY, bounds.minZ, Direction::WEST, i);
                break;
            case Direction::EAST:
                generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY, bounds.minZ, Direction::EAST, i);
                break;
        }
    }
}

bool MineshaftPieces::Stairs::addComponentParts(WorldGenRegion &region, TemplateManager& templates, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) {
    if (isLiquidInStructureBoundingBox(region, bb)) {
        return false;
    }

    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();

    fillWithBlocks(region, bb, 0, 5, 0, 2, 7, 1, CAVE_AIR, CAVE_AIR, false);
    fillWithBlocks(region, bb, 0, 0, 7, 2, 2, 8, CAVE_AIR, CAVE_AIR, false);

    for (int i = 0; i < 5; ++i) {
        fillWithBlocks(region, bb, 0, 5 - i - (i < 4 ? 1 : 0), 2 + i, 2, 7 - i, 2 + i, CAVE_AIR, CAVE_AIR, false);
    }

    return true;
}
