#include "DungeonsFeature.hpp"
#include <world/WorldGenRegion.hpp>
#include <block/Blocks.hpp>
#include <block/Block.hpp>

bool DungeonsFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    int j = random.nextInt(2) + 2;
    int k = -j - 1;
    int l = j + 1;
    int k1 = random.nextInt(2) + 2;
    int l1 = -k1 - 1;
    int i2 = k1 + 1;
    int j2 = 0;

    for (int k2 = k; k2 <= l; ++k2) {
        for (int l2 = -1; l2 <= 4; ++l2) {
            for (int i3 = l1; i3 <= i2; ++i3) {
                const auto blockpos = pos.add(k2, l2, i3);
                const auto material = reader.getData(blockpos).getMaterial();
                const auto is_solid = material->isSolid;
                if (l2 == -1 && !is_solid) {
                    return false;
                }

                if (l2 == 4 && !is_solid) {
                    return false;
                }

                if ((k2 == k || k2 == l || i3 == l1 || i3 == i2) && l2 == 0 && reader.isAirBlock(blockpos) && reader.isAirBlock(blockpos.up())) {
                    ++j2;
                }
            }
        }
    }

    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();

    if (j2 >= 1 && j2 <= 5) {
        for (int k3 = k; k3 <= l; ++k3) {
            for (int i4 = 3; i4 >= -1; --i4) {
                for (int k4 = l1; k4 <= i2; ++k4) {
                    const auto blockpos1 = pos.add(k3, i4, k4);
                    const auto blockstate = reader.getData(blockpos1);
                    if (k3 != k && i4 != -1 && k4 != l1 && k3 != l && i4 != 4 && k4 != i2) {
                        if (!blockstate.is(Blocks::CHEST) && !blockstate.is(Blocks::SPAWNER)) {
                            reader.setData(blockpos1, CAVE_AIR /*, 2*/);
                        }
                    } else if (blockpos1.y >= 0 && !reader.getData(blockpos1.down()).getMaterial()->isSolid) {
                        reader.setData(blockpos1, CAVE_AIR /*, 2*/);
                    } else if (blockstate.getMaterial()->isSolid && !blockstate.is(Blocks::CHEST)) {
                        if (i4 == -1 && random.nextInt(4) != 0) {
                            reader.setData(blockpos1, Blocks::MOSSY_COBBLESTONE->getDefaultState() /*, 2*/);
                        } else {
                            reader.setData(blockpos1, Blocks::COBBLESTONE->getDefaultState() /*, 2*/);
                        }
                    }
                }
            }
        }

        for (int l3 = 0; l3 < 2; ++l3) {
            for (int j4 = 0; j4 < 3; ++j4) {
                const auto l4 = pos.x + random.nextInt(j * 2 + 1) - j;
                const auto i5 = pos.y;
                const auto j5 = pos.z + random.nextInt(k1 * 2 + 1) - k1;
                const auto blockpos2 = BlockPos::from(l4, i5, j5);
                if (reader.isAirBlock(blockpos2)) {
                    int j3 = 0;

                    for (const auto direction : DirectionUtil::Plane::HORIZONTAL) {
                        if (reader.getData(blockpos2.offset(direction)).getMaterial()->isSolid) {
                            ++j3;
                        }
                    }

                    if (j3 == 1) {
//                        reader.setData(blockpos2, StructurePiece.correctFacing(reader, blockpos2, Blocks::CHEST->getDefaultState()), 2);
//                        LockableLootTileEntity.setLootTable(reader, random, blockpos2, LootTables.CHESTS_SIMPLE_DUNGEON);
                        break;
                    }
                }
            }
        }

        reader.setData(pos, Blocks::SPAWNER->getDefaultState() /*, 2*/);
//        TileEntity tileentity = reader.getTileEntity(pos);
//        if (tileentity instanceof MobSpawnerTileEntity) {
//            ((MobSpawnerTileEntity)tileentity).getSpawnerBaseLogic().setEntityType(this.getRandomDungeonMob(random));
//        } else {
//            LOGGER.error("Failed to fetch mob spawner entity at ({}, {}, {})", pos.x, pos.y, pos.getZ());
//        }
        return true;
    }
    return false;
}