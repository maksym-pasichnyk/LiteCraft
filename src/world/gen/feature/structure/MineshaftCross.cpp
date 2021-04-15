#include "MineshaftCross.hpp"
#include "../../../WorldGenRegion.hpp"
#include "../../../../block/Block.hpp"
#include "../../../../block/Blocks.hpp"

std::optional<BoundingBox> MineshaftPieces::Cross::findCrossing(std::span<StructurePiece *> pieces, Random &random, int x, int y, int z, Direction facing) {
    BoundingBox bounds{x, y, z, x, y + 3 - 1, z};
    if (random.nextInt(4) == 0) {
        bounds.maxY += 4;
    }

    switch (facing) {
        case Direction::NORTH:
        default:
            bounds.minX = x - 1;
            bounds.maxX = x + 3;
            bounds.minZ = z - 4;
            break;
        case Direction::SOUTH:
            bounds.minX = x - 1;
            bounds.maxX = x + 3;
            bounds.maxZ = z + 3 + 1;
            break;
        case Direction::WEST:
            bounds.minX = x - 4;
            bounds.minZ = z - 1;
            bounds.maxZ = z + 3;
            break;
        case Direction::EAST:
            bounds.maxX = x + 3 + 1;
            bounds.minZ = z - 1;
            bounds.maxZ = z + 3;
            break;
    }

    if (hasIntersecting(pieces, bounds)) {
        return std::nullopt;
    }
    return bounds;
}

void MineshaftPieces::Cross::buildComponent(StructurePiece *start, std::vector<StructurePiece *> &pieces, Random &random) {
    const int i = getComponentType();
    auto dyn_start = dynamic_cast<Piece*>(start);
    
    switch (corridorDirection) {
        case Direction::NORTH:
        default:
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY, bounds.minZ - 1, Direction::NORTH, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY, bounds.minZ + 1, Direction::WEST, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY, bounds.minZ + 1, Direction::EAST, i);
            break;
        case Direction::SOUTH:
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY, bounds.maxZ + 1, Direction::SOUTH, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY, bounds.minZ + 1, Direction::WEST, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY, bounds.minZ + 1, Direction::EAST, i);
            break;
        case Direction::WEST:
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY, bounds.minZ - 1, Direction::NORTH, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY, bounds.maxZ + 1, Direction::SOUTH, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY, bounds.minZ + 1, Direction::WEST, i);
            break;
        case Direction::EAST:
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY, bounds.minZ - 1, Direction::NORTH, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY, bounds.maxZ + 1, Direction::SOUTH, i);
            generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY, bounds.minZ + 1, Direction::EAST, i);
            break;
    }

    if (isMultipleFloors) {
        if (random.nextBoolean()) {
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY + 3 + 1, bounds.minZ - 1, Direction::NORTH, i);
        }

        if (random.nextBoolean()) {
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY + 3 + 1, bounds.minZ + 1, Direction::WEST, i);
        }

        if (random.nextBoolean()) {
            generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY + 3 + 1, bounds.minZ + 1, Direction::EAST, i);
        }

        if (random.nextBoolean()) {
            generateAndAddPiece(dyn_start, pieces, random, bounds.minX + 1, bounds.minY + 3 + 1, bounds.maxZ + 1, Direction::SOUTH, i);
        }
    }
}

bool MineshaftPieces::Cross::addComponentParts(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) {
    if (isLiquidInStructureBoundingBox(region, bb)) {
        return false;
    }
    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();

    const auto state = getPlanksBlock();
    if (isMultipleFloors) {
        fillWithBlocks(region, bb, bounds.minX + 1, bounds.minY, bounds.minZ, bounds.maxX - 1, bounds.minY + 3 - 1, bounds.maxZ, CAVE_AIR, CAVE_AIR, false);
        fillWithBlocks(region, bb, bounds.minX, bounds.minY, bounds.minZ + 1, bounds.maxX, bounds.minY + 3 - 1, bounds.maxZ - 1, CAVE_AIR, CAVE_AIR, false);
        fillWithBlocks(region, bb, bounds.minX + 1, bounds.maxY - 2, bounds.minZ, bounds.maxX - 1, bounds.maxY, bounds.maxZ, CAVE_AIR, CAVE_AIR, false);
        fillWithBlocks(region, bb, bounds.minX, bounds.maxY - 2, bounds.minZ + 1, bounds.maxX, bounds.maxY, bounds.maxZ - 1, CAVE_AIR, CAVE_AIR, false);
        fillWithBlocks(region, bb, bounds.minX + 1, bounds.minY + 3, bounds.minZ + 1, bounds.maxX - 1, bounds.minY + 3, bounds.maxZ - 1, CAVE_AIR, CAVE_AIR, false);
    } else {
        fillWithBlocks(region, bb, bounds.minX + 1, bounds.minY, bounds.minZ, bounds.maxX - 1, bounds.maxY, bounds.maxZ, CAVE_AIR, CAVE_AIR, false);
        fillWithBlocks(region, bb, bounds.minX, bounds.minY, bounds.minZ + 1, bounds.maxX, bounds.maxY, bounds.maxZ - 1, CAVE_AIR, CAVE_AIR, false);
    }

    placeSupportPillar(region, bb, bounds.minX + 1, bounds.minY, bounds.minZ + 1, bounds.maxY);
    placeSupportPillar(region, bb, bounds.minX + 1, bounds.minY, bounds.maxZ - 1, bounds.maxY);
    placeSupportPillar(region, bb, bounds.maxX - 1, bounds.minY, bounds.minZ + 1, bounds.maxY);
    placeSupportPillar(region, bb, bounds.maxX - 1, bounds.minY, bounds.maxZ - 1, bounds.maxY);

    for (int i = bounds.minX; i <= bounds.maxX; ++i) {
        for (int j = bounds.minZ; j <= bounds.maxZ; ++j) {
            if (getBlockStateFromPos(region, i, bounds.minY - 1, j, bb).isAir() && isUnderOceanFloor(region, i, bounds.minY - 1, j, bb)) {
                setBlockState(region, state, i, bounds.minY - 1, j, bb);
            }
        }
    }

    return true;
}

void MineshaftPieces::Cross::placeSupportPillar(WorldGenRegion &region, const BoundingBox &bb, int x, int minY, int z, int maxY) {
    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();

    if (!getBlockStateFromPos(region, x, maxY + 1, z, bb).isAir()) {
        fillWithBlocks(region, bb, x, minY, z, x, maxY, z, getPlanksBlock(), CAVE_AIR, false);
    }
}
