#include "NoiseChunkGenerator.hpp"

#include "../chunk/Chunk.hpp"
#include "../biome/Biome.hpp"
#include "../biome/provider/BiomeProvider.hpp"
#include "../biome/provider/EndBiomeProvider.hpp"
#include "../../WorldGenRegion.hpp"

#include <glm/ext.hpp>

struct ScalingSettings {
    double xz_scale;
    double y_scale;
    double xz_factor;
    double y_factor;
};

struct SlideSettings {
    float target;
    float size;
    float offset;
};

struct NoiseSettings {
    ScalingSettings sampling;
    SlideSettings topSlide;
    SlideSettings bottomSlide;
    int height;
    int sizeVertical;
    int sizeHorizontal;
    double destinyFactor;
    double densityOffset;
    bool randomDensityOffset;
};

NoiseSettings settings{
    .sampling{
        .xz_scale = 0.9999999814507745,
        .y_scale = 0.9999999814507745,
        .xz_factor = 80,
        .y_factor = 160
    },
    .topSlide{
        .target = -10,
        .size = 3,
        .offset = 0
    },
    .bottomSlide{
        .target = -30,
        .size = 0,
        .offset = 0
    },
    .height = 256,
    .sizeVertical = 2,
    .sizeHorizontal = 1,
    .destinyFactor = 1.0,
    .densityOffset = -0.46875,
    .randomDensityOffset = true
};

//NoiseSettings settings{
//    .sampling{
//        .xz_scale = 1,
//        .y_scale = 3,
//        .xz_factor = 80,
//        .y_factor = 60
//    },
//    .topSlide{
//        .target = 120,
//        .size = 3,
//        .offset = 0
//    },
//    .bottomSlide{
//        .target = 320,
//        .size = 4,
//        .offset = -1
//    },
//    .height = 128,
//    .sizeVertical = 2,
//    .sizeHorizontal = 1,
//    .destinyFactor = 1.0,
//    .densityOffset = 0.019921875,
//    .randomDensityOffset = false
//};

NoiseChunkGenerator::NoiseChunkGenerator(int64_t seed, std::unique_ptr<BiomeProvider>&& biomeProvider)
    : ChunkGenerator(std::move(biomeProvider))
{
    defaultBlock = BlockData{Blocks::stone->id, 0};
    defaultFluid = BlockData{Blocks::water->id, 0};

    dimensionHeight = settings.height;
    bedrockFloorPosition = 0;
    bedrockRoofPosition = -1;

    horizontalNoiseGranularity = settings.sizeHorizontal * 4;
    verticalNoiseGranularity = settings.sizeVertical * 4;

    noiseSizeX = 16 / horizontalNoiseGranularity;
    noiseSizeY = dimensionHeight / verticalNoiseGranularity;
    noiseSizeZ = 16 / horizontalNoiseGranularity;

    auto randomSeed = Random::from(seed);
    minLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, std::views::iota(-15, 1));
    maxLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, std::views::iota(-15, 1));
    mainLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, std::views::iota(-7, 1));

    surfaceNoise = std::make_unique<PerlinNoiseGenerator>(randomSeed, std::views::iota(-3, 1));

    randomSeed.skip(2620);
    depthNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, std::views::iota(-15, 1));
    endNoise = nullptr;

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            biomeWeights[i + 2 + (j + 2) * 5] = 10.0F / std::sqrt(static_cast<float>(i * i + j * j) + 0.2F);
        }
    }
}

