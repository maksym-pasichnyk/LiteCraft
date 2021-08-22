#include "MineshaftCorridor.hpp"
#include "../../../WorldGenRegion.hpp"
#include <block/Blocks.hpp>
#include <block/RailBlock.hpp>
#include <block/FenceBlock.hpp>
#include <block/WallTorchBlock.hpp>

std::optional<BoundingBox> MineshaftPieces::Corridor::findCorridor(std::span<StructurePiece *> pieces, Random &random, int x, int y, int z, Direction facing) {
    BoundingBox bounds{x, y, z, x, y + 3 - 1, z};

    int i = random.nextInt(3) + 2;
    for (; i > 0; --i) {
        const int j = i * 5;
        switch (facing) {
            case Direction::NORTH:
            default:
                bounds.maxX = x + 3 - 1;
                bounds.minZ = z - (j - 1);
                break;
            case Direction::SOUTH:
                bounds.maxX = x + 3 - 1;
                bounds.maxZ = z + j - 1;
                break;
            case Direction::WEST:
                bounds.minX = x - (j - 1);
                bounds.maxZ = z + 3 - 1;
                break;
            case Direction::EAST:
                bounds.maxX = x + j - 1;
                bounds.maxZ = z + 3 - 1;
                break;
        }

        if (!hasIntersecting(pieces, bounds)) {
            return bounds;
        }
    }

    return std::nullopt;
}

void MineshaftPieces::Corridor::buildComponent(StructurePiece *start, std::vector<StructurePiece *> &pieces, Random &random) {
    const int i = getComponentType();
    const int j = random.nextInt(4);

    auto dyn_start = dynamic_cast<Piece*>(start);

    if (coordBaseMode.has_value()) {
        switch (auto direction = *coordBaseMode) {
            case Direction::NORTH:
            default:
                if (j <= 1) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX, bounds.minY - 1 + random.nextInt(3), bounds.minZ - 1, direction, i);
                } else if (j == 2) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY - 1 + random.nextInt(3), bounds.minZ, Direction::WEST, i);
                } else {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY - 1 + random.nextInt(3), bounds.minZ, Direction::EAST, i);
                }
                break;
            case Direction::SOUTH:
                if (j <= 1) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX, bounds.minY - 1 + random.nextInt(3), bounds.maxZ + 1, direction, i);
                } else if (j == 2) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY - 1 + random.nextInt(3), bounds.maxZ - 3, Direction::WEST, i);
                } else {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY - 1 + random.nextInt(3), bounds.maxZ - 3, Direction::EAST, i);
                }
                break;
            case Direction::WEST:
                if (j <= 1) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY - 1 + random.nextInt(3), bounds.minZ, direction, i);
                } else if (j == 2) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX, bounds.minY - 1 + random.nextInt(3), bounds.minZ - 1, Direction::NORTH, i);
                } else {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX, bounds.minY - 1 + random.nextInt(3), bounds.maxZ + 1, Direction::SOUTH, i);
                }
                break;
            case Direction::EAST:
                if (j <= 1) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY - 1 + random.nextInt(3), bounds.minZ, direction, i);
                } else if (j == 2) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.maxX - 3, bounds.minY - 1 + random.nextInt(3), bounds.minZ - 1, Direction::NORTH, i);
                } else {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.maxX - 3, bounds.minY - 1 + random.nextInt(3), bounds.maxZ + 1, Direction::SOUTH, i);
                }
                break;
        }
    }

    if (i < 8) {
        if (!coordBaseMode.has_value() || *coordBaseMode != Direction::NORTH && *coordBaseMode != Direction::SOUTH) {
            for (int i1 = bounds.minX + 3; i1 + 3 <= bounds.maxX; i1 += 5) {
                const int j1 = random.nextInt(5);
                if (j1 == 0) {
                    generateAndAddPiece(dyn_start, pieces, random, i1, bounds.minY, bounds.minZ - 1, Direction::NORTH, i + 1);
                } else if (j1 == 1) {
                    generateAndAddPiece(dyn_start, pieces, random, i1, bounds.minY, bounds.maxZ + 1, Direction::SOUTH, i + 1);
                }
            }
        } else {
            for (int k = bounds.minZ + 3; k + 3 <= bounds.maxZ; k += 5) {
                const int l = random.nextInt(5);
                if (l == 0) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.minX - 1, bounds.minY, k, Direction::WEST, i + 1);
                } else if (l == 1) {
                    generateAndAddPiece(dyn_start, pieces, random, bounds.maxX + 1, bounds.minY, k, Direction::EAST, i + 1);
                }
            }
        }
    }
}

