#define _USE_MATH_DEFINES

#include "SurfaceBuilder.hpp"
#include "../PerlinNoiseGenerator.hpp"
#include "../../biome/Biome.hpp"
#include "../../chunk/Chunk.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/material/Materials.hpp"

#include "ThreadLocal.hpp"

#include <cmath>
#include <range/v3/view.hpp>

Registry<SurfaceBuilder> SurfaceBuilder::builders;

SurfaceBuilder* SurfaceBuilder::Noop;
SurfaceBuilder* SurfaceBuilder::Default;
SurfaceBuilder* SurfaceBuilder::Mountain;
SurfaceBuilder* SurfaceBuilder::ShatteredSavanna;
SurfaceBuilder* SurfaceBuilder::GravellyMountain;
SurfaceBuilder* SurfaceBuilder::GiantTreeTaiga;
SurfaceBuilder* SurfaceBuilder::Swamp;
SurfaceBuilder* SurfaceBuilder::Badlands;
SurfaceBuilder* SurfaceBuilder::WoodedBadlands;
SurfaceBuilder* SurfaceBuilder::ErodedBadlands;
SurfaceBuilder* SurfaceBuilder::FrozenOcean;
SurfaceBuilder* SurfaceBuilder::Nether;
SurfaceBuilder* SurfaceBuilder::NetherForest;
SurfaceBuilder* SurfaceBuilder::SoulSandValley;
SurfaceBuilder* SurfaceBuilder::BasaltDeltas;

struct NoopSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
    }
};

struct DefaultSurfaceBuilder : public SurfaceBuilder {
    const BlockData AIR = Blocks::AIR->getDefaultState();
    const BlockData ICE = Blocks::ICE->getDefaultState();

    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, config.top, config.mid, config.underWater, seaLevel);
    }

    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData filler, BlockData underWater, int sealevel) {
        auto blockstate = top;
        auto blockstate1 = filler;
        int i = -1;
        int j = (int)(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
        int xPos = xStart & 15;
        int zPos = zStart & 15;

        for (int yPos = startHeight; yPos >= 0; --yPos) {
            auto blockstate2 = chunk.getData(xPos, yPos, zPos);
            if (blockstate2.isAir()) {
                i = -1;
            } else if (blockstate2.is(defaultBlock.getBlock())) {
                if (i == -1) {
                    if (j <= 0) {
                        blockstate = AIR;
                        blockstate1 = defaultBlock;
                    } else if (yPos >= sealevel - 4 && yPos <= sealevel + 1) {
                        blockstate = top;
                        blockstate1 = filler;
                    }

                    if (yPos < sealevel && blockstate.isAir()) {
                        if (biome.getTemperature(BlockPos{xStart, yPos, zStart}) < 0.15F) {
                            blockstate = ICE;
                        } else {
                            blockstate = defaultFluid;
                        }
                    }

                    i = j;
                    if (yPos >= sealevel - 1) {
                        chunk.setData(xPos, yPos, zPos, blockstate/*, false*/);
                    } else if (yPos < sealevel - 7 - j) {
                        blockstate = AIR;
                        blockstate1 = defaultBlock;
                        chunk.setData(xPos, yPos, zPos, underWater/*, false*/);
                    } else {
                        chunk.setData(xPos, yPos, zPos, blockstate1/*, false*/);
                    }
                } else if (i > 0) {
                    --i;
                    chunk.setData(xPos, yPos, zPos, blockstate1/*, false*/);
                    if (i == 0 && blockstate1.is(Blocks::SAND) && j > 1) {
                        i = rand.nextInt(4) + std::max(0, yPos - 63);
                        blockstate1 = blockstate1.is(Blocks::RED_SAND)
                                        ? Blocks::RED_SAND->getDefaultState()
                                        : Blocks::SANDSTONE->getDefaultState();
                    }
                }
            }
        }
    }
};

struct MountainSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        if (noise > 1.0) {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
        } else {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
        }
    }
};

