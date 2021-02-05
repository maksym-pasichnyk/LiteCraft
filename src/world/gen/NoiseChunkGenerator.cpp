#include "NoiseChunkGenerator.hpp"

#include "../../Chunk.hpp"
#include "../../worldgenregion.hpp"
#include "layer/LayerUtil.hpp"

#include <glm/ext.hpp>

std::map<int, Biome*> biomes {};

struct ScalingSettings {
    float xz_scale;
    float y_scale;
    float xz_factor;
    float y_factor;
};

struct SlideSettings {
    float target;
    float size;
    float offset;
};

ScalingSettings sampling{
        0.9999999814507745,
        0.9999999814507745,
        80,
        160
};

SlideSettings topSlide{
        -10,
        3,
        0
};

SlideSettings bottomSlide{
        -30,
        0,
        0
};

struct BiomeMaker {

};

Biome* makeGenericOceanBiome(bool isDeapVariant) {
    return new Biome(isDeapVariant ?  -1.8F : -1.0F, 0.1);
}

Biome* makeOceanBiome(bool isDeapVariant) {
    return makeGenericOceanBiome(isDeapVariant);
}

Biome* makePlainsBiome(bool isSunflowerVariant) {
    return new Biome(0.125, 0.05);
}

Biome* makeDesertBiome(float depth, float scale, bool hasVillageAndOutpost, bool hasDesertPyramid, bool hasFossils) {
    return new Biome(depth, scale);
}

Biome* makeMountainBiome(float depth, float scale, /*ConfiguredSurfaceBuilder<SurfaceBuilderConfig> surfaceBuilder,*/ bool isEdge) {
    return new Biome(depth, scale);
}

struct OverworldBiomeProvider : BiomeProvider {
    std::unique_ptr<Layer> genBiomes{};

    OverworldBiomeProvider(int64_t seed, bool legacyBiomes, bool largeBiomes) {
        genBiomes = LayerUtil::createOverworldBiomes(seed, legacyBiomes, largeBiomes ? 6 : 4, 4);
    }

    Biome* getNoiseBiome(int x, int y, int z) override {
        return genBiomes->getBiome(biomes, x, z);
    }
};

//void generateTree(Chunk* chunk, BlockTable& pallete, int32_t x, int32_t z, WorldGenRegion& blocks, Random& rand) {
//	const auto height = chunk->heightmap[x & 15][z & 15];
//    const auto treeHeight = 4 + rand.nextInt(0, 2);
//
//	for (auto y = treeHeight - 2; y <= treeHeight + 1; y++) {
//        blocks.setBlock(x - 1, y + height, z - 1, BlockData{pallete.getId("leaves"), 0});
//        blocks.setBlock(x + 0, y + height, z - 1, BlockData{pallete.getId("leaves"), 0});
//        blocks.setBlock(x + 1, y + height, z - 1, BlockData{pallete.getId("leaves"), 0});
//
//        blocks.setBlock(x - 1, y + height, z, BlockData{pallete.getId("leaves"), 0});
//        blocks.setBlock(x + 0, y + height, z, BlockData{pallete.getId("leaves"), 0});
//        blocks.setBlock(x + 1, y + height, z, BlockData{pallete.getId("leaves"), 0});
//
//        blocks.setBlock(x - 1, y + height, z + 1, BlockData{pallete.getId("leaves"), 0});
//        blocks.setBlock(x + 0, y + height, z + 1, BlockData{pallete.getId("leaves"), 0});
//        blocks.setBlock(x + 1, y + height, z + 1, BlockData{pallete.getId("leaves"), 0});
//	}
//
//	for (auto y = height; y < height + treeHeight; y++) {
//        blocks.setBlock(x, y, z, BlockData{pallete.getId("log"), 0});
//	}
//}

