#pragma once

#include "WorldCarver.hpp"

struct CaveWorldCarver : WorldCarver {
    using WorldCarver::WorldCarver;

    bool carveRegion(Chunk &chunk, Random &rand, int seaLevel, int xoffset, int zoffset, int chunkx, int chunkz) override {
        return false;
    }
};