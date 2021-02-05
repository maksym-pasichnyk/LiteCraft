#include "Biome.hpp"

#include "src/Chunk.hpp"

void Biome::buildSurface(Random& rand, Chunk* chunk, int xStart, int zStart, int startHeight, double noise, BlockData defaultBlock, BlockData defaultFluid, BlockData top, BlockData middle, BlockData bottom, int sealevel) {
    BlockData blockstate = top;
    BlockData blockstate1 = middle;
    int i = -1;
    int j = (int)(noise / 3.0 + 3.0 + rand.nextDouble() * 0.25);
    int xPos = xStart & 15;
    int zPos = zStart & 15;

    for(int yPos = startHeight; yPos >= 0; --yPos) {
        BlockData blockstate2 = chunk->getBlock(xPos, yPos, zPos);
        if (/*blockstate2.isAir()*/blockstate2.id == BlockID::AIR) {
            i = -1;
} else if (/*blockstate2.isIn(defaultBlock.getBlock())*/ blockstate2.id == defaultBlock.id) {
            if (i == -1) {
                if (j <= 0) {
                    blockstate = {BlockID::AIR, 0};// Blocks.AIR.getDefaultState();
                    blockstate1 = defaultBlock;
                } else if (yPos >= sealevel - 4 && yPos <= sealevel + 1) {
                    blockstate = top;
                    blockstate1 = middle;
                }

                if (yPos < sealevel && /*(blockstate == null || blockstate.isAir())*/ blockstate.id == BlockID::AIR) {
//                    if (biome->getTemperature(xStart, yPos, zStart) < 0.15F) {
//                        blockstate = Blocks.ICE.getDefaultState();
//                    } else {
                        blockstate = defaultFluid;
//                    }
                }

                i = j;
                if (yPos >= sealevel - 1) {
                    chunk->setBlock(xPos, yPos, zPos, blockstate/*, false*/);
                } else if (yPos < sealevel - 7 - j) {
                    blockstate = BlockData{BlockID::AIR, 0};// Blocks.AIR.getDefaultState();
                    blockstate1 = defaultBlock;
                    chunk->setBlock(xPos, yPos, zPos, bottom/*, false*/);
                } else {
                    chunk->setBlock(xPos, yPos, zPos, blockstate1/*, false*/);
                }
            } else if (i > 0) {
                --i;
                chunk->setBlock(xPos, yPos, zPos, blockstate1/*, false*/);
//                if (i == 0 && blockstate1.isIn(Blocks.SAND) && j > 1) {
//                    i = random.nextInt(4) + Math.max(0, yPos - 63);
//                    blockstate1 = blockstate1.isIn(Blocks.RED_SAND)
//                                  ? Blocks.RED_SANDSTONE.getDefaultState()
//                                  : Blocks.SANDSTONE.getDefaultState();
//                }
            }
        }
    }
}