struct ShatteredSavannaSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        if (noise > 1.75) {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
        } else if (noise > -0.5) {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::CORASE_DIRT_DIRT_GRAVEL_CONFIG);
        } else {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
        }
    }
};

struct GravellyMountainSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        if (noise < -1.0 || noise > 2.0) {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::GRAVEL_CONFIG);
        } else if (noise > 1.0) {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::STONE_STONE_GRAVEL_CONFIG);
        } else {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
        }
    }
};

struct GiantTreeTaigaSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        if (noise > 1.75) {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::CORASE_DIRT_DIRT_GRAVEL_CONFIG);
        } else if (noise > -0.95) {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::PODZOL_DIRT_GRAVEL_CONFIG);
        } else {
            Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, SurfaceBuilderConfig::GRASS_DIRT_GRAVEL_CONFIG);
        }
    }
};

struct SwampSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        const double d0 = Biome::INFO_NOISE.noiseAt((double)xStart * 0.25, (double)zStart * 0.25, false);
        if (d0 > 0.0) {
            const int i = xStart & 15;
            const int j = zStart & 15;

            for(int k = startHeight; k >= 0; --k) {
                if (!chunk.getData(i, k, j).isAir()) {
                    if (k == 62 && !chunk.getData(i, k, j).is(defaultFluid.getBlock())) {
                        chunk.setData(i, k, j, defaultFluid/*, false*/);
                    }
                    break;
                }
            }
        }

        Default->buildSurface(rand, chunk, biome, xStart, zStart, startHeight, noise, defaultBlock, defaultFluid, seaLevel, config);
    }
};

struct BadlandsSurfaceBuilder : public SurfaceBuilder {
    const BlockData AIR = Blocks::AIR->getDefaultState();
    const BlockData TERRACOTTA = Blocks::TERRACOTTA->getDefaultState();
    const BlockData WHITE_TERRACOTTA = Blocks::WHITE_TERRACOTTA->getDefaultState();
    const BlockData ORANGE_TERRACOTTA = Blocks::ORANGE_TERRACOTTA->getDefaultState();
    const BlockData MAGENTA_TERRACOTTA = Blocks::MAGENTA_TERRACOTTA->getDefaultState();
    const BlockData LIGHT_BLUE_TERRACOTTA = Blocks::LIGHT_BLUE_TERRACOTTA->getDefaultState();
    const BlockData YELLOW_TERRACOTTA = Blocks::YELLOW_TERRACOTTA->getDefaultState();
    const BlockData LIME_TERRACOTTA = Blocks::LIME_TERRACOTTA->getDefaultState();
    const BlockData PINK_TERRACOTTA = Blocks::PINK_TERRACOTTA->getDefaultState();
    const BlockData GRAY_TERRACOTTA = Blocks::GRAY_TERRACOTTA->getDefaultState();
    const BlockData LIGHT_GRAY_TERRACOTTA = Blocks::LIGHT_GRAY_TERRACOTTA->getDefaultState();
    const BlockData CYAN_TERRACOTTA = Blocks::CYAN_TERRACOTTA->getDefaultState();
    const BlockData PURPLE_TERRACOTTA = Blocks::PURPLE_TERRACOTTA->getDefaultState();
    const BlockData BLUE_TERRACOTTA = Blocks::BLUE_TERRACOTTA->getDefaultState();
    const BlockData BROWN_TERRACOTTA = Blocks::BROWN_TERRACOTTA->getDefaultState();
    const BlockData GREEN_TERRACOTTA = Blocks::GREEN_TERRACOTTA->getDefaultState();
    const BlockData RED_TERRACOTTA = Blocks::RED_TERRACOTTA->getDefaultState();
    const BlockData BLACK_TERRACOTTA = Blocks::BLACK_TERRACOTTA->getDefaultState();

    struct Cache {
        std::optional<int64_t> seed = std::nullopt;
        std::optional<PerlinNoiseGenerator> noise1 = std::nullopt;
        std::optional<PerlinNoiseGenerator> noise2 = std::nullopt;
        std::optional<PerlinNoiseGenerator> noise3 = std::nullopt;
        std::array<BlockData, 64> clayBands;