bool MineshaftPieces::Corridor::addComponentParts(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos, const BlockPos &blockPos) {
    if (isLiquidInStructureBoundingBox(region, bb)) {
        return false;
    }
    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();
    const auto COBWEB = Blocks::COBWEB->getDefaultState();

    const auto i1 = sectionCount * 5 - 1;
    const auto blockstate = getPlanksBlock();
    fillWithBlocks(region, bb, 0, 0, 0, 2, 1, i1, CAVE_AIR, CAVE_AIR, false);
    generateMaybeBox(region, bb, random, 0.8F, 0, 2, 0, 2, 2, i1, CAVE_AIR, CAVE_AIR, false, false);
    if (hasSpiders) {
        generateMaybeBox(region, bb, random, 0.6F, 0, 0, 0, 2, 1, i1, COBWEB, CAVE_AIR, false, true);
    }

    for (int j1 = 0; j1 < sectionCount; ++j1) {
        const int k1 = 2 + j1 * 5;
        placeSupport(region, bb, 0, 0, k1, 2, 2, random);
        placeCobWeb(region, bb, random, 0.1F, 0, 2, k1 - 1);
        placeCobWeb(region, bb, random, 0.1F, 2, 2, k1 - 1);
        placeCobWeb(region, bb, random, 0.1F, 0, 2, k1 + 1);
        placeCobWeb(region, bb, random, 0.1F, 2, 2, k1 + 1);
        placeCobWeb(region, bb, random, 0.05F, 0, 2, k1 - 2);
        placeCobWeb(region, bb, random, 0.05F, 2, 2, k1 - 2);
        placeCobWeb(region, bb, random, 0.05F, 0, 2, k1 + 2);
        placeCobWeb(region, bb, random, 0.05F, 2, 2, k1 + 2);

        if (random.nextInt(100) == 0) {
//            generateChest(region, bb, random, 2, 0, k1 - 1, LootTables::CHESTS_ABANDONED_MINESHAFT);
        }

        if (random.nextInt(100) == 0) {
//            generateChest(region, bb, random, 0, 0, k1 + 1, LootTables::CHESTS_ABANDONED_MINESHAFT);
        }

        if (hasSpiders && !spawnerPlaced) {
            const int l1 = getYWithOffset(0);
            const int i2 = k1 - 1 + random.nextInt(3);
            const int j2 = getXWithOffset(1, i2);
            const int k2 = getZWithOffset(1, i2);
            const auto blockpos = BlockPos::from(j2, l1, k2);
            if (bb.isVecInside(blockpos) && isUnderOceanFloor(region, 1, 0, i2, bb)) {
                spawnerPlaced = true;
                region.setData(blockpos, Blocks::SPAWNER->getDefaultState() /*, 2*/);
//                TileEntity tileentity = region.getTileEntity(blockpos);
//                if (tileentity instanceof MobSpawnerTileEntity) {
//                    ((MobSpawnerTileEntity)tileentity).getSpawnerBaseLogic().setEntityType(EntityType.CAVE_SPIDER);
//                }
            }
        }
    }

    for (int l2 = 0; l2 <= 2; ++l2) {
        for (int i3 = 0; i3 <= i1; ++i3) {
            const auto blockstate3 = getBlockStateFromPos(region, l2, -1, i3, bb);
            if (blockstate3.isAir() && isUnderOceanFloor(region, l2, -1, i3, bb)) {
                setBlockState(region, blockstate, l2, -1, i3, bb);
            }
        }
    }

    if (hasRails) {
        const auto rail = Blocks::RAIL->getDefaultState().set<RailBlock::SHAPE>(RailShape::NORTH_SOUTH);

        for (int j3 = 0; j3 <= i1; ++j3) {
            const auto state = getBlockStateFromPos(region, 1, -1, j3, bb);
            if (!state.isAir() && state.isOpaque() /* && state.isOpaqueCube(region, BlockPos{getXWithOffset(1, j3), getYWithOffset(-1), getZWithOffset(1, j3)})*/) {
                const auto f = isUnderOceanFloor(region, 1, 0, j3, bb) ? 0.7F : 0.9F;
                randomlyPlaceBlock(region, bb, random, f, 1, 0, j3, rail);
            }
        }
    }

    return true;
}

void MineshaftPieces::Corridor::placeSupport(WorldGenRegion &region, const BoundingBox &bb, int xmin, int ymin, int z, int ymax, int xmax, Random &random) {
    if (isSupportingBox(region, bb, xmin, xmax, ymax, z)) {
        const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();
        const auto WALL_TORCH = Blocks::WALL_TORCH->getDefaultState();

        const auto planks = getPlanksBlock();
        const auto fence = getFenceBlock();
        fillWithBlocks(region, bb, xmin, ymin, z, xmin, ymax - 1, z, fence.set<FenceBlock::WEST>(true), CAVE_AIR, false);
        fillWithBlocks(region, bb, xmax, ymin, z, xmax, ymax - 1, z, fence.set<FenceBlock::EAST>(true), CAVE_AIR, false);
        if (random.nextInt(4) == 0) {
            fillWithBlocks(region, bb, xmin, ymax, z, xmin, ymax, z, planks, CAVE_AIR, false);
            fillWithBlocks(region, bb, xmax, ymax, z, xmax, ymax, z, planks, CAVE_AIR, false);
        } else {
            fillWithBlocks(region, bb, xmin, ymax, z, xmax, ymax, z, planks, CAVE_AIR, false);
            randomlyPlaceBlock(region, bb, random, 0.05F, xmin + 1, ymax, z - 1, WALL_TORCH.set<WallTorchBlock::FACING>(Direction::NORTH));
            randomlyPlaceBlock(region, bb, random, 0.05F, xmin + 1, ymax, z + 1, WALL_TORCH.set<WallTorchBlock::FACING>(Direction::SOUTH));
        }
    }
}

void MineshaftPieces::Corridor::placeCobWeb(WorldGenRegion &region, const BoundingBox &bb, Random &random, float chance, int x, int y, int z) {
    if (isUnderOceanFloor(region, x, y, z, bb)) {
        const auto COBWEB = Blocks::COBWEB->getDefaultState();
        randomlyPlaceBlock(region, bb, random, chance, x, y, z, COBWEB);
    }
}