NoiseChunkGenerator::NoiseChunkGenerator(BlockTable& pallete) {
    defaultBlock = BlockData{pallete.getId("stone")};
    defaultFluid = BlockData{pallete.getId("water")};

//    fmt::print("defaultBlock: {}\n", defaultBlock.id);
//    fmt::print("defaultFluid: {}\n", defaultFluid.id);

    auto randomSeed = Random::from(seed);

    biomes[0] = makeOceanBiome(false);
    biomes[1] = makePlainsBiome(false);
    biomes[2] = makeDesertBiome(0.125, 0.05, true, true, true);
    biomes[3] = makeMountainBiome(1.0, 0.5, false);
    biomes[4] = new Biome(0.1, 0.2);
    biomes[5] = new Biome(0.2, 0.2);
    biomes[6] = new Biome(-0.2, 0.1);
    biomes[7] = new Biome(-0.5, 0.0);
    biomes[8] = new Biome(0.1, 0.2);
    biomes[9] = new Biome(0.1, 0.2);
    biomes[10] = new Biome(-1.0, 0.1);
    biomes[11] = new Biome(-0.5, 0.0);
    biomes[12] = new Biome(0.125, 0.05);
    biomes[13] = new Biome(0.45, 0.3);
    biomes[14] = new Biome(0.2, 0.3);
    biomes[15] = new Biome(0.0, 0.025);
    biomes[16] = new Biome(0.0, 0.025);
    biomes[17] = new Biome(0.45, 0.3);
    biomes[18] = new Biome(0.45, 0.3);
    biomes[19] = new Biome(0.45, 0.3);
    biomes[20] = new Biome(0.8, 0.3);
    biomes[21] = new Biome(0.1, 0.2);
    biomes[22] = new Biome(0.45, 0.3);
    biomes[23] = new Biome(0.1, 0.2);
    biomes[24] = new Biome(-1.8, 0.1);
    biomes[25] = new Biome(0.1, 0.8);
    biomes[26] = new Biome(0.0, 0.025);
    biomes[27] = new Biome(0.1, 0.2);
    biomes[28] = new Biome(0.45, 0.3);
    biomes[29] = new Biome(0.1, 0.2);
    biomes[30] = new Biome(0.2, 0.2);
    biomes[31] = new Biome(0.45, 0.3);
    biomes[32] = new Biome(0.2, 0.2);
    biomes[33] = new Biome(0.45, 0.3);
    biomes[34] = new Biome(1.0, 0.5);
    biomes[35] = new Biome(0.125, 0.05);
    biomes[36] = new Biome(1.5, 0.025);
    biomes[37] = new Biome(0.1, 0.2);
    biomes[38] = new Biome(1.5, 0.025);
    biomes[39] = new Biome(1.5, 0.025);
    biomes[40] = new Biome(0.1, 0.2);
    biomes[41] = new Biome(0.1, 0.2);
    biomes[42] = new Biome(0.1, 0.2);
    biomes[43] = new Biome(0.1, 0.2);
    biomes[44] = new Biome(-1.0, 0.1);
    biomes[45] = new Biome(-1.0, 0.1);
    biomes[46] = new Biome(-1.0, 0.1);
    biomes[47] = new Biome(-1.8, 0.1);
    biomes[48] = new Biome(-1.8, 0.1);
    biomes[49] = new Biome(-1.8, 0.1);
    biomes[50] = new Biome(-1.8, 0.1);
    biomes[127] = new Biome(0.1, 0.2);
    biomes[129] = new Biome(0.125, 0.05);
    biomes[130] = new Biome(0.225, 0.25);
    biomes[131] = new Biome(1.0, 0.5);
    biomes[132] = new Biome(0.1, 0.4);
    biomes[133] = new Biome(0.3, 0.4);
    biomes[134] = new Biome(-0.1, 0.3);
    biomes[140] = new Biome(0.425, 0.45000002);
    biomes[149] = new Biome(0.2, 0.4);
    biomes[151] = new Biome(0.2, 0.4);
    biomes[155] = new Biome(0.2, 0.4);
    biomes[156] = new Biome(0.55, 0.5);
    biomes[157] = new Biome(0.2, 0.4);
    biomes[158] = new Biome(0.3, 0.4);
    biomes[160] = new Biome(0.2, 0.2);
    biomes[161] = new Biome(0.2, 0.2);
    biomes[162] = new Biome(1.0, 0.5);
    biomes[163] = new Biome(0.3625, 1.225);
    biomes[164] = new Biome(1.05, 1.2125001);
    biomes[165] = new Biome(0.1, 0.2);
    biomes[166] = new Biome(0.45, 0.3);
    biomes[167] = new Biome(0.45, 0.3);
    biomes[168] = new Biome(0.1, 0.2);
    biomes[169] = new Biome(0.45, 0.3);
    biomes[170] = new Biome(0.1, 0.2);
    biomes[171] = new Biome(0.1, 0.2);
    biomes[172] = new Biome(0.1, 0.2);
    biomes[173] = new Biome(0.1, 0.2);

    minLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, -15, 0);
    maxLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, -15, 0);
    mainLimitPerlinNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, -7, 0);

    surfaceNoise = std::make_unique<PerlinNoiseGenerator>(randomSeed, -3, 0);

    randomSeed.skip(2620);
    depthNoise = std::make_unique<OctavesNoiseGenerator>(randomSeed, -15, 0);
    endNoise = nullptr;

    biomeProvider = std::make_unique<OverworldBiomeProvider>(seed, false, false);

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            biomeWeights[i + 2 + (j + 2) * 5] = 10.0F / std::sqrt(static_cast<float>(i * i + j * j) + 0.2F);
        }
    }
}

