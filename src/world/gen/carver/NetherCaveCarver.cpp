#include "NetherCaveCarver.hpp"
#include "../../chunk/Chunk.hpp"
#include <util/Random.hpp>
#include <block/Blocks.hpp>
#include <block/States.hpp>

NetherCaveCarver::NetherCaveCarver() : CaveWorldCarver(128) {
    carvableBlocks = {
        Blocks::STONE,
        Blocks::GRANITE,
        Blocks::DIORITE,
        Blocks::ANDESITE,
        Blocks::DIRT,
        Blocks::COARSE_DIRT,
        Blocks::PODZOL,
        Blocks::GRASS_BLOCK,
        Blocks::NETHERRACK,
        Blocks::SOUL_SAND,
        Blocks::SOUL_SOIL,
        Blocks::CRIMSON_NYLIUM,
        Blocks::WARPED_NYLIUM,
        Blocks::NETHER_WART_BLOCK,
        Blocks::WARPED_WART_BLOCK,
        Blocks::BASALT,
        Blocks::BLACKSTONE
    };
    carvableFluids = {
        Blocks::WATER,
        Blocks::LAVA,
    };
}

int NetherCaveCarver::getRandomStartY(Random &rand) {
    return rand.nextInt(maxHeight);
}

float NetherCaveCarver::getRandomCaveRadius(Random &rand) {
    const float f0 = rand.nextFloat();
    return (f0 * 2.0F + rand.nextFloat()) * 2.0F;
}

bool NetherCaveCarver::carveBlock(Chunk &chunk, const BiomeReadFn &getBiome, Random &rand, int seaLevel, int chunkX, int chunkZ, int posX, int posY, int posZ, bool &isSurface) {
//    int i = x | z << 4 | posY << 8;
//    if (carvingMask.get(i)) {
//        return false;
//    }
//    carvingMask.set(i);
    if (carvableBlocks.contains(chunk.getBlock(posX, posY, posZ))) {
        if (posY <= 31) {
            chunk.setData(posX, posY, posZ, States::LAVA/*, false*/);
        } else {
            chunk.setData(posX, posY, posZ, States::AIR/*, false*/);
        }
        return true;
    }
    return false;
}