void NoiseChunkGenerator::makeBedrock(Chunk& chunk, Random &rand) const {
    const auto maxAvailableHeight = dimensionHeight - 1 - bedrockRoofPosition;
    const bool makeRoofBedrock = maxAvailableHeight + 4 >= 0 && maxAvailableHeight < dimensionHeight;
    const bool makeFloorBedrock = bedrockFloorPosition + 4 >= 0 && bedrockFloorPosition < dimensionHeight;

    if (makeRoofBedrock || makeFloorBedrock) {
        const auto bedrock = BlockData{Blocks::bedrock->id, 0};

        for (auto x = 0; x <= 15; x++) {
            for (auto z = 0; z <= 15; z++) {
                if (makeRoofBedrock) {
                    for (auto y = 0; y < 5; y++) {
                        if (y <= rand.nextInt(5)) {
                            chunk.setData(x, maxAvailableHeight - y, z, bedrock);
                        }
                    }
                }

                if (makeFloorBedrock) {
                    for (auto y = 4; y >= 0; y--) {
                        if (y <= rand.nextInt(5)) {
                            chunk.setData(x, bedrockFloorPosition + y, z, bedrock);
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
        const double x2 = OctavesNoiseGenerator::maintainPrecision((double)x * xzScale * d);
        const double y2 = OctavesNoiseGenerator::maintainPrecision((double)y * yScale * d);
        const double z2 = OctavesNoiseGenerator::maintainPrecision((double)z * xzScale * d);
        const double e = yScale * d;
        auto minLimitNoise = minLimitPerlinNoise->getOctave(i);
        if (minLimitNoise != nullptr) {
            a += minLimitNoise->getNoiseValue(x2, y2, z2, e, (double)y * e) / d;
        }

        auto maxLimitNoise = maxLimitPerlinNoise->getOctave(i);
        if (maxLimitNoise != nullptr) {
            b += maxLimitNoise->getNoiseValue(x2, y2, z2, e, (double)y * e) / d;
        }

        if (i < 8) {
            auto mainNoise = mainLimitPerlinNoise->getOctave(i);
            if (mainNoise != nullptr) {
                c += mainNoise->getNoiseValue(
                        OctavesNoiseGenerator::maintainPrecision((double)x * xzFactor * d),
                        OctavesNoiseGenerator::maintainPrecision((double)y * yFactor * d),
                        OctavesNoiseGenerator::maintainPrecision((double)z * xzFactor * d),
                        yFactor * d,
                        (double)y * yFactor * d
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

void NoiseChunkGenerator::fillNoiseColumn(std::array<double, 33>& column, int xpos, int zpos) {
    double biomeDepth;
    double biomeScale;
    if (endNoise != nullptr) {
         biomeDepth = EndBiomeProvider::getRandomNoise(*endNoise, xpos, zpos) - 8.0F;
         if (biomeDepth > 0.0) {
            biomeScale = 0.25;
         } else {
            biomeScale = 1.0;
         }
      } else {
        float f = 0.0F;
        float f1 = 0.0F;
        float f2 = 0.0F;
        const int seaLevel = 63;//settings->seaLevel;
        const float mainBiomeDepth = biomeProvider->getNoiseBiome(xpos, seaLevel, zpos)->getDepth();

        for (int xPos = -2; xPos <= 2; ++xPos) {
            for (int zPos = -2; zPos <= 2; ++zPos) {
                const auto biome = biomeProvider->getNoiseBiome(xpos + xPos, seaLevel, zpos + zPos);
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
                const float f9 = f8 * biomeWeights[xPos + 2 + (zPos + 2) * 5] / (f6 + 2.0F);
                f += f7 * f9;
                f1 += f6 * f9;
                f2 += f9;
            }
        }

        const float f10 = f1 / f2;
        const float scale = f / f2;
        biomeDepth = (f10 * 0.5F - 0.125F) * 0.265625;
        biomeScale = 96.0 / (scale * 0.9F + 0.1F);
    }
    const double xzScale = 684.412 * settings.sampling.xz_scale;
    const double yScale = 684.412 * settings.sampling.y_scale;
    const double xzFactor = xzScale / settings.sampling.xz_factor;
    const double yFactor = yScale / settings.sampling.y_factor;
    const double randomDensity = settings.randomDensityOffset ? getRandomDensity(xpos, zpos) : 0.0;
    const double destinyFactor = settings.destinyFactor;
    const double densityOffset = settings.densityOffset;

    for (int y = 0; y <= noiseSizeY; ++y) {
        double noise = sampleAndClampNoise(xpos, y, zpos, xzScale, yScale, xzFactor, yFactor);
        const double yOffset = 1.0 - (double)y * 2.0 / (double)noiseSizeY + randomDensity;
        const double density = yOffset * destinyFactor + densityOffset;
        const double falloff = (density + biomeDepth) * biomeScale;
        if (falloff > 0.0) {
            noise = noise + falloff * 4.0;
        } else {
            noise = noise + falloff;
        }

        if (settings.topSlide.size > 0.0) {
            noise = Math::clampedLerp(settings.topSlide.target, noise, ((double)(noiseSizeY - y) - settings.topSlide.offset) / settings.topSlide.size);
        }

        if (settings.bottomSlide.size > 0.0) {
            noise = Math::clampedLerp(settings.bottomSlide.target, noise, ((double)y - settings.bottomSlide.offset) / settings.bottomSlide.size);
        }

        column[y] = noise;
    }
}

void NoiseChunkGenerator::generateSurface(WorldGenRegion &region, Chunk& chunk) {
    const auto xStart = chunk.pos.getStartX();
    const auto zStart = chunk.pos.getStartZ();

    Random rand{};
    rand.setBaseChunkSeed(chunk.pos.x, chunk.pos.z);

    for (auto x = 0; x < 16; x++) {
        for (auto z = 0; z < 16; z++) {
            const auto xPos = xStart + x;
            const auto zPos = zStart + z;
            const auto yPos = chunk.getTopBlockY(/*Heightmap.Type.WORLD_SURFACE_WG,*/ x, z) + 1;
            const auto noise = 15.0 * surfaceNoise->noiseAt(
                    static_cast<double>(xPos) * 0.0625,
                    static_cast<double>(zPos) * 0.0625,
                    0.0625,
                    (double) x * 0.0625
            );
            auto biome = region.getBiome(xPos, yPos, zPos);
            biome->buildSurface(rand, chunk, xPos, zPos, yPos, noise, defaultBlock, defaultFluid, 63);
        }
    }

    makeBedrock(chunk, rand);
}

void NoiseChunkGenerator::generateTerrain(Chunk& chunk) {
    const auto chunkPosX = chunk.pos.x;
    const auto chunkPosZ = chunk.pos.z;
    const int seaLevel = 63;

    for (int z = 0; z < noiseSizeZ + 1; ++z) {
        fillNoiseColumn(noises[0][z], chunkPosX * noiseSizeX, chunkPosZ * noiseSizeZ + z);
    }

    for (int x = 0; x < noiseSizeX; x++) {
        for (int z = 0; z < noiseSizeZ + 1; ++z) {
            fillNoiseColumn(noises[1][z], chunkPosX * noiseSizeX + x + 1, chunkPosZ * noiseSizeZ + z);
        }

        for (int z = 0; z < noiseSizeZ; ++z) {
            for (int y = noiseSizeY - 1; y >= 0; --y) {
                const double d0 = noises[0][z][y];
                const double d1 = noises[0][z + 1][y];
                const double d2 = noises[1][z][y];
                const double d3 = noises[1][z + 1][y];
                const double d4 = noises[0][z][y + 1];
                const double d5 = noises[0][z + 1][y + 1];
                const double d6 = noises[1][z][y + 1];
                const double d7 = noises[1][z + 1][y + 1];

                for (int l1 = verticalNoiseGranularity - 1; l1 >= 0; --l1) {
                    const int ypos = y * verticalNoiseGranularity + l1;

                    const double d8 = (double) l1 / (double) verticalNoiseGranularity;
                    const double d9 = Math::lerp(d8, d0, d4);
                    const double d10 = Math::lerp(d8, d2, d6);
                    const double d11 = Math::lerp(d8, d1, d5);
                    const double d12 = Math::lerp(d8, d3, d7);

                    for (int l2 = 0; l2 < horizontalNoiseGranularity; ++l2) {
                        const int xpos = x * horizontalNoiseGranularity + l2;
                        const double d13 = (double) l2 / (double) horizontalNoiseGranularity;
                        const double d14 = Math::lerp(d13, d9, d10);
                        const double d15 = Math::lerp(d13, d11, d12);

                        for (int k3 = 0; k3 < horizontalNoiseGranularity; ++k3) {
                            const int zpos = z * horizontalNoiseGranularity + k3;
                            const double d16 = (double) k3 / (double) horizontalNoiseGranularity;
                            const double d17 = Math::lerp(d16, d14, d15);
                            double d18 = Math::clamp(d17 / 200.0, -1.0, 1.0);

                            d18 = (d18 / 2.0) - ((d18 * d18 * d18) / 24.0);

                            if (d18 > 0.0) {
                                chunk.setData(xpos & 15, ypos, zpos & 15, defaultBlock);
                            } else if (ypos < seaLevel) {
                                chunk.setData(xpos & 15, ypos, zpos & 15, defaultFluid);
                            }
                        }
                    }
                }
            }
        }

        std::swap(noises[0], noises[1]);
    }
}