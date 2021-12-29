#include "SurfaceBuilders.hpp"
#include "SurfaceBuilder.hpp"
#include "../PerlinNoiseGenerator.hpp"
#include "../../biome/Biome.hpp"
#include "../../chunk/Chunk.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/material/Materials.hpp"

#include "ThreadLocal.hpp"
#include <block/States.hpp>

#include <cmath>
#include <Json.hpp>

Registry<SurfaceBuilder> SurfaceBuilders::builders;

SurfaceBuilder* SurfaceBuilders::Noop;
SurfaceBuilder* SurfaceBuilders::Default;
SurfaceBuilder* SurfaceBuilders::Mountain;
SurfaceBuilder* SurfaceBuilders::ShatteredSavanna;
SurfaceBuilder* SurfaceBuilders::GravellyMountain;
SurfaceBuilder* SurfaceBuilders::GiantTreeTaiga;
SurfaceBuilder* SurfaceBuilders::Swamp;
SurfaceBuilder* SurfaceBuilders::Badlands;
SurfaceBuilder* SurfaceBuilders::WoodedBadlands;
SurfaceBuilder* SurfaceBuilders::ErodedBadlands;
SurfaceBuilder* SurfaceBuilders::FrozenOcean;
SurfaceBuilder* SurfaceBuilders::Nether;
SurfaceBuilder* SurfaceBuilders::NetherForest;
SurfaceBuilder* SurfaceBuilders::SoulSandValley;
SurfaceBuilder* SurfaceBuilders::BasaltDeltas;

struct NoopSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
    }
};

struct DefaultSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
        auto topBlock = config.getTop();
        auto underBlock = config.getUnder();

        int i = -1;
        const auto j = static_cast<int>(ctx.noise / 3.0 + 3.0 + ctx.random.nextDouble() * 0.25);

        for (auto pos = ctx.pos; pos.y >= 0; --pos.y) {
            const auto state = ctx.chunk.getData(pos);
            if (state.isAir()) {
                i = -1;
                continue;
            }

            if (state.is(ctx.block.getBlock())) {
                if (i == -1) {
                    if (j <= 0) {
                        topBlock = States::AIR;
                        underBlock = ctx.block;
                    } else if (pos.y >= ctx.seaLevel - 4 && pos.y <= ctx.seaLevel + 1) {
                        topBlock = config.getTop();
                        underBlock = config.getUnder();
                    }

                    if (pos.y < ctx.seaLevel && topBlock.isAir()) {
                        if (ctx.biome.getTemperature(pos) < 0.15F) {
                            topBlock = States::ICE;
                        } else {
                            topBlock = ctx.fluid;
                        }
                    }

                    i = j;
                    if (pos.y >= ctx.seaLevel - 1) {
                        ctx.chunk.setData(pos, topBlock/*, false*/);
                    } else if (pos.y < ctx.seaLevel - 7 - j) {
                        topBlock = States::AIR;
                        underBlock = ctx.block;
                        ctx.chunk.setData(pos, config.getUnderWaterMaterial()/*, false*/);
                    } else {
                        ctx.chunk.setData(pos, underBlock/*, false*/);
                    }
                } else if (i > 0) {
                    --i;
                    ctx.chunk.setData(pos, underBlock/*, false*/);
                    if (i == 0 && underBlock.is(Blocks::SAND) && j > 1) {
                        i = ctx.random.nextInt(4) + std::max(0, pos.y - 63);
                        underBlock = underBlock.is(Blocks::RED_SAND) ? States::RED_SAND : States::SANDSTONE;
                    }
                }
            }
        }
    }
};

struct MultiConfigSurfaceBuilder : public SurfaceBuilder {
    using GetConfig = auto(*)(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) -> SurfaceBuilderConfig;

    SurfaceBuilder* builder;
    GetConfig getConfig;

    MultiConfigSurfaceBuilder(SurfaceBuilder* builder, GetConfig getConfig) : builder(builder), getConfig(getConfig) {}

    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
        builder->buildSurface(ctx, getConfig(ctx, config));
    }
};

struct SwampSurfaceBuilder : public SurfaceBuilder {
    SurfaceBuilder* builder;

    SwampSurfaceBuilder(SurfaceBuilder* builder) : builder(builder) {}

    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
        const auto noise = Biome::INFO_NOISE.noiseAt(
            static_cast<double>(ctx.pos.x) * 0.25,
            static_cast<double>(ctx.pos.z) * 0.25,
            false
        );

        if (noise > 0.0) {
            for (auto pos = ctx.pos; pos.y >= 0; --pos.y) {
                if (!ctx.chunk.getData(pos).isAir()) {
                    if (pos.y == 62 && !ctx.chunk.getData(pos).is(ctx.fluid.getBlock())) {
                        ctx.chunk.setData(pos, ctx.fluid/*, false*/);
                    }
                    break;
                }
            }
        }

        builder->buildSurface(ctx, config);
    }
};

struct BadlandsSurfaceBuilder : public SurfaceBuilder {
    struct Cache {
        tl::optional<int64_t> seed = tl::nullopt;
        tl::optional<PerlinNoiseGenerator> noise1 = tl::nullopt;
        tl::optional<PerlinNoiseGenerator> noise2 = tl::nullopt;
        tl::optional<PerlinNoiseGenerator> noise3 = tl::nullopt;
        std::array<BlockData, 64> clayBands;

        void setSeed(int64_t _seed) {
            if (seed != _seed) {
                seed = _seed;

                generateBands(_seed);

                auto random = Random::from(_seed);
                noise1.emplace(random, ranges::views::iota(-3, 1));
                noise2.emplace(random, ranges::views::single(0));
            }
        }

        void generateBands(int64_t _seed) {
            clayBands.fill(States::TERRACOTTA);

            auto random = Random::from(_seed);

            noise3.emplace(random, ranges::views::single(0));

            for (int i = 0; i < 64; ++i) {
                i += random.nextInt(5) + 1;
                if (i < 64) {
                    clayBands[i] = States::ORANGE_TERRACOTTA;
                }
            }

            const auto yellowCount = random.nextInt(4) + 2;
            for (int i = 0; i < yellowCount; ++i) {
                const int j = random.nextInt(3) + 1;
                const int k = random.nextInt(64);

                for (int l = 0; k + l < 64 && l < j; ++l) {
                    clayBands[k + l] = States::YELLOW_TERRACOTTA;
                }
            }

            const auto brownCount = random.nextInt(4) + 2;
            for (int i = 0; i < brownCount; ++i) {
                const auto j = random.nextInt(3) + 2;
                const auto k = random.nextInt(64);

                for (int l = 0; k + l < 64 && l < j; ++l) {
                    clayBands[k + l] = States::BROWN_TERRACOTTA;
                }
            }

            const auto redCount = random.nextInt(4) + 2;
            for (int i = 0; i < redCount; ++i) {
                const auto j = random.nextInt(3) + 1;
                const auto k = random.nextInt(64);

                for (int l = 0; k + l < 64 && l < j; ++l) {
                    clayBands[k + l] = States::RED_TERRACOTTA;
                }
            }

            const auto count = random.nextInt(3) + 3;
            int j = 0;
            for (int i = 0; i < count; ++i) {
                j += random.nextInt(16) + 4;

                for (int k = 0; j + k < 64 && k < 1; ++k) {
                    clayBands[j + k] = States::WHITE_TERRACOTTA;
                    if (j + k > 1 && random.nextBoolean()) {
                        clayBands[j + k - 1] = States::LIGHT_GRAY_TERRACOTTA;
                    }

                    if (j + k < 63 && random.nextBoolean()) {
                        clayBands[j + k + 1] = States::LIGHT_GRAY_TERRACOTTA;
                    }
                }
            }
        }

        auto getClay(const BlockPos& pos) -> BlockData {
            const auto noise = noise3->noiseAt(
                static_cast<double>(pos.x) / 512.0,
                static_cast<double>(pos.z) / 512.0,
                false
            );
            const auto i = static_cast<int>(std::round(noise * 2.0));
            return clayBands[(pos.y + i + 64) % 64];
        }
    };

    ThreadLocal<Cache> cache{};

    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
        const auto biomeSurfaceConfig = ctx.biome.getGenerationSettings().getSurfaceBuilderConfig();
        auto underBlock = biomeSurfaceConfig.getUnder();
        auto topBlock = States::WHITE_TERRACOTTA;
        const auto k = static_cast<int>(ctx.noise / 3.0 + 3.0 + ctx.random.nextDouble() * 0.25);
        const auto flag = std::cos(ctx.noise / 3.0 * M_PI) > 0.0;
        int l = -1;
        bool flag1 = false;
        int i1 = 0;

        auto& clayBands = getClayBands();

        for (auto pos = ctx.pos; pos.y >= 0 && i1 < 15; --pos.y, ++i1) {
            const auto data = ctx.chunk.getData(pos);
            if (data.isAir()) {
                l = -1;
            } else if (data.is(ctx.block.getBlock())) {
                if (l == -1) {
                    flag1 = false;
                    if (k <= 0) {
                        topBlock = States::AIR;
                        underBlock = ctx.block;
                    } else if (pos.y >= ctx.seaLevel - 4 && pos.y <= ctx.seaLevel + 1) {
                        topBlock = States::WHITE_TERRACOTTA;
                        underBlock = biomeSurfaceConfig.getUnder();
                    }

                    if (pos.y < ctx.seaLevel && topBlock.isAir()) {
                        topBlock = ctx.fluid;
                    }

                    l = k + std::max(0, pos.y - ctx.seaLevel);
                    if (pos.y >= ctx.seaLevel - 1) {
                        if (pos.y > ctx.seaLevel + 3 + k) {
                            const auto clay = pos.y >= 64 && pos.y <= 127
                                            ? flag ? States::TERRACOTTA : clayBands.getClay(pos)
                                            : States::ORANGE_TERRACOTTA;

                            ctx.chunk.setData(pos, clay/*, false*/);
                        } else {
                            ctx.chunk.setData(pos, biomeSurfaceConfig.getTop()/*, false*/);
                            flag1 = true;
                        }
                    } else {
                        ctx.chunk.setData(pos, underBlock/*, false*/);
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
                            ctx.chunk.setData(pos, States::ORANGE_TERRACOTTA/*, false*/);
                        }
                    }
                } else if (l > 0) {
                    --l;

                    const auto clay = flag1 ? States::ORANGE_TERRACOTTA : clayBands.getClay(pos);
                    ctx.chunk.setData(pos, clay/*, false*/);
                }
            }
        }
    }

    auto getClayBands() -> Cache& {
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
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
        const auto biomeSurfaceConfig = ctx.biome.getGenerationSettings().getSurfaceBuilderConfig();
        auto underBlock = biomeSurfaceConfig.getUnder();
        auto topBlock = States::WHITE_TERRACOTTA;
        const auto k = static_cast<int>(ctx.noise / 3.0 + 3.0 + ctx.random.nextDouble() * 0.25);
        const auto flag = std::cos(ctx.noise / 3.0 * M_PI) > 0.0;
        int l = -1;
        bool flag1 = false;
        int i1 = 0;

        auto& clayBands = getClayBands();

        for (auto pos = ctx.pos; pos.y >= 0 && i1 < 15; --pos.y, ++i1) {
            const auto data = ctx.chunk.getData(pos);
            if (data.isAir()) {
                l = -1;
            } else if (data.is(ctx.block.getBlock())) {
                if (l == -1) {
                    flag1 = false;
                    if (k <= 0) {
                        topBlock = States::AIR;
                        underBlock = ctx.block;
                    } else if (pos.y >= ctx.seaLevel - 4 && pos.y <= ctx.seaLevel + 1) {
                        topBlock = States::WHITE_TERRACOTTA;
                        underBlock = biomeSurfaceConfig.getUnder();
                    }

                    if (pos.y < ctx.seaLevel && topBlock.isAir()) {
                        topBlock = ctx.fluid;
                    }

                    l = k + std::max(0, pos.y - ctx.seaLevel);
                    if (pos.y >= ctx.seaLevel - 1) {
                        if (pos.y > 86 + k * 2) {
                            const auto dirt = flag ? States::COARSE_DIRT : States::GRASS_BLOCK;
                            ctx.chunk.setData(pos, dirt/*, false*/);
                        } else if (pos.y > ctx.seaLevel + 3 + k) {
                            const auto clay = pos.y >= 64 && pos.y <= 127
                                        ? flag ? States::TERRACOTTA : clayBands.getClay(pos)
                                        : States::ORANGE_TERRACOTTA;

                            ctx.chunk.setData(pos, clay/*, false*/);
                        } else {
                            ctx.chunk.setData(pos, biomeSurfaceConfig.getTop()/*, false*/);
                            flag1 = true;
                        }
                    } else {
                        const auto clay = underBlock == States::WHITE_TERRACOTTA
                                        ? States::ORANGE_TERRACOTTA
                                        : underBlock;

                        ctx.chunk.setData(pos, clay/*, false*/);
                    }
                } else if (l > 0) {
                    --l;

                    const auto clay = flag1 ? States::ORANGE_TERRACOTTA : clayBands.getClay(pos);
                    ctx.chunk.setData(pos, clay/*, false*/);
                }
            }
        }
    }
};

struct ErodedBadlandsSurfaceBuilder : public BadlandsSurfaceBuilder {
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
        auto& clayBands = getClayBands();

        double d0 = 0.0;
        const auto d1 = std::min(std::abs(ctx.noise), clayBands.noise1->noiseAt(static_cast<double>(ctx.pos.x) * 0.25, static_cast<double>(ctx.pos.z) * 0.25, false) * 15.0);
        if (d1 > 0.0) {
            const auto d3 = std::abs(clayBands.noise2->noiseAt(static_cast<double>(ctx.pos.x) * 0.001953125, static_cast<double>(ctx.pos.z) * 0.001953125, false));
            d0 = d1 * d1 * 2.5;
            const auto d4 = std::ceil(d3 * 50.0) + 14.0;
            if (d0 > d4) {
                d0 = d4;
            }

            d0 = d0 + 64.0;
        }

        const auto biomeSurfaceConfig = ctx.biome.getGenerationSettings().getSurfaceBuilderConfig();
        auto underBlock = biomeSurfaceConfig.getUnder();
        auto topBlock = States::WHITE_TERRACOTTA;
        const auto j = static_cast<int>(ctx.noise / 3.0 + 3.0 + ctx.random.nextDouble() * 0.25);
        const auto flag = std::cos(ctx.noise / 3.0 * M_PI) > 0.0;
        int k = -1;
        bool flag1 = false;

        auto pos = ctx.pos.up(std::max(ctx.pos.y, static_cast<int>(d0) + 1) - ctx.pos.y);

        for (; pos.y >= 0; --pos.y) {
            const auto data = ctx.chunk.getData(pos);
            if (data.isAir() && pos.y < static_cast<int>(d0)) {
                ctx.chunk.setData(pos, ctx.block/*, false*/);
            }

            if (data.isAir()) {
                k = -1;
            } else if (data.is(ctx.block.getBlock())) {
                if (k == -1) {
                    flag1 = false;
                    if (j <= 0) {
                        topBlock = States::AIR;
                        underBlock = ctx.block;
                    } else if (pos.y >= ctx.seaLevel - 4 && pos.y <= ctx.seaLevel + 1) {
                        topBlock = States::WHITE_TERRACOTTA;
                        underBlock = biomeSurfaceConfig.getUnder();
                    }

                    if (pos.y < ctx.seaLevel && topBlock.isAir()) {
                        topBlock = ctx.fluid;
                    }

                    k = j + std::max(0, pos.y - ctx.seaLevel);
                    if (pos.y >= ctx.seaLevel - 1) {
                        if (pos.y <= ctx.seaLevel + 3 + j) {
                            ctx.chunk.setData(pos, biomeSurfaceConfig.getTop()/*, false*/);
                            flag1 = true;
                        } else {
                            const auto clay = pos.y >= 64 && pos.y <= 127
                                            ? flag ? States::TERRACOTTA : clayBands.getClay(pos)
                                            : States::ORANGE_TERRACOTTA;

                            ctx.chunk.setData(pos, clay/*, false*/);
                        }
                    } else {
                        ctx.chunk.setData(pos, underBlock/*, false*/);

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
                            ctx.chunk.setData(pos, States::ORANGE_TERRACOTTA/*, false*/);
                        }
                    }
                } else if (k > 0) {
                    --k;

                    const auto clay = flag1 ? States::ORANGE_TERRACOTTA : clayBands.getClay(pos);
                    ctx.chunk.setData(pos, clay/*, false*/);
                }
            }
        }
    }
};

struct FrozenOceanSurfaceBuilder : public SurfaceBuilder {
    struct Cache {
        tl::optional<int64_t> seed = tl::nullopt;
        tl::optional<PerlinNoiseGenerator> noise1 = tl::nullopt;
        tl::optional<PerlinNoiseGenerator> noise2 = tl::nullopt;

        void setSeed(int64_t _seed) {
            if (seed != _seed) {
                seed = _seed;

                auto random = Random::from(_seed);
                noise1.emplace(random, ranges::views::iota(-3, 1));
                noise2.emplace(random, ranges::views::single(0));
            }
        }
    };

    ThreadLocal<Cache> cache{};

    auto getCache() -> Cache& {
        if (!cache.has_value()) {
            cache.set(new Cache());
        }
        return *cache.get();
    }

    void setSeed(int64_t _seed) override {
        getCache().setSeed(_seed);
    }

    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
        auto& _cache = getCache();

        auto d0 = 0.0;
        auto d1 = 0.0;
        const auto temperature = ctx.biome.getTemperature(BlockPos{ctx.pos.x, 63, ctx.pos.z});
        const auto d2 = std::min(std::abs(ctx.noise), _cache.noise1->noiseAt(
            static_cast<double>(ctx.pos.x) * 0.1,
            static_cast<double>(ctx.pos.z) * 0.1,
            false
        ) * 15.0);

        if (d2 > 1.8) {
            const auto d4 = std::abs(_cache.noise2->noiseAt(
                static_cast<double>(ctx.pos.x) * 0.09765625,
                static_cast<double>(ctx.pos.z) * 0.09765625,
                false
            ));

            d0 = d2 * d2 * 1.2;
            const auto d5 = std::ceil(d4 * 40.0) + 14.0;
            if (d0 > d5) {
                d0 = d5;
            }

            if (temperature > 0.1F) {
                d0 -= 2.0;
            }

            if (d0 > 2.0) {
                d1 = static_cast<double>(ctx.seaLevel) - d0 - 7.0;
                d0 = d0 + static_cast<double>(ctx.seaLevel);
            } else {
                d0 = 0.0;
            }
        }

        const auto biomeSurfaceConfig = ctx.biome.getGenerationSettings().getSurfaceBuilderConfig();
        auto underBlock = biomeSurfaceConfig.getUnder();
        auto topBlock = biomeSurfaceConfig.getTop();
        const auto j = static_cast<int>(ctx.noise / 3.0 + 3.0 + ctx.random.nextDouble() * 0.25);
        const auto max_snow_blocks_count = 2 + ctx.random.nextInt(4);
        const auto j1 = ctx.seaLevel + 18 + ctx.random.nextInt(10);

        int snow_blocks_count = 0;
        int k = -1;

        auto pos = ctx.pos.up(std::max(ctx.pos.y, static_cast<int>(d0) + 1) - ctx.pos.y);
        for (; pos.y >= 0; --pos.y) {
            {
                const auto state = ctx.chunk.getData(pos);
                if (state.isAir() && pos.y < static_cast<int>(d0) && ctx.random.nextDouble() > 0.01) {
                    ctx.chunk.setData(pos, States::PACKED_ICE/*, false*/);
                } else if (state.getBlock()->getMaterial() == Materials::WATER && pos.y > static_cast<int>(d1) && pos.y < ctx.seaLevel && d1 != 0.0 && ctx.random.nextDouble() > 0.15) {
                    ctx.chunk.setData(pos, States::PACKED_ICE/*, false*/);
                }
            }

            const auto state = ctx.chunk.getData(pos);
            if (state.isAir()) {
                k = -1;
            } else if (!state.is(ctx.block.getBlock())) {
                if (state.is(Blocks::PACKED_ICE) && snow_blocks_count <= max_snow_blocks_count && pos.y > j1) {
                    ctx.chunk.setData(pos, States::SNOW_BLOCK/*, false*/);
                    ++snow_blocks_count;
                }
            } else if (k == -1) {
                if (j <= 0) {
                    topBlock = States::AIR;
                    underBlock = ctx.block;
                } else if (pos.y >= ctx.seaLevel - 4 && pos.y <= ctx.seaLevel + 1) {
                    topBlock = biomeSurfaceConfig.getTop();
                    underBlock = biomeSurfaceConfig.getUnder();
                }

                if (pos.y < ctx.seaLevel && topBlock.isAir()) {
                    topBlock = ctx.biome.getTemperature(pos) < 0.15F
                                ? States::ICE
                                : ctx.fluid;
                }

                k = j;
                if (pos.y >= ctx.seaLevel - 1) {
                    ctx.chunk.setData(pos, topBlock/*, false*/);
                } else if (pos.y < ctx.seaLevel - 7 - j) {
                    topBlock = States::AIR;
                    underBlock = ctx.block;
                    ctx.chunk.setData(pos, States::GRAVEL/*, false*/);
                } else {
                    ctx.chunk.setData(pos, underBlock/*, false*/);
                }
            } else if (k > 0) {
                --k;
                ctx.chunk.setData(pos, underBlock/*, false*/);
                if (k == 0 && underBlock.is(Blocks::SAND) && j > 1) {
                    k = ctx.random.nextInt(4) + std::max(0, pos.y - 63);
                    underBlock = underBlock.is(Blocks::RED_SAND) ? States::RED_SANDSTONE : States::SANDSTONE;
                }
            }
        }
    }
};

struct NetherSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
    }
};

struct NetherForestsSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
    }
};

struct SoulSandValleySurfaceBuilder : public SurfaceBuilder {
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
    }
};

struct BasaltDeltasSurfaceBuilder : public SurfaceBuilder {
    void buildSurface(SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) override {
    }
};

template<>
auto Json::From<SurfaceBuilder*>::from(SurfaceBuilder* const& builder) -> Self {
    return SurfaceBuilders::builders.name(builder).value();
}

template<>
auto Json::Into<SurfaceBuilder*>::into(const Self& obj) -> Result {
    return SurfaceBuilders::builders.get(obj.as_string().value());
}

template<>
auto Json::From<SurfaceBuilderConfig>::from(const SurfaceBuilderConfig &config) -> Json {
    return {
        {"top_material", config.top},
        {"under_material", config.mid},
        {"underwater_material", config.underWater}
    };
}

template<>
auto Json::Into<SurfaceBuilderConfig>::into(const Json& obj) -> Result {
    return obj.as_object().map([](auto&& o) {
        return SurfaceBuilderConfig{
            .top = o.at("top_material"),
            .mid = o.at("under_material"),
            .underWater = o.at("underwater_material")
        };
    });
}

void SurfaceBuilders::init() {
    Noop             = create<NoopSurfaceBuilder>("noop");
    Default          = create<DefaultSurfaceBuilder>("default");
    Mountain         = create<MultiConfigSurfaceBuilder>("mountain", Default, [](SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) -> SurfaceBuilderConfig {
        const auto config1 = SurfaceBuilderConfig{
            States::STONE,
            States::STONE,
            States::GRAVEL
        };
        const auto config2 = SurfaceBuilderConfig{
            States::GRASS_BLOCK,
            States::DIRT,
            States::GRAVEL
        };
        return ctx.noise > 1.0 ? config1 : config2;
    });
    ShatteredSavanna = create<MultiConfigSurfaceBuilder>("shattered_savanna", Default, [](SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) -> SurfaceBuilderConfig {
        const auto config1 = SurfaceBuilderConfig{
            States::STONE,
            States::STONE,
            States::GRAVEL
        };
        const auto config2 = SurfaceBuilderConfig{
            States::COARSE_DIRT,
            States::DIRT,
            States::GRAVEL
        };
        const auto config3 = SurfaceBuilderConfig{
            States::GRASS_BLOCK,
            States::DIRT,
            States::GRAVEL
        };
        return ctx.noise > 1.75 ? config1 : ctx.noise > -0.5 ? config2 : config3;
    });
    GravellyMountain = create<MultiConfigSurfaceBuilder>("gravelly_mountain", Default, [](SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) -> SurfaceBuilderConfig {
        const auto config1 = SurfaceBuilderConfig{
            States::GRAVEL,
            States::GRAVEL,
            States::GRAVEL
        };
        const auto config2 = SurfaceBuilderConfig{
            States::STONE,
            States::STONE,
            States::GRAVEL
        };
        const auto config3 = SurfaceBuilderConfig{
            States::GRASS_BLOCK,
            States::DIRT,
            States::GRAVEL
        };
        const auto config4 = SurfaceBuilderConfig{
            States::GRAVEL,
            States::GRAVEL,
            States::GRAVEL
        };
        return ctx.noise > 2.0 ? config1 : ctx.noise > 1.0 ? config2 : ctx.noise >= -1.0 ? config3 : config4;
//        return (ctx.noise < -1.0 || ctx.noise > 2.0) ? config1 : ctx.noise > 1.0 ? config2 : config3;
    });
    GiantTreeTaiga   = create<MultiConfigSurfaceBuilder>("giant_tree_taiga", Default, [](SurfaceBuilderContext& ctx, const SurfaceBuilderConfig& config) -> SurfaceBuilderConfig {
        const auto config1 = SurfaceBuilderConfig{
            States::COARSE_DIRT,
            States::DIRT,
            States::GRAVEL
        };
        const auto config2 = SurfaceBuilderConfig{
            States::PODZOL,
            States::DIRT,
            States::GRAVEL
        };
        const auto config3 = SurfaceBuilderConfig{
            States::GRASS_BLOCK,
            States::DIRT,
            States::GRAVEL
        };
        return ctx.noise > 1.75 ? config1 : ctx.noise > -0.95 ? config2 : config3;
    });
    Swamp            = create<SwampSurfaceBuilder>("swamp", Default);
    Badlands         = create<BadlandsSurfaceBuilder>("badlands");
    WoodedBadlands   = create<WoodedBadlandsSurfaceBuilder>("wooded_badlands");
    ErodedBadlands   = create<ErodedBadlandsSurfaceBuilder>("eroded_badlands");
    FrozenOcean      = create<FrozenOceanSurfaceBuilder>("frozen_ocean");
    Nether           = create<NetherSurfaceBuilder>("nether");
    NetherForest     = create<NetherForestsSurfaceBuilder>("nether_forest");
    SoulSandValley   = create<SoulSandValleySurfaceBuilder>("soul_sand_valley");
    BasaltDeltas     = create<BasaltDeltasSurfaceBuilder>("basalt_deltas");

//    NETHERRACK_CONFIG = SurfaceBuilderConfig{
//            States::NETHERRACK,
//            States::NETHERRACK,
//            States::NETHERRACK
//    };
//
//    SOUL_SAND__CONFIG = SurfaceBuilderConfig{
//            States::SOUL_SAND,
//            States::SOUL_SAND,
//            States::SOUL_SAND
//    };
//
//    crimson_forest_config = SurfaceBuilderConfig{
//            States::CRIMSON_NYLIUM,
//            States::NETHERRACK,
//            States::NETHER_WART_BLOCK
//    };
//
//    WARPED_FOREST_CONFIG = SurfaceBuilderConfig{
//            States::WARPED_NYLIUM,
//            States::NETHERRACK,
//            States::WARPED_WART_BLOCK
//    };
//    BASALT_DELTAS_CONFIG = SurfaceBuilderConfig{
//            States::BLACKSTONE,
//            States::BASALT,
//            States::MAGMA_BLOCK
//    };
}