        void setSeed(int64_t _seed) {
            if (seed != _seed) {
                seed = _seed;

                generateBands(_seed);

                auto rand = Random::from(_seed);
                noise1.emplace(rand, ranges::views::iota(-3, 1));
                noise2.emplace(rand, ranges::views::single(0));
            }
        }

        void generateBands(int64_t _seed) {
            const BlockData AIR = Blocks::AIR->getDefaultState();
            const BlockData TERRACOTTA = Blocks::TERRACOTTA->getDefaultState();
            const BlockData WHITE_TERRACOTTA = Blocks::WHITE_TERRACOTTA->getDefaultState();
            const BlockData ORANGE_TERRACOTTA = Blocks::ORANGE_TERRACOTTA->getDefaultState();
            const BlockData MAGENTA_TERRACOTTA = Blocks::MAGENTA_TERRACOTTA->getDefaultState();
            const BlockData LIGHT_BLUE_TERRACOTTA = Blocks::LIGHT_BLUE_TERRACOTTA->getDefaultState();
            const BlockData YELLOW_TERRACOTTA = Blocks::YELLOW_TERRACOTTA->getDefaultState();
            const BlockData LIME_TERRACOTTA = Blocks::LIME_TERRACOTTA->getDefaultState();
            const BlockData PINK_TERRACOTTA = Blocks::PINK_TERRACOTTA->getDefaultState();
            const BlockData GRAY_TERRACOTTA = Blocks::GRAY_TERRACOTTA->getDefaultState();
            const BlockData LIGHT_GRAY_TERRACOTTA = Blocks::LIGHT_GRAY_TERRACOTTA->getDefaultState();
            const BlockData CYAN_TERRACOTTA = Blocks::CYAN_TERRACOTTA->getDefaultState();
            const BlockData PURPLE_TERRACOTTA = Blocks::PURPLE_TERRACOTTA->getDefaultState();
            const BlockData BLUE_TERRACOTTA = Blocks::BLUE_TERRACOTTA->getDefaultState();
            const BlockData BROWN_TERRACOTTA = Blocks::BROWN_TERRACOTTA->getDefaultState();
            const BlockData GREEN_TERRACOTTA = Blocks::GREEN_TERRACOTTA->getDefaultState();
            const BlockData RED_TERRACOTTA = Blocks::RED_TERRACOTTA->getDefaultState();
            const BlockData BLACK_TERRACOTTA = Blocks::BLACK_TERRACOTTA->getDefaultState();

            clayBands.fill(TERRACOTTA);

            auto rand = Random::from(_seed);

            noise3.emplace(rand, ranges::views::single(0));

            for (int i = 0; i < 64; ++i) {
                i += rand.nextInt(5) + 1;
                if (i < 64) {
                    clayBands[i] = ORANGE_TERRACOTTA;
                }
            }

            const int yellowCount = rand.nextInt(4) + 2;
            for (int i = 0; i < yellowCount; ++i) {
                const int j = rand.nextInt(3) + 1;
                const int k = rand.nextInt(64);

                for (int l = 0; k + l < 64 && l < j; ++l) {
                    clayBands[k + l] = YELLOW_TERRACOTTA;
                }
            }

            const int brownCount = rand.nextInt(4) + 2;
            for (int i = 0; i < brownCount; ++i) {
                const int j = rand.nextInt(3) + 2;
                const int k = rand.nextInt(64);

                for (int l = 0; k + l < 64 && l < j; ++l) {
                    clayBands[k + l] = BROWN_TERRACOTTA;
                }
            }

            const int redCount = rand.nextInt(4) + 2;
            for (int i = 0; i < redCount; ++i) {
                const int j = rand.nextInt(3) + 1;
                const int k = rand.nextInt(64);

                for (int l = 0; k + l < 64 && l < j; ++l) {
                    clayBands[k + l] = RED_TERRACOTTA;
                }
            }

            const int count = rand.nextInt(3) + 3;
            int j = 0;
            for (int i = 0; i < count; ++i) {
                j += rand.nextInt(16) + 4;

                for (int k = 0; j + k < 64 && k < 1; ++k) {
                    clayBands[j + k] = WHITE_TERRACOTTA;
                    if (j + k > 1 && rand.nextBoolean()) {
                        clayBands[j + k - 1] = LIGHT_GRAY_TERRACOTTA;
                    }

                    if (j + k < 63 && rand.nextBoolean()) {
                        clayBands[j + k + 1] = LIGHT_GRAY_TERRACOTTA;
                    }
                }
            }
        }

