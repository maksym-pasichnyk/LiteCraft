#include "Biome.hpp"
#include "../chunk/Chunk.hpp"

struct ISurfaceBuilder {
    virtual void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) = 0;
};

struct NoopSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct DefaultSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
        BlockData blockstate = top;
        BlockData blockstate1 = filler;
        int i = -1;
        int j = (int)(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
        int xPos = xStart & 15;
        int zPos = zStart & 15;

        for(int yPos = startHeight; yPos >= 0; --yPos) {
            BlockData blockstate2 = chunk.getData(xPos, yPos, zPos);
            if (/*blockstate2.isAir()*/blockstate2.id == BlockID::AIR) {
                i = -1;
            } else if (/*blockstate2.isIn(defaultBlock.getData())*/ blockstate2.id == defaultBlock.id) {
                if (i == -1) {
                    if (j <= 0) {
                        blockstate = {BlockID::AIR, 0};// Blocks.AIR.getDefaultState();
                        blockstate1 = defaultBlock;
                    } else if (yPos >= sealevel - 4 && yPos <= sealevel + 1) {
                        blockstate = top;
                        blockstate1 = filler;
                    }

                    if (yPos < sealevel && /*(blockstate == null || blockstate.isAir())*/ blockstate.id == BlockID::AIR) {
//                    if (biome->getTemperature(xStart, yPos, zStart) < 0.15F) {
//                        blockstate = Blocks.ICE.getDefaultState();
//                    } else {
                        blockstate = defaultFluid;
//                    }
                    }

                    i = j;
                    if (yPos >= sealevel - 1) {
                        chunk.setData(xPos, yPos, zPos, blockstate/*, false*/);
                    } else if (yPos < sealevel - 7 - j) {
                        blockstate = BlockData{BlockID::AIR, 0};// Blocks.AIR.getDefaultState();
                        blockstate1 = defaultBlock;
                        chunk.setData(xPos, yPos, zPos, underWater/*, false*/);
                    } else {
                        chunk.setData(xPos, yPos, zPos, blockstate1/*, false*/);
                    }
                } else if (i > 0) {
                    --i;
                    chunk.setData(xPos, yPos, zPos, blockstate1/*, false*/);
//                if (i == 0 && blockstate1.isIn(Blocks.SAND) && j > 1) {
//                    i = random.nextInt(4) + Math.max(0, yPos - 63);
//                    blockstate1 = blockstate1.isIn(Blocks.RED_SAND)
//                                  ? Blocks.RED_SANDSTONE.getDefaultState()
//                                  : Blocks.SANDSTONE.getDefaultState();
//                }
                }
            }
        }
    }
};

struct MountainSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
        if (noise > 1.0) {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*stone*/, filler/*stone*/, underWater/*gravel*/, sealevel);
        } else {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*grass*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        }
    }
};

struct ShatteredSavannaSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
        if (noise > 1.75) {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*stone*/, filler/*stone*/, underWater/*gravel*/, sealevel);
        } else if (noise > -0.5) {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*coarse_dirt*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        } else {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*grass*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        }
    }
};

struct GravellyMountainSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
        if (noise < -1.0 || noise > 2.0) {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*gravel*/, filler/*gravel*/, underWater/*gravel*/, sealevel);
        } else if (noise > 1.0) {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*stone*/, filler/*stone*/, underWater/*gravel*/, sealevel);
        } else {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*grass*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        }
    }
};

struct GiantTreeTaigaSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
        if (noise > 1.75) {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*coarse_dirt*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        } else if (noise > -0.95) {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*podzol*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        } else {
            DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*grass*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        }
    }
};

struct SwampSurface {
//    {pallete.getId("grass")}, {pallete.getId("dirt")}, {pallete.getId("gravel")}

    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
        double d0 = Biome::INFO_NOISE.noiseAt((double)xStart * 0.25, (double)zStart * 0.25, false);
        if (d0 > 0.0) {
            const int i = xStart & 15;
            const int j = zStart & 15;

            for(int k = startHeight; k >= 0; --k) {
                if (/*!chunk.getData(i, k, j).isAir()*/chunk.getData(i, k, j).id != BlockID::AIR) {
//                    if (k == 62 && !chunkIn.getBlockState(i, k, j).isIn(defaultFluid.getData())) {
                    if (k == 62 && chunk.getData(i, k, j).id != defaultFluid.id) {
                        chunk.setData(i, k, j, defaultFluid/*, false*/);
                    }
                    break;
                }
            }
        }

        DefaultSurface::buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top, filler, underWater, sealevel);
    }
};

struct BadlandsSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct WoodedBadlandsSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct ErodedBadlandsSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct FrozenOceanSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct NetherSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct NetherForestsSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct SoulSandValleySurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

struct BasaltDeltasSurface {
    static void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
    }
};

std::map<int, std::unique_ptr<Biome>> Biome::biomes;

void Biome::registerBiome(int id, Biome* biome) {
    biomes[id] = std::unique_ptr<Biome>(biome);
}

