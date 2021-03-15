#pragma once

#include "CaveWorldCarver.hpp"

struct NetherCaveCarver : CaveWorldCarver {
    NetherCaveCarver();

    int getMaxTryCount() override {
        return 10;
    }
    double getUnkScale() override {
        return 5.0;
    }
    int getRandomStartY(Random &rand) override;
    float getRandomCaveRadius(Random &rand) override;
    bool carveBlock(Chunk& chunk, const BiomeReadFn& getBiome, /*BitSet carvingMask,*/ Random& rand, int seaLevel, int chunkX, int chunkZ, int posX, int posZ, int x, int posY, int z, bool& isSurface) override;
};