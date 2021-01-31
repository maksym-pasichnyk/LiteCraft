#pragma once

#include "SimplexNoiseGenerator.hpp"

#include <cmath>
#include <array>

class ImprovedNoiseGenerator {
    std::array<uint8_t, 256> permutations;
    double xCoord;
    double yCoord;
    double zCoord;

public:
//    ImprovedNoiseGenerator(const ImprovedNoiseGenerator&) = delete;
//    ImprovedNoiseGenerator& operator=(const ImprovedNoiseGenerator&) = delete;

    explicit ImprovedNoiseGenerator(Random&& rand) {
        xCoord = rand.nextDouble();
        yCoord = rand.nextDouble();
        zCoord = rand.nextDouble();

        for (int i = 0; i < 256; ++i) {
            permutations[i] = i;
        }

        for (int i = 0; i < 256; ++i) {
            const int idx = rand.nextInt(256 - i);
            std::swap(permutations[i], permutations[i + idx]);
        }
    }

    int getPermutValue(int permutIndex) {
        return permutations[permutIndex & 255] & 255;
    }

    double calcValue(int ix, int iy, int iz, double dx, double dy, double dz, double xFade, double yFade, double zFade) {
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

        return lerp3(xFade, yFade, zFade, d0, d1, d2, d3, d4, d5, d6, d7);
    }

    double getNoiseValue(double x, double y, double z, double unk1, double unk2) {
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
    static double dotGrad(int gradIndex, double xFactor, double yFactor, double zFactor) {
        return SimplexNoiseGenerator::processGrad(SimplexNoiseGenerator::GRADS[gradIndex & 15], xFactor, yFactor, zFactor);
    }

    static constexpr double perlinFade(double v) {
        return v * v * v * (v * (v * 6.0 - 15.0) + 10.0);
    }

    static float lerp(float pct, float start, float end) {
        return start + pct * (end - start);
    }

    static double lerp(double pct, double start, double end) {
        return start + pct * (end - start);
    }

    static double lerp2(double xFade, double yFade, double d0, double d1, double d2, double d3) {
        return lerp(yFade, lerp(xFade, d0, d1), lerp(xFade, d2, d3));
    }

    static double lerp3(double xFade, double yFade, double zFade, double d0, double d1, double d2, double d3, double d4, double d5, double d6, double d7) {
        return lerp(zFade, lerp2(xFade, yFade, d0, d1, d2, d3), lerp2(xFade, yFade, d4, d5, d6, d7));
    }
};