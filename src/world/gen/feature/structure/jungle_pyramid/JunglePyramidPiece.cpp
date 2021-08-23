#include "JunglePyramidPiece.hpp"
#include <block/Blocks.hpp>
#include <block/VineBlock.hpp>
#include <block/LeverBlock.hpp>
#include <block/StairsBlock.hpp>
#include <block/PistonBlock.hpp>
#include <block/RepeaterBlock.hpp>
#include <block/TripWireBlock.hpp>
#include <block/TripWireHookBlock.hpp>
#include <block/RedstoneWireBlock.hpp>

struct MossyBlockSelector : BlockSelector {
    auto select(Random& random, int x, int y, int z, bool wall) -> BlockData override {
        if (random.nextFloat() < 0.4F) {
            return Blocks::COBBLESTONE->getDefaultState();
        } else {
            return Blocks::MOSSY_COBBLESTONE->getDefaultState();
        }
    }
};

bool JunglePyramidPiece::addComponentParts(WorldGenRegion& region, StructureManager& structureManager, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) {
    if (!isInsideBounds(region, bb, 0)) {
        return false;
    }

    MossyBlockSelector MOSS_STONE_SELECTOR{};
    
    const auto AIR = Blocks::AIR->getDefaultState();
    const auto VINE = Blocks::VINE->getDefaultState();
    const auto LEVER = Blocks::LEVER->getDefaultState();
    const auto REPEATER = Blocks::REPEATER->getDefaultState();
    const auto TRIPWIRE = Blocks::TRIPWIRE->getDefaultState();
    const auto TRIPWIRE_HOOK = Blocks::TRIPWIRE_HOOK->getDefaultState();
    const auto STICKY_PISTON = Blocks::STICKY_PISTON->getDefaultState();
    const auto REDSTONE_WIRE = Blocks::REDSTONE_WIRE->getDefaultState();
    const auto LEVER_NORTH_WALL = LEVER.set<LeverBlock::FACING>(Direction::NORTH).set<LeverBlock::FACE>(AttachFace::WALL);
    const auto MOSSY_COBBLESTONE = Blocks::MOSSY_COBBLESTONE->getDefaultState();
    const auto COBBLESTONE_STAIRS = Blocks::COBBLESTONE_STAIRS->getDefaultState();
    const auto CHISELED_STONE_BRICKS = Blocks::CHISELED_STONE_BRICKS->getDefaultState();
    const auto COBBLESTONE_STAIRS_EAST = COBBLESTONE_STAIRS.set<StairsBlock::FACING>(Direction::EAST);
    const auto COBBLESTONE_STAIRS_WEST = COBBLESTONE_STAIRS.set<StairsBlock::FACING>(Direction::WEST);
    const auto COBBLESTONE_STAIRS_SOUTH = COBBLESTONE_STAIRS.set<StairsBlock::FACING>(Direction::SOUTH);
    const auto COBBLESTONE_STAIRS_NORTH = COBBLESTONE_STAIRS.set<StairsBlock::FACING>(Direction::NORTH);
    const auto REDSTONE_WIRE_NORTH_SOUTH = REDSTONE_WIRE
        .set<RedstoneWireBlock::NORTH>(RedstoneSide::SIDE)
        .set<RedstoneWireBlock::SOUTH>(RedstoneSide::SIDE);
    const auto REDSTONE_WIRE_NORTH_SOUTH_EAST_WEST = REDSTONE_WIRE.set<RedstoneWireBlock::NORTH>(RedstoneSide::SIDE)
        .set<RedstoneWireBlock::SOUTH>(RedstoneSide::SIDE)
        .set<RedstoneWireBlock::EAST>(RedstoneSide::SIDE)
        .set<RedstoneWireBlock::WEST>(RedstoneSide::SIDE);

    fillWithRandomizedBlocks(region, bb, 0, -4, 0, width - 1, 0, depth - 1, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 2, 1, 2, 9, 2, 2, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 2, 1, 12, 9, 2, 12, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 2, 1, 3, 2, 2, 11, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 9, 1, 3, 9, 2, 11, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 1, 3, 1, 10, 6, 1, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 1, 3, 13, 10, 6, 13, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 1, 3, 2, 1, 6, 12, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 10, 3, 2, 10, 6, 12, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 2, 3, 2, 9, 3, 12, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 2, 6, 2, 9, 6, 12, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 3, 7, 3, 8, 7, 11, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 4, 8, 4, 7, 8, 10, false, random, MOSS_STONE_SELECTOR);
    fillWithAir(region, bb, 3, 1, 3, 8, 2, 11);
    fillWithAir(region, bb, 4, 3, 6, 7, 3, 9);
    fillWithAir(region, bb, 2, 4, 2, 9, 5, 12);
    fillWithAir(region, bb, 4, 6, 5, 7, 6, 9);
    fillWithAir(region, bb, 5, 7, 6, 6, 7, 8);
    fillWithAir(region, bb, 5, 1, 2, 6, 2, 2);
    fillWithAir(region, bb, 5, 2, 12, 6, 2, 12);
    fillWithAir(region, bb, 5, 5, 1, 6, 5, 1);
    fillWithAir(region, bb, 5, 5, 13, 6, 5, 13);
    setBlockState(region, AIR, 1, 5, 5, bb);
    setBlockState(region, AIR, 10, 5, 5, bb);
    setBlockState(region, AIR, 1, 5, 9, bb);
    setBlockState(region, AIR, 10, 5, 9, bb);

    for(int i = 0; i <= 14; i += 14) {
        fillWithRandomizedBlocks(region, bb, 2, 4, i, 2, 5, i, false, random, MOSS_STONE_SELECTOR);
        fillWithRandomizedBlocks(region, bb, 4, 4, i, 4, 5, i, false, random, MOSS_STONE_SELECTOR);
        fillWithRandomizedBlocks(region, bb, 7, 4, i, 7, 5, i, false, random, MOSS_STONE_SELECTOR);
        fillWithRandomizedBlocks(region, bb, 9, 4, i, 9, 5, i, false, random, MOSS_STONE_SELECTOR);
    }

    fillWithRandomizedBlocks(region, bb, 5, 6, 0, 6, 6, 0, false, random, MOSS_STONE_SELECTOR);

    for(int l = 0; l <= 11; l += 11) {
        for(int j = 2; j <= 12; j += 2) {
            fillWithRandomizedBlocks(region, bb, l, 4, j, l, 5, j, false, random, MOSS_STONE_SELECTOR);
        }

        fillWithRandomizedBlocks(region, bb, l, 6, 5, l, 6, 5, false, random, MOSS_STONE_SELECTOR);
        fillWithRandomizedBlocks(region, bb, l, 6, 9, l, 6, 9, false, random, MOSS_STONE_SELECTOR);
    }

    fillWithRandomizedBlocks(region, bb, 2, 7, 2, 2, 9, 2, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 9, 7, 2, 9, 9, 2, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 2, 7, 12, 2, 9, 12, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 9, 7, 12, 9, 9, 12, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 4, 9, 4, 4, 9, 4, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 7, 9, 4, 7, 9, 4, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 4, 9, 10, 4, 9, 10, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 7, 9, 10, 7, 9, 10, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 5, 9, 7, 6, 9, 7, false, random, MOSS_STONE_SELECTOR);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 5, 9, 6, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 6, 9, 6, bb);
    setBlockState(region, COBBLESTONE_STAIRS_SOUTH, 5, 9, 8, bb);
    setBlockState(region, COBBLESTONE_STAIRS_SOUTH, 6, 9, 8, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 4, 0, 0, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 5, 0, 0, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 6, 0, 0, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 7, 0, 0, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 4, 1, 8, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 4, 2, 9, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 4, 3, 10, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 7, 1, 8, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 7, 2, 9, bb);
    setBlockState(region, COBBLESTONE_STAIRS_NORTH, 7, 3, 10, bb);
    fillWithRandomizedBlocks(region, bb, 4, 1, 9, 4, 1, 9, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 7, 1, 9, 7, 1, 9, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 4, 1, 10, 7, 2, 10, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 5, 4, 5, 6, 4, 5, false, random, MOSS_STONE_SELECTOR);
    setBlockState(region, COBBLESTONE_STAIRS_EAST, 4, 4, 5, bb);
    setBlockState(region, COBBLESTONE_STAIRS_WEST, 7, 4, 5, bb);

    for(int k = 0; k < 4; ++k) {
        setBlockState(region, COBBLESTONE_STAIRS_SOUTH, 5, 0 - k, 6 + k, bb);
        setBlockState(region, COBBLESTONE_STAIRS_SOUTH, 6, 0 - k, 6 + k, bb);
        fillWithAir(region, bb, 5, 0 - k, 7 + k, 6, 0 - k, 9 + k);
    }

    fillWithAir(region, bb, 1, -3, 12, 10, -1, 13);
    fillWithAir(region, bb, 1, -3, 1, 3, -1, 13);
    fillWithAir(region, bb, 1, -3, 1, 9, -1, 5);

    for(int i1 = 1; i1 <= 13; i1 += 2) {
        fillWithRandomizedBlocks(region, bb, 1, -3, i1, 1, -2, i1, false, random, MOSS_STONE_SELECTOR);
    }

    for(int j1 = 2; j1 <= 12; j1 += 2) {
        fillWithRandomizedBlocks(region, bb, 1, -1, j1, 3, -1, j1, false, random, MOSS_STONE_SELECTOR);
    }

    fillWithRandomizedBlocks(region, bb, 2, -2, 1, 5, -2, 1, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 7, -2, 1, 9, -2, 1, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 6, -3, 1, 6, -3, 1, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 6, -1, 1, 6, -1, 1, false, random, MOSS_STONE_SELECTOR);
    setBlockState(region, TRIPWIRE_HOOK.set<TripWireHookBlock::FACING>(Direction::EAST).set<TripWireHookBlock::ATTACHED>(true), 1, -3, 8, bb);
    setBlockState(region, TRIPWIRE_HOOK.set<TripWireHookBlock::FACING>(Direction::WEST).set<TripWireHookBlock::ATTACHED>(true), 4, -3, 8, bb);
    setBlockState(region, TRIPWIRE.set<TripWireBlock::EAST>(true).set<TripWireBlock::WEST>(true).set<TripWireBlock::ATTACHED>(true), 2, -3, 8, bb);
    setBlockState(region, TRIPWIRE.set<TripWireBlock::EAST>(true).set<TripWireBlock::WEST>(true).set<TripWireBlock::ATTACHED>(true), 3, -3, 8, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 5, -3, 7, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 5, -3, 6, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 5, -3, 5, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 5, -3, 4, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 5, -3, 3, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 5, -3, 2, bb);
    setBlockState(region, REDSTONE_WIRE.set<RedstoneWireBlock::NORTH>(RedstoneSide::SIDE).set<RedstoneWireBlock::WEST>(RedstoneSide::SIDE), 5, -3, 1, bb);
    setBlockState(region, REDSTONE_WIRE.set<RedstoneWireBlock::EAST>(RedstoneSide::SIDE).set<RedstoneWireBlock::WEST>(RedstoneSide::SIDE), 4, -3, 1, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 3, -3, 1, bb);
    if (!placedTrap1) {
//        placedTrap1 = createDispenser(region, bb, random, 3, -2, 1, Direction::NORTH, LootTables::CHESTS_JUNGLE_TEMPLE_DISPENSER);
    }

    setBlockState(region, VINE.set<VineBlock::SOUTH>(true), 3, -2, 2, bb);
    setBlockState(region, TRIPWIRE_HOOK.set<TripWireHookBlock::FACING>(Direction::NORTH).set<TripWireHookBlock::ATTACHED>(true), 7, -3, 1, bb);
    setBlockState(region, TRIPWIRE_HOOK.set<TripWireHookBlock::FACING>(Direction::SOUTH).set<TripWireHookBlock::ATTACHED>(true), 7, -3, 5, bb);
    setBlockState(region, TRIPWIRE.set<TripWireBlock::NORTH>(true).set<TripWireBlock::SOUTH>(true).set<TripWireBlock::ATTACHED>(true), 7, -3, 2, bb);
    setBlockState(region, TRIPWIRE.set<TripWireBlock::NORTH>(true).set<TripWireBlock::SOUTH>(true).set<TripWireBlock::ATTACHED>(true), 7, -3, 3, bb);
    setBlockState(region, TRIPWIRE.set<TripWireBlock::NORTH>(true).set<TripWireBlock::SOUTH>(true).set<TripWireBlock::ATTACHED>(true), 7, -3, 4, bb);
    setBlockState(region, REDSTONE_WIRE.set<RedstoneWireBlock::EAST>(RedstoneSide::SIDE).set<RedstoneWireBlock::WEST>(RedstoneSide::SIDE), 8, -3, 6, bb);
    setBlockState(region, REDSTONE_WIRE.set<RedstoneWireBlock::WEST>(RedstoneSide::SIDE).set<RedstoneWireBlock::SOUTH>(RedstoneSide::SIDE), 9, -3, 6, bb);
    setBlockState(region, REDSTONE_WIRE.set<RedstoneWireBlock::NORTH>(RedstoneSide::SIDE).set<RedstoneWireBlock::SOUTH>(RedstoneSide::UP), 9, -3, 5, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 9, -3, 4, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 9, -2, 4, bb);
    if (!placedTrap2) {
//        placedTrap2 = createDispenser(region, bb, random, 9, -2, 3, Direction.WEST, LootTables::CHESTS_JUNGLE_TEMPLE_DISPENSER);
    }

    setBlockState(region, VINE.set<VineBlock::EAST>(true), 8, -1, 3, bb);
    setBlockState(region, VINE.set<VineBlock::EAST>(true), 8, -2, 3, bb);
    if (!placedMainChest) {
//        placedMainChest = generateChest(region, bb, random, 8, -3, 3, LootTables::CHESTS_JUNGLE_TEMPLE);
    }

    setBlockState(region, MOSSY_COBBLESTONE, 9, -3, 2, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 8, -3, 1, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 4, -3, 5, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 5, -2, 5, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 5, -1, 5, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 6, -3, 5, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 7, -2, 5, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 7, -1, 5, bb);
    setBlockState(region, MOSSY_COBBLESTONE, 8, -3, 5, bb);
    fillWithRandomizedBlocks(region, bb, 9, -1, 1, 9, -1, 5, false, random, MOSS_STONE_SELECTOR);
    fillWithAir(region, bb, 8, -3, 8, 10, -1, 10);
    setBlockState(region, CHISELED_STONE_BRICKS, 8, -2, 11, bb);
    setBlockState(region, CHISELED_STONE_BRICKS, 9, -2, 11, bb);
    setBlockState(region, CHISELED_STONE_BRICKS, 10, -2, 11, bb);
    setBlockState(region, LEVER_NORTH_WALL, 8, -2, 12, bb);
    setBlockState(region, LEVER_NORTH_WALL, 9, -2, 12, bb);
    setBlockState(region, LEVER_NORTH_WALL, 10, -2, 12, bb);
    fillWithRandomizedBlocks(region, bb, 8, -3, 8, 8, -3, 10, false, random, MOSS_STONE_SELECTOR);
    fillWithRandomizedBlocks(region, bb, 10, -3, 8, 10, -3, 10, false, random, MOSS_STONE_SELECTOR);
    setBlockState(region, MOSSY_COBBLESTONE, 10, -2, 9, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 8, -2, 9, bb);
    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH, 8, -2, 10, bb);

    setBlockState(region, REDSTONE_WIRE_NORTH_SOUTH_EAST_WEST, 10, -1, 9, bb);
    setBlockState(region, STICKY_PISTON.set<PistonBlock::FACING>(Direction::UP), 9, -2, 8, bb);
    setBlockState(region, STICKY_PISTON.set<PistonBlock::FACING>(Direction::WEST), 10, -2, 8, bb);
    setBlockState(region, STICKY_PISTON.set<PistonBlock::FACING>(Direction::WEST), 10, -1, 8, bb);
    setBlockState(region, REPEATER.set<RepeaterBlock::FACING>(Direction::NORTH), 10, -2, 10, bb);
    if (!placedHiddenChest) {
//        placedHiddenChest = generateChest(region, bb, random, 9, -3, 10, LootTables::CHESTS_JUNGLE_TEMPLE);
    }

    return true;
}