#pragma once

#include <functional>
#include <memory>
#include <set>

#include <glm/vec3.hpp>

struct Chunk;
struct Block;
struct Biome;
struct Random;
struct BlockData;

using BiomeReadFn = std::function<Biome*(glm::ivec3)>;

struct WorldCarver {
    static std::unique_ptr<WorldCarver> CAVE;
    static std::unique_ptr<WorldCarver> NETHER_CAVE;
    static std::unique_ptr<WorldCarver> CANYON;
//    static std::unique_ptr<WorldCarver> UNDERWATER_CANYON;
//    static std::unique_ptr<WorldCarver> UNDERWATER_CAVE;

    static void registerCarvers();

    int32_t maxHeight;
    std::set<Block*> carvableBlocks;
    std::set<Block*> carvableFluids;

    explicit WorldCarver(int32_t maxHeight);

    int32_t getRange() const {
        return 4;
    }
    bool canCarveBlock(const BlockData& data, const BlockData& above);

    virtual bool shouldCarveBlock(double d0, double d1, double d2, int d3) = 0;
    virtual bool carveRegion(Chunk& chunk, const BiomeReadFn& getBiome, Random& rand, int32_t seaLevel, int32_t xoffset, int32_t zoffset, int32_t chunkx, int32_t chunkz/*, BitSet carvingMask*/) = 0;
    virtual bool carveBlock(Chunk& chunk, const BiomeReadFn& getBiome, /*BitSet carvingMask,*/ Random& rand, int seaLevel, int chunkX, int chunkZ, int posX, int posZ, int x, int posY, int z, bool& isSurface);
    virtual bool hasCarvableFluids(Chunk& chunk, int chunkX, int chunkZ, int minX, int maxX, int minY, int maxY, int minZ, int maxZ);

    bool carveBlocks(Chunk& chunk, const BiomeReadFn& getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double xcoord, double ycoord, double zcoord, double unk1, double unk2/*, BitSet carvingMask*/);
    bool isInsideCarveRadius(int chunkx, int chunkz, double xcoord, double zcoord, int yoffset, int ycoord, float radius);
    bool isOnEdge(int minX, int maxX, int minZ, int maxZ, int x, int z);
};