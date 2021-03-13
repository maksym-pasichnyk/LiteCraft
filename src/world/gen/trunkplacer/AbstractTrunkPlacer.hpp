#pragma once

struct AbstractTrunkPlacer {
    int base_height;
    int height_rand_a;
    int height_rand_b;

    AbstractTrunkPlacer(int base_height, int height_rand_a, int height_rand_b)
        : base_height(base_height)
        , height_rand_a(height_rand_a)
        , height_rand_b(height_rand_b) {}
};