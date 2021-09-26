#include "SwampHutPiece.hpp"
#include <block/Blocks.hpp>
#include <block/StairsBlock.hpp>

bool SwampHutPiece::addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) {
    if (!isInsideBounds(region, bb, 0)) {
        return false;
    }
    
    const auto AIR = Blocks::AIR->getDefaultState();
    const auto OAK_LOG = Blocks::OAK_LOG->getDefaultState();
    const auto CAULDRON = Blocks::CAULDRON->getDefaultState();
    const auto OAK_FENCE = Blocks::OAK_FENCE->getDefaultState();
    const auto SPRUCE_STAIRS = Blocks::SPRUCE_STAIRS->getDefaultState();
    const auto SPRUCE_PLANKS = Blocks::SPRUCE_PLANKS->getDefaultState();
    const auto CRAFTING_TABLE = Blocks::CRAFTING_TABLE->getDefaultState();
    const auto POTTED_RED_MUSHROOM = Blocks::POTTED_RED_MUSHROOM->getDefaultState();
    
    const auto SPRUCE_STAIRS_NORTH = SPRUCE_STAIRS.set<StairsBlock::FACING>(Direction::NORTH);
    const auto SPRUCE_STAIRS_SOUTH = SPRUCE_STAIRS.set<StairsBlock::FACING>(Direction::SOUTH);
    const auto SPRUCE_STAIRS_EAST = SPRUCE_STAIRS.set<StairsBlock::FACING>(Direction::EAST);
    const auto SPRUCE_STAIRS_WEST = SPRUCE_STAIRS.set<StairsBlock::FACING>(Direction::WEST);

    fillWithBlocks(region, bb, 1, 1, 1, 5, 1, 7, SPRUCE_PLANKS, SPRUCE_PLANKS, false);
    fillWithBlocks(region, bb, 1, 4, 2, 5, 4, 7, SPRUCE_PLANKS, SPRUCE_PLANKS, false);
    fillWithBlocks(region, bb, 2, 1, 0, 4, 1, 0, SPRUCE_PLANKS, SPRUCE_PLANKS, false);
    fillWithBlocks(region, bb, 2, 2, 2, 3, 3, 2, SPRUCE_PLANKS, SPRUCE_PLANKS, false);
    fillWithBlocks(region, bb, 1, 2, 3, 1, 3, 6, SPRUCE_PLANKS, SPRUCE_PLANKS, false);
    fillWithBlocks(region, bb, 5, 2, 3, 5, 3, 6, SPRUCE_PLANKS, SPRUCE_PLANKS, false);
    fillWithBlocks(region, bb, 2, 2, 7, 4, 3, 7, SPRUCE_PLANKS, SPRUCE_PLANKS, false);
    fillWithBlocks(region, bb, 1, 0, 2, 1, 3, 2, OAK_LOG, OAK_LOG, false);
    fillWithBlocks(region, bb, 5, 0, 2, 5, 3, 2, OAK_LOG, OAK_LOG, false);
    fillWithBlocks(region, bb, 1, 0, 7, 1, 3, 7, OAK_LOG, OAK_LOG, false);
    fillWithBlocks(region, bb, 5, 0, 7, 5, 3, 7, OAK_LOG, OAK_LOG, false);
    setBlockState(region, OAK_FENCE, 2, 3, 2, bb);
    setBlockState(region, OAK_FENCE, 3, 3, 7, bb);
    setBlockState(region, AIR, 1, 3, 4, bb);
    setBlockState(region, AIR, 5, 3, 4, bb);
    setBlockState(region, AIR, 5, 3, 5, bb);
    setBlockState(region, POTTED_RED_MUSHROOM, 1, 3, 5, bb);
    setBlockState(region, CRAFTING_TABLE, 3, 2, 6, bb);
    setBlockState(region, CAULDRON, 4, 2, 6, bb);
    setBlockState(region, OAK_FENCE, 1, 2, 1, bb);
    setBlockState(region, OAK_FENCE, 5, 2, 1, bb);
    fillWithBlocks(region, bb, 0, 4, 1, 6, 4, 1, SPRUCE_STAIRS_NORTH, SPRUCE_STAIRS_NORTH, false);
    fillWithBlocks(region, bb, 0, 4, 2, 0, 4, 7, SPRUCE_STAIRS_EAST, SPRUCE_STAIRS_EAST, false);
    fillWithBlocks(region, bb, 6, 4, 2, 6, 4, 7, SPRUCE_STAIRS_WEST, SPRUCE_STAIRS_WEST, false);
    fillWithBlocks(region, bb, 0, 4, 8, 6, 4, 8, SPRUCE_STAIRS_SOUTH, SPRUCE_STAIRS_SOUTH, false);
    setBlockState(region, SPRUCE_STAIRS_NORTH.set<StairsBlock::SHAPE>(StairsShape::OUTER_RIGHT), 0, 4, 1, bb);
    setBlockState(region, SPRUCE_STAIRS_NORTH.set<StairsBlock::SHAPE>(StairsShape::OUTER_LEFT), 6, 4, 1, bb);
    setBlockState(region, SPRUCE_STAIRS_SOUTH.set<StairsBlock::SHAPE>(StairsShape::OUTER_LEFT), 0, 4, 8, bb);
    setBlockState(region, SPRUCE_STAIRS_SOUTH.set<StairsBlock::SHAPE>(StairsShape::OUTER_RIGHT), 6, 4, 8, bb);

    for (int i = 2; i <= 7; i += 5) {
        for (int j = 1; j <= 5; j += 4) {
            replaceAirAndLiquidDownwards(region, OAK_LOG, j, -1, i, bb);
        }
    }

    spawnWitch(region, bb);
    spawnCat(region, bb);
    return true;
}


void SwampHutPiece::spawnWitch(WorldGenRegion& region, const BoundingBox& bb) {
    if (witch) {
        return;
    }

    const auto pos = getRelativePosition(2, 2, 5);
    if (bb.isVecInside(pos)) {
        witch = true;
//        WitchEntity entity = EntityType.WITCH.create(region.getWorld());
//        entity.enablePersistence();
//        entity.setLocationAndAngles((double)pos.x + 0.5, (double)pos.y, (double)pos.z + 0.5, 0.0F, 0.0F);
//        entity.onInitialSpawn(region, region.getDifficultyForLocation(pos), SpawnReason.STRUCTURE, (ILivingEntityData)null, (CompoundNBT)null);
//        region.func_242417_l(entity);
    }
}

void SwampHutPiece::spawnCat(WorldGenRegion& region, const BoundingBox& bb) {
    if (cat) {
        return;
    }

    const auto pos = getRelativePosition(2, 2, 5);
    if (bb.isVecInside(pos)) {
        cat = true;
//        CatEntity entity = EntityType.CAT.create(region.getWorld());
//        entity.enablePersistence();
//        entity.setLocationAndAngles((double)pos.x + 0.5, (double)pos.y, (double)pos.z + 0.5, 0.0F, 0.0F);
//        entity.onInitialSpawn(region, region.getDifficultyForLocation(pos), SpawnReason.STRUCTURE, (ILivingEntityData)null, (CompoundNBT)null);
//        region.func_242417_l(entity);
    }
}
