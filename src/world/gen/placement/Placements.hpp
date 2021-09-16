#pragma once

#include <util/Registry.hpp>
#include <memory>
#include <string>
#include <map>

struct Placement;
struct Placements {
    static Registry<Placement> placements;
    static Placement* NOPE;
    static Placement* CHANCE;
    static Placement* COUNT;
    static Placement* COUNT_NOISE;
    static Placement* COUNT_NOISE_BIASED;
    static Placement* COUNT_EXTRA;
    static Placement* SQUARE;
    static Placement* HEIGHTMAP;
    static Placement* HEIGHTMAP_SPREAD_DOUBLE;
    static Placement* TOP_SOLID_HEIGHTMAP;
    static Placement* HEIGHTMAP_WORLD_SURFACE;
    static Placement* RANGE;
    static Placement* RANGE_BIASED;
    static Placement* RANGE_VERY_BIASED;
    static Placement* DEPTH_AVERAGE;
    static Placement* SPREAD_32_ABOVE;
    static Placement* CARVING_MASK;
    static Placement* FIRE;
    static Placement* MAGMA;
    static Placement* EMERALD_ORE;
    static Placement* LAVA_LAKE;
    static Placement* WATER_LAKE;
    static Placement* GLOWSTONE;
    static Placement* END_GATEWAY;
    static Placement* DARK_OAK_TREE;
    static Placement* ICEBERG;
    static Placement* END_ISLAND;
    static Placement* DECORATED;
    static Placement* COUNT_MULTILAYER;

    static void init();
};