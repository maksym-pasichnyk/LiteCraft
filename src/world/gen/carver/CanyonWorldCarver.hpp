#pragma once

#include "WorldCarver.hpp"

struct CanyonWorldCarver : WorldCarver {
    CanyonWorldCarver() : WorldCarver(256) {}

    bool carveRegion(Chunk &chunk, Random &rand, int seaLevel, int xoffset, int zoffset, int chunkx, int chunkz) override {
        return false;
    }
};