        BlockData getClay(int x, int y, int z) {
            const int i = static_cast<int>(std::round(noise3->noiseAt(static_cast<double>(x) / 512.0, static_cast<double>(z) / 512.0, false) * 2.0));
            return clayBands[(y + i + 64) % 64];
        }
    };

    ThreadLocal<Cache> cache{};

    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        const auto xpos = xStart & 15;
        const auto zpos = zStart & 15;
        const auto biomeSurfaceConfig = biome.getGenerationSettings().getSurfaceBuilderConfig();
        const auto underBlockDefault = biomeSurfaceConfig.getUnder();
        const auto topBlockDefault = biomeSurfaceConfig.getTop();
        auto underBlock = underBlockDefault;
        auto topBlock = WHITE_TERRACOTTA;
        const auto k = static_cast<int>(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
        bool flag = std::cos(noise / 3.0 * M_PI) > 0.0;
        int l = -1;
        bool flag1 = false;
        int i1 = 0;

        auto& clayBands = getClayBands();

        for(int j1 = startHeight; j1 >= 0; --j1) {
            if (i1 < 15) {
                const auto blockpos = BlockPos::from(xpos, j1, zpos);
                const auto data = chunk.getData(blockpos);
                if (data.isAir()) {
                    l = -1;
                } else if (data.is(defaultBlock.getBlock())) {
                    if (l == -1) {
                        flag1 = false;
                        if (k <= 0) {
                            topBlock = AIR;
                            underBlock = defaultBlock;
                        } else if (j1 >= seaLevel - 4 && j1 <= seaLevel + 1) {
                            topBlock = WHITE_TERRACOTTA;
                            underBlock = underBlockDefault;
                        }

                        if (j1 < seaLevel && topBlock.isAir()) {
                            topBlock = defaultFluid;
                        }

                        l = k + std::max(0, j1 - seaLevel);
                        if (j1 >= seaLevel - 1) {
                            if (j1 > seaLevel + 3 + k) {
                                auto blockstate5 = ORANGE_TERRACOTTA;
                                if (j1 >= 64 && j1 <= 127) {
                                    if (flag) {
                                        blockstate5 = TERRACOTTA;
                                    } else {
                                        blockstate5 = clayBands.getClay(xStart, j1, zStart);
                                    }
                                }

                                chunk.setData(blockpos, blockstate5/*, false*/);
                            } else {
                                chunk.setData(blockpos, topBlockDefault/*, false*/);
                                flag1 = true;
                            }
                        } else {
                            chunk.setData(blockpos, underBlock/*, false*/);
                            auto block = underBlock.getBlock();
                            if (block == Blocks::WHITE_TERRACOTTA ||
                                block == Blocks::ORANGE_TERRACOTTA ||
                                block == Blocks::MAGENTA_TERRACOTTA ||
                                block == Blocks::LIGHT_BLUE_TERRACOTTA ||
                                block == Blocks::YELLOW_TERRACOTTA ||
                                block == Blocks::LIME_TERRACOTTA ||
                                block == Blocks::PINK_TERRACOTTA ||
                                block == Blocks::GRAY_TERRACOTTA ||
                                block == Blocks::LIGHT_GRAY_TERRACOTTA ||
                                block == Blocks::CYAN_TERRACOTTA ||
                                block == Blocks::PURPLE_TERRACOTTA ||
                                block == Blocks::BLUE_TERRACOTTA ||
                                block == Blocks::BROWN_TERRACOTTA ||
                                block == Blocks::GREEN_TERRACOTTA ||
                                block == Blocks::RED_TERRACOTTA ||
                                block == Blocks::BLACK_TERRACOTTA) {
                                chunk.setData(blockpos, ORANGE_TERRACOTTA/*, false*/);
                            }
                        }
                    } else if (l > 0) {
                        --l;
                        if (flag1) {
                            chunk.setData(blockpos, ORANGE_TERRACOTTA/*, false*/);
                        } else {
                            chunk.setData(blockpos, clayBands.getClay(xStart, j1, zStart)/*, false*/);
                        }
                    }

                    ++i1;
                }
            }
        }
    }

