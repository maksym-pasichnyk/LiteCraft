#pragma once

#include <map>
#include <vector>
#include <string>
#include <util/Registry.hpp>

struct Block;
struct BlockTable;

struct Blocks {
    static BlockTable pallete;
    static Registry<Block> blocks;

    [[maybe_unused]] static Block* AIR;
    [[maybe_unused]] static Block* STONE;
    [[maybe_unused]] static Block* GRANITE;
    [[maybe_unused]] static Block* POLISHED_GRANITE;
    [[maybe_unused]] static Block* DIORITE;
    [[maybe_unused]] static Block* POLISHED_DIORITE;
    [[maybe_unused]] static Block* ANDESITE;
    [[maybe_unused]] static Block* POLISHED_ANDESITE;
    [[maybe_unused]] static Block* GRASS_BLOCK;
    [[maybe_unused]] static Block* DIRT;
    [[maybe_unused]] static Block* COARSE_DIRT;
    [[maybe_unused]] static Block* PODZOL;
    [[maybe_unused]] static Block* COBBLESTONE;
    [[maybe_unused]] static Block* OAK_PLANKS;
    [[maybe_unused]] static Block* SPRUCE_PLANKS;
    [[maybe_unused]] static Block* BIRCH_PLANKS;
    [[maybe_unused]] static Block* JUNGLE_PLANKS;
    [[maybe_unused]] static Block* ACACIA_PLANKS;
    [[maybe_unused]] static Block* DARK_OAK_PLANKS;
    [[maybe_unused]] static Block* OAK_SAPLING;
    [[maybe_unused]] static Block* SPRUCE_SAPLING;
    [[maybe_unused]] static Block* BIRCH_SAPLING;
    [[maybe_unused]] static Block* JUNGLE_SAPLING;
    [[maybe_unused]] static Block* ACACIA_SAPLING;
    [[maybe_unused]] static Block* DARK_OAK_SAPLING;
    [[maybe_unused]] static Block* BEDROCK;
    [[maybe_unused]] static Block* WATER;
    [[maybe_unused]] static Block* LAVA;
    [[maybe_unused]] static Block* SAND;
    [[maybe_unused]] static Block* RED_SAND;
    [[maybe_unused]] static Block* GRAVEL;
    [[maybe_unused]] static Block* GOLD_ORE;
    [[maybe_unused]] static Block* IRON_ORE;
    [[maybe_unused]] static Block* COAL_ORE;
    [[maybe_unused]] static Block* NETHER_GOLD_ORE;
    [[maybe_unused]] static Block* OAK_LOG;
    [[maybe_unused]] static Block* SPRUCE_LOG;
    [[maybe_unused]] static Block* BIRCH_LOG;
    [[maybe_unused]] static Block* JUNGLE_LOG;
    [[maybe_unused]] static Block* ACACIA_LOG;
    [[maybe_unused]] static Block* DARK_OAK_LOG;
    [[maybe_unused]] static Block* STRIPPED_SPRUCE_LOG;
    [[maybe_unused]] static Block* STRIPPED_BIRCH_LOG;
    [[maybe_unused]] static Block* STRIPPED_JUNGLE_LOG;
    [[maybe_unused]] static Block* STRIPPED_ACACIA_LOG;
    [[maybe_unused]] static Block* STRIPPED_DARK_OAK_LOG;
    [[maybe_unused]] static Block* STRIPPED_OAK_LOG;
    [[maybe_unused]] static Block* OAK_WOOD;
    [[maybe_unused]] static Block* SPRUCE_WOOD;
    [[maybe_unused]] static Block* BIRCH_WOOD;
    [[maybe_unused]] static Block* JUNGLE_WOOD;
    [[maybe_unused]] static Block* ACACIA_WOOD;
    [[maybe_unused]] static Block* DARK_OAK_WOOD;
    [[maybe_unused]] static Block* STRIPPED_OAK_WOOD;
    [[maybe_unused]] static Block* STRIPPED_SPRUCE_WOOD;
    [[maybe_unused]] static Block* STRIPPED_BIRCH_WOOD;
    [[maybe_unused]] static Block* STRIPPED_JUNGLE_WOOD;
    [[maybe_unused]] static Block* STRIPPED_ACACIA_WOOD;
    [[maybe_unused]] static Block* STRIPPED_DARK_OAK_WOOD;
    [[maybe_unused]] static Block* OAK_LEAVES;
    [[maybe_unused]] static Block* SPRUCE_LEAVES;
    [[maybe_unused]] static Block* BIRCH_LEAVES;
    [[maybe_unused]] static Block* JUNGLE_LEAVES;
    [[maybe_unused]] static Block* ACACIA_LEAVES;
    [[maybe_unused]] static Block* DARK_OAK_LEAVES;
    [[maybe_unused]] static Block* SPONGE;
    [[maybe_unused]] static Block* WET_SPONGE;
    [[maybe_unused]] static Block* GLASS;
    [[maybe_unused]] static Block* LAPIS_ORE;
    [[maybe_unused]] static Block* LAPIS_BLOCK;
    [[maybe_unused]] static Block* DISPENSER;
    [[maybe_unused]] static Block* SANDSTONE;
    [[maybe_unused]] static Block* CHISELED_SANDSTONE;
    [[maybe_unused]] static Block* CUT_SANDSTONE;
    [[maybe_unused]] static Block* NOTE_BLOCK;
    [[maybe_unused]] static Block* WHITE_BED;
    [[maybe_unused]] static Block* ORANGE_BED;
    [[maybe_unused]] static Block* MAGENTA_BED;
    [[maybe_unused]] static Block* LIGHT_BLUE_BED;
    [[maybe_unused]] static Block* YELLOW_BED;
    [[maybe_unused]] static Block* LIME_BED;
    [[maybe_unused]] static Block* PINK_BED;
    [[maybe_unused]] static Block* GRAY_BED;
    [[maybe_unused]] static Block* LIGHT_GRAY_BED;
    [[maybe_unused]] static Block* CYAN_BED;
    [[maybe_unused]] static Block* PURPLE_BED;
    [[maybe_unused]] static Block* BLUE_BED;
    [[maybe_unused]] static Block* BROWN_BED;
    [[maybe_unused]] static Block* GREEN_BED;
    [[maybe_unused]] static Block* RED_BED;
    [[maybe_unused]] static Block* BLACK_BED;
    [[maybe_unused]] static Block* POWERED_RAIL;
    [[maybe_unused]] static Block* DETECTOR_RAIL;
    [[maybe_unused]] static Block* STICKY_PISTON;
    [[maybe_unused]] static Block* COBWEB;
    [[maybe_unused]] static Block* GRASS;
    [[maybe_unused]] static Block* FERN;
    [[maybe_unused]] static Block* DEAD_BUSH;
    [[maybe_unused]] static Block* SEAGRASS;
    [[maybe_unused]] static Block* TALL_SEAGRASS;
    [[maybe_unused]] static Block* PISTON;
    [[maybe_unused]] static Block* PISTON_HEAD;
    [[maybe_unused]] static Block* WHITE_WOOL;
    [[maybe_unused]] static Block* ORANGE_WOOL;
    [[maybe_unused]] static Block* MAGENTA_WOOL;
    [[maybe_unused]] static Block* LIGHT_BLUE_WOOL;
    [[maybe_unused]] static Block* YELLOW_WOOL;
    [[maybe_unused]] static Block* LIME_WOOL;
    [[maybe_unused]] static Block* PINK_WOOL;
    [[maybe_unused]] static Block* GRAY_WOOL;
    [[maybe_unused]] static Block* LIGHT_GRAY_WOOL;
    [[maybe_unused]] static Block* CYAN_WOOL;
    [[maybe_unused]] static Block* PURPLE_WOOL;
    [[maybe_unused]] static Block* BLUE_WOOL;
    [[maybe_unused]] static Block* BROWN_WOOL;
    [[maybe_unused]] static Block* GREEN_WOOL;
    [[maybe_unused]] static Block* RED_WOOL;
    [[maybe_unused]] static Block* BLACK_WOOL;
    [[maybe_unused]] static Block* MOVING_PISTON;
    [[maybe_unused]] static Block* DANDELION;
    [[maybe_unused]] static Block* POPPY;
    [[maybe_unused]] static Block* BLUE_ORCHID;
    [[maybe_unused]] static Block* ALLIUM;
    [[maybe_unused]] static Block* AZURE_BLUET;
    [[maybe_unused]] static Block* RED_TULIP;
    [[maybe_unused]] static Block* ORANGE_TULIP;
    [[maybe_unused]] static Block* WHITE_TULIP;
    [[maybe_unused]] static Block* PINK_TULIP;
    [[maybe_unused]] static Block* OXEYE_DAISY;
    [[maybe_unused]] static Block* CORNFLOWER;
    [[maybe_unused]] static Block* WITHER_ROSE;
    [[maybe_unused]] static Block* LILY_OF_THE_VALLEY;
    [[maybe_unused]] static Block* BROWN_MUSHROOM;
    [[maybe_unused]] static Block* RED_MUSHROOM;
    [[maybe_unused]] static Block* GOLD_BLOCK;
    [[maybe_unused]] static Block* IRON_BLOCK;
    [[maybe_unused]] static Block* BRICKS;
    [[maybe_unused]] static Block* TNT;
    [[maybe_unused]] static Block* BOOKSHELF;
    [[maybe_unused]] static Block* MOSSY_COBBLESTONE;
    [[maybe_unused]] static Block* OBSIDIAN;
    [[maybe_unused]] static Block* TORCH;
    [[maybe_unused]] static Block* WALL_TORCH;
    [[maybe_unused]] static Block* FIRE;
    [[maybe_unused]] static Block* SOUL_FIRE;
    [[maybe_unused]] static Block* SPAWNER;
    [[maybe_unused]] static Block* OAK_STAIRS;
    [[maybe_unused]] static Block* CHEST;
    [[maybe_unused]] static Block* REDSTONE_WIRE;
    [[maybe_unused]] static Block* DIAMOND_ORE;
    [[maybe_unused]] static Block* DIAMOND_BLOCK;
    [[maybe_unused]] static Block* CRAFTING_TABLE;
    [[maybe_unused]] static Block* WHEAT;
    [[maybe_unused]] static Block* FARMLAND;
    [[maybe_unused]] static Block* FURNACE;
    [[maybe_unused]] static Block* OAK_SIGN;
    [[maybe_unused]] static Block* SPRUCE_SIGN;
    [[maybe_unused]] static Block* BIRCH_SIGN;
    [[maybe_unused]] static Block* ACACIA_SIGN;
    [[maybe_unused]] static Block* JUNGLE_SIGN;
    [[maybe_unused]] static Block* DARK_OAK_SIGN;
    [[maybe_unused]] static Block* OAK_DOOR;
    [[maybe_unused]] static Block* LADDER;
    [[maybe_unused]] static Block* RAIL;
    [[maybe_unused]] static Block* COBBLESTONE_STAIRS;
    [[maybe_unused]] static Block* OAK_WALL_SIGN;
    [[maybe_unused]] static Block* SPRUCE_WALL_SIGN;
    [[maybe_unused]] static Block* BIRCH_WALL_SIGN;
    [[maybe_unused]] static Block* ACACIA_WALL_SIGN;
    [[maybe_unused]] static Block* JUNGLE_WALL_SIGN;
    [[maybe_unused]] static Block* DARK_OAK_WALL_SIGN;
    [[maybe_unused]] static Block* LEVER;
    [[maybe_unused]] static Block* STONE_PRESSURE_PLATE;
    [[maybe_unused]] static Block* IRON_DOOR;
    [[maybe_unused]] static Block* OAK_PRESSURE_PLATE;
    [[maybe_unused]] static Block* SPRUCE_PRESSURE_PLATE;
    [[maybe_unused]] static Block* BIRCH_PRESSURE_PLATE;
    [[maybe_unused]] static Block* JUNGLE_PRESSURE_PLATE;
    [[maybe_unused]] static Block* ACACIA_PRESSURE_PLATE;
    [[maybe_unused]] static Block* DARK_OAK_PRESSURE_PLATE;
    [[maybe_unused]] static Block* REDSTONE_ORE;
    [[maybe_unused]] static Block* REDSTONE_TORCH;
    [[maybe_unused]] static Block* REDSTONE_WALL_TORCH;
    [[maybe_unused]] static Block* STONE_BUTTON;
    [[maybe_unused]] static Block* SNOW;
    [[maybe_unused]] static Block* ICE;
    [[maybe_unused]] static Block* SNOW_BLOCK;
    [[maybe_unused]] static Block* CACTUS;
    [[maybe_unused]] static Block* CLAY;
    [[maybe_unused]] static Block* SUGAR_CANE;
    [[maybe_unused]] static Block* JUKEBOX;
    [[maybe_unused]] static Block* OAK_FENCE;
    [[maybe_unused]] static Block* PUMPKIN;
    [[maybe_unused]] static Block* NETHERRACK;
    [[maybe_unused]] static Block* SOUL_SAND;
    [[maybe_unused]] static Block* SOUL_SOIL;
    [[maybe_unused]] static Block* BASALT;
    [[maybe_unused]] static Block* POLISHED_BASALT;
    [[maybe_unused]] static Block* SOUL_TORCH;
    [[maybe_unused]] static Block* SOUL_WALL_TORCH;
    [[maybe_unused]] static Block* GLOWSTONE;
    [[maybe_unused]] static Block* NETHER_PORTAL;
    [[maybe_unused]] static Block* CARVED_PUMPKIN;
    [[maybe_unused]] static Block* JACK_O_LANTERN;
    [[maybe_unused]] static Block* CAKE;
    [[maybe_unused]] static Block* REPEATER;
    [[maybe_unused]] static Block* WHITE_STAINED_GLASS;
    [[maybe_unused]] static Block* ORANGE_STAINED_GLASS;
    [[maybe_unused]] static Block* MAGENTA_STAINED_GLASS;
    [[maybe_unused]] static Block* LIGHT_BLUE_STAINED_GLASS;
    [[maybe_unused]] static Block* YELLOW_STAINED_GLASS;
    [[maybe_unused]] static Block* LIME_STAINED_GLASS;
    [[maybe_unused]] static Block* PINK_STAINED_GLASS;
    [[maybe_unused]] static Block* GRAY_STAINED_GLASS;
    [[maybe_unused]] static Block* LIGHT_GRAY_STAINED_GLASS;
    [[maybe_unused]] static Block* CYAN_STAINED_GLASS;
    [[maybe_unused]] static Block* PURPLE_STAINED_GLASS;
    [[maybe_unused]] static Block* BLUE_STAINED_GLASS;
    [[maybe_unused]] static Block* BROWN_STAINED_GLASS;
    [[maybe_unused]] static Block* GREEN_STAINED_GLASS;
    [[maybe_unused]] static Block* RED_STAINED_GLASS;
    [[maybe_unused]] static Block* BLACK_STAINED_GLASS;
    [[maybe_unused]] static Block* OAK_TRAPDOOR;
    [[maybe_unused]] static Block* SPRUCE_TRAPDOOR;
    [[maybe_unused]] static Block* BIRCH_TRAPDOOR;
    [[maybe_unused]] static Block* JUNGLE_TRAPDOOR;
    [[maybe_unused]] static Block* ACACIA_TRAPDOOR;
    [[maybe_unused]] static Block* DARK_OAK_TRAPDOOR;
    [[maybe_unused]] static Block* STONE_BRICKS;
    [[maybe_unused]] static Block* MOSSY_STONE_BRICKS;
    [[maybe_unused]] static Block* CRACKED_STONE_BRICKS;
    [[maybe_unused]] static Block* CHISELED_STONE_BRICKS;
    [[maybe_unused]] static Block* INFESTED_STONE;
    [[maybe_unused]] static Block* INFESTED_COBBLESTONE;
    [[maybe_unused]] static Block* INFESTED_STONE_BRICKS;
    [[maybe_unused]] static Block* INFESTED_MOSSY_STONE_BRICKS;
    [[maybe_unused]] static Block* INFESTED_CRACKED_STONE_BRICKS;
    [[maybe_unused]] static Block* INFESTED_CHISELED_STONE_BRICKS;
    [[maybe_unused]] static Block* BROWN_MUSHROOM_BLOCK;
    [[maybe_unused]] static Block* RED_MUSHROOM_BLOCK;
    [[maybe_unused]] static Block* MUSHROOM_STEM;
    [[maybe_unused]] static Block* IRON_BARS;
    [[maybe_unused]] static Block* CHAIN;
    [[maybe_unused]] static Block* GLASS_PANE;
    [[maybe_unused]] static Block* MELON;
    [[maybe_unused]] static Block* ATTACHED_PUMPKIN_STEM;
    [[maybe_unused]] static Block* ATTACHED_MELON_STEM;
    [[maybe_unused]] static Block* PUMPKIN_STEM;
    [[maybe_unused]] static Block* MELON_STEM;
    [[maybe_unused]] static Block* VINE;
    [[maybe_unused]] static Block* OAK_FENCE_GATE;
    [[maybe_unused]] static Block* BRICK_STAIRS;
    [[maybe_unused]] static Block* STONE_BRICK_STAIRS;
    [[maybe_unused]] static Block* MYCELIUM;
    [[maybe_unused]] static Block* LILY_PAD;
    [[maybe_unused]] static Block* NETHER_BRICKS;
    [[maybe_unused]] static Block* NETHER_BRICK_FENCE;
    [[maybe_unused]] static Block* NETHER_BRICK_STAIRS;
    [[maybe_unused]] static Block* NETHER_WART;
    [[maybe_unused]] static Block* ENCHANTING_TABLE;
    [[maybe_unused]] static Block* BREWING_STAND;
    [[maybe_unused]] static Block* CAULDRON;
    [[maybe_unused]] static Block* END_PORTAL;
    [[maybe_unused]] static Block* END_PORTAL_FRAME;
    [[maybe_unused]] static Block* END_STONE;
    [[maybe_unused]] static Block* DRAGON_EGG;
    [[maybe_unused]] static Block* REDSTONE_LAMP;
    [[maybe_unused]] static Block* COCOA;
    [[maybe_unused]] static Block* SANDSTONE_STAIRS;
    [[maybe_unused]] static Block* EMERALD_ORE;
    [[maybe_unused]] static Block* ENDER_CHEST;
    [[maybe_unused]] static Block* TRIPWIRE_HOOK;
    [[maybe_unused]] static Block* TRIPWIRE;
    [[maybe_unused]] static Block* EMERALD_BLOCK;
    [[maybe_unused]] static Block* SPRUCE_STAIRS;
    [[maybe_unused]] static Block* BIRCH_STAIRS;
    [[maybe_unused]] static Block* JUNGLE_STAIRS;
    [[maybe_unused]] static Block* COMMAND_BLOCK;
    [[maybe_unused]] static Block* BEACON;
    [[maybe_unused]] static Block* COBBLESTONE_WALL;
    [[maybe_unused]] static Block* MOSSY_COBBLESTONE_WALL;
    [[maybe_unused]] static Block* FLOWER_POT;
    [[maybe_unused]] static Block* POTTED_OAK_SAPLING;
    [[maybe_unused]] static Block* POTTED_SPRUCE_SAPLING;
    [[maybe_unused]] static Block* POTTED_BIRCH_SAPLING;
    [[maybe_unused]] static Block* POTTED_JUNGLE_SAPLING;
    [[maybe_unused]] static Block* POTTED_ACACIA_SAPLING;
    [[maybe_unused]] static Block* POTTED_DARK_OAK_SAPLING;
    [[maybe_unused]] static Block* POTTED_FERN;
    [[maybe_unused]] static Block* POTTED_DANDELION;
    [[maybe_unused]] static Block* POTTED_POPPY;
    [[maybe_unused]] static Block* POTTED_BLUE_ORCHID;
    [[maybe_unused]] static Block* POTTED_ALLIUM;
    [[maybe_unused]] static Block* POTTED_AZURE_BLUET;
    [[maybe_unused]] static Block* POTTED_RED_TULIP;
    [[maybe_unused]] static Block* POTTED_ORANGE_TULIP;
    [[maybe_unused]] static Block* POTTED_WHITE_TULIP;
    [[maybe_unused]] static Block* POTTED_PINK_TULIP;
    [[maybe_unused]] static Block* POTTED_OXEYE_DAISY;
    [[maybe_unused]] static Block* POTTED_CORNFLOWER;
    [[maybe_unused]] static Block* POTTED_LILY_OF_THE_VALLEY;
    [[maybe_unused]] static Block* POTTED_WITHER_ROSE;
    [[maybe_unused]] static Block* POTTED_RED_MUSHROOM;
    [[maybe_unused]] static Block* POTTED_BROWN_MUSHROOM;
    [[maybe_unused]] static Block* POTTED_DEAD_BUSH;
    [[maybe_unused]] static Block* POTTED_CACTUS;
    [[maybe_unused]] static Block* CARROTS;
    [[maybe_unused]] static Block* POTATOES;
    [[maybe_unused]] static Block* OAK_BUTTON;
    [[maybe_unused]] static Block* SPRUCE_BUTTON;
    [[maybe_unused]] static Block* BIRCH_BUTTON;
    [[maybe_unused]] static Block* JUNGLE_BUTTON;
    [[maybe_unused]] static Block* ACACIA_BUTTON;
    [[maybe_unused]] static Block* DARK_OAK_BUTTON;
    [[maybe_unused]] static Block* SKELETON_SKULL;
    [[maybe_unused]] static Block* SKELETON_WALL_SKULL;
    [[maybe_unused]] static Block* WITHER_SKELETON_SKULL;
    [[maybe_unused]] static Block* WITHER_SKELETON_WALL_SKULL;
    [[maybe_unused]] static Block* ZOMBIE_HEAD;
    [[maybe_unused]] static Block* ZOMBIE_WALL_HEAD;
    [[maybe_unused]] static Block* PLAYER_HEAD;
    [[maybe_unused]] static Block* PLAYER_WALL_HEAD;
    [[maybe_unused]] static Block* CREEPER_HEAD;
    [[maybe_unused]] static Block* CREEPER_WALL_HEAD;
    [[maybe_unused]] static Block* DRAGON_HEAD;
    [[maybe_unused]] static Block* DRAGON_WALL_HEAD;
    [[maybe_unused]] static Block* ANVIL;
    [[maybe_unused]] static Block* CHIPPED_ANVIL;
    [[maybe_unused]] static Block* DAMAGED_ANVIL;
    [[maybe_unused]] static Block* TRAPPED_CHEST;
    [[maybe_unused]] static Block* LIGHT_WEIGHTED_PRESSURE_PLATE;
    [[maybe_unused]] static Block* HEAVY_WEIGHTED_PRESSURE_PLATE;
    [[maybe_unused]] static Block* COMPARATOR;
    [[maybe_unused]] static Block* DAYLIGHT_DETECTOR;
    [[maybe_unused]] static Block* REDSTONE_BLOCK;
    [[maybe_unused]] static Block* NETHER_QUARTZ_ORE;
    [[maybe_unused]] static Block* HOPPER;
    [[maybe_unused]] static Block* QUARTZ_BLOCK;
    [[maybe_unused]] static Block* CHISELED_QUARTZ_BLOCK;
    [[maybe_unused]] static Block* QUARTZ_PILLAR;
    [[maybe_unused]] static Block* QUARTZ_STAIRS;
    [[maybe_unused]] static Block* ACTIVATOR_RAIL;
    [[maybe_unused]] static Block* DROPPER;
    [[maybe_unused]] static Block* WHITE_TERRACOTTA;
    [[maybe_unused]] static Block* ORANGE_TERRACOTTA;
    [[maybe_unused]] static Block* MAGENTA_TERRACOTTA;
    [[maybe_unused]] static Block* LIGHT_BLUE_TERRACOTTA;
    [[maybe_unused]] static Block* YELLOW_TERRACOTTA;
    [[maybe_unused]] static Block* LIME_TERRACOTTA;
    [[maybe_unused]] static Block* PINK_TERRACOTTA;
    [[maybe_unused]] static Block* GRAY_TERRACOTTA;
    [[maybe_unused]] static Block* LIGHT_GRAY_TERRACOTTA;
    [[maybe_unused]] static Block* CYAN_TERRACOTTA;
    [[maybe_unused]] static Block* PURPLE_TERRACOTTA;
    [[maybe_unused]] static Block* BLUE_TERRACOTTA;
    [[maybe_unused]] static Block* BROWN_TERRACOTTA;
    [[maybe_unused]] static Block* GREEN_TERRACOTTA;
    [[maybe_unused]] static Block* RED_TERRACOTTA;
    [[maybe_unused]] static Block* BLACK_TERRACOTTA;
    [[maybe_unused]] static Block* WHITE_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* ORANGE_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* MAGENTA_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* LIGHT_BLUE_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* YELLOW_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* LIME_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* PINK_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* GRAY_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* LIGHT_GRAY_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* CYAN_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* PURPLE_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* BLUE_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* BROWN_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* GREEN_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* RED_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* BLACK_STAINED_GLASS_PANE;
    [[maybe_unused]] static Block* ACACIA_STAIRS;
    [[maybe_unused]] static Block* DARK_OAK_STAIRS;
    [[maybe_unused]] static Block* SLIME_BLOCK;
    [[maybe_unused]] static Block* BARRIER;
    [[maybe_unused]] static Block* IRON_TRAPDOOR;
    [[maybe_unused]] static Block* PRISMARINE;
    [[maybe_unused]] static Block* PRISMARINE_BRICKS;
    [[maybe_unused]] static Block* DARK_PRISMARINE;
    [[maybe_unused]] static Block* PRISMARINE_STAIRS;
    [[maybe_unused]] static Block* PRISMARINE_BRICK_STAIRS;
    [[maybe_unused]] static Block* DARK_PRISMARINE_STAIRS;
    [[maybe_unused]] static Block* PRISMARINE_SLAB;
    [[maybe_unused]] static Block* PRISMARINE_BRICK_SLAB;
    [[maybe_unused]] static Block* DARK_PRISMARINE_SLAB;
    [[maybe_unused]] static Block* SEA_LANTERN;
    [[maybe_unused]] static Block* HAY_BLOCK;
    [[maybe_unused]] static Block* WHITE_CARPET;
    [[maybe_unused]] static Block* ORANGE_CARPET;
    [[maybe_unused]] static Block* MAGENTA_CARPET;
    [[maybe_unused]] static Block* LIGHT_BLUE_CARPET;
    [[maybe_unused]] static Block* YELLOW_CARPET;
    [[maybe_unused]] static Block* LIME_CARPET;
    [[maybe_unused]] static Block* PINK_CARPET;
    [[maybe_unused]] static Block* GRAY_CARPET;
    [[maybe_unused]] static Block* LIGHT_GRAY_CARPET;
    [[maybe_unused]] static Block* CYAN_CARPET;
    [[maybe_unused]] static Block* PURPLE_CARPET;
    [[maybe_unused]] static Block* BLUE_CARPET;
    [[maybe_unused]] static Block* BROWN_CARPET;
    [[maybe_unused]] static Block* GREEN_CARPET;
    [[maybe_unused]] static Block* RED_CARPET;
    [[maybe_unused]] static Block* BLACK_CARPET;
    [[maybe_unused]] static Block* TERRACOTTA;
    [[maybe_unused]] static Block* COAL_BLOCK;
    [[maybe_unused]] static Block* PACKED_ICE;
    [[maybe_unused]] static Block* SUNFLOWER;
    [[maybe_unused]] static Block* LILAC;
    [[maybe_unused]] static Block* ROSE_BUSH;
    [[maybe_unused]] static Block* PEONY;
    [[maybe_unused]] static Block* TALL_GRASS;
    [[maybe_unused]] static Block* LARGE_FERN;
    [[maybe_unused]] static Block* WHITE_BANNER;
    [[maybe_unused]] static Block* ORANGE_BANNER;
    [[maybe_unused]] static Block* MAGENTA_BANNER;
    [[maybe_unused]] static Block* LIGHT_BLUE_BANNER;
    [[maybe_unused]] static Block* YELLOW_BANNER;
    [[maybe_unused]] static Block* LIME_BANNER;
    [[maybe_unused]] static Block* PINK_BANNER;
    [[maybe_unused]] static Block* GRAY_BANNER;
    [[maybe_unused]] static Block* LIGHT_GRAY_BANNER;
    [[maybe_unused]] static Block* CYAN_BANNER;
    [[maybe_unused]] static Block* PURPLE_BANNER;
    [[maybe_unused]] static Block* BLUE_BANNER;
    [[maybe_unused]] static Block* BROWN_BANNER;
    [[maybe_unused]] static Block* GREEN_BANNER;
    [[maybe_unused]] static Block* RED_BANNER;
    [[maybe_unused]] static Block* BLACK_BANNER;
    [[maybe_unused]] static Block* WHITE_WALL_BANNER;
    [[maybe_unused]] static Block* ORANGE_WALL_BANNER;
    [[maybe_unused]] static Block* MAGENTA_WALL_BANNER;
    [[maybe_unused]] static Block* LIGHT_BLUE_WALL_BANNER;
    [[maybe_unused]] static Block* YELLOW_WALL_BANNER;
    [[maybe_unused]] static Block* LIME_WALL_BANNER;
    [[maybe_unused]] static Block* PINK_WALL_BANNER;
    [[maybe_unused]] static Block* GRAY_WALL_BANNER;
    [[maybe_unused]] static Block* LIGHT_GRAY_WALL_BANNER;
    [[maybe_unused]] static Block* CYAN_WALL_BANNER;
    [[maybe_unused]] static Block* PURPLE_WALL_BANNER;
    [[maybe_unused]] static Block* BLUE_WALL_BANNER;
    [[maybe_unused]] static Block* BROWN_WALL_BANNER;
    [[maybe_unused]] static Block* GREEN_WALL_BANNER;
    [[maybe_unused]] static Block* RED_WALL_BANNER;
    [[maybe_unused]] static Block* BLACK_WALL_BANNER;
    [[maybe_unused]] static Block* RED_SANDSTONE;
    [[maybe_unused]] static Block* CHISELED_RED_SANDSTONE;
    [[maybe_unused]] static Block* CUT_RED_SANDSTONE;
    [[maybe_unused]] static Block* RED_SANDSTONE_STAIRS;
    [[maybe_unused]] static Block* OAK_SLAB;
    [[maybe_unused]] static Block* SPRUCE_SLAB;
    [[maybe_unused]] static Block* BIRCH_SLAB;
    [[maybe_unused]] static Block* JUNGLE_SLAB;
    [[maybe_unused]] static Block* ACACIA_SLAB;
    [[maybe_unused]] static Block* DARK_OAK_SLAB;
    [[maybe_unused]] static Block* STONE_SLAB;
    [[maybe_unused]] static Block* SMOOTH_STONE_SLAB;
    [[maybe_unused]] static Block* SANDSTONE_SLAB;
    [[maybe_unused]] static Block* CUT_SANDSTONE_SLAB;
    [[maybe_unused]] static Block* PETRIFIED_OAK_SLAB;
    [[maybe_unused]] static Block* COBBLESTONE_SLAB;
    [[maybe_unused]] static Block* BRICK_SLAB;
    [[maybe_unused]] static Block* STONE_BRICK_SLAB;
    [[maybe_unused]] static Block* NETHER_BRICK_SLAB;
    [[maybe_unused]] static Block* QUARTZ_SLAB;
    [[maybe_unused]] static Block* RED_SANDSTONE_SLAB;
    [[maybe_unused]] static Block* CUT_RED_SANDSTONE_SLAB;
    [[maybe_unused]] static Block* PURPUR_SLAB;
    [[maybe_unused]] static Block* SMOOTH_STONE;
    [[maybe_unused]] static Block* SMOOTH_SANDSTONE;
    [[maybe_unused]] static Block* SMOOTH_QUARTZ;
    [[maybe_unused]] static Block* SMOOTH_RED_SANDSTONE;
    [[maybe_unused]] static Block* SPRUCE_FENCE_GATE;
    [[maybe_unused]] static Block* BIRCH_FENCE_GATE;
    [[maybe_unused]] static Block* JUNGLE_FENCE_GATE;
    [[maybe_unused]] static Block* ACACIA_FENCE_GATE;
    [[maybe_unused]] static Block* DARK_OAK_FENCE_GATE;
    [[maybe_unused]] static Block* SPRUCE_FENCE;
    [[maybe_unused]] static Block* BIRCH_FENCE;
    [[maybe_unused]] static Block* JUNGLE_FENCE;
    [[maybe_unused]] static Block* ACACIA_FENCE;
    [[maybe_unused]] static Block* DARK_OAK_FENCE;
    [[maybe_unused]] static Block* SPRUCE_DOOR;
    [[maybe_unused]] static Block* BIRCH_DOOR;
    [[maybe_unused]] static Block* JUNGLE_DOOR;
    [[maybe_unused]] static Block* ACACIA_DOOR;
    [[maybe_unused]] static Block* DARK_OAK_DOOR;
    [[maybe_unused]] static Block* END_ROD;
    [[maybe_unused]] static Block* CHORUS_PLANT;
    [[maybe_unused]] static Block* CHORUS_FLOWER;
    [[maybe_unused]] static Block* PURPUR_BLOCK;
    [[maybe_unused]] static Block* PURPUR_PILLAR;
    [[maybe_unused]] static Block* PURPUR_STAIRS;
    [[maybe_unused]] static Block* END_STONE_BRICKS;
    [[maybe_unused]] static Block* BEETROOTS;
    [[maybe_unused]] static Block* GRASS_PATH;
    [[maybe_unused]] static Block* END_GATEWAY;
    [[maybe_unused]] static Block* REPEATING_COMMAND_BLOCK;
    [[maybe_unused]] static Block* CHAIN_COMMAND_BLOCK;
    [[maybe_unused]] static Block* FROSTED_ICE;
    [[maybe_unused]] static Block* MAGMA_BLOCK;
    [[maybe_unused]] static Block* NETHER_WART_BLOCK;
    [[maybe_unused]] static Block* RED_NETHER_BRICKS;
    [[maybe_unused]] static Block* BONE_BLOCK;
    [[maybe_unused]] static Block* STRUCTURE_VOID;
    [[maybe_unused]] static Block* OBSERVER;
    [[maybe_unused]] static Block* SHULKER_BOX;
    [[maybe_unused]] static Block* WHITE_SHULKER_BOX;
    [[maybe_unused]] static Block* ORANGE_SHULKER_BOX;
    [[maybe_unused]] static Block* MAGENTA_SHULKER_BOX;
    [[maybe_unused]] static Block* LIGHT_BLUE_SHULKER_BOX;
    [[maybe_unused]] static Block* YELLOW_SHULKER_BOX;
    [[maybe_unused]] static Block* LIME_SHULKER_BOX;
    [[maybe_unused]] static Block* PINK_SHULKER_BOX;
    [[maybe_unused]] static Block* GRAY_SHULKER_BOX;
    [[maybe_unused]] static Block* LIGHT_GRAY_SHULKER_BOX;
    [[maybe_unused]] static Block* CYAN_SHULKER_BOX;
    [[maybe_unused]] static Block* PURPLE_SHULKER_BOX;
    [[maybe_unused]] static Block* BLUE_SHULKER_BOX;
    [[maybe_unused]] static Block* BROWN_SHULKER_BOX;
    [[maybe_unused]] static Block* GREEN_SHULKER_BOX;
    [[maybe_unused]] static Block* RED_SHULKER_BOX;
    [[maybe_unused]] static Block* BLACK_SHULKER_BOX;
    [[maybe_unused]] static Block* WHITE_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* ORANGE_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* MAGENTA_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* LIGHT_BLUE_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* YELLOW_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* LIME_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* PINK_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* GRAY_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* LIGHT_GRAY_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* CYAN_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* PURPLE_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* BLUE_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* BROWN_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* GREEN_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* RED_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* BLACK_GLAZED_TERRACOTTA;
    [[maybe_unused]] static Block* WHITE_CONCRETE;
    [[maybe_unused]] static Block* ORANGE_CONCRETE;
    [[maybe_unused]] static Block* MAGENTA_CONCRETE;
    [[maybe_unused]] static Block* LIGHT_BLUE_CONCRETE;
    [[maybe_unused]] static Block* YELLOW_CONCRETE;
    [[maybe_unused]] static Block* LIME_CONCRETE;
    [[maybe_unused]] static Block* PINK_CONCRETE;
    [[maybe_unused]] static Block* GRAY_CONCRETE;
    [[maybe_unused]] static Block* LIGHT_GRAY_CONCRETE;
    [[maybe_unused]] static Block* CYAN_CONCRETE;
    [[maybe_unused]] static Block* PURPLE_CONCRETE;
    [[maybe_unused]] static Block* BLUE_CONCRETE;
    [[maybe_unused]] static Block* BROWN_CONCRETE;
    [[maybe_unused]] static Block* GREEN_CONCRETE;
    [[maybe_unused]] static Block* RED_CONCRETE;
    [[maybe_unused]] static Block* BLACK_CONCRETE;
    [[maybe_unused]] static Block* WHITE_CONCRETE_POWDER;
    [[maybe_unused]] static Block* ORANGE_CONCRETE_POWDER;
    [[maybe_unused]] static Block* MAGENTA_CONCRETE_POWDER;
    [[maybe_unused]] static Block* LIGHT_BLUE_CONCRETE_POWDER;
    [[maybe_unused]] static Block* YELLOW_CONCRETE_POWDER;
    [[maybe_unused]] static Block* LIME_CONCRETE_POWDER;
    [[maybe_unused]] static Block* PINK_CONCRETE_POWDER;
    [[maybe_unused]] static Block* GRAY_CONCRETE_POWDER;
    [[maybe_unused]] static Block* LIGHT_GRAY_CONCRETE_POWDER;
    [[maybe_unused]] static Block* CYAN_CONCRETE_POWDER;
    [[maybe_unused]] static Block* PURPLE_CONCRETE_POWDER;
    [[maybe_unused]] static Block* BLUE_CONCRETE_POWDER;
    [[maybe_unused]] static Block* BROWN_CONCRETE_POWDER;
    [[maybe_unused]] static Block* GREEN_CONCRETE_POWDER;
    [[maybe_unused]] static Block* RED_CONCRETE_POWDER;
    [[maybe_unused]] static Block* BLACK_CONCRETE_POWDER;
    [[maybe_unused]] static Block* KELP;
    [[maybe_unused]] static Block* KELP_PLANT;
    [[maybe_unused]] static Block* DRIED_KELP_BLOCK;
    [[maybe_unused]] static Block* TURTLE_EGG;
    [[maybe_unused]] static Block* DEAD_TUBE_CORAL_BLOCK;
    [[maybe_unused]] static Block* DEAD_BRAIN_CORAL_BLOCK;
    [[maybe_unused]] static Block* DEAD_BUBBLE_CORAL_BLOCK;
    [[maybe_unused]] static Block* DEAD_FIRE_CORAL_BLOCK;
    [[maybe_unused]] static Block* DEAD_HORN_CORAL_BLOCK;
    [[maybe_unused]] static Block* TUBE_CORAL_BLOCK;
    [[maybe_unused]] static Block* BRAIN_CORAL_BLOCK;
    [[maybe_unused]] static Block* BUBBLE_CORAL_BLOCK;
    [[maybe_unused]] static Block* FIRE_CORAL_BLOCK;
    [[maybe_unused]] static Block* HORN_CORAL_BLOCK;
    [[maybe_unused]] static Block* DEAD_TUBE_CORAL;
    [[maybe_unused]] static Block* DEAD_BRAIN_CORAL;
    [[maybe_unused]] static Block* DEAD_BUBBLE_CORAL;
    [[maybe_unused]] static Block* DEAD_FIRE_CORAL;
    [[maybe_unused]] static Block* DEAD_HORN_CORAL;
    [[maybe_unused]] static Block* TUBE_CORAL;
    [[maybe_unused]] static Block* BRAIN_CORAL;
    [[maybe_unused]] static Block* BUBBLE_CORAL;
    [[maybe_unused]] static Block* FIRE_CORAL;
    [[maybe_unused]] static Block* HORN_CORAL;
    [[maybe_unused]] static Block* DEAD_TUBE_CORAL_FAN;
    [[maybe_unused]] static Block* DEAD_BRAIN_CORAL_FAN;
    [[maybe_unused]] static Block* DEAD_BUBBLE_CORAL_FAN;
    [[maybe_unused]] static Block* DEAD_FIRE_CORAL_FAN;
    [[maybe_unused]] static Block* DEAD_HORN_CORAL_FAN;
    [[maybe_unused]] static Block* TUBE_CORAL_FAN;
    [[maybe_unused]] static Block* BRAIN_CORAL_FAN;
    [[maybe_unused]] static Block* BUBBLE_CORAL_FAN;
    [[maybe_unused]] static Block* FIRE_CORAL_FAN;
    [[maybe_unused]] static Block* HORN_CORAL_FAN;
    [[maybe_unused]] static Block* DEAD_TUBE_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* DEAD_BRAIN_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* DEAD_BUBBLE_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* DEAD_FIRE_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* DEAD_HORN_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* TUBE_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* BRAIN_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* BUBBLE_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* FIRE_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* HORN_CORAL_WALL_FAN;
    [[maybe_unused]] static Block* SEA_PICKLE;
    [[maybe_unused]] static Block* BLUE_ICE;
    [[maybe_unused]] static Block* CONDUIT;
    [[maybe_unused]] static Block* BAMBOO_SAPLING;
    [[maybe_unused]] static Block* BAMBOO;
    [[maybe_unused]] static Block* POTTED_BAMBOO;
    [[maybe_unused]] static Block* VOID_AIR;
    [[maybe_unused]] static Block* CAVE_AIR;
    [[maybe_unused]] static Block* BUBBLE_COLUMN;
    [[maybe_unused]] static Block* POLISHED_GRANITE_STAIRS;
    [[maybe_unused]] static Block* SMOOTH_RED_SANDSTONE_STAIRS;
    [[maybe_unused]] static Block* MOSSY_STONE_BRICK_STAIRS;
    [[maybe_unused]] static Block* POLISHED_DIORITE_STAIRS;
    [[maybe_unused]] static Block* MOSSY_COBBLESTONE_STAIRS;
    [[maybe_unused]] static Block* END_STONE_BRICK_STAIRS;
    [[maybe_unused]] static Block* STONE_STAIRS;
    [[maybe_unused]] static Block* SMOOTH_SANDSTONE_STAIRS;
    [[maybe_unused]] static Block* SMOOTH_QUARTZ_STAIRS;
    [[maybe_unused]] static Block* GRANITE_STAIRS;
    [[maybe_unused]] static Block* ANDESITE_STAIRS;
    [[maybe_unused]] static Block* RED_NETHER_BRICK_STAIRS;
    [[maybe_unused]] static Block* POLISHED_ANDESITE_STAIRS;
    [[maybe_unused]] static Block* DIORITE_STAIRS;
    [[maybe_unused]] static Block* POLISHED_GRANITE_SLAB;
    [[maybe_unused]] static Block* SMOOTH_RED_SANDSTONE_SLAB;
    [[maybe_unused]] static Block* MOSSY_STONE_BRICK_SLAB;
    [[maybe_unused]] static Block* POLISHED_DIORITE_SLAB;
    [[maybe_unused]] static Block* MOSSY_COBBLESTONE_SLAB;
    [[maybe_unused]] static Block* END_STONE_BRICK_SLAB;
    [[maybe_unused]] static Block* SMOOTH_SANDSTONE_SLAB;
    [[maybe_unused]] static Block* SMOOTH_QUARTZ_SLAB;
    [[maybe_unused]] static Block* GRANITE_SLAB;
    [[maybe_unused]] static Block* ANDESITE_SLAB;
    [[maybe_unused]] static Block* RED_NETHER_BRICK_SLAB;
    [[maybe_unused]] static Block* POLISHED_ANDESITE_SLAB;
    [[maybe_unused]] static Block* DIORITE_SLAB;
    [[maybe_unused]] static Block* BRICK_WALL;
    [[maybe_unused]] static Block* PRISMARINE_WALL;
    [[maybe_unused]] static Block* RED_SANDSTONE_WALL;
    [[maybe_unused]] static Block* MOSSY_STONE_BRICK_WALL;
    [[maybe_unused]] static Block* GRANITE_WALL;
    [[maybe_unused]] static Block* STONE_BRICK_WALL;
    [[maybe_unused]] static Block* NETHER_BRICK_WALL;
    [[maybe_unused]] static Block* ANDESITE_WALL;
    [[maybe_unused]] static Block* RED_NETHER_BRICK_WALL;
    [[maybe_unused]] static Block* SANDSTONE_WALL;
    [[maybe_unused]] static Block* END_STONE_BRICK_WALL;
    [[maybe_unused]] static Block* DIORITE_WALL;
    [[maybe_unused]] static Block* SCAFFOLDING;
    [[maybe_unused]] static Block* LOOM;
    [[maybe_unused]] static Block* BARREL;
    [[maybe_unused]] static Block* SMOKER;
    [[maybe_unused]] static Block* BLAST_FURNACE;
    [[maybe_unused]] static Block* CARTOGRAPHY_TABLE;
    [[maybe_unused]] static Block* FLETCHING_TABLE;
    [[maybe_unused]] static Block* GRINDSTONE;
    [[maybe_unused]] static Block* LECTERN;
    [[maybe_unused]] static Block* SMITHING_TABLE;
    [[maybe_unused]] static Block* STONECUTTER;
    [[maybe_unused]] static Block* BELL;
    [[maybe_unused]] static Block* LANTERN;
    [[maybe_unused]] static Block* SOUL_LANTERN;
    [[maybe_unused]] static Block* CAMPFIRE;
    [[maybe_unused]] static Block* SOUL_CAMPFIRE;
    [[maybe_unused]] static Block* SWEET_BERRY_BUSH;
    [[maybe_unused]] static Block* WARPED_STEM;
    [[maybe_unused]] static Block* STRIPPED_WARPED_STEM;
    [[maybe_unused]] static Block* WARPED_HYPHAE;
    [[maybe_unused]] static Block* STRIPPED_WARPED_HYPHAE;
    [[maybe_unused]] static Block* WARPED_NYLIUM;
    [[maybe_unused]] static Block* WARPED_FUNGUS;
    [[maybe_unused]] static Block* WARPED_WART_BLOCK;
    [[maybe_unused]] static Block* WARPED_ROOTS;
    [[maybe_unused]] static Block* NETHER_SPROUTS;
    [[maybe_unused]] static Block* CRIMSON_STEM;
    [[maybe_unused]] static Block* STRIPPED_CRIMSON_STEM;
    [[maybe_unused]] static Block* CRIMSON_HYPHAE;
    [[maybe_unused]] static Block* STRIPPED_CRIMSON_HYPHAE;
    [[maybe_unused]] static Block* CRIMSON_NYLIUM;
    [[maybe_unused]] static Block* CRIMSON_FUNGUS;
    [[maybe_unused]] static Block* SHROOMLIGHT;
    [[maybe_unused]] static Block* WEEPING_VINES;
    [[maybe_unused]] static Block* WEEPING_VINES_PLANT;
    [[maybe_unused]] static Block* TWISTING_VINES;
    [[maybe_unused]] static Block* TWISTING_VINES_PLANT;
    [[maybe_unused]] static Block* CRIMSON_ROOTS;
    [[maybe_unused]] static Block* CRIMSON_PLANKS;
    [[maybe_unused]] static Block* WARPED_PLANKS;
    [[maybe_unused]] static Block* CRIMSON_SLAB;
    [[maybe_unused]] static Block* WARPED_SLAB;
    [[maybe_unused]] static Block* CRIMSON_PRESSURE_PLATE;
    [[maybe_unused]] static Block* WARPED_PRESSURE_PLATE;
    [[maybe_unused]] static Block* CRIMSON_FENCE;
    [[maybe_unused]] static Block* WARPED_FENCE;
    [[maybe_unused]] static Block* CRIMSON_TRAPDOOR;
    [[maybe_unused]] static Block* WARPED_TRAPDOOR;
    [[maybe_unused]] static Block* CRIMSON_FENCE_GATE;
    [[maybe_unused]] static Block* WARPED_FENCE_GATE;
    [[maybe_unused]] static Block* CRIMSON_STAIRS;
    [[maybe_unused]] static Block* WARPED_STAIRS;
    [[maybe_unused]] static Block* CRIMSON_BUTTON;
    [[maybe_unused]] static Block* WARPED_BUTTON;
    [[maybe_unused]] static Block* CRIMSON_DOOR;
    [[maybe_unused]] static Block* WARPED_DOOR;
    [[maybe_unused]] static Block* CRIMSON_SIGN;
    [[maybe_unused]] static Block* WARPED_SIGN;
    [[maybe_unused]] static Block* CRIMSON_WALL_SIGN;
    [[maybe_unused]] static Block* WARPED_WALL_SIGN;
    [[maybe_unused]] static Block* STRUCTURE_BLOCK;
    [[maybe_unused]] static Block* JIGSAW;
    [[maybe_unused]] static Block* COMPOSTER;
    [[maybe_unused]] static Block* TARGET;
    [[maybe_unused]] static Block* BEE_NEST;
    [[maybe_unused]] static Block* BEEHIVE;
    [[maybe_unused]] static Block* HONEY_BLOCK;
    [[maybe_unused]] static Block* HONEYCOMB_BLOCK;
    [[maybe_unused]] static Block* NETHERITE_BLOCK;
    [[maybe_unused]] static Block* ANCIENT_DEBRIS;
    [[maybe_unused]] static Block* CRYING_OBSIDIAN;
    [[maybe_unused]] static Block* RESPAWN_ANCHOR;
    [[maybe_unused]] static Block* POTTED_CRIMSON_FUNGUS;
    [[maybe_unused]] static Block* POTTED_WARPED_FUNGUS;
    [[maybe_unused]] static Block* POTTED_CRIMSON_ROOTS;
    [[maybe_unused]] static Block* POTTED_WARPED_ROOTS;
    [[maybe_unused]] static Block* LODESTONE;
    [[maybe_unused]] static Block* BLACKSTONE;
    [[maybe_unused]] static Block* BLACKSTONE_STAIRS;
    [[maybe_unused]] static Block* BLACKSTONE_WALL;
    [[maybe_unused]] static Block* BLACKSTONE_SLAB;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_BRICKS;
    [[maybe_unused]] static Block* CRACKED_POLISHED_BLACKSTONE_BRICKS;
    [[maybe_unused]] static Block* CHISELED_POLISHED_BLACKSTONE;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_BRICK_SLAB;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_BRICK_STAIRS;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_BRICK_WALL;
    [[maybe_unused]] static Block* GILDED_BLACKSTONE;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_STAIRS;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_SLAB;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_PRESSURE_PLATE;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_BUTTON;
    [[maybe_unused]] static Block* POLISHED_BLACKSTONE_WALL;
    [[maybe_unused]] static Block* CHISELED_NETHER_BRICKS;
    [[maybe_unused]] static Block* CRACKED_NETHER_BRICKS;
    [[maybe_unused]] static Block* QUARTZ_BRICKS;

    static void init();
};
