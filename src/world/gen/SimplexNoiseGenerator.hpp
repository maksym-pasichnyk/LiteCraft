#pragma once

#include "INoiseGenerator.hpp"
#include "../../util/Random.hpp"

#include <cmath>
#include <array>
#include <spdlog/spdlog.h>

class SimplexNoiseGenerator {
public:
    static constexpr int GRADS[16][3] {
            {1,  1,  0},
            {-1, 1,  0},
            {1,  -1, 0},
            {-1, -1, 0},
            {1,  0,  1},
            {-1, 0,  1},
            {1,  0,  -1},
            {-1, 0,  -1},
            {0,  1,  1},
            {0,  -1, 1},
            {0,  1,  -1},
            {0,  -1, -1},
            {1,  1,  0},
            {0,  -1, 1},
            {-1, 1,  0},
            {0,  -1, -1}
    };
    static constexpr double SQRT_3 = 1.7320508075688772935274463415058723669428052538103806280558069794;
    static constexpr double F2 = 0.5 * (SQRT_3 - 1.0);
    static constexpr double G2 = (3.0 - SQRT_3) / 6.0;

private:
    std::array<int, 512> p;

public:
    double xo;
    double yo;
    double zo;

public:
    explicit constexpr SimplexNoiseGenerator(Random&& rand) : SimplexNoiseGenerator(rand) {}
    explicit constexpr SimplexNoiseGenerator(Random& rand) {
        xo = rand.nextDouble() * 256.0;
        yo = rand.nextDouble() * 256.0;
        zo = rand.nextDouble() * 256.0;

        for (int i = 0; i < 256; ++i) {
            p[i] = i;
        }

        for (int l = 0; l < 256; ++l) {
            const int j = rand.nextInt(256 - l);
            std::swap(p[l], p[l + j]);
        }
    }

    constexpr int getPermutValue(int permutIndex) const {
        return p[permutIndex & 255];
    }

    /*constexpr*/ double getValue2D(double x, double y) const {
        const double d0 = (x + y) * F2;
        const int i = std::floor(x + d0);
        const int j = std::floor(y + d0);
        const double d1 = (double)(i + j) * G2;
        const double d2 = (double)i - d1;
        const double d3 = (double)j - d1;
        const double d4 = x - d2;
        const double d5 = y - d3;
        int k;
        int l;
        if (d4 > d5) {
            k = 1;
            l = 0;
        } else {
            k = 0;
            l = 1;
        }

        const double d6 = d4 - (double)k + G2;
        const double d7 = d5 - (double)l + G2;
        const double d8 = d4 - 1.0 + 2.0 * G2;
        const double d9 = d5 - 1.0 + 2.0 * G2;
        const int i1 = i & 255;
        const int j1 = j & 255;
        const int k1 = getPermutValue(i1 + getPermutValue(j1)) % 12;
        const int l1 = getPermutValue(i1 + k + getPermutValue(j1 + l)) % 12;
        const int i2 = getPermutValue(i1 + 1 + getPermutValue(j1 + 1)) % 12;
        const double d10 = getContrib(k1, d4, d5, 0.0, 0.5);
        const double d11 = getContrib(l1, d6, d7, 0.0, 0.5);
        const double d12 = getContrib(i2, d8, d9, 0.0, 0.5);
        return 70.0 * (d10 + d11 + d12);
    }