    Cache& getClayBands() {
        if (!cache.has_value()) {
            cache.set(new Cache());
        }
        return *cache.get();
    }

    void setSeed(int64_t _seed) override {
        getClayBands().setSeed(_seed);
    }
};

struct WoodedBadlandsSurfaceBuilder : public BadlandsSurfaceBuilder {
    const BlockData GRASS_BLOCK = Blocks::GRASS_BLOCK->getDefaultState();
    const BlockData COARSE_DIRT = Blocks::COARSE_DIRT->getDefaultState();

    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        const auto xpos = xStart & 15;
        const auto zpos = zStart & 15;
        const auto biomeSurfaceConfig = biome.getGenerationSettings().getSurfaceBuilderConfig();
        const auto underBlockDefault = biomeSurfaceConfig.getUnder();
        const auto topBlockDefault = biomeSurfaceConfig.getTop();
        auto underBlock = underBlockDefault;
        auto topBlock = WHITE_TERRACOTTA;
        const auto k = static_cast<int>(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
        const auto flag = std::cos(noise / 3.0 * M_PI) > 0.0;
        int l = -1;
        bool flag1 = false;
        int i1 = 0;

        auto& clayBands = getClayBands();

        for (int j1 = startHeight; j1 >= 0; --j1) {
            if (i1 < 15) {
                const auto blockpos = BlockPos::from(xpos, j1, zpos);
                const auto data = chunk.getData(blockpos);
                if (data.isAir()) {
                    l = -1;
                } else if (data.is(defaultBlock.getBlock())) {
                    if (l == -1) {
                        flag1 = false;
                        if (k <= 0) {
                            topBlock = AIR;
                            underBlock = defaultBlock;
                        } else if (j1 >= seaLevel - 4 && j1 <= seaLevel + 1) {
                            topBlock = WHITE_TERRACOTTA;
                            underBlock = underBlockDefault;
                        }

                        if (j1 < seaLevel && topBlock.isAir()) {
                            topBlock = defaultFluid;
                        }

                        l = k + std::max(0, j1 - seaLevel);
                        if (j1 >= seaLevel - 1) {
                            if (j1 > 86 + k * 2) {
                                if (flag) {
                                    chunk.setData(blockpos, COARSE_DIRT/*, false*/);
                                } else {
                                    chunk.setData(blockpos, GRASS_BLOCK/*, false*/);
                                }
                            } else if (j1 > seaLevel + 3 + k) {
                                auto blockstate5 = ORANGE_TERRACOTTA;
                                if (j1 >= 64 && j1 <= 127) {
                                    if (flag) {
                                        blockstate5 = TERRACOTTA;
                                    } else {
                                        blockstate5 = clayBands.getClay(xStart, j1, zStart);
                                    }
                                }

                                chunk.setData(blockpos, blockstate5/*, false*/);
                            } else {
                                chunk.setData(blockpos, topBlockDefault/*, false*/);
                                flag1 = true;
                            }
                        } else {
                            if (underBlock == WHITE_TERRACOTTA) {
                                chunk.setData(blockpos, ORANGE_TERRACOTTA/*, false*/);
                            } else {
                                chunk.setData(blockpos, underBlock/*, false*/);
                            }
                        }
                    } else if (l > 0) {
                        --l;
                        if (flag1) {
                            chunk.setData(blockpos, ORANGE_TERRACOTTA/*, false*/);
                        } else {
                            chunk.setData(blockpos, clayBands.getClay(xStart, j1, zStart)/*, false*/);
                        }
                    }

                    ++i1;
                }
            }
        }
    }
};