void Biome::registerBiomes() {
    registerBiome(0, new Biome(-1.0, 0.1, DefaultSurface::buildSurface));
    registerBiome(1, new Biome(0.125, 0.05, DefaultSurface::buildSurface));
    registerBiome(2, new Biome(0.125, 0.05, DefaultSurface::buildSurface));
    registerBiome(3, new Biome(1.0, 0.5, MountainSurface::buildSurface));
    registerBiome(4, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(5, new Biome(0.2, 0.2, DefaultSurface::buildSurface));
    registerBiome(6, new Biome(-0.2, 0.1, SwampSurface::buildSurface));
    registerBiome(7, new Biome(-0.5, 0.0, DefaultSurface::buildSurface));
    registerBiome(8, new Biome(0.1, 0.2, NetherSurface::buildSurface));
    registerBiome(9, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(10, new Biome(-1.0, 0.1, FrozenOceanSurface::buildSurface));
    registerBiome(11, new Biome(-0.5, 0.0, DefaultSurface::buildSurface));
    registerBiome(12, new Biome(0.125, 0.05, DefaultSurface::buildSurface));
    registerBiome(13, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(14, new Biome(0.2, 0.3, DefaultSurface::buildSurface));
    registerBiome(15, new Biome(0.0, 0.025, DefaultSurface::buildSurface));
    registerBiome(16, new Biome(0.0, 0.025, DefaultSurface::buildSurface));
    registerBiome(17, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(18, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(19, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(20, new Biome(0.8, 0.3, DefaultSurface::buildSurface));
    registerBiome(21, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(22, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(23, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(24, new Biome(-1.8, 0.1, DefaultSurface::buildSurface));
    registerBiome(25, new Biome(0.1, 0.8, DefaultSurface::buildSurface));
    registerBiome(26, new Biome(0.0, 0.025, DefaultSurface::buildSurface));
    registerBiome(27, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(28, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(29, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(30, new Biome(0.2, 0.2, DefaultSurface::buildSurface));
    registerBiome(31, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(32, new Biome(0.2, 0.2, GiantTreeTaigaSurface::buildSurface));
    registerBiome(33, new Biome(0.45, 0.3, GiantTreeTaigaSurface::buildSurface));
    registerBiome(34, new Biome(1.0, 0.5, DefaultSurface::buildSurface));
    registerBiome(35, new Biome(0.125, 0.05, DefaultSurface::buildSurface));
    registerBiome(36, new Biome(1.5, 0.025, DefaultSurface::buildSurface));
    registerBiome(37, new Biome(0.1, 0.2, BadlandsSurface::buildSurface));
    registerBiome(38, new Biome(1.5, 0.025, WoodedBadlandsSurface::buildSurface));
    registerBiome(39, new Biome(1.5, 0.025, BadlandsSurface::buildSurface));
    registerBiome(40, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(41, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(42, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(43, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(44, new Biome(-1.0, 0.1, DefaultSurface::buildSurface));
    registerBiome(45, new Biome(-1.0, 0.1, DefaultSurface::buildSurface));
    registerBiome(46, new Biome(-1.0, 0.1, DefaultSurface::buildSurface));
    registerBiome(47, new Biome(-1.8, 0.1, DefaultSurface::buildSurface));
    registerBiome(48, new Biome(-1.8, 0.1, DefaultSurface::buildSurface));
    registerBiome(49, new Biome(-1.8, 0.1, DefaultSurface::buildSurface));
    registerBiome(50, new Biome(-1.8, 0.1, FrozenOceanSurface::buildSurface));
    registerBiome(127, new Biome(0.1, 0.2, NoopSurface::buildSurface));
    registerBiome(129, new Biome(0.125, 0.05, DefaultSurface::buildSurface));
    registerBiome(130, new Biome(0.225, 0.25, DefaultSurface::buildSurface));
    registerBiome(131, new Biome(1.0, 0.5, GravellyMountainSurface::buildSurface));
    registerBiome(132, new Biome(0.1, 0.4, DefaultSurface::buildSurface));
    registerBiome(133, new Biome(0.3, 0.4, DefaultSurface::buildSurface));
    registerBiome(134, new Biome(-0.1, 0.3, SwampSurface::buildSurface));
    registerBiome(140, new Biome(0.425, 0.45000002, DefaultSurface::buildSurface));
    registerBiome(149, new Biome(0.2, 0.4, DefaultSurface::buildSurface));
    registerBiome(151, new Biome(0.2, 0.4, DefaultSurface::buildSurface));
    registerBiome(155, new Biome(0.2, 0.4, DefaultSurface::buildSurface));
    registerBiome(156, new Biome(0.55, 0.5, DefaultSurface::buildSurface));
    registerBiome(157, new Biome(0.2, 0.4, DefaultSurface::buildSurface));
    registerBiome(158, new Biome(0.3, 0.4, DefaultSurface::buildSurface));
    registerBiome(160, new Biome(0.2, 0.2, GiantTreeTaigaSurface::buildSurface));
    registerBiome(161, new Biome(0.2, 0.2, GiantTreeTaigaSurface::buildSurface));
    registerBiome(162, new Biome(1.0, 0.5, GravellyMountainSurface::buildSurface));
    registerBiome(163, new Biome(0.3625, 1.225, ShatteredSavannaSurface::buildSurface));
    registerBiome(164, new Biome(1.05, 1.2125001, ShatteredSavannaSurface::buildSurface));
    registerBiome(165, new Biome(0.1, 0.2, ErodedBadlandsSurface::buildSurface));
    registerBiome(166, new Biome(0.45, 0.3, WoodedBadlandsSurface::buildSurface));
    registerBiome(167, new Biome(0.45, 0.3, BadlandsSurface::buildSurface));
    registerBiome(168, new Biome(0.1, 0.2, DefaultSurface::buildSurface));
    registerBiome(169, new Biome(0.45, 0.3, DefaultSurface::buildSurface));
    registerBiome(170, new Biome(0.1, 0.2, SoulSandValleySurface::buildSurface));
    registerBiome(171, new Biome(0.1, 0.2, NetherForestsSurface::buildSurface));
    registerBiome(172, new Biome(0.1, 0.2, NetherForestsSurface::buildSurface));
    registerBiome(173, new Biome(0.1, 0.2, BasaltDeltasSurface::buildSurface));
}
