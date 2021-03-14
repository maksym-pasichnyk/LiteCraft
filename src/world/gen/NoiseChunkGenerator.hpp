#pragma once

#include "ChunkGenerator.hpp"
#include "OctavesNoiseGenerator.hpp"
#include "PerlinNoiseGenerator.hpp"
#include "../../block/BlockData.hpp"

#include <memory>

struct Random;
struct BiomeProvider;

class NoiseChunkGenerator : public ChunkGenerator {
    std::array<float, 25> biomeWeights;
    int dimensionHeight;
    int noiseSizeX;
    int noiseSizeZ;
    int noiseSizeY;
    int horizontalNoiseGranularity;
    int verticalNoiseGranularity;
    int bedrockFloorPosition;
    int bedrockRoofPosition;

    std::array<std::array<std::array<double, 33>, 5>, 2> noises{};

    std::unique_ptr<OctavesNoiseGenerator> minLimitPerlinNoise;
    std::unique_ptr<OctavesNoiseGenerator> maxLimitPerlinNoise;
    std::unique_ptr<OctavesNoiseGenerator> mainLimitPerlinNoise;

    std::unique_ptr<INoiseGenerator> surfaceNoise;
    std::unique_ptr<OctavesNoiseGenerator> depthNoise;
    std::unique_ptr<SimplexNoiseGenerator> endNoise;

    BlockData defaultBlock;
    BlockData defaultFluid;

public:
    NoiseChunkGenerator(int64_t seed, std::unique_ptr<BiomeProvider>&& biomeProvider);

    double getRandomDensity(int x, int z);
    double sampleAndClampNoise(int x, int y, int z, double xzScale, double yScale, double xzFactor, double yFactor);
    void fillNoiseColumn(std::array<double, 33>& column, int xpos, int zpos);

    void makeBedrock(Chunk& chunk, Random& rand) const;
    void generateSurface(WorldGenRegion& region, Chunk& chunk) override;
    void generateTerrain(Chunk& chunk) override;
};