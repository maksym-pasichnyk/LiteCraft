#include "LakesFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../biome/Biome.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/material/Materials.hpp"

LakesFeature::LakesFeature() {
    AIR = Blocks::AIR->getDefaultState();
}

bool LakesFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    while (pos.y > 5 && reader.isAirBlock(pos)) {
        pos.y -= 1;
    }

    if (pos.y <= 4) {
        return false;
    }

    pos.y -= 4;

//    if (reader.func_241827_a(SectionPos.from(pos), Structure.VILLAGE).findAny().isPresent()) {
//        return false;
//    }

    const auto &cfg = std::get<BlockStateFeatureConfig>(config);

    std::array<bool, 2048> flags{};
    const int i = random.nextInt(4) + 4;

    for (int j = 0; j < i; ++j) {
        const double d0 = random.nextDouble() * 6.0 + 3.0;
        const double d1 = random.nextDouble() * 4.0 + 2.0;
        const double d2 = random.nextDouble() * 6.0 + 3.0;
        const double d3 = random.nextDouble() * (16.0 - d0 - 2.0) + 1.0 + d0 / 2.0;
        const double d4 = random.nextDouble() * (8.0 - d1 - 4.0) + 2.0 + d1 / 2.0;
        const double d5 = random.nextDouble() * (16.0 - d2 - 2.0) + 1.0 + d2 / 2.0;

        for (int l = 1; l < 15; ++l) {
            for (int i1 = 1; i1 < 15; ++i1) {
                for (int j1 = 1; j1 < 7; ++j1) {
                    const double d6 = (static_cast<double>(l) - d3) / (d0 / 2.0);
                    const double d7 = (static_cast<double>(j1) - d4) / (d1 / 2.0);
                    const double d8 = (static_cast<double>(i1) - d5) / (d2 / 2.0);
                    const double d9 = d6 * d6 + d7 * d7 + d8 * d8;
                    if (d9 < 1.0) {
                        flags[(l * 16 + i1) * 8 + j1] = true;
                    }
                }
            }
        }
    }

    for (int k1 = 0; k1 < 16; ++k1) {
        for (int l2 = 0; l2 < 16; ++l2) {
            for (int k = 0; k < 8; ++k) {
                if (flags[(k1 * 16 + l2) * 8 + k]) {
                    continue;
                }
                const auto flag = k1 < 15 && flags[((k1 + 1) * 16 + l2) * 8 + k] ||
                                  k1 > 0 && flags[((k1 - 1) * 16 + l2) * 8 + k] ||
                                  l2 < 15 && flags[(k1 * 16 + l2 + 1) * 8 + k] ||
                                  l2 > 0 && flags[(k1 * 16 + (l2 - 1)) * 8 + k] ||
                                  k < 7 && flags[(k1 * 16 + l2) * 8 + k + 1] ||
                                  k > 0 && flags[(k1 * 16 + l2) * 8 + (k - 1)];
                if (flag) {
                    auto material1 = reader.getData(pos + BlockPos(k1, k, l2)).getMaterial();
                    if (k >= 4 && material1->isLiquid) {
                        return false;
                    }

                    if (k < 4 && !material1->isSolid && reader.getData(pos + BlockPos(k1, k, l2)) != cfg.state) {
                        return false;
                    }
                }
            }
        }
    }

    for (int l1 = 0; l1 < 16; ++l1) {
        for (int i3 = 0; i3 < 16; ++i3) {
            for (int i4 = 0; i4 < 8; ++i4) {
                if (flags[(l1 * 16 + i3) * 8 + i4]) {
                    reader.setData(pos + BlockPos(l1, i4, i3), i4 >= 4 ? AIR : cfg.state/*, 2*/);
                }
            }
        }
    }

    for (int i2 = 0; i2 < 16; ++i2) {
        for (int j3 = 0; j3 < 16; ++j3) {
            for (int j4 = 4; j4 < 8; ++j4) {
                if (flags[(i2 * 16 + j3) * 8 + j4]) {
                    const auto blockpos = pos + BlockPos(i2, j4 - 1, j3);
                    if (isDirt(reader.getData(blockpos).getBlock())/* && reader.getLightFor(LightType.SKY, pos + BlockPos(i2, j4, j3)) > 0*/) {
                        auto biome = reader.getBiome(blockpos);
                        if (biome->getGenerationSettings().getSurfaceBuilderConfig().getTop().is(Blocks::MYCELIUM)) {
                            reader.setData(blockpos, Blocks::MYCELIUM->getDefaultState()/*, 2*/);
                        } else {
                            reader.setData(blockpos, Blocks::GRASS_BLOCK->getDefaultState()/*, 2*/);
                        }
                    }
                }
            }
        }
    }

    const auto material = cfg.state.getMaterial();

    if (material == Materials::LAVA) {
        for (int j2 = 0; j2 < 16; ++j2) {
            for (int k3 = 0; k3 < 16; ++k3) {
                for (int k4 = 0; k4 < 8; ++k4) {
                    if (flags[(j2 * 16 + k3) * 8 + k4]) continue;
                    const auto flag = j2 < 15 && flags[((j2 + 1) * 16 + k3) * 8 + k4] ||
                                      j2 > 0 && flags[((j2 - 1) * 16 + k3) * 8 + k4] ||
                                      k3 < 15 && flags[(j2 * 16 + k3 + 1) * 8 + k4] ||
                                      k3 > 0 && flags[(j2 * 16 + (k3 - 1)) * 8 + k4] ||
                                      k4 < 7 && flags[(j2 * 16 + k3) * 8 + k4 + 1] ||
                                      k4 > 0 && flags[(j2 * 16 + k3) * 8 + (k4 - 1)];
                    if (flag) {
                        if ((k4 < 4 || random.nextInt(2) != 0) &&
                            reader.getData(pos + BlockPos(j2, k4, k3)).getMaterial()->isSolid) {
                            reader.setData(pos + BlockPos(j2, k4, k3), Blocks::STONE->getDefaultState()/*, 2*/);
                        }
                    }
                }
            }
        }
    }

    if (material == Materials::WATER) {
        for (int k2 = 0; k2 < 16; ++k2) {
            for (int l3 = 0; l3 < 16; ++l3) {
                const auto blockpos1 = pos + BlockPos(k2, 4, l3);
                if (reader.getBiome(blockpos1)->doesWaterFreeze(reader, blockpos1, false)) {
                    reader.setData(blockpos1, Blocks::ICE->getDefaultState()/*, 2*/);
                }
            }
        }
    }

    return true;
}