struct ErodedBadlandsSurfaceBuilder : public BadlandsSurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        auto& clayBands = getClayBands();

        double d0 = 0.0;
        const double d1 = std::min(std::abs(noise), clayBands.noise1->noiseAt(static_cast<double>(xStart) * 0.25, static_cast<double>(zStart) * 0.25, false) * 15.0);
        if (d1 > 0.0) {
            const double d3 = std::abs(clayBands.noise2->noiseAt(static_cast<double>(xStart) * 0.001953125, static_cast<double>(zStart) * 0.001953125, false));
            d0 = d1 * d1 * 2.5;
            const double d4 = std::ceil(d3 * 50.0) + 14.0;
            if (d0 > d4) {
                d0 = d4;
            }

            d0 = d0 + 64.0;
        }

        const auto xpos = xStart & 15;
        const auto zpos = zStart & 15;
        const auto biomeSurfaceConfig = biome.getGenerationSettings().getSurfaceBuilderConfig();
        const auto underBlockDefault = biomeSurfaceConfig.getUnder();
        const auto topBlockDefault = biomeSurfaceConfig.getTop();
        auto underBlock = underBlockDefault;
        auto topBlock = WHITE_TERRACOTTA;
        const auto j = static_cast<int>(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
        const auto flag = std::cos(noise / 3.0 * M_PI) > 0.0;
        int k = -1;
        bool flag1 = false;

        for(int l = std::max(startHeight, static_cast<int>(d0) + 1); l >= 0; --l) {
            const auto blockpos = BlockPos::from(xpos, l, zpos);
            const auto data = chunk.getData(blockpos);
            if (data.isAir() && l < static_cast<int>(d0)) {
                chunk.setData(blockpos, defaultBlock/*, false*/);
            }

            if (data.isAir()) {
                k = -1;
            } else if (data.is(defaultBlock.getBlock())) {
                if (k == -1) {
                    flag1 = false;
                    if (j <= 0) {
                        topBlock = AIR;
                        underBlock = defaultBlock;
                    } else if (l >= seaLevel - 4 && l <= seaLevel + 1) {
                        topBlock = WHITE_TERRACOTTA;
                        underBlock = underBlockDefault;
                    }

                    if (l < seaLevel && topBlock.isAir()) {
                        topBlock = defaultFluid;
                    }

                    k = j + std::max(0, l - seaLevel);
                    if (l >= seaLevel - 1) {
                        if (l <= seaLevel + 3 + j) {
                            chunk.setData(blockpos, topBlockDefault/*, false*/);
                            flag1 = true;
                        } else {
                            auto blockstate5 = ORANGE_TERRACOTTA;
                            if (l >= 64 && l <= 127) {
                                if (flag) {
                                    blockstate5 = TERRACOTTA;
                                } else {
                                    blockstate5 = clayBands.getClay(xStart, l, zStart);
                                }
                            }

                            chunk.setData(blockpos, blockstate5/*, false*/);
                        }
                    } else {
                        chunk.setData(blockpos, underBlock/*, false*/);
                        auto block = underBlock.getBlock();
                        if (block == Blocks::WHITE_TERRACOTTA ||
                            block == Blocks::ORANGE_TERRACOTTA ||
                            block == Blocks::MAGENTA_TERRACOTTA ||
                            block == Blocks::LIGHT_BLUE_TERRACOTTA ||
                            block == Blocks::YELLOW_TERRACOTTA ||
                            block == Blocks::LIME_TERRACOTTA ||
                            block == Blocks::PINK_TERRACOTTA ||
                            block == Blocks::GRAY_TERRACOTTA ||
                            block == Blocks::LIGHT_GRAY_TERRACOTTA ||
                            block == Blocks::CYAN_TERRACOTTA ||
                            block == Blocks::PURPLE_TERRACOTTA ||
                            block == Blocks::BLUE_TERRACOTTA ||
                            block == Blocks::BROWN_TERRACOTTA ||
                            block == Blocks::GREEN_TERRACOTTA ||
                            block == Blocks::RED_TERRACOTTA ||
                            block == Blocks::BLACK_TERRACOTTA) {
                            chunk.setData(blockpos, ORANGE_TERRACOTTA/*, false*/);
                        }
                    }
                } else if (k > 0) {
                    --k;
                    if (flag1) {
                        chunk.setData(blockpos, ORANGE_TERRACOTTA/*, false*/);
                    } else {
                        chunk.setData(blockpos, clayBands.getClay(xStart, l, zStart)/*, false*/);
                    }
                }
            }
        }
    }
};

