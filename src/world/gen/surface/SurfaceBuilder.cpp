#include "SurfaceBuilder.hpp"
#include "../../biome/Biome.hpp"
#include "../../chunk/Chunk.hpp"

std::unique_ptr<SurfaceBuilder> SurfaceBuilder::Noop{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::Default{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::Mountain{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::ShatteredSavanna{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::GravellyMountain{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::GiantTreeTaiga{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::Swamp{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::Badlands{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::WoodedBadlands{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::ErodedBadlands{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::FrozenOcean{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::Nether{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::NetherForests{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::SoulSandValley{nullptr};
std::unique_ptr<SurfaceBuilder> SurfaceBuilder::BasaltDeltas{nullptr};

struct NoopSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct DefaultSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
        BlockData blockstate = top;
        BlockData blockstate1 = filler;
        int i = -1;
        int j = (int)(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
        int xPos = xStart & 15;
        int zPos = zStart & 15;

        for(int yPos = startHeight; yPos >= 0; --yPos) {
            BlockData blockstate2 = chunk.getData(xPos, yPos, zPos);
            if (blockstate2.isAir()) {
                i = -1;
            } else if (/*blockstate2.isIn(defaultBlock.getData())*/ blockstate2.id == defaultBlock.id) {
                if (i == -1) {
                    if (j <= 0) {
                        blockstate = {Block::air->id, 0};// Blocks.AIR.getDefaultState();
                        blockstate1 = defaultBlock;
                    } else if (yPos >= sealevel - 4 && yPos <= sealevel + 1) {
                        blockstate = top;
                        blockstate1 = filler;
                    }

                    if (yPos < sealevel && blockstate.isAir()) {
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
                        blockstate = BlockData{Block::air->id, 0};// Blocks.AIR.getDefaultState();
                        blockstate1 = defaultBlock;
                        chunk.setData(xPos, yPos, zPos, underWater/*, false*/);
                    } else {
                        chunk.setData(xPos, yPos, zPos, blockstate1/*, false*/);
                    }
                } else if (i > 0) {
                    --i;
                    chunk.setData(xPos, yPos, zPos, blockstate1/*, false*/);
                    if (i == 0 && /*blockstate1.isIn(Block::sand)*/ (blockstate1.id == Block::sand->id && blockstate1.val == 0) && j > 1) {
                        i = rand.nextInt(4) + std::max(0, yPos - 63);
//                        blockstate1 = blockstate1.isIn(Blocks.RED_SAND)
//                                      ? Blocks.RED_SANDSTONE.getDefaultState()
//                                      : Blocks.SANDSTONE.getDefaultState();
//                        blockstate1 = blockstate1.isIn(Blocks.RED_SAND)
//                                      ? Blocks.RED_SANDSTONE.getDefaultState()
//                                      : Blocks.SANDSTONE.getDefaultState();
                    }
                }
            }
        }
    }
};

struct MountainSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
        if (noise > 1.0) {
            const BlockData stone{Block::stone->id, 0};
            const BlockData gravel{Block::gravel->id, 0};

            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, stone, stone, gravel, sealevel);
        } else {
            const BlockData grass{Block::grass->id, 0};
            const BlockData dirt{Block::dirt->id, 0};
            const BlockData gravel{Block::gravel->id, 0};

            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, grass, dirt, gravel, sealevel);
        }
    }
};

struct ShatteredSavannaSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
        if (noise > 1.75) {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*stone*/, filler/*stone*/, underWater/*gravel*/, sealevel);
        } else if (noise > -0.5) {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*coarse_dirt*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        } else {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*grass*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        }
    }
};

struct GravellyMountainSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
        if (noise < -1.0 || noise > 2.0) {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*gravel*/, filler/*gravel*/, underWater/*gravel*/, sealevel);
        } else if (noise > 1.0) {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*stone*/, filler/*stone*/, underWater/*gravel*/, sealevel);
        } else {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*grass*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        }
    }
};

struct GiantTreeTaigaSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
        if (noise > 1.75) {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*coarse_dirt*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        } else if (noise > -0.95) {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*podzol*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        } else {
            SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top/*grass*/, filler/*dirt*/, underWater/*gravel*/, sealevel);
        }
    }
};

struct SwampSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
        double d0 = Biome::INFO_NOISE.noiseAt((double)xStart * 0.25, (double)zStart * 0.25, false);
        if (d0 > 0.0) {
            const int i = xStart & 15;
            const int j = zStart & 15;

            for(int k = startHeight; k >= 0; --k) {
                if (!chunk.getData(i, k, j).isAir()) {
//                    if (k == 62 && !chunkIn.getBlockState(i, k, j).isIn(defaultFluid.getData())) {
                    if (k == 62 && chunk.getData(i, k, j).id != defaultFluid.id) {
                        chunk.setData(i, k, j, defaultFluid/*, false*/);
                    }
                    break;
                }
            }
        }

        SurfaceBuilder::Default->buildSurface(rand, chunk, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, top, filler, underWater, sealevel);
    }
};

struct BadlandsSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct WoodedBadlandsSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct ErodedBadlandsSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct FrozenOceanSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct NetherSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct NetherForestsSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct SoulSandValleySurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

struct BasaltDeltasSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) override {
    }
};

void SurfaceBuilder::registerSurfaceBuilders() {
    Noop             = std::make_unique<NoopSurfaceBuilder>();
    Default          = std::make_unique<DefaultSurfaceBuilder>();
    Mountain         = std::make_unique<MountainSurfaceBuilder>();
    ShatteredSavanna = std::make_unique<ShatteredSavannaSurfaceBuilder>();
    GravellyMountain = std::make_unique<GravellyMountainSurfaceBuilder>();
    GiantTreeTaiga   = std::make_unique<GiantTreeTaigaSurfaceBuilder>();
    Swamp            = std::make_unique<SwampSurfaceBuilder>();
    Badlands         = std::make_unique<BadlandsSurfaceBuilder>();
    WoodedBadlands   = std::make_unique<WoodedBadlandsSurfaceBuilder>();
    ErodedBadlands   = std::make_unique<ErodedBadlandsSurfaceBuilder>();
    FrozenOcean      = std::make_unique<FrozenOceanSurfaceBuilder>();
    Nether           = std::make_unique<NetherSurfaceBuilder>();
    NetherForests    = std::make_unique<NetherForestsSurfaceBuilder>();
    SoulSandValley   = std::make_unique<SoulSandValleySurfaceBuilder>();
    BasaltDeltas     = std::make_unique<BasaltDeltasSurfaceBuilder>();
}
