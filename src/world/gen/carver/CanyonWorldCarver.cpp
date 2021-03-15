#include "CanyonWorldCarver.hpp"
#include "../../../util/Random.hpp"

bool CanyonWorldCarver::carveRegion(Chunk &chunk, const BiomeReadFn &getBiome, Random &rand, int seaLevel, int xoffset, int zoffset, int chunkx, int chunkz) {
    const int i = (getRange() * 2 - 1) * 16;
    const double xpos = xoffset * 16 + rand.nextInt(16);
    const double ypos = rand.nextInt(rand.nextInt(40) + 8) + 20;
    const double zpos = zoffset * 16 + rand.nextInt(16);

    const float pitch = rand.nextFloat() * (static_cast<float>(M_PI) * 2.0F);
    const float yaw = (rand.nextFloat() - 0.5F) * 2.0F / 8.0F;
    const float radius = (rand.nextFloat() * 2.0F + rand.nextFloat()) * 2.0F;
    const int j = i - rand.nextInt(i / 4);

    addTunel(chunk, getBiome, rand.nextLong(), seaLevel, chunkx, chunkz, xpos, ypos, zpos, radius, pitch, yaw, 0, j, 3.0/*, carvingMask*/);
    return true;
}

void CanyonWorldCarver::addTunel(Chunk &chunk, const BiomeReadFn &getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double xcoord, double ycoord, double zcoord, float radius, float pitch, float yaw, int unk1, int unk2, double unk3) {
    auto rand = Random::from(seed);

    float f = 1.0F;
    for (int i = 0; i < 256; ++i) {
        if (i == 0 || rand.nextInt(3) == 0) {
            f = 1.0F + rand.nextFloat() * rand.nextFloat();
        }

        rs[i] = f * f;
    }

    float f4 = 0.0F;
    float f1 = 0.0F;

    for (int j = unk1; j < unk2; ++j) {
        double d0 = 1.5 + static_cast<double>(std::sin(static_cast<float>(j) * static_cast<float>(M_PI) / static_cast<float>(unk2)) * radius);
        double d1 = d0 * unk3;
        d0 = d0 * (static_cast<double>(rand.nextFloat()) * 0.25 + 0.75);
        d1 = d1 * (static_cast<double>(rand.nextFloat()) * 0.25 + 0.75);
        float f2 = std::cos(yaw);
        float f3 = std::sin(yaw);
        xcoord += std::cos(pitch) * f2;
        ycoord += f3;
        zcoord += std::sin(pitch) * f2;
        yaw = yaw * 0.7F;
        yaw = yaw + f1 * 0.05F;
        pitch += f4 * 0.05F;
        f1 = f1 * 0.8F + (rand.nextFloat() - rand.nextFloat()) * rand.nextFloat() * 2.0F;
        f4 = f4 * 0.5F + (rand.nextFloat() - rand.nextFloat()) * rand.nextFloat() * 4.0F;
        if (rand.nextInt(4) != 0) {
            if (!isInsideCarveRadius(chunkx, chunkz, xcoord, zcoord, j, unk2, radius)) {
                return;
            }

            carveBlocks(chunk, getBiome, seed, seaLevel, chunkx, chunkz, xcoord, ycoord, zcoord, d0, d1/*, carvingMask*/);
        }
    }
}