    /*constexpr*/ double getValue3D(double x, double y, double z) const {
        const double d1 = (x + y + z) * 0.3333333333333333;
        const int i = std::floor(x + d1);
        const int j = std::floor(y + d1);
        const int k = std::floor(z + d1);
        const double d3 = static_cast<double>(i + j + k) * 0.16666666666666666;
        const double d4 = static_cast<double>(i) - d3;
        const double d5 = static_cast<double>(j) - d3;
        const double d6 = static_cast<double>(k) - d3;
        const double d7 = x - d4;
        const double d8 = y - d5;
        const double d9 = z - d6;
        int l;
        int i1;
        int j1;
        int k1;
        int l1;
        int i2;
        if (d7 >= d8) {
            if (d8 >= d9) {
                l = 1;
                i1 = 0;
                j1 = 0;
                k1 = 1;
                l1 = 1;
                i2 = 0;
            } else if (d7 >= d9) {
                l = 1;
                i1 = 0;
                j1 = 0;
                k1 = 1;
                l1 = 0;
                i2 = 1;
            } else {
                l = 0;
                i1 = 0;
                j1 = 1;
                k1 = 1;
                l1 = 0;
                i2 = 1;
            }
        } else if (d8 < d9) {
            l = 0;
            i1 = 0;
            j1 = 1;
            k1 = 0;
            l1 = 1;
            i2 = 1;
        } else if (d7 < d9) {
            l = 0;
            i1 = 1;
            j1 = 0;
            k1 = 0;
            l1 = 1;
            i2 = 1;
        } else {
            l = 0;
            i1 = 1;
            j1 = 0;
            k1 = 1;
            l1 = 1;
            i2 = 0;
        }
//        l = d7 >= d8 && (d8 >= d9 || d7 >= d9);
//        i1 = !(d7 >= d8) || d8 >= d9;
//        j1 = d7 >= d8 && d8 < d9 && d7 < d9 || !(d7 >= d8) && d8 < d9;
//        k1 = d7 >= d8 || d8 >= d9 && d7 >= d9;
//        l1 = d7 >= d8 && d8 >= d9 || !(d7 >= d8);
//        i2 = (d7 >= d8 || !(d7 >= d8)) && d8 < d9 || !(d7 >= d8) && d7 < d9;

        const double d10 = d7 - (double)l + 0.16666666666666666;
        const double d11 = d8 - (double)i1 + 0.16666666666666666;
        const double d12 = d9 - (double)j1 + 0.16666666666666666;
        const double d13 = d7 - (double)k1 + 0.3333333333333333;
        const double d14 = d8 - (double)l1 + 0.3333333333333333;
        const double d15 = d9 - (double)i2 + 0.3333333333333333;
        const double d16 = d7 - 1.0 + 0.5;
        const double d17 = d8 - 1.0 + 0.5;
        const double d18 = d9 - 1.0 + 0.5;
        const int j2 = i & 255;
        const int k2 = j & 255;
        const int l2 = k & 255;
        const int i3 = getPermutValue(j2 + getPermutValue(k2 + getPermutValue(l2))) % 12;
        const int j3 = getPermutValue(j2 + l + getPermutValue(k2 + i1 + getPermutValue(l2 + j1))) % 12;
        const int k3 = getPermutValue(j2 + k1 + getPermutValue(k2 + l1 + getPermutValue(l2 + i2))) % 12;
        const int l3 = getPermutValue(j2 + 1 + getPermutValue(k2 + 1 + getPermutValue(l2 + 1))) % 12;
        const double d19 = getContrib(i3, d7, d8, d9, 0.6);
        const double d20 = getContrib(j3, d10, d11, d12, 0.6);
        const double d21 = getContrib(k3, d13, d14, d15, 0.6);
        const double d22 = getContrib(l3, d16, d17, d18, 0.6);
        return 32.0 * (d19 + d20 + d21 + d22);
    }

    static constexpr double getContrib(int gradIndex, double x, double y, double z, double offset) {
        double d1 = offset - x * x - y * y - z * z;
        double d0;
        if (d1 < 0.0) {
            d0 = 0.0;
        } else {
            d1 = d1 * d1;
            d0 = d1 * d1 * processGrad(GRADS[gradIndex], x, y, z);
        }
        return d0;
    }

    static constexpr double processGrad(const int (&gradElement)[3], double xFactor, double yFactor, double zFactor) {
        return static_cast<double>(gradElement[0]) * xFactor +
               static_cast<double>(gradElement[1]) * yFactor +
               static_cast<double>(gradElement[2]) * zFactor;
    }
};