auto NoiseChunkGenerator::getNoiseValue(int32_t x, int32_t z) -> float {
    auto scale = 256.0f;
    auto frequency = 1.0f / scale;

    auto amplitute = 1.0f;
    auto lacunarity = 2.0f;
    auto persistence = 0.5f;

    auto val = 0.0f;
    auto max = 0.0f;

    for (auto i = 0; i < 8; i++) {
        auto noise = glm::simplex(glm::vec2{float(x) * frequency, float(z) * frequency});
        noise = noise * 0.5f + 0.5f;

        val += noise * amplitute;
        max += amplitute;

        frequency *= lacunarity;
        amplitute *= persistence;
    }

    return val / max;
}

void NoiseChunkGenerator::makeBedrock(Chunk *chunk, BlockTable &pallete, Random &rand) const {
    const auto maxAvailableHeight = dimensionHeight - 1 - bedrockRoofPosition;
    const bool makeRoofBedrock = maxAvailableHeight + 4 >= 0 && maxAvailableHeight < dimensionHeight;
    const bool makeFloorBedrock = bedrockFloorPosition + 4 >= 0 && bedrockFloorPosition < dimensionHeight;

    if (makeRoofBedrock || makeFloorBedrock) {
        for (auto x = 0; x <= 15; x++) {
            for (auto z = 0; z <= 15; z++) {
                if (makeRoofBedrock) {
                    for (auto y = 0; y < 5; y++) {
                        if (y <= rand.nextInt(5)) {
                            chunk->setBlock(x, maxAvailableHeight - y, z, BlockData{pallete.getId("bedrock"), 0});
                        }
                    }
                }

                if (makeFloorBedrock) {
                    for (auto y = 4; y >= 0; y--) {
                        if (y <= rand.nextInt(5)) {
                            chunk->setBlock(x, bedrockFloorPosition + y, z, BlockData{pallete.getId("bedrock"), 0});
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
        const double x2 = maintainPrecision((double)x * xzScale * d);
        const double y2 = maintainPrecision((double)y * yScale * d);
        const double z2 = maintainPrecision((double)z * xzScale * d);
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
                c += mainNoise->getNoiseValue(maintainPrecision((double)x * xzFactor * d), maintainPrecision((double)y * yFactor * d), maintainPrecision((double)z * xzFactor * d), yFactor * d, (double)y * yFactor * d) / d;
            }
        }

        d /= 2.0;
    }

    return clampedLerp(a / 512.0, b / 512.0, (c / 10.0 + 1.0) / 2.0);
}

double NoiseChunkGenerator::getRandomDensity(int x, int z) {
    const double noise = depthNoise->getValue(x * 200, 10.0, z * 200, 1.0, 0.0, true);
    const double a = noise < 0.0 ? -noise * 0.3 : noise;
    const double b = a * 24.575625 - 2.0;
    return b < 0.0 ? b * 0.009486607142857142 : std::min(b, 1.0) * 0.006640625;
}

void NoiseChunkGenerator::fillNoiseColumn(double column[33], int xpos, int zpos) {
//    const auto biomeProvider = region.world->getBiomeProvider();

    double biomeDepth;
    double biomeScale;
//      if (this.endNoise != null) {
//         biomeDepth = EndBiomeProvider.getRandomNoise(this.endNoise, xpos, zpos) - 8.0F;
//         if (biomeDepth > 0.0D) {
//            biomeScale = 0.25D;
//         } else {
//            biomeScale = 1.0D;
//         }
//      } else {
    float f = 0.0F;
    float f1 = 0.0F;
    float f2 = 0.0F;
    const int seaLevel = 63;//settings->seaLevel;
    const float mainBiomeDepth = biomeProvider->getNoiseBiome(xpos, seaLevel, zpos)->getBaseHeight();

    for (int xPos = -2; xPos <= 2; ++xPos) {
        for (int zPos = -2; zPos <= 2; ++zPos) {
            const auto biome = biomeProvider->getNoiseBiome(xpos + xPos, seaLevel, zpos + zPos);
            const float secondBiomeDepth = biome->getBaseHeight();
            const float scale = biome->getHeightVariation();
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
//      }
    const double xzScale = 684.412 * sampling.xz_scale;
    const double yScale = 684.412 * sampling.y_scale;
    const double xzFactor = xzScale / sampling.xz_factor;
    const double yFactor = yScale / sampling.y_factor;
    const double randomDensity = getRandomDensity(xpos, zpos);
    const double destinyFactor = 1.0;// noisesettings.destinyFactor();
    const double densityOffset = -0.46875;// noisesettings.densityOffset();

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

        if (topSlide.size > 0.0) {
            noise = clampedLerp(topSlide.target, noise, ((double)(noiseSizeY - y) - topSlide.offset) / topSlide.size);
        }

        if (bottomSlide.size > 0.0) {
            noise = clampedLerp(bottomSlide.target, noise, ((double)y - bottomSlide.offset) / bottomSlide.size);
        }

        column[y] = noise;
    }
}

//void NoiseChunkGenerator::generateNoise(WorldGenRegion& region, Chunk* chunk, int chunkPosX, int chunkPosZ) {
//    const int seaLevel = region.getSeaLevel();
//    const int xStart = chunkPosX << 4;
//    const int zStart = chunkPosZ << 4;
//
//    for (int z = 0; z < noiseSizeZ + 1; ++z) {
//        fillNoiseColumn(region, noises[0][z], chunkPosX * noiseSizeX, chunkPosZ * noiseSizeZ + z);
//    }
//
//    for (int x = 0; x < noiseSizeX; x++) {
//        for (int z = 0; z < noiseSizeZ + 1; ++z) {
//            fillNoiseColumn(region, noises[1][z], chunkPosX * noiseSizeX + x + 1, chunkPosZ * noiseSizeZ + z);
//        }
//
//        for (int z = 0; z < noiseSizeZ; ++z) {
//            for (int y = noiseSizeY - 1; y >= 0; --y) {
//                const double d0 = noises[0][z][y];
//                const double d1 = noises[0][z + 1][y];
//                const double d2 = noises[1][z][y];
//                const double d3 = noises[1][z + 1][y];
//                const double d4 = noises[0][z][y + 1];
//                const double d5 = noises[0][z + 1][y + 1];
//                const double d6 = noises[1][z][y + 1];
//                const double d7 = noises[1][z + 1][y + 1];
//
//                for (int l1 = verticalNoiseGranularity - 1; l1 >= 0; --l1) {
//                    const int ypos = y * verticalNoiseGranularity + l1;
//                    //                    const int k2 = ypos >> 4;
//
//                    const double d8 = (double)l1 / (double)verticalNoiseGranularity;
//                    const double d9 = lerp(d8, d0, d4);
//                    const double d10 = lerp(d8, d2, d6);
//                    const double d11 = lerp(d8, d1, d5);
//                    const double d12 = lerp(d8, d3, d7);
//
//                    for (int l2 = 0; l2 < horizontalNoiseGranularity; ++l2) {
//                        const int xpos = xStart + x * horizontalNoiseGranularity + l2;
//                        const double d13 = (double)l2 / (double)horizontalNoiseGranularity;
//                        const double d14 = lerp(d13, d9, d10);
//                        const double d15 = lerp(d13, d11, d12);
//                        for (int k3 = 0; k3 < horizontalNoiseGranularity; ++k3) {
//                            const int zpos = zStart + z * horizontalNoiseGranularity + k3;
//                            //                            int i4 = zpos & 15;
//                            const double d16 = (double)k3 / (double)horizontalNoiseGranularity;
//                            const double d17 = lerp(d16, d14, d15);
//                            double d18 = clamp(d17 / 200.0, -1.0, 1.0);
//
//                            d18 = (d18 / 2.0) - ((d18 * d18 * d18) / 24.0);
//
//                            if (d18 > 0.0) {
//                                chunk->SetBlockData(xpos & 15, ypos/* & 15*/, zpos & 15, TCRAFT::BlockData{ E_BLOCKTYPE_STONE, 0 });
//                            }
//                            else if (ypos < seaLevel) {
//                                chunk->SetBlockData(xpos & 15, ypos/* & 15*/, zpos & 15, TCRAFT::BlockData{ oceanBlock, 0 });
//                            }
//                        }
//                    }
//                }
//            }
//        }
//
//        std::swap(noises[0], noises[1]);
//    }
//}

void NoiseChunkGenerator::generateSurface(WorldGenRegion &region, Chunk *chunk, BlockTable &pallete) {
    const auto xStart = chunk->pos.getStartX();
    const auto zStart = chunk->pos.getStartZ();

    Random rand{};
    rand.setBaseChunkSeed(chunk->pos.x, chunk->pos.z);

    for (auto x = 0; x < 16; x++) {
        for (auto z = 0; z < 16; z++) {
            const auto xPos = xStart + x;
            const auto zPos = zStart + z;
            const auto yPos = chunk->getTopBlockY(/*Heightmap.Type.WORLD_SURFACE_WG,*/ x, z) + 1;
            const auto noise = 15.0 * surfaceNoise->noiseAt(
                    static_cast<double>(xPos) * 0.0625,
                    static_cast<double>(zPos) * 0.0625,
                    0.0625,
                    (double) x * 0.0625
            );
            auto biome = region.getBiome(xPos, yPos, zPos);
            biome->buildSurface(rand, chunk, xPos, zPos, yPos, noise, defaultBlock, defaultFluid,
                                {pallete.getId("grass")}, {pallete.getId("dirt")}, {pallete.getId("gravel")}, 63);

//            biome->buildSurface(rand, chunk, xPos, zPos, yPos, noise, defaultBlock, defaultFluid, 63);
        }
    }

    makeBedrock(chunk, pallete, rand);
}

void NoiseChunkGenerator::generateTerrain(Chunk *chunk, BlockTable &pallete) {
    const auto chunkPosX = chunk->pos.x;
    const auto chunkPosZ = chunk->pos.z;
    const auto xStart = chunkPosX << 4;
    const auto zStart = chunkPosZ << 4;
    const int seaLevel = 63;

    double noises[2][5][33];
    auto noises_0 = noises[0];
    auto noises_1 = noises[1];

    for (int z = 0; z < noiseSizeZ + 1; ++z) {
        fillNoiseColumn(noises_0[z], chunkPosX * noiseSizeX, chunkPosZ * noiseSizeZ + z);
    }

    for (int x = 0; x < noiseSizeX; x++) {
        for (int z = 0; z < noiseSizeZ + 1; ++z) {
            fillNoiseColumn(noises_1[z], chunkPosX * noiseSizeX + x + 1, chunkPosZ * noiseSizeZ + z);
        }

        for (int z = 0; z < noiseSizeZ; ++z) {
            for (int y = noiseSizeY - 1; y >= 0; --y) {
                const double d0 = noises_0[z][y];
                const double d1 = noises_0[z + 1][y];
                const double d2 = noises_1[z][y];
                const double d3 = noises_1[z + 1][y];
                const double d4 = noises_0[z][y + 1];
                const double d5 = noises_0[z + 1][y + 1];
                const double d6 = noises_1[z][y + 1];
                const double d7 = noises_1[z + 1][y + 1];

                for (int l1 = verticalNoiseGranularity - 1; l1 >= 0; --l1) {
                    const int ypos = y * verticalNoiseGranularity + l1;

                    const double d8 = (double) l1 / (double) verticalNoiseGranularity;
                    const double d9 = lerp(d8, d0, d4);
                    const double d10 = lerp(d8, d2, d6);
                    const double d11 = lerp(d8, d1, d5);
                    const double d12 = lerp(d8, d3, d7);

                    for (int l2 = 0; l2 < horizontalNoiseGranularity; ++l2) {
                        const int xpos = /*xStart +*/ x * horizontalNoiseGranularity + l2;
                        const double d13 = (double) l2 / (double) horizontalNoiseGranularity;
                        const double d14 = lerp(d13, d9, d10);
                        const double d15 = lerp(d13, d11, d12);

                        for (int k3 = 0; k3 < horizontalNoiseGranularity; ++k3) {
                            const int zpos = /*zStart + */z * horizontalNoiseGranularity + k3;
                            const double d16 = (double) k3 / (double) horizontalNoiseGranularity;
                            const double d17 = lerp(d16, d14, d15);
                            double d18 = clamp(d17 / 200.0, -1.0, 1.0);

                            d18 = (d18 / 2.0) - ((d18 * d18 * d18) / 24.0);


                            if (d18 > 0.0) {
                                chunk->setBlock(xpos & 15, ypos, zpos & 15, BlockData{pallete.getId("stone")});
                            } else if (ypos < seaLevel) {
//                                fmt::print("{}, {}\n", xStart + (xpos & 15), zStart + (zpos & 15));

                                chunk->setBlock(xpos & 15, ypos, zpos & 15, BlockData{pallete.getId("water")});
                            }
                        }
                    }
                }
            }
        }

        std::swap(noises_0, noises_1);
    }


//    const auto xStart = chunk->pos.getStartX();
//    const auto zStart = chunk->pos.getStartZ();
//
//    Random random{};
//    random.setBaseChunkSeed(chunk->pos.x, chunk->pos.z);
//
//    for (auto x = xStart; x < xStart + 16; x++) {
//        for (auto z = zStart; z < zStart + 16; z++) {
//            const auto noise = getNoiseValue(x, z);
//            const auto height = static_cast<int32_t>(noise * 60 + 40);
//
//            chunk->heightmap[x & 15][z & 15] = height;
//
//            for (auto y = 0; y < height; y++) {
//                chunk->setBlock(x, y, z, BlockData{pallete.getId("grass"), 0});
//            }
//
//            for (auto y = height; y < 68; y++) {
//                chunk->setBlock(x, y, z, BlockData{pallete.getId("water"), 0});
//            }
//        }
//    }
}