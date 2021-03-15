#pragma once

#include <memory>
#include <set>

struct Chunk;
struct Block;
struct Random;

struct WorldCarver {
    static std::unique_ptr<WorldCarver> CAVE;
    static std::unique_ptr<WorldCarver> NETHER_CAVE;
    static std::unique_ptr<WorldCarver> CANYON;
    static std::unique_ptr<WorldCarver> UNDERWATER_CANYON;
    static std::unique_ptr<WorldCarver> UNDERWATER_CAVE;

    static void registerCarvers();

    int32_t maxHeight;
    std::set<Block*> carvableBlocks;
    std::set<Block*> carvableFluids;

    explicit WorldCarver(int32_t maxHeight);

    int32_t getRange() const {
        return 4;
    }

    virtual bool carveRegion(Chunk& chunk, Random& rand, int32_t seaLevel, int32_t xoffset, int32_t zoffset, int32_t chunkx, int32_t chunkz/*, BitSet carvingMask*/) = 0;
};