#pragma once

#include "ChunkGenerator.hpp"
#include "OctavesNoiseGenerator.hpp"
#include "PerlinNoiseGenerator.hpp"

#include <memory>

struct Random;
struct Biome;

struct BiomeProvider {
    virtual ~BiomeProvider() = default;
    virtual Biome* getNoiseBiome(int x, int y, int z) = 0;
};

class NoiseChunkGenerator : public ChunkGenerator {
    std::unique_ptr<BiomeProvider> biomeProvider;

    std::array<float, 25> biomeWeights;
    int noiseSizeX = 4;
    int noiseSizeZ = 4;
    int noiseSizeY = 32;
    int horizontalNoiseGranularity = 4;
    int verticalNoiseGranularity = 8;

    std::unique_ptr<OctavesNoiseGenerator> minLimitPerlinNoise;
    std::unique_ptr<OctavesNoiseGenerator> maxLimitPerlinNoise;
    std::unique_ptr<OctavesNoiseGenerator> mainLimitPerlinNoise;

    std::unique_ptr<INoiseGenerator> surfaceNoise;
    std::unique_ptr<OctavesNoiseGenerator> depthNoise;
    std::unique_ptr<SimplexNoiseGenerator> endNoise;

    int64_t seed = 1;
    int bedrockFloorPosition = 0;
    int bedrockRoofPosition = -1;
    int dimensionHeight = 256;

    BlockData defaultBlock;
    BlockData defaultFluid;

public:
    NoiseChunkGenerator(BlockTable& pallete);

    auto getNoiseValue(int32_t x, int32_t z) -> float;

    double getRandomDensity(int x, int z);
    double sampleAndClampNoise(int x, int y, int z, double xzScale, double yScale, double xzFactor, double yFactor);
    void fillNoiseColumn(double column[33], int xpos, int zpos);

    void makeBedrock(Chunk* chunk, BlockTable& pallete, Random& rand) const;
    void generateSurface(WorldGenRegion& region, Chunk* chunk, BlockTable& pallete) override;
    void generateTerrain(Chunk* chunk, BlockTable& pallete) override;
};