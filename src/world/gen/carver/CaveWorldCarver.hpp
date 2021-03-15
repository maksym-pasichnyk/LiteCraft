#pragma once

#include "WorldCarver.hpp"

struct CaveWorldCarver : WorldCarver {
    using WorldCarver::WorldCarver;

    virtual double getUnkScale() {
        return 1.0;
    }

    virtual int getMaxTryCount() {
        return 15;
    }

    virtual int getRandomStartY(Random& rand);
    virtual float getRandomCaveRadius(Random& rand);

    bool carveRegion(Chunk &chunk, const BiomeReadFn& getBiome, Random &rand, int seaLevel, int xoffset, int zoffset, int chunkx, int chunkz) override;

    void addRoom(Chunk &chunk, const BiomeReadFn& getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double randOffsetXCoord, double ycoord, double zcoord, float caveRadius, double unk3/*, BitSet carvingMask*/);
    void addTunel(Chunk &chunk, const BiomeReadFn& getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double xcoord, double ycoord, double zcoord, float radius, float pitch, float yaw, int unk1, int unk2, double unk3/*, BitSet carvingMask*/);

    bool shouldCarveBlock(double d0, double d1, double d2, int d3) override;
};