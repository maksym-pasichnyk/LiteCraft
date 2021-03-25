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

//    ImprovedNoiseGenerator(const ImprovedNoiseGenerator&) = delete;
//    ImprovedNoiseGenerator& operator=(const ImprovedNoiseGenerator&) = delete;
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
        const double d0 = x + xCoord;
        const double d1 = y + yCoord;
        const double d2 = z + zCoord;
        const int i = std::floor(d0);
        const int j = std::floor(d1);
        const int k = std::floor(d2);
        const double d3 = d0 - (double)i;
        const double d4 = d1 - (double)j;
        const double d5 = d2 - (double)k;
        const double d6 = perlinFade(d3);
        const double d7 = perlinFade(d4);
        const double d8 = perlinFade(d5);

        double d9 = 0.0;
        if (unk1 != 0.0) {
            d9 = (double)std::floor(std::min(unk2, d4) / unk1) * unk1;
        }
        return calcValue(i, j, k, d3, d4 - d9, d5, d6, d7, d8);
    }

public:
    static constexpr double dotGrad(int gradIndex, double xFactor, double yFactor, double zFactor) {
        return SimplexNoiseGenerator::processGrad(SimplexNoiseGenerator::GRADS[gradIndex & 15], xFactor, yFactor, zFactor);
    }

    static constexpr double perlinFade(double v) {
        return v * v * v * (v * (v * 6.0 - 15.0) + 10.0);
    }
};