struct FrozenOceanSurfaceBuilder : public SurfaceBuilder {
    const BlockData AIR = Blocks::AIR->getDefaultState();
    const BlockData ICE = Blocks::ICE->getDefaultState();
    const BlockData PACKED_ICE = Blocks::PACKED_ICE->getDefaultState();
    const BlockData SNOW_BLOCK = Blocks::SNOW_BLOCK->getDefaultState();
    const BlockData GRAVEL = Blocks::GRAVEL->getDefaultState();

    struct Cache {
        std::optional<int64_t> seed = std::nullopt;
        std::optional<PerlinNoiseGenerator> noise1 = std::nullopt;
        std::optional<PerlinNoiseGenerator> noise2 = std::nullopt;

        void setSeed(int64_t _seed) {
            if (seed != _seed) {
                seed = _seed;

                auto rand = Random::from(_seed);
                noise1.emplace(rand, ranges::views::iota(-3, 1));
                noise2.emplace(rand, ranges::views::single(0));
            }
        }
    };

    ThreadLocal<Cache> cache{};

    Cache& getCache() {
        if (!cache.has_value()) {
            cache.set(new Cache());
        }
        return *cache.get();
    }

    void setSeed(int64_t _seed) override {
        getCache().setSeed(_seed);
    }

    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
        auto& _cache = getCache();

        double d0 = 0.0;
        double d1 = 0.0;
        const float temperature = biome.getTemperature(BlockPos{xStart, 63, zStart});
        const double d2 = std::min(std::abs(noise), _cache.noise1->noiseAt(static_cast<double>(xStart) * 0.1, static_cast<double>(zStart) * 0.1, false) * 15.0);

        if (d2 > 1.8) {
            const double d4 = std::abs(_cache.noise2->noiseAt(static_cast<double>(xStart) * 0.09765625, static_cast<double>(zStart) * 0.09765625, false));

            d0 = d2 * d2 * 1.2;
            const double d5 = std::ceil(d4 * 40.0) + 14.0;
            if (d0 > d5) {
                d0 = d5;
            }

            if (temperature > 0.1F) {
                d0 -= 2.0;
            }

            if (d0 > 2.0) {
                d1 = static_cast<double>(seaLevel) - d0 - 7.0;
                d0 = d0 + static_cast<double>(seaLevel);
            } else {
                d0 = 0.0;
            }
        }

