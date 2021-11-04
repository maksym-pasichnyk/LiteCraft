#include "NoiseChunkGenerator.hpp"

#include "../WorldGenRegion.hpp"
#include "../biome/Biome.hpp"
#include "../biome/provider/EndBiomeProvider.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"
#include "../../block/Blocks.hpp"

#include <world/gen/surface/SurfaceBuilder.hpp>

struct DefaultNoiseProvider : NoiseProvider {
    std::pair<double, double> get(NoiseChunkGenerator* generator, int xpos, int zpos) override {
        float f = 0.0F;
        float f1 = 0.0F;
        float f2 = 0.0F;
        const int seaLevel = generator->getSeaLevel();
        const float mainBiomeDepth = generator->getNoiseBiome(xpos, seaLevel, zpos)->getDepth();

        for (int xPos = -2; xPos <= 2; ++xPos) {
            for (int zPos = -2; zPos <= 2; ++zPos) {
                const auto biome = generator->getNoiseBiome(xpos + xPos, seaLevel, zpos + zPos);
                const float secondBiomeDepth = biome->getDepth();
                const float scale = biome->getScale();
                float f6;
                float f7;
                /*if (noisesettings.amplified() && secondBiomeDepth > 0.0F) {
                    f6 = 1.0F + secondBiomeDepth * 2.0F;
                    f7 = 1.0F + scale * 4.0F;
                }
                else {*/
                f6 = secondBiomeDepth;
                f7 = scale;
                //}

                const float f8 = secondBiomeDepth > mainBiomeDepth ? 0.5F : 1.0F;
                const float f9 = f8 * generator->biomeWeights[xPos + 2 + (zPos + 2) * 5] / (f6 + 2.0F);
                f += f7 * f9;
                f1 += f6 * f9;
                f2 += f9;
            }
        }

        const float f10 = f1 / f2;
        const float scale = f / f2;
        const double biomeDepth = (f10 * 0.5F - 0.125F) * 0.265625;
        const double biomeScale = 96.0 / (scale * 0.9F + 0.1F);
        return {biomeDepth, biomeScale};
    }
};

struct EndNoiseProvider : NoiseProvider {
    EndBiomeProvider* provider;

    explicit EndNoiseProvider(EndBiomeProvider* provider) : provider(provider) {}

    std::pair<double, double> get(NoiseChunkGenerator* generator, int xpos, int zpos) override {
        const double biomeDepth = provider->getRandomNoise(xpos, zpos) - 8.0F;
        const double biomeScale = biomeDepth > 0.0 ? 0.25 : 1.0;
        return {biomeDepth, biomeScale};
    }
};

NoiseChunkGenerator::NoiseChunkGenerator(int64_t seed, DimensionSettings settings, std::unique_ptr<BiomeProvider>&& biomeProvider)
    : ChunkGenerator(std::move(biomeProvider)), settings(settings)
{
//    defaultBlock = Blocks::STONE->getDefaultState();
//    defaultFluid = Blocks::WATER->getDefaultState();

//    dimensionHeight = settings.noise.height;
//    bedrockFloorPosition = 0;
//    bedrockRoofPosition = -1;

    horizontalNoiseGranularity = settings.noise.sizeHorizontal * 4;
    verticalNoiseGranularity = settings.noise.sizeVertical * 4;

    noiseSizeX = 16 / horizontalNoiseGranularity;
    noiseSizeY = settings.noise.height / verticalNoiseGranularity;
    noiseSizeZ = 16 / horizontalNoiseGranularity;

    auto randomSeed = Random::from(seed);
    minLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, ranges::views::iota(-15, 1));
    maxLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, ranges::views::iota(-15, 1));
    mainLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, ranges::views::iota(-7, 1));

    surfaceNoise = std::make_unique<PerlinNoiseGenerator>(randomSeed, ranges::views::iota(-3, 1));

    randomSeed.skip(2620);
    depthNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, ranges::views::iota(-15, 1));

    if (settings.noise.islandNoiseOverride) {
        noiseProvider = std::make_unique<EndNoiseProvider>(dynamic_cast<EndBiomeProvider*>(biomeProvider.get()));
    } else {
        noiseProvider = std::make_unique<DefaultNoiseProvider>();
    }
}

