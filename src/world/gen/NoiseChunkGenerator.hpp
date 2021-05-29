#pragma once

#include "ChunkGenerator.hpp"
#include "OctavesNoiseGenerator.hpp"
#include "PerlinNoiseGenerator.hpp"
#include "settings/DimensionSettings.hpp"
#include "../../block/BlockData.hpp"

#include <memory>
#include <optional>
#include <span>

struct Random;
struct BiomeProvider;

class NoiseChunkGenerator;

struct NoiseProvider {
    virtual ~NoiseProvider() = default;
    virtual std::pair<double, double> get(NoiseChunkGenerator* generator, int xpos, int zpos) = 0;
};

struct NoiseChunkGenerator : public ChunkGenerator {
    static constexpr std::array<float, 25> biomeWeights = [] {
        std::array<float, 25> weights{};
        for (int i = -2; i <= 2; ++i) {
            for (int j = -2; j <= 2; ++j) {
                weights[i + 2 + (j + 2) * 5] = 10.0F / std::sqrt(static_cast<float>(i * i + j * j) + 0.2F);
            }
        }
        return weights;
    }();

//    int dimensionHeight;
    int noiseSizeX;
    int noiseSizeZ;
    int noiseSizeY;
    int horizontalNoiseGranularity;
    int verticalNoiseGranularity;
//    int bedrockFloorPosition;
//    int bedrockRoofPosition;

    std::array<std::vector<std::vector<double>>, 2> cacheNoiseColumns;

    std::unique_ptr<OctavesNoiseGenerator> minLimitPerlinNoise;
    std::unique_ptr<OctavesNoiseGenerator> maxLimitPerlinNoise;
    std::unique_ptr<OctavesNoiseGenerator> mainLimitPerlinNoise;

    std::unique_ptr<INoiseGenerator> surfaceNoise;
    std::unique_ptr<OctavesNoiseGenerator> depthNoise;
//    std::unique_ptr<SimplexNoiseGenerator> endNoise;

    std::unique_ptr<NoiseProvider> noiseProvider;

    DimensionSettings settings;

public:
    NoiseChunkGenerator(int64_t seed, DimensionSettings settings, std::unique_ptr<BiomeProvider>&& biomeProvider);

    double getRandomDensity(int x, int z);
    double sampleAndClampNoise(int x, int y, int z, double xzScale, double yScale, double xzFactor, double yFactor);
    void fillNoiseColumn(std::span<double> column, int xpos, int zpos);

    void makeBedrock(Chunk& chunk, Random& random) const;
    void generateSurface(WorldGenRegion& region, Chunk& chunk) override;
    void generateTerrain(Chunk& chunk) override;

    int getSeaLevel() const {
        return settings.seaLevel;
    }

    std::vector<double> getNoiseColumn(int x, int z);
    int getColumn(int x, int z, std::span<BlockData> datas, bool(*predicate)(BlockData));
};