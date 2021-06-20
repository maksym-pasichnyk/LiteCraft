#pragma once

#include "WorldCarver.hpp"
#include "ThreadLocal.hpp"

struct CanyonWorldCarver : WorldCarver {
    ThreadLocal<std::array<float, 1024>> rs{};

    CanyonWorldCarver() : WorldCarver(256) {}

    bool isOutsideCaveRadius(double d0, double d1, double d2, int d3) override {
        return ((((d0 * d0) + (d2 * d2)) * static_cast<double>((*rs.get())[d3 - 1])) + ((d1 * d1) / 6.0)) >= 1.0;
    }

    bool carveRegion(Chunk &chunk, const BiomeReadFn& getBiome, Random &rand, int seaLevel, int xoffset, int zoffset, int chunkx, int chunkz) override;
    void addTunel(Chunk &chunk, const BiomeReadFn& getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double xcoord, double ycoord, double zcoord, float radius, float pitch, float yaw, int unk1, int unk2, double unk3/*, BitSet carvingMask*/);
};