        const auto xpos = xStart & 15;
        const auto zpos = zStart & 15;
        const auto biomeSurfaceConfig = biome.getGenerationSettings().getSurfaceBuilderConfig();
        const auto midDefault = biomeSurfaceConfig.getUnder();
        const auto topDefault = biomeSurfaceConfig.getTop();
        auto blockstate1 = midDefault;
        auto blockstate2 = topDefault;
        const auto j = static_cast<int>(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
        int k = -1;
        int l = 0;
        const auto i1 = 2 + rand.nextInt(4);
        const auto j1 = seaLevel + 18 + rand.nextInt(10);

        for (int k1 = std::max(startHeight, static_cast<int>(d0) + 1); k1 >= 0; --k1) {
            const auto blockpos = BlockPos::from(xpos, k1, zpos);
            auto data = chunk.getData(blockpos);
            if (data.isAir() && k1 < static_cast<int>(d0) && rand.nextDouble() > 0.01) {
                chunk.setData(blockpos, PACKED_ICE/*, false*/);
            } else if (data.getBlock()->getMaterial() == Materials::WATER && k1 > static_cast<int>(d1) && k1 < seaLevel && d1 != 0.0 && rand.nextDouble() > 0.15) {
                chunk.setData(blockpos, PACKED_ICE/*, false*/);
            }
            data = chunk.getData(blockpos);
            if (data.isAir()) {
                k = -1;
            } else if (!data.is(defaultBlock.getBlock())) {
                if (data.is(Blocks::PACKED_ICE) && l <= i1 && k1 > j1) {
                    chunk.setData(blockpos, SNOW_BLOCK/*, false*/);
                    ++l;
                }
            } else if (k == -1) {
                if (j <= 0) {
                    blockstate2 = AIR;
                    blockstate1 = defaultBlock;
                } else if (k1 >= seaLevel - 4 && k1 <= seaLevel + 1) {
                    blockstate2 = topDefault;
                    blockstate1 = midDefault;
                }

                if (k1 < seaLevel && blockstate2.isAir()) {
                    if (biome.getTemperature(BlockPos{xStart, k1, zStart}) < 0.15F) {
                        blockstate2 = ICE;
                    } else {
                        blockstate2 = defaultFluid;
                    }
                }

                k = j;
                if (k1 >= seaLevel - 1) {
                    chunk.setData(blockpos, blockstate2/*, false*/);
                } else if (k1 < seaLevel - 7 - j) {
                    blockstate2 = AIR;
                    blockstate1 = defaultBlock;
                    chunk.setData(blockpos, GRAVEL/*, false*/);
                } else {
                    chunk.setData(blockpos, blockstate1/*, false*/);
                }
            } else if (k > 0) {
                --k;
                chunk.setData(blockpos, blockstate1/*, false*/);
                if (k == 0 && blockstate1.is(Blocks::SAND) && j > 1) {
                    k = rand.nextInt(4) + std::max(0, k1 - 63);
                    blockstate1 = blockstate1.is(Blocks::RED_SAND)
                                    ? Blocks::RED_SANDSTONE->getDefaultState()
                                    : Blocks::SANDSTONE->getDefaultState();
                }
            }
        }
    }
};

struct NetherSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
    }
};

struct NetherForestsSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
    }
};

struct SoulSandValleySurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
    }
};

struct BasaltDeltasSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(Random& rand, Chunk& chunk, Biome& biome, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, int seaLevel, SurfaceBuilderConfig config) override {
    }
};

template <typename T, typename... Args>
static auto create(std::string name, Args&&... args) -> T* {
    return dynamic_cast<T*>(SurfaceBuilder::builders.add(std::move(name), std::make_unique<T>(std::forward<Args>(args)...)));
}

void SurfaceBuilder::init() {
    Noop             = create<NoopSurfaceBuilder>("noop");
    Default          = create<DefaultSurfaceBuilder>("default");
    Mountain         = create<MountainSurfaceBuilder>("mountain");
    ShatteredSavanna = create<ShatteredSavannaSurfaceBuilder>("shattered_savanna");
    GravellyMountain = create<GravellyMountainSurfaceBuilder>("gravelly_mountain");
    GiantTreeTaiga   = create<GiantTreeTaigaSurfaceBuilder>("giant_tree_taiga");
    Swamp            = create<SwampSurfaceBuilder>("swamp");
    Badlands         = create<BadlandsSurfaceBuilder>("badlands");
    WoodedBadlands   = create<WoodedBadlandsSurfaceBuilder>("wooded_badlands");
    ErodedBadlands   = create<ErodedBadlandsSurfaceBuilder>("eroded_badlands");
    FrozenOcean      = create<FrozenOceanSurfaceBuilder>("frozen_ocean");
    Nether           = create<NetherSurfaceBuilder>("nether");
    NetherForest     = create<NetherForestsSurfaceBuilder>("nether_forest");
    SoulSandValley   = create<SoulSandValleySurfaceBuilder>("soul_sand_valley");
    BasaltDeltas     = create<BasaltDeltasSurfaceBuilder>("basalt_deltas");
}
