#include "CaveWorldCarver.hpp"
#include "../../../util/Random.hpp"

#include <cmath>

int CaveWorldCarver::getRandomStartY(Random &rand) {
    return rand.nextInt(rand.nextInt(120) + 8);
}

float CaveWorldCarver::getRandomCaveRadius(Random &rand) {
    const float f0 = rand.nextFloat();
    float radius = f0 * 2.0F + rand.nextFloat();
    if (rand.nextInt(10) == 0) {
        const float f1 = rand.nextFloat();
        radius *= f1 * rand.nextFloat() * 3.0F + 1.0F;
    }
    return radius;
}

bool CaveWorldCarver::carveRegion(Chunk &chunk, const BiomeReadFn &getBiome, Random &rand, int seaLevel, int xoffset, int zoffset, int chunkx, int chunkz) {
    const int i = (getRange() * 2 - 1) * 16;
    const int j = rand.nextInt(rand.nextInt(rand.nextInt(getMaxTryCount()) + 1) + 1);

    for (int k = 0; k < j; ++k) {
        const double xcoord = xoffset * 16 + rand.nextInt(16);
        const double ycoord = getRandomStartY(rand);
        const double zcoord = zoffset * 16 + rand.nextInt(16);
        int l = 1;
        if (rand.nextInt(4) == 0) {
            const float f1 = 1.0F + rand.nextFloat() * 6.0F;
            addRoom(chunk, getBiome, rand.nextLong(), seaLevel, chunkx, chunkz, xcoord, ycoord, zcoord, f1, 0.5/*, carvingMask*/);
            l += rand.nextInt(4);
        }

        for (int k1 = 0; k1 < l; ++k1) {
            const float pitch = rand.nextFloat() * (static_cast<float>(M_PI) * 2.0F);
            const float yaw = (rand.nextFloat() - 0.5F) / 4.0F;
            const float caveRadius = getRandomCaveRadius(rand);
            const int i1 = i - rand.nextInt(i / 4);
            addTunel(chunk, getBiome, rand.nextLong(), seaLevel, chunkx, chunkz, xcoord, ycoord, zcoord, caveRadius, pitch, yaw, 0, i1, getUnkScale()/*, carvingMask*/);
        }
    }

    return false;
}

void CaveWorldCarver::addRoom(Chunk &chunk, const BiomeReadFn& getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double randOffsetXCoord, double ycoord, double zcoord, float caveRadius, double unk3/*, BitSet carvingMask*/) {
    const double d0 = 1.5 + static_cast<double>(std::sin(static_cast<float>(M_PI) / 2.0F) * caveRadius);
    const double d1 = d0 * unk3;
    carveBlocks(chunk, getBiome, seed, seaLevel, chunkx, chunkz, randOffsetXCoord + 1.0, ycoord, zcoord, d0, d1/*, carvingMask*/);
}

void CaveWorldCarver::addTunel(Chunk &chunk, const BiomeReadFn& getBiome, int64_t seed, int seaLevel, int chunkx, int chunkz, double xcoord, double ycoord, double zcoord, float radius, float pitch, float yaw, int unk1, int unk2, double unk3) {
    auto rand = Random::from(seed);
    const int i = rand.nextInt(unk2 / 2) + unk2 / 4;
    const bool flag = rand.nextInt(6) == 0;
    float f = 0.0F;
    float f1 = 0.0F;

    for (int j = unk1; j < unk2; ++j) {
        const double d0 = 1.5 + static_cast<double>(std::sin(static_cast<float>(M_PI) * (float)j / (float)unk2) * radius);
        const double d1 = d0 * unk3;
        const float f2 = std::cos(yaw);
        xcoord += std::cos(pitch) * f2;
        ycoord += std::sin(yaw);
        zcoord += std::sin(pitch) * f2;
        yaw = yaw * (flag ? 0.92F : 0.7F);
        yaw = yaw + f1 * 0.1F;
        pitch += f * 0.1F;
        const float g0 = rand.nextFloat();
        const float g1 = rand.nextFloat();
        f1 = f1 * 0.9F + (g0 - g1) * rand.nextFloat() * 2.0F;
        const float g2 = rand.nextFloat();
        const float g3 = rand.nextFloat();
        f = f * 0.75F + (g2 - g3) * rand.nextFloat() * 4.0F;
        if (j == i && radius > 1.0F) {
            const auto seed2 = rand.nextLong();
            addTunel(chunk, getBiome, seed2, seaLevel, chunkx, chunkz, xcoord, ycoord, zcoord, rand.nextFloat() * 0.5F + 0.5F, pitch - (static_cast<float>(M_PI) / 2.0F), yaw / 3.0F, j, unk2, 1.0/*, carvingMask*/);
            const auto seed3 = rand.nextLong();
            addTunel(chunk, getBiome, seed3, seaLevel, chunkx, chunkz, xcoord, ycoord, zcoord, rand.nextFloat() * 0.5F + 0.5F, pitch + (static_cast<float>(M_PI) / 2.0F), yaw / 3.0F, j, unk2, 1.0/*, carvingMask*/);
            return;
        }

        if (rand.nextInt(4) != 0) {
            if (!isInsideCarveRadius(chunkx, chunkz, xcoord, zcoord, j, unk2, radius)) {
                return;
            }

            carveBlocks(chunk, getBiome, seed, seaLevel, chunkx, chunkz, xcoord, ycoord, zcoord, d0, d1/*, carvingMask*/);
        }
    }
}

bool CaveWorldCarver::isOutsideCaveRadius(double d0, double d1, double d2, int d3) {
    return d1 <= -0.7 || d0 * d0 + d1 * d1 + d2 * d2 >= 1.0;
}
