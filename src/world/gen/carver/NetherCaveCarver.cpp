#include "NetherCaveCarver.hpp"
#include "../../chunk/Chunk.hpp"
#include "../../../util/Random.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

NetherCaveCarver::NetherCaveCarver() : CaveWorldCarver(128) {
    carvableBlocks = {
    };
    carvableFluids = {

    };
}

int NetherCaveCarver::getRandomStartY(Random &rand) {
    return rand.nextInt(maxHeight);
}

float NetherCaveCarver::getRandomCaveRadius(Random &rand) {
    return (rand.nextFloat() * 2.0F + rand.nextFloat()) * 2.0F;
}

bool NetherCaveCarver::carveBlock(Chunk &chunk, const BiomeReadFn &getBiome, Random &rand, int seaLevel, int chunkX, int chunkZ, int posX, int posZ, int x, int posY, int z, bool &isSurface) {
//    int i = x | z << 4 | posY << 8;
//    if (carvingMask.get(i)) {
//        return false;
//    }
//    carvingMask.set(i);
    if (carvableBlocks.contains(chunk.getBlock(posX, posY, posZ))) {
        if (posY <= 31) {
            chunk.setData(posX, posY, posZ, Blocks::LAVA->getDefaultState()/*, false*/);
        } else {
            chunk.setData(posX, posY, posZ, Blocks::AIR->getDefaultState()/*, false*/);
        }
        return true;
    }
    return false;
}

