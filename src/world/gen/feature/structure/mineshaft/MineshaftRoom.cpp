#include "MineshaftRoom.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

static auto makeBounds(Random &random, int x, int z) -> BoundingBox {
    const auto dx = random.nextInt(6);
    const auto dy = random.nextInt(6);
    const auto dz = random.nextInt(6);
    return BoundingBox{x, 50, z, x + 7 + dx, 54 + dy, z + 7 + dz};
}

MineshaftPieces::Room::Room(int componentIndex, Random &random, int x, int z, MineshaftType type) : Piece(componentIndex, type, ::makeBounds(random, x, z)) {}

void MineshaftPieces::Room::buildComponent(StructurePiece *start, std::vector<StructurePiece*> &pieces, Random &random) {
    const int i = getComponentType();
    int j = bounds.getYSize() - 3 - 1;
    if (j <= 0) {
        j = 1;
    }

    auto dyn_start = dynamic_cast<Piece*>(start);

    for (int k = 0; k < bounds.getXSize(); k = k + 4) {
        k = k + random.nextInt(bounds.getXSize());
        if (k + 3 > bounds.getXSize()) {
            break;
        }

        if (auto piece = generateAndAddPiece(dyn_start, pieces, random, bounds.minX + k, bounds.minY + random.nextInt(j) + 1, bounds.minZ - 1, Direction::NORTH, i)) {
            const auto bb = piece->getBoundingBox();
            connectedRooms.emplace_back(BoundingBox{bb.minX, bb.minY, bounds.minZ, bb.maxX, bb.maxY, bounds.minZ + 1});
        }
    }

    for (int k = 0; k < bounds.getXSize(); k = k + 4) {
        k = k + random.nextInt(bounds.getXSize());
        if (k + 3 > bounds.getXSize()) {
            break;
        }

        if (auto piece = generateAndAddPiece(dyn_start, pieces, random, bounds.minX + k, bounds.minY + random.nextInt(j) + 1, bounds.maxZ + 1, Direction::SOUTH, i)) {
            const auto bb = piece->getBoundingBox();
            connectedRooms.emplace_back(BoundingBox{bb.minX, bb.minY, bounds.maxZ - 1, bb.maxX, bb.maxY, bounds.maxZ});
        }
    }

    for (int k = 0; k < bounds.getZSize(); k = k + 4) {
        k = k + random.nextInt(bounds.getZSize());
        if (k + 3 > bounds.getZSize()) {
            break;
        }

        if (auto piece = generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY + random.nextInt(j) + 1, bounds.minZ + k, Direction::WEST, i)) {
            const auto bb = piece->getBoundingBox();
            connectedRooms.emplace_back(BoundingBox{bounds.minX, bb.minY, bb.minZ, bounds.minX + 1, bb.maxY, bb.maxZ});
        }
    }

    for (int k = 0; k < bounds.getZSize(); k = k + 4) {
        k = k + random.nextInt(bounds.getZSize());
        if (k + 3 > bounds.getZSize()) {
            break;
        }

        if (auto piece = generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY + random.nextInt(j) + 1, bounds.minZ + k, Direction::EAST, i)) {
            const auto bb = piece->getBoundingBox();
            connectedRooms.emplace_back(BoundingBox{bounds.maxX - 1, bb.minY, bb.minZ, bounds.maxX, bb.maxY, bb.maxZ});
        }
    }
}

bool MineshaftPieces::Room::addComponentParts(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) {
    if (isLiquidInStructureBoundingBox(region, bb)) {
        return false;
    }

    const auto DIRT = Blocks::DIRT->getDefaultState();
    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();

    fillWithBlocks(region, bb, bounds.minX, bounds.minY, bounds.minZ, bounds.maxX, bounds.minY, bounds.maxZ, DIRT, CAVE_AIR, true);
    fillWithBlocks(region, bb, bounds.minX, bounds.minY + 1, bounds.minZ, bounds.maxX, std::min(bounds.minY + 3, bounds.maxY), bounds.maxZ, CAVE_AIR, CAVE_AIR, false);

    for (const auto& room_bb : connectedRooms) {
        fillWithBlocks(region, bb, room_bb.minX, room_bb.maxY - 2, room_bb.minZ, room_bb.maxX, room_bb.maxY, room_bb.maxZ, CAVE_AIR, CAVE_AIR, false);
    }

    randomlyRareFillWithBlocks(region, bb, bounds.minX, bounds.minY + 4, bounds.minZ, bounds.maxX, bounds.maxY, bounds.maxZ, CAVE_AIR, false);
    return true;
}
