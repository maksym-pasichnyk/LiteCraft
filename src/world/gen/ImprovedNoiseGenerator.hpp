#pragma once

#include "SimplexNoiseGenerator.hpp"

#include <cmath>
#include <array>

static constexpr float MathHelper_lerp(float pct, float start, float end) {
    return start + pct * (end - start);
}

static constexpr double MathHelper_lerp(double pct, double start, double end) {
    return start + pct * (end - start);
}

static constexpr double MathHelper_lerp2(double xFade, double yFade, double d0, double d1, double d2, double d3) {
    return MathHelper_lerp(yFade, MathHelper_lerp(xFade, d0, d1), MathHelper_lerp(xFade, d2, d3));
}

static constexpr double MathHelper_lerp3(double xFade, double yFade, double zFade, double d0, double d1, double d2, double d3, double d4, double d5, double d6, double d7) {
    return MathHelper_lerp(zFade, MathHelper_lerp2(xFade, yFade, d0, d1, d2, d3), MathHelper_lerp2(xFade, yFade, d4, d5, d6, d7));
}

class ImprovedNoiseGenerator {
    std::array<int8_t, 256> permutations;

public:
    double xCoord;
    double yCoord;
    double zCoord;

    explicit ImprovedNoiseGenerator(Random&& rand) : ImprovedNoiseGenerator(rand) {}
    explicit ImprovedNoiseGenerator(Random& rand) {
        xCoord = rand.nextDouble() * 256.0;
        yCoord = rand.nextDouble() * 256.0;
        zCoord = rand.nextDouble() * 256.0;

        for (int i = 0; i < 256; ++i) {
            permutations[i] = i;
        }

        for (int i = 0; i < 256; ++i) {
            const int idx = rand.nextInt(256 - i);
            std::swap(permutations[i], permutations[i + idx]);
        }
    }

    int getPermutValue(int permutIndex) const {
        return permutations[permutIndex & 255] & 255;
    }

    double calcValue(int ix, int iy, int iz, double dx, double dy, double dz, double xFade, double yFade, double zFade) const {
        const int i = getPermutValue(ix) + iy;
        const int j = getPermutValue(i) + iz;
        const int k = getPermutValue(i + 1) + iz;
        const int l = getPermutValue(ix + 1) + iy;
        const int i1 = getPermutValue(l) + iz;
        const int j1 = getPermutValue(l + 1) + iz;
        const double d0 = dotGrad(getPermutValue(j), dx, dy, dz);
        const double d1 = dotGrad(getPermutValue(i1), dx - 1.0, dy, dz);
        const double d2 = dotGrad(getPermutValue(k), dx, dy - 1.0, dz);
        const double d3 = dotGrad(getPermutValue(j1), dx - 1.0, dy - 1.0, dz);
        const double d4 = dotGrad(getPermutValue(j + 1), dx, dy, dz - 1.0);
        const double d5 = dotGrad(getPermutValue(i1 + 1), dx - 1.0, dy, dz - 1.0);
        const double d6 = dotGrad(getPermutValue(k + 1), dx, dy - 1.0, dz - 1.0);
        const double d7 = dotGrad(getPermutValue(j1 + 1), dx - 1.0, dy - 1.0, dz - 1.0);

        return MathHelper_lerp3(xFade, yFade, zFade, d0, d1, d2, d3, d4, d5, d6, d7);
    }

    double getNoiseValue(double x, double y, double z, double unk1, double unk2) const {
        const double x1 = x + xCoord;
        const double y1 = y + yCoord;
        const double z1 = z + zCoord;
        const int ix = std::floor(x1);
        const int iy = std::floor(y1);
        const int iz = std::floor(z1);
        const double dx = x1 - (double)ix;
        const double dy = y1 - (double)iy;
        const double dz = z1 - (double)iz;
        const double xfade = perlinFade(dx);
        const double yfade = perlinFade(dy);
        const double zfade = perlinFade(dz);

        double d9 = 0.0;
        if (unk1 != 0.0) {
            d9 = (double)std::floor(std::min(unk2, dy) / unk1) * unk1;
        }
        return calcValue(ix, iy, iz, dx, dy - d9, dz, xfade, yfade, zfade);
    }

public:
    static constexpr double dotGrad(int gradIndex, double xFactor, double yFactor, double zFactor) {
        return SimplexNoiseGenerator::processGrad(SimplexNoiseGenerator::GRADS[gradIndex & 15], xFactor, yFactor, zFactor);
    }

    static constexpr double perlinFade(double v) {
        return v * v * v * (v * (v * 6.0 - 15.0) + 10.0);
    }
};