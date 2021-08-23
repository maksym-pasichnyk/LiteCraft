#include "DesertPyramidPiece.hpp"
#include <block/Blocks.hpp>
#include <block/StairsBlock.hpp>

bool DesertPyramidPiece::addComponentParts(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) {
    const auto AIR = Blocks::AIR->getDefaultState();
    const auto TNT = Blocks::TNT->getDefaultState();
    const auto SANDSTONE = Blocks::SANDSTONE->getDefaultState();
    const auto CUT_SANDSTONE = Blocks::CUT_SANDSTONE->getDefaultState();
    const auto SANDSTONE_SLAB = Blocks::SANDSTONE_SLAB->getDefaultState();
    const auto BLUE_TERRACOTTA = Blocks::BLUE_TERRACOTTA->getDefaultState();
    const auto SANDSTONE_STAIRS = Blocks::SANDSTONE_STAIRS->getDefaultState();
    const auto ORANGE_TERRACOTTA = Blocks::ORANGE_TERRACOTTA->getDefaultState();
    const auto CHISELED_SANDSTONE = Blocks::CHISELED_SANDSTONE->getDefaultState();
    const auto STONE_PRESSURE_PLATE = Blocks::STONE_PRESSURE_PLATE->getDefaultState();
    const auto SANDSTONE_STAIRS_NORTH = SANDSTONE_STAIRS.set<StairsBlock::FACING>(Direction::NORTH);
    const auto SANDSTONE_STAIRS_SOUTH = SANDSTONE_STAIRS.set<StairsBlock::FACING>(Direction::SOUTH);
    const auto SANDSTONE_STAIRS_EAST = SANDSTONE_STAIRS.set<StairsBlock::FACING>(Direction::EAST);
    const auto SANDSTONE_STAIRS_WEST = SANDSTONE_STAIRS.set<StairsBlock::FACING>(Direction::WEST);

    fillWithBlocks(region, bb, 0, -4, 0, width - 1, 0, depth - 1, SANDSTONE, SANDSTONE, false);

    for (int i = 1; i <= 9; ++i) {
        fillWithBlocks(region, bb, i, i, i, width - 1 - i, i, depth - 1 - i, SANDSTONE, SANDSTONE, false);
        fillWithBlocks(region, bb, i + 1, i, i + 1, width - 2 - i, i, depth - 2 - i, AIR, AIR, false);
    }

    for (int k1 = 0; k1 < width; ++k1) {
        for (int j = 0; j < depth; ++j) {
            int k = -5;
            replaceAirAndLiquidDownwards(region, SANDSTONE, k1, -5, j, bb);
        }
    }

    fillWithBlocks(region, bb, 0, 0, 0, 4, 9, 4, SANDSTONE, AIR, false);
    fillWithBlocks(region, bb, 1, 10, 1, 3, 10, 3, SANDSTONE, SANDSTONE, false);
    setBlockState(region, SANDSTONE_STAIRS_NORTH, 2, 10, 0, bb);
    setBlockState(region, SANDSTONE_STAIRS_SOUTH, 2, 10, 4, bb);
    setBlockState(region, SANDSTONE_STAIRS_EAST, 0, 10, 2, bb);
    setBlockState(region, SANDSTONE_STAIRS_WEST, 4, 10, 2, bb);
    fillWithBlocks(region, bb, width - 5, 0, 0, width - 1, 9, 4, SANDSTONE, AIR, false);
    fillWithBlocks(region, bb, width - 4, 10, 1, width - 2, 10, 3, SANDSTONE, SANDSTONE, false);
    setBlockState(region, SANDSTONE_STAIRS_NORTH, width - 3, 10, 0, bb);
    setBlockState(region, SANDSTONE_STAIRS_SOUTH, width - 3, 10, 4, bb);
    setBlockState(region, SANDSTONE_STAIRS_EAST, width - 5, 10, 2, bb);
    setBlockState(region, SANDSTONE_STAIRS_WEST, width - 1, 10, 2, bb);
    fillWithBlocks(region, bb, 8, 0, 0, 12, 4, 4, SANDSTONE, AIR, false);
    fillWithBlocks(region, bb, 9, 1, 0, 11, 3, 4, AIR, AIR, false);
    setBlockState(region, CUT_SANDSTONE, 9, 1, 1, bb);
    setBlockState(region, CUT_SANDSTONE, 9, 2, 1, bb);
    setBlockState(region, CUT_SANDSTONE, 9, 3, 1, bb);
    setBlockState(region, CUT_SANDSTONE, 10, 3, 1, bb);
    setBlockState(region, CUT_SANDSTONE, 11, 3, 1, bb);
    setBlockState(region, CUT_SANDSTONE, 11, 2, 1, bb);
    setBlockState(region, CUT_SANDSTONE, 11, 1, 1, bb);
    fillWithBlocks(region, bb, 4, 1, 1, 8, 3, 3, SANDSTONE, AIR, false);
    fillWithBlocks(region, bb, 4, 1, 2, 8, 2, 2, AIR, AIR, false);
    fillWithBlocks(region, bb, 12, 1, 1, 16, 3, 3, SANDSTONE, AIR, false);
    fillWithBlocks(region, bb, 12, 1, 2, 16, 2, 2, AIR, AIR, false);
    fillWithBlocks(region, bb, 5, 4, 5, width - 6, 4, depth - 6, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, 9, 4, 9, 11, 4, 11, AIR, AIR, false);
    fillWithBlocks(region, bb, 8, 1, 8, 8, 3, 8, CUT_SANDSTONE, CUT_SANDSTONE, false);
    fillWithBlocks(region, bb, 12, 1, 8, 12, 3, 8, CUT_SANDSTONE, CUT_SANDSTONE, false);
    fillWithBlocks(region, bb, 8, 1, 12, 8, 3, 12, CUT_SANDSTONE, CUT_SANDSTONE, false);
    fillWithBlocks(region, bb, 12, 1, 12, 12, 3, 12, CUT_SANDSTONE, CUT_SANDSTONE, false);
    fillWithBlocks(region, bb, 1, 1, 5, 4, 4, 11, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, width - 5, 1, 5, width - 2, 4, 11, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, 6, 7, 9, 6, 7, 11, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, width - 7, 7, 9, width - 7, 7, 11, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, 5, 5, 9, 5, 7, 11, CUT_SANDSTONE, CUT_SANDSTONE, false);
    fillWithBlocks(region, bb, width - 6, 5, 9, width - 6, 7, 11, CUT_SANDSTONE, CUT_SANDSTONE, false);
    setBlockState(region, AIR, 5, 5, 10, bb);
    setBlockState(region, AIR, 5, 6, 10, bb);
    setBlockState(region, AIR, 6, 6, 10, bb);
    setBlockState(region, AIR, width - 6, 5, 10, bb);
    setBlockState(region, AIR, width - 6, 6, 10, bb);
    setBlockState(region, AIR, width - 7, 6, 10, bb);
    fillWithBlocks(region, bb, 2, 4, 4, 2, 6, 4, AIR, AIR, false);
    fillWithBlocks(region, bb, width - 3, 4, 4, width - 3, 6, 4, AIR, AIR, false);
    setBlockState(region, SANDSTONE_STAIRS_NORTH, 2, 4, 5, bb);
    setBlockState(region, SANDSTONE_STAIRS_NORTH, 2, 3, 4, bb);
    setBlockState(region, SANDSTONE_STAIRS_NORTH, width - 3, 4, 5, bb);
    setBlockState(region, SANDSTONE_STAIRS_NORTH, width - 3, 3, 4, bb);
    fillWithBlocks(region, bb, 1, 1, 3, 2, 2, 3, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, width - 3, 1, 3, width - 2, 2, 3, SANDSTONE, SANDSTONE, false);
    setBlockState(region, SANDSTONE, 1, 1, 2, bb);
    setBlockState(region, SANDSTONE, width - 2, 1, 2, bb);
    setBlockState(region, SANDSTONE_SLAB, 1, 2, 2, bb);
    setBlockState(region, SANDSTONE_SLAB, width - 2, 2, 2, bb);
    setBlockState(region, SANDSTONE_STAIRS_WEST, 2, 1, 2, bb);
    setBlockState(region, SANDSTONE_STAIRS_EAST, width - 3, 1, 2, bb);
    fillWithBlocks(region, bb, 4, 3, 5, 4, 3, 17, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, width - 5, 3, 5, width - 5, 3, 17, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, 3, 1, 5, 4, 2, 16, AIR, AIR, false);
    fillWithBlocks(region, bb, width - 6, 1, 5, width - 5, 2, 16, AIR, AIR, false);

    for (int l = 5; l <= 17; l += 2) {
        setBlockState(region, CUT_SANDSTONE, 4, 1, l, bb);
        setBlockState(region, CHISELED_SANDSTONE, 4, 2, l, bb);
        setBlockState(region, CUT_SANDSTONE, width - 5, 1, l, bb);
        setBlockState(region, CHISELED_SANDSTONE, width - 5, 2, l, bb);
    }

    setBlockState(region, ORANGE_TERRACOTTA, 10, 0, 7, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 10, 0, 8, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 9, 0, 9, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 11, 0, 9, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 8, 0, 10, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 12, 0, 10, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 7, 0, 10, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 13, 0, 10, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 9, 0, 11, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 11, 0, 11, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 10, 0, 12, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 10, 0, 13, bb);
    setBlockState(region, BLUE_TERRACOTTA, 10, 0, 10, bb);

    for (int l1 = 0; l1 <= width - 1; l1 += width - 1) {
        setBlockState(region, CUT_SANDSTONE, l1, 2, 1, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 2, 2, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 2, 3, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 3, 1, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 3, 2, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 3, 3, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 4, 1, bb);
        setBlockState(region, CHISELED_SANDSTONE, l1, 4, 2, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 4, 3, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 5, 1, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 5, 2, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 5, 3, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 6, 1, bb);
        setBlockState(region, CHISELED_SANDSTONE, l1, 6, 2, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 6, 3, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 7, 1, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 7, 2, bb);
        setBlockState(region, ORANGE_TERRACOTTA, l1, 7, 3, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 8, 1, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 8, 2, bb);
        setBlockState(region, CUT_SANDSTONE, l1, 8, 3, bb);
    }

    for (int i2 = 2; i2 <= width - 3; i2 += width - 3 - 2) {
        setBlockState(region, CUT_SANDSTONE, i2 - 1, 2, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2, 2, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2 + 1, 2, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2 - 1, 3, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2, 3, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2 + 1, 3, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2 - 1, 4, 0, bb);
        setBlockState(region, CHISELED_SANDSTONE, i2, 4, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2 + 1, 4, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2 - 1, 5, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2, 5, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2 + 1, 5, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2 - 1, 6, 0, bb);
        setBlockState(region, CHISELED_SANDSTONE, i2, 6, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2 + 1, 6, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2 - 1, 7, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2, 7, 0, bb);
        setBlockState(region, ORANGE_TERRACOTTA, i2 + 1, 7, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2 - 1, 8, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2, 8, 0, bb);
        setBlockState(region, CUT_SANDSTONE, i2 + 1, 8, 0, bb);
    }

    fillWithBlocks(region, bb, 8, 4, 0, 12, 6, 0, CUT_SANDSTONE, CUT_SANDSTONE, false);
    setBlockState(region, AIR, 8, 6, 0, bb);
    setBlockState(region, AIR, 12, 6, 0, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 9, 5, 0, bb);
    setBlockState(region, CHISELED_SANDSTONE, 10, 5, 0, bb);
    setBlockState(region, ORANGE_TERRACOTTA, 11, 5, 0, bb);
    fillWithBlocks(region, bb, 8, -14, 8, 12, -11, 12, CUT_SANDSTONE, CUT_SANDSTONE, false);
    fillWithBlocks(region, bb, 8, -10, 8, 12, -10, 12, CHISELED_SANDSTONE, CHISELED_SANDSTONE, false);
    fillWithBlocks(region, bb, 8, -9, 8, 12, -9, 12, CUT_SANDSTONE, CUT_SANDSTONE, false);
    fillWithBlocks(region, bb, 8, -8, 8, 12, -1, 12, SANDSTONE, SANDSTONE, false);
    fillWithBlocks(region, bb, 9, -11, 9, 11, -1, 11, AIR, AIR, false);
    setBlockState(region, STONE_PRESSURE_PLATE, 10, -11, 10, bb);
    fillWithBlocks(region, bb, 9, -13, 9, 11, -13, 11, TNT, AIR, false);
    setBlockState(region, AIR, 8, -11, 10, bb);
    setBlockState(region, AIR, 8, -10, 10, bb);
    setBlockState(region, CHISELED_SANDSTONE, 7, -10, 10, bb);
    setBlockState(region, CUT_SANDSTONE, 7, -11, 10, bb);
    setBlockState(region, AIR, 12, -11, 10, bb);
    setBlockState(region, AIR, 12, -10, 10, bb);
    setBlockState(region, CHISELED_SANDSTONE, 13, -10, 10, bb);
    setBlockState(region, CUT_SANDSTONE, 13, -11, 10, bb);
    setBlockState(region, AIR, 10, -11, 8, bb);
    setBlockState(region, AIR, 10, -10, 8, bb);
    setBlockState(region, CHISELED_SANDSTONE, 10, -10, 7, bb);
    setBlockState(region, CUT_SANDSTONE, 10, -11, 7, bb);
    setBlockState(region, AIR, 10, -11, 12, bb);
    setBlockState(region, AIR, 10, -10, 12, bb);
    setBlockState(region, CHISELED_SANDSTONE, 10, -10, 13, bb);
    setBlockState(region, CUT_SANDSTONE, 10, -11, 13, bb);

    for (const auto direction : DirectionUtil::Plane::HORIZONTAL) {
        if (!hasPlacedChest[static_cast<size_t>(direction)]) {
            const auto dx = DirectionUtil::getXOffset(direction) * 2;
            const auto dz = DirectionUtil::getZOffset(direction) * 2;
//            hasPlacedChest[static_cast<size_t>(direction)] = generateChest(region, bb, random, 10 + dx, -11, 10 + dz, LootTables::CHESTS_DESERT_PYRAMID);
        }
    }

    return true;
}