void NoiseChunkGenerator::makeBedrock(Chunk& chunk, Random &random) const {
    const auto dimensionHeight = settings.noise.height;
    const auto maxAvailableHeight = dimensionHeight - 1 - settings.bedrockRoofPosition;
    const auto makeRoofBedrock = maxAvailableHeight + 4 >= 0 && maxAvailableHeight < dimensionHeight;
    const auto makeFloorBedrock = settings.bedrockFloorPosition + 4 >= 0 && settings.bedrockFloorPosition < dimensionHeight;

    if (makeRoofBedrock || makeFloorBedrock) {
        const auto bedrock = Blocks::BEDROCK->getDefaultState();

        for (auto x = 0; x <= 15; x++) {
            for (auto z = 0; z <= 15; z++) {
                if (makeRoofBedrock) {
                    for (auto y = 0; y < 5; y++) {
                        if (y <= random.nextInt(5)) {
                            chunk.setData(x, maxAvailableHeight - y, z, bedrock);
                        }
                    }
                }

                if (makeFloorBedrock) {
                    for (auto y = 4; y >= 0; y--) {
                        if (y <= random.nextInt(5)) {
                            chunk.setData(x, settings.bedrockFloorPosition + y, z, bedrock);
                        }
                    }
                }
            }
        }
    }
}

double NoiseChunkGenerator::sampleAndClampNoise(int x, int y, int z, double xzScale, double yScale, double xzFactor, double yFactor) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double d = 1.0;

    for (int i = 0; i < 16; ++i) {
        const auto x2 = OctavesNoiseGenerator::maintainPrecision(static_cast<double>(x) * xzScale * d);
        const auto y2 = OctavesNoiseGenerator::maintainPrecision(static_cast<double>(y) * yScale * d);
        const auto z2 = OctavesNoiseGenerator::maintainPrecision(static_cast<double>(z) * xzScale * d);
        const auto e = yScale * d;
        auto minLimitNoise = minLimitPerlinNoise->getOctave(i);
        if (minLimitNoise != nullptr) {
            a += minLimitNoise->getNoiseValue(x2, y2, z2, e, static_cast<double>(y) * e) / d;
        }

        auto maxLimitNoise = maxLimitPerlinNoise->getOctave(i);
        if (maxLimitNoise != nullptr) {
            b += maxLimitNoise->getNoiseValue(x2, y2, z2, e, static_cast<double>(y) * e) / d;
        }

        if (i < 8) {
            auto mainNoise = mainLimitPerlinNoise->getOctave(i);
            if (mainNoise != nullptr) {
                c += mainNoise->getNoiseValue(
                        OctavesNoiseGenerator::maintainPrecision(static_cast<double>(x) * xzFactor * d),
                        OctavesNoiseGenerator::maintainPrecision(static_cast<double>(y) * yFactor * d),
                        OctavesNoiseGenerator::maintainPrecision(static_cast<double>(z) * xzFactor * d),
                        yFactor * d,
                        static_cast<double>(y) * yFactor * d
                ) / d;
            }
        }

        d /= 2.0;
    }
    
    return Math::clampedLerp(a / 512.0, b / 512.0, (c / 10.0 + 1.0) / 2.0);
}

double NoiseChunkGenerator::getRandomDensity(int x, int z) {
    const double noise = depthNoise->getValue(x * 200, 10.0, z * 200, 1.0, 0.0, true);
    const double a = noise < 0.0 ? -noise * 0.3 : noise;
    const double b = a * 24.575625 - 2.0;
    return b < 0.0 ? b * 0.009486607142857142 : std::min(b, 1.0) * 0.006640625;
}

void NoiseChunkGenerator::fillNoiseColumn(std::span<double> column, int xpos, int zpos) {
    const auto [biomeDepth, biomeScale] = noiseProvider->get(this, xpos, zpos);

    const auto xzScale = 684.412 * settings.noise.sampling.xz_scale;
    const auto yScale = 684.412 * settings.noise.sampling.y_scale;
    const auto xzFactor = xzScale / settings.noise.sampling.xz_factor;
    const auto yFactor = yScale / settings.noise.sampling.y_factor;
    const auto randomDensity = settings.noise.randomDensityOffset ? getRandomDensity(xpos, zpos) : 0.0;
    const auto destinyFactor = settings.noise.destinyFactor;
    const auto densityOffset = settings.noise.densityOffset;

    for (int y = 0; y <= noiseSizeY; ++y) {
        const auto yOffset = 1.0 - static_cast<double>(y) * 2.0 / static_cast<double>(noiseSizeY) + randomDensity;
        const auto density = yOffset * destinyFactor + densityOffset;
        const auto falloff = (density + biomeDepth) * biomeScale;

        double noise = sampleAndClampNoise(xpos, y, zpos, xzScale, yScale, xzFactor, yFactor);
        noise = falloff > 0.0 ? (noise + falloff * 4.0) : noise + falloff;

        if (settings.noise.topSlide.size > 0.0) {
            const auto target = settings.noise.topSlide.target;
            const auto slide = (static_cast<double>(noiseSizeY - y) - settings.noise.topSlide.offset) / settings.noise.topSlide.size;

            noise = Math::clampedLerp(target, noise, slide);
        }

        if (settings.noise.bottomSlide.size > 0.0) {
            const auto target = settings.noise.bottomSlide.target;
            const auto slide = (static_cast<double>(y) - settings.noise.bottomSlide.offset) / settings.noise.bottomSlide.size;

            noise = Math::clampedLerp(target, noise, slide);
        }

        column[y] = noise;
    }
}

std::vector<double> NoiseChunkGenerator::getNoiseColumn(int x, int z) {
    std::vector<double> noises(noiseSizeY + 1);
    fillNoiseColumn(noises, x, z);
    return std::move(noises);
}

int NoiseChunkGenerator::getColumn(int x, int z, std::span<BlockData> datas, bool(*predicate)(BlockData)) {
    const auto i = Math::floorDiv(x, horizontalNoiseGranularity);
    const auto j = Math::floorDiv(z, horizontalNoiseGranularity);
    const auto k = Math::floorDiv(x, horizontalNoiseGranularity);
    const auto l = Math::floorDiv(z, horizontalNoiseGranularity);
    const auto d0 = static_cast<double>(k) / static_cast<double>(horizontalNoiseGranularity);
    const auto d1 = static_cast<double>(l) / static_cast<double>(horizontalNoiseGranularity);
    const auto seaLevel = settings.seaLevel;

    const auto columns = std::array{
        getNoiseColumn(i, j),
        getNoiseColumn(i, j + 1),
        getNoiseColumn(i + 1, j),
        getNoiseColumn(i + 1, j + 1)
    };

    for (int i1 = noiseSizeY - 1; i1 >= 0; --i1) {
        const double d2 = columns[0][i1];
        const double d3 = columns[1][i1];
        const double d4 = columns[2][i1];
        const double d5 = columns[3][i1];
        const double d6 = columns[0][i1 + 1];
        const double d7 = columns[1][i1 + 1];
        const double d8 = columns[2][i1 + 1];
        const double d9 = columns[3][i1 + 1];

        for (int j1 = verticalNoiseGranularity - 1; j1 >= 0; --j1) {
            const double d10 = static_cast<double>(j1) / static_cast<double>(verticalNoiseGranularity);
            const double d11 = MathHelper_lerp3(d10, d0, d1, d2, d6, d4, d8, d3, d7, d5, d9);
            const int ypos = i1 * verticalNoiseGranularity + j1;

            const auto data = d11 > 0.0
                                ? settings.layer
                                : ypos < seaLevel
                                    ? settings.fluid
                                    : Blocks::AIR->getDefaultState();

            if (!datas.empty()) {
                datas[ypos] = data;
            }

            if (predicate && predicate(data)) {
                return ypos + 1;
            }
        }
    }

    return 0;
}

void NoiseChunkGenerator::generateSurface(WorldGenRegion &region, Chunk& chunk) {
    Random random{};
    random.setBaseChunkSeed(chunk.pos.x, chunk.pos.z);

    for (auto x = 0; x < 16; x++) {
        for (auto z = 0; z < 16; z++) {
            const auto pos = chunk.getHeight(
                HeightmapType::WORLD_SURFACE_WG,
                chunk.pos.getBlockPos(x, 0, z)
            );

            const auto noise = 15.0 * surfaceNoise->noiseAt(
                static_cast<double>(pos.x) * 0.0625,
                static_cast<double>(pos.z) * 0.0625,
                0.0625,
                static_cast<double>(x) * 0.0625
            );

            auto biome = region.getBiome(pos.x, pos.y, pos.z);

            auto ctx = SurfaceBuilderContext {
                .random = random,
                .chunk = chunk,
                .biome = *biome,
                .pos = pos,
                .noise = noise,
                .block = settings.layer,
                .fluid = settings.fluid,
                .seaLevel = 63
            };

            biome->buildSurface(ctx, region.getSeed());
        }
    }

    makeBedrock(chunk, random);
}

void NoiseChunkGenerator::generateTerrain(Chunk& chunk) {
    if (!cacheNoiseColumns.has_value()) {
        auto cache = new std::array<std::vector<std::vector<double>>, 2>();
        (*cache)[0].resize(noiseSizeZ + 1);
        (*cache)[1].resize(noiseSizeZ + 1);
        for (int z = 0; z < noiseSizeZ + 1; ++z) {
            (*cache)[0][z].resize(noiseSizeY + 1);
            (*cache)[1][z].resize(noiseSizeY + 1);
        }
        cacheNoiseColumns.set(cache);
    }

    const auto chunkPosX = chunk.pos.x;
    const auto chunkPosZ = chunk.pos.z;
    const auto seaLevel = 63;

    auto& cache = *cacheNoiseColumns.get();

    for (int z = 0; z < noiseSizeZ + 1; ++z) {
        fillNoiseColumn(cache[0][z], chunkPosX * noiseSizeX, chunkPosZ * noiseSizeZ + z);
    }

    for (int x = 0; x < noiseSizeX; x++) {
        for (int z = 0; z < noiseSizeZ + 1; ++z) {
            fillNoiseColumn(cache[1][z], chunkPosX * noiseSizeX + x + 1, chunkPosZ * noiseSizeZ + z);
        }

        for (int z = 0; z < noiseSizeZ; ++z) {
            for (int y = noiseSizeY - 1; y >= 0; --y) {
                const auto d0 = cache[0][z][y];
                const auto d1 = cache[0][z + 1][y];
                const auto d2 = cache[1][z][y];
                const auto d3 = cache[1][z + 1][y];
                const auto d4 = cache[0][z][y + 1];
                const auto d5 = cache[0][z + 1][y + 1];
                const auto d6 = cache[1][z][y + 1];
                const auto d7 = cache[1][z + 1][y + 1];

                for (int l1 = verticalNoiseGranularity - 1; l1 >= 0; --l1) {
                    const auto ypos = y * verticalNoiseGranularity + l1;

                    const auto d8 = static_cast<double>(l1) / static_cast<double>(verticalNoiseGranularity);
                    const auto d9 = Math::lerp(d8, d0, d4);
                    const auto d10 = Math::lerp(d8, d2, d6);
                    const auto d11 = Math::lerp(d8, d1, d5);
                    const auto d12 = Math::lerp(d8, d3, d7);

                    for (int l2 = 0; l2 < horizontalNoiseGranularity; ++l2) {
                        const int xpos = x * horizontalNoiseGranularity + l2;
                        const double d13 = static_cast<double>(l2) / static_cast<double>(horizontalNoiseGranularity);
                        const double d14 = Math::lerp(d13, d9, d10);
                        const double d15 = Math::lerp(d13, d11, d12);

                        for (int k3 = 0; k3 < horizontalNoiseGranularity; ++k3) {
                            const int zpos = z * horizontalNoiseGranularity + k3;
                            const double d16 = static_cast<double>(k3) / static_cast<double>(horizontalNoiseGranularity);
                            const double d17 = Math::lerp(d16, d14, d15);
                            double d18 = Math::clamp(d17 / 200.0, -1.0, 1.0);

                            d18 = (d18 / 2.0) - ((d18 * d18 * d18) / 24.0);

                            if (d18 > 0.0) {
                                chunk.setData(xpos & 15, ypos, zpos & 15, settings.layer);
                            } else if (ypos < seaLevel) {
                                chunk.setData(xpos & 15, ypos, zpos & 15, settings.fluid);
                            }
                        }
                    }
                }
            }
        }

        std::swap(cache[0], cache[1]);
    }
}