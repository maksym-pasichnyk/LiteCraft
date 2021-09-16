#pragma once

#include <util/Registry.hpp>
#include <string>
#include <memory>
#include <map>

struct Feature;
struct Features {
    static Registry<Feature> features;
    static Feature* NO_OP;
    static Feature* TREE;
    static Feature* FLOWER;
    static Feature* NO_BONEMEAL_FLOWER;
    static Feature* RANDOM_PATCH;
    static Feature* BLOCK_PILE;
    static Feature* SPRING_FEATURE;
    static Feature* CHORUS_PLANT;
    static Feature* EMERALD_ORE;
    static Feature* VOID_START_PLATFORM;
    static Feature* DESERT_WELL;
    static Feature* FOSSIL;
    static Feature* HUGE_RED_MUSHROOM;
    static Feature* HUGE_BROWN_MUSHROOM;
    static Feature* ICE_SPIKE;
    static Feature* GLOWSTONE_BLOB;
    static Feature* FREEZE_TOP_LAYER;
    static Feature* VINES;
    static Feature* MONSTER_ROOM;
    static Feature* BLUE_ICE;
    static Feature* ICEBERG;
    static Feature* FOREST_ROCK;
    static Feature* DISK;
    static Feature* ICE_PATCH;
    static Feature* LAKE;
    static Feature* ORE;
    static Feature* END_SPIKE;
    static Feature* END_ISLAND;
    static Feature* END_GATEWAY;
    static Feature* SEAGRASS;
    static Feature* KELP;
    static Feature* CORAL_TREE;
    static Feature* CORAL_MUSHROOM;
    static Feature* CORAL_CLAW;
    static Feature* SEA_PICKLE;
    static Feature* SIMPLE_BLOCK;
    static Feature* BAMBOO;
    static Feature* HUGE_FUNGUS;
    static Feature* NETHER_FOREST_VEGETATION;
    static Feature* WEEPING_VINES;
    static Feature* TWISTING_VINES;
    static Feature* BASALT_COLUMNS;
    static Feature* DELTA_FEATURE;
    static Feature* NETHERRACK_REPLACE_BLOBS;
    static Feature* FILL_LAYER;
    static Feature* BONUS_CHEST;
    static Feature* BASALT_PILLAR;
    static Feature* NO_SURFACE_ORE;
    static Feature* RANDOM_SELECTOR;
    static Feature* SIMPLE_RANDOM_SELECTOR;
    static Feature* RANDOM_BOOLEAN_SELECTOR;
    static Feature* DECORATED;

    static void init();
};