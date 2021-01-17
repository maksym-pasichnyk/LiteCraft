#pragma once

#include <glm/vec4.hpp>

#include <map>
#include <vector>
#include <string>

struct TextureAtlasTextureItem;

struct TileData {
	TextureAtlasTextureItem* topTexture;
	TextureAtlasTextureItem* bottomTexture;
	TextureAtlasTextureItem* southTexture;
	TextureAtlasTextureItem* northTexture;
	TextureAtlasTextureItem* eastTexture;
	TextureAtlasTextureItem* westTexture;
};

enum class Tint {
	None,
	Grass,
	Foliage
};

enum class RenderType {
	Air,
	Liquid,
	Block,
	Leaves,
	Cross,
};

enum class RenderLayer {
	Opaque,
	Cutout,
	Transparent
};

extern std::map<std::string, TileData> tile_datas;

struct Tile {
	[[maybe_unused]] static Tile* acacia_button;
	[[maybe_unused]] static Tile* acacia_door;
	[[maybe_unused]] static Tile* acacia_fence_gate;
	[[maybe_unused]] static Tile* acacia_pressure_plate;
	[[maybe_unused]] static Tile* acacia_stairs;
	[[maybe_unused]] static Tile* acacia_standing_sign;
	[[maybe_unused]] static Tile* acacia_trapdoor;
	[[maybe_unused]] static Tile* acacia_wall_sign;
	[[maybe_unused]] static Tile* activator_rail;
	[[maybe_unused]] static Tile* air;
	[[maybe_unused]] static Tile* allow;
	[[maybe_unused]] static Tile* andesite_stairs;
	[[maybe_unused]] static Tile* anvil;
	[[maybe_unused]] static Tile* bamboo;
	[[maybe_unused]] static Tile* bamboo_sapling;
	[[maybe_unused]] static Tile* barrel;
	[[maybe_unused]] static Tile* barrier;
	[[maybe_unused]] static Tile* beacon;
	[[maybe_unused]] static Tile* bed;
	[[maybe_unused]] static Tile* bedrock;
	[[maybe_unused]] static Tile* beetroot;
	[[maybe_unused]] static Tile* bell;
	[[maybe_unused]] static Tile* birch_button;
	[[maybe_unused]] static Tile* birch_door;
	[[maybe_unused]] static Tile* birch_fence_gate;
	[[maybe_unused]] static Tile* birch_pressure_plate;
	[[maybe_unused]] static Tile* birch_stairs;
	[[maybe_unused]] static Tile* birch_standing_sign;
	[[maybe_unused]] static Tile* birch_trapdoor;
	[[maybe_unused]] static Tile* birch_wall_sign;
	[[maybe_unused]] static Tile* black_glazed_terracotta;
	[[maybe_unused]] static Tile* blast_furnace;
	[[maybe_unused]] static Tile* blue_glazed_terracotta;
	[[maybe_unused]] static Tile* blue_ice;
	[[maybe_unused]] static Tile* bone_block;
	[[maybe_unused]] static Tile* bookshelf;
	[[maybe_unused]] static Tile* border_block;
	[[maybe_unused]] static Tile* brewing_stand;
	[[maybe_unused]] static Tile* brick_block;
	[[maybe_unused]] static Tile* brick_stairs;
	[[maybe_unused]] static Tile* brown_glazed_terracotta;
	[[maybe_unused]] static Tile* brown_mushroom;
	[[maybe_unused]] static Tile* brown_mushroom_block;
	[[maybe_unused]] static Tile* bubble_column;
	[[maybe_unused]] static Tile* cactus;
	[[maybe_unused]] static Tile* cake;
	[[maybe_unused]] static Tile* camera;
	[[maybe_unused]] static Tile* campfire;
	[[maybe_unused]] static Tile* carpet;
	[[maybe_unused]] static Tile* carrots;
	[[maybe_unused]] static Tile* cartography_table;
	[[maybe_unused]] static Tile* carved_pumpkin;
	[[maybe_unused]] static Tile* cauldron;
	[[maybe_unused]] static Tile* chain_command_block;
	[[maybe_unused]] static Tile* chest;
	[[maybe_unused]] static Tile* chorus_flower;
	[[maybe_unused]] static Tile* chorus_plant;
	[[maybe_unused]] static Tile* clay;
	[[maybe_unused]] static Tile* coal_block;
	[[maybe_unused]] static Tile* coal_ore;
	[[maybe_unused]] static Tile* cobblestone;
	[[maybe_unused]] static Tile* cobblestone_wall;
	[[maybe_unused]] static Tile* cocoa;
	[[maybe_unused]] static Tile* command_block;
	[[maybe_unused]] static Tile* composter;
	[[maybe_unused]] static Tile* concrete;
	[[maybe_unused]] static Tile* concretePowder;
	[[maybe_unused]] static Tile* conduit;
	[[maybe_unused]] static Tile* coral;
	[[maybe_unused]] static Tile* coral_block;
	[[maybe_unused]] static Tile* coral_fan;
	[[maybe_unused]] static Tile* coral_fan_dead;
	[[maybe_unused]] static Tile* coral_fan_hang;
	[[maybe_unused]] static Tile* coral_fan_hang2;
	[[maybe_unused]] static Tile* coral_fan_hang3;
	[[maybe_unused]] static Tile* crafting_table;
	[[maybe_unused]] static Tile* cyan_glazed_terracotta;
	[[maybe_unused]] static Tile* dark_oak_button;
	[[maybe_unused]] static Tile* dark_oak_door;
	[[maybe_unused]] static Tile* dark_oak_fence_gate;
	[[maybe_unused]] static Tile* dark_oak_pressure_plate;
	[[maybe_unused]] static Tile* dark_oak_stairs;
	[[maybe_unused]] static Tile* dark_oak_trapdoor;
	[[maybe_unused]] static Tile* dark_prismarine_stairs;
	[[maybe_unused]] static Tile* darkoak_standing_sign;
	[[maybe_unused]] static Tile* darkoak_wall_sign;
	[[maybe_unused]] static Tile* daylight_detector;
	[[maybe_unused]] static Tile* daylight_detector_inverted;
	[[maybe_unused]] static Tile* deadbush;
	[[maybe_unused]] static Tile* deny;
	[[maybe_unused]] static Tile* detector_rail;
	[[maybe_unused]] static Tile* diamond_block;
	[[maybe_unused]] static Tile* diamond_ore;
	[[maybe_unused]] static Tile* diorite_stairs;
	[[maybe_unused]] static Tile* dirt;
	[[maybe_unused]] static Tile* dispenser;
	[[maybe_unused]] static Tile* double_plant;
	[[maybe_unused]] static Tile* double_stone_slab;
	[[maybe_unused]] static Tile* double_stone_slab2;
	[[maybe_unused]] static Tile* double_stone_slab3;
	[[maybe_unused]] static Tile* double_stone_slab4;
	[[maybe_unused]] static Tile* double_wooden_slab;
	[[maybe_unused]] static Tile* dragon_egg;
	[[maybe_unused]] static Tile* dried_kelp_block;
	[[maybe_unused]] static Tile* dropper;
	[[maybe_unused]] static Tile* emerald_block;
	[[maybe_unused]] static Tile* emerald_ore;
	[[maybe_unused]] static Tile* enchanting_table;
	[[maybe_unused]] static Tile* end_brick_stairs;
	[[maybe_unused]] static Tile* end_bricks;
	[[maybe_unused]] static Tile* end_gateway;
	[[maybe_unused]] static Tile* end_portal;
	[[maybe_unused]] static Tile* end_portal_frame;
	[[maybe_unused]] static Tile* end_rod;
	[[maybe_unused]] static Tile* end_stone;
	[[maybe_unused]] static Tile* ender_chest;
	[[maybe_unused]] static Tile* farmland;
	[[maybe_unused]] static Tile* fence;
	[[maybe_unused]] static Tile* fence_gate;
	[[maybe_unused]] static Tile* fire;
	[[maybe_unused]] static Tile* fletching_table;
	[[maybe_unused]] static Tile* flower_pot;
	[[maybe_unused]] static Tile* flowing_lava;
	[[maybe_unused]] static Tile* flowing_water;
	[[maybe_unused]] static Tile* frame;
	[[maybe_unused]] static Tile* frosted_ice;
	[[maybe_unused]] static Tile* furnace;
	[[maybe_unused]] static Tile* glass;
	[[maybe_unused]] static Tile* glass_pane;
	[[maybe_unused]] static Tile* glowingobsidian;
	[[maybe_unused]] static Tile* glowstone;
	[[maybe_unused]] static Tile* gold_block;
	[[maybe_unused]] static Tile* gold_ore;
	[[maybe_unused]] static Tile* golden_rail;
	[[maybe_unused]] static Tile* granite_stairs;
	[[maybe_unused]] static Tile* grass;
	[[maybe_unused]] static Tile* grass_path;
	[[maybe_unused]] static Tile* gravel;
	[[maybe_unused]] static Tile* gray_glazed_terracotta;
	[[maybe_unused]] static Tile* green_glazed_terracotta;
	[[maybe_unused]] static Tile* grindstone;
	[[maybe_unused]] static Tile* hardened_clay;
	[[maybe_unused]] static Tile* hay_block;
	[[maybe_unused]] static Tile* heavy_weighted_pressure_plate;
	[[maybe_unused]] static Tile* hopper;
	[[maybe_unused]] static Tile* ice;
	[[maybe_unused]] static Tile* info_update;
	[[maybe_unused]] static Tile* info_update2;
	[[maybe_unused]] static Tile* invisibleBedrock;
	[[maybe_unused]] static Tile* iron_bars;
	[[maybe_unused]] static Tile* iron_block;
	[[maybe_unused]] static Tile* iron_door;
	[[maybe_unused]] static Tile* iron_ore;
	[[maybe_unused]] static Tile* iron_trapdoor;
	[[maybe_unused]] static Tile* jigsaw;
	[[maybe_unused]] static Tile* jukebox;
	[[maybe_unused]] static Tile* jungle_button;
	[[maybe_unused]] static Tile* jungle_door;
	[[maybe_unused]] static Tile* jungle_fence_gate;
	[[maybe_unused]] static Tile* jungle_pressure_plate;
	[[maybe_unused]] static Tile* jungle_stairs;
	[[maybe_unused]] static Tile* jungle_standing_sign;
	[[maybe_unused]] static Tile* jungle_trapdoor;
	[[maybe_unused]] static Tile* jungle_wall_sign;
	[[maybe_unused]] static Tile* kelp;
	[[maybe_unused]] static Tile* ladder;
	[[maybe_unused]] static Tile* lantern;
	[[maybe_unused]] static Tile* lapis_block;
	[[maybe_unused]] static Tile* lapis_ore;
	[[maybe_unused]] static Tile* lava;
	[[maybe_unused]] static Tile* lava_cauldron;
	[[maybe_unused]] static Tile* leaves;
	[[maybe_unused]] static Tile* leaves2;
	[[maybe_unused]] static Tile* lectern;
	[[maybe_unused]] static Tile* lever;
	[[maybe_unused]] static Tile* light_block;
	[[maybe_unused]] static Tile* light_blue_glazed_terracotta;
	[[maybe_unused]] static Tile* light_weighted_pressure_plate;
	[[maybe_unused]] static Tile* lime_glazed_terracotta;
	[[maybe_unused]] static Tile* lit_blast_furnace;
	[[maybe_unused]] static Tile* lit_furnace;
	[[maybe_unused]] static Tile* lit_pumpkin;
	[[maybe_unused]] static Tile* lit_redstone_lamp;
	[[maybe_unused]] static Tile* lit_redstone_ore;
	[[maybe_unused]] static Tile* lit_smoker;
	[[maybe_unused]] static Tile* log;
	[[maybe_unused]] static Tile* log2;
	[[maybe_unused]] static Tile* loom;
	[[maybe_unused]] static Tile* magenta_glazed_terracotta;
	[[maybe_unused]] static Tile* magma;
	[[maybe_unused]] static Tile* melon_block;
	[[maybe_unused]] static Tile* melon_stem;
	[[maybe_unused]] static Tile* mob_spawner;
	[[maybe_unused]] static Tile* monster_egg;
	[[maybe_unused]] static Tile* mossy_cobblestone;
	[[maybe_unused]] static Tile* mossy_cobblestone_stairs;
	[[maybe_unused]] static Tile* mossy_stone_brick_stairs;
	[[maybe_unused]] static Tile* movingBlock;
	[[maybe_unused]] static Tile* mycelium;
	[[maybe_unused]] static Tile* nether_brick;
	[[maybe_unused]] static Tile* nether_brick_fence;
	[[maybe_unused]] static Tile* nether_brick_stairs;
	[[maybe_unused]] static Tile* nether_wart;
	[[maybe_unused]] static Tile* nether_wart_block;
	[[maybe_unused]] static Tile* netherrack;
	[[maybe_unused]] static Tile* netherreactor;
	[[maybe_unused]] static Tile* normal_stone_stairs;
	[[maybe_unused]] static Tile* noteblock;
	[[maybe_unused]] static Tile* oak_stairs;
	[[maybe_unused]] static Tile* observer;
	[[maybe_unused]] static Tile* obsidian;
	[[maybe_unused]] static Tile* orange_glazed_terracotta;
	[[maybe_unused]] static Tile* packed_ice;
	[[maybe_unused]] static Tile* pink_glazed_terracotta;
	[[maybe_unused]] static Tile* piston;
	[[maybe_unused]] static Tile* pistonArmCollision;
	[[maybe_unused]] static Tile* planks;
	[[maybe_unused]] static Tile* podzol;
	[[maybe_unused]] static Tile* polished_andesite_stairs;
	[[maybe_unused]] static Tile* polished_diorite_stairs;
	[[maybe_unused]] static Tile* polished_granite_stairs;
	[[maybe_unused]] static Tile* portal;
	[[maybe_unused]] static Tile* potatoes;
	[[maybe_unused]] static Tile* powered_comparator;
	[[maybe_unused]] static Tile* powered_repeater;
	[[maybe_unused]] static Tile* prismarine;
	[[maybe_unused]] static Tile* prismarine_bricks_stairs;
	[[maybe_unused]] static Tile* prismarine_stairs;
	[[maybe_unused]] static Tile* pumpkin;
	[[maybe_unused]] static Tile* pumpkin_stem;
	[[maybe_unused]] static Tile* purple_glazed_terracotta;
	[[maybe_unused]] static Tile* purpur_block;
	[[maybe_unused]] static Tile* purpur_stairs;
	[[maybe_unused]] static Tile* quartz_block;
	[[maybe_unused]] static Tile* quartz_ore;
	[[maybe_unused]] static Tile* quartz_stairs;
	[[maybe_unused]] static Tile* rail;
	[[maybe_unused]] static Tile* red_flower;
	[[maybe_unused]] static Tile* red_glazed_terracotta;
	[[maybe_unused]] static Tile* red_mushroom;
	[[maybe_unused]] static Tile* red_mushroom_block;
	[[maybe_unused]] static Tile* red_nether_brick;
	[[maybe_unused]] static Tile* red_nether_brick_stairs;
	[[maybe_unused]] static Tile* red_sandstone;
	[[maybe_unused]] static Tile* red_sandstone_stairs;
	[[maybe_unused]] static Tile* redstone_block;
	[[maybe_unused]] static Tile* redstone_lamp;
	[[maybe_unused]] static Tile* redstone_ore;
	[[maybe_unused]] static Tile* redstone_torch;
	[[maybe_unused]] static Tile* redstone_wire;
	[[maybe_unused]] static Tile* reeds;
	[[maybe_unused]] static Tile* repeating_command_block;
	[[maybe_unused]] static Tile* reserved6;
	[[maybe_unused]] static Tile* sand;
	[[maybe_unused]] static Tile* sandstone;
	[[maybe_unused]] static Tile* sandstone_stairs;
	[[maybe_unused]] static Tile* sapling;
	[[maybe_unused]] static Tile* scaffolding;
	[[maybe_unused]] static Tile* seaLantern;
	[[maybe_unused]] static Tile* sea_pickle;
	[[maybe_unused]] static Tile* seagrass;
	[[maybe_unused]] static Tile* shulker_box;
	[[maybe_unused]] static Tile* silver_glazed_terracotta;
	[[maybe_unused]] static Tile* skull;
	[[maybe_unused]] static Tile* slime;
	[[maybe_unused]] static Tile* smithing_table;
	[[maybe_unused]] static Tile* smoker;
	[[maybe_unused]] static Tile* smooth_quartz_stairs;
	[[maybe_unused]] static Tile* smooth_red_sandstone_stairs;
	[[maybe_unused]] static Tile* smooth_sandstone_stairs;
	[[maybe_unused]] static Tile* smooth_stone;
	[[maybe_unused]] static Tile* snow;
	[[maybe_unused]] static Tile* snow_layer;
	[[maybe_unused]] static Tile* soul_sand;
	[[maybe_unused]] static Tile* sponge;
	[[maybe_unused]] static Tile* spruce_button;
	[[maybe_unused]] static Tile* spruce_door;
	[[maybe_unused]] static Tile* spruce_fence_gate;
	[[maybe_unused]] static Tile* spruce_pressure_plate;
	[[maybe_unused]] static Tile* spruce_stairs;
	[[maybe_unused]] static Tile* spruce_standing_sign;
	[[maybe_unused]] static Tile* spruce_trapdoor;
	[[maybe_unused]] static Tile* spruce_wall_sign;
	[[maybe_unused]] static Tile* stained_glass;
	[[maybe_unused]] static Tile* stained_glass_pane;
	[[maybe_unused]] static Tile* stained_hardened_clay;
	[[maybe_unused]] static Tile* standing_banner;
	[[maybe_unused]] static Tile* standing_sign;
	[[maybe_unused]] static Tile* stickyPistonArmCollision;
	[[maybe_unused]] static Tile* sticky_piston;
	[[maybe_unused]] static Tile* stone;
	[[maybe_unused]] static Tile* stone_brick_stairs;
	[[maybe_unused]] static Tile* stone_button;
	[[maybe_unused]] static Tile* stone_pressure_plate;
	[[maybe_unused]] static Tile* stone_slab;
	[[maybe_unused]] static Tile* stone_slab2;
	[[maybe_unused]] static Tile* stone_slab3;
	[[maybe_unused]] static Tile* stone_slab4;
	[[maybe_unused]] static Tile* stone_stairs;
	[[maybe_unused]] static Tile* stonebrick;
	[[maybe_unused]] static Tile* stonecutter;
	[[maybe_unused]] static Tile* stonecutter_block;
	[[maybe_unused]] static Tile* stripped_acacia_log;
	[[maybe_unused]] static Tile* stripped_birch_log;
	[[maybe_unused]] static Tile* stripped_dark_oak_log;
	[[maybe_unused]] static Tile* stripped_jungle_log;
	[[maybe_unused]] static Tile* stripped_oak_log;
	[[maybe_unused]] static Tile* stripped_spruce_log;
	[[maybe_unused]] static Tile* structure_block;
	[[maybe_unused]] static Tile* structure_void;
	[[maybe_unused]] static Tile* sweet_berry_bush;
	[[maybe_unused]] static Tile* tallgrass;
	[[maybe_unused]] static Tile* tnt;
	[[maybe_unused]] static Tile* torch;
	[[maybe_unused]] static Tile* trapdoor;
	[[maybe_unused]] static Tile* trapped_chest;
	[[maybe_unused]] static Tile* tripWire;
	[[maybe_unused]] static Tile* tripwire_hook;
	[[maybe_unused]] static Tile* turtle_egg;
	[[maybe_unused]] static Tile* undyed_shulker_box;
	[[maybe_unused]] static Tile* unlit_redstone_torch;
	[[maybe_unused]] static Tile* unpowered_comparator;
	[[maybe_unused]] static Tile* unpowered_repeater;
	[[maybe_unused]] static Tile* vine;
	[[maybe_unused]] static Tile* wall_banner;
	[[maybe_unused]] static Tile* wall_sign;
	[[maybe_unused]] static Tile* water;
	[[maybe_unused]] static Tile* waterlily;
	[[maybe_unused]] static Tile* web;
	[[maybe_unused]] static Tile* wheat;
	[[maybe_unused]] static Tile* white_glazed_terracotta;
	[[maybe_unused]] static Tile* wither_rose;
	[[maybe_unused]] static Tile* wood;
	[[maybe_unused]] static Tile* wooden_button;
	[[maybe_unused]] static Tile* wooden_door;
	[[maybe_unused]] static Tile* wooden_pressure_plate;
	[[maybe_unused]] static Tile* wooden_slab;
	[[maybe_unused]] static Tile* wool;
	[[maybe_unused]] static Tile* yellow_flower;
	[[maybe_unused]] static Tile* yellow_glazed_terracotta;

	explicit Tile(const std::string& key) {
		auto const& data = tile_datas.at(key);

		topTexture = data.topTexture;
		bottomTexture = data.bottomTexture;
		southTexture = data.southTexture;
		northTexture = data.northTexture;
		eastTexture = data.eastTexture;
		westTexture = data.westTexture;
	}

	auto setRenderType(RenderType renderTypeIn) -> Tile* {
		renderType = renderTypeIn;
		return this;
	}

	auto setRenderLayer(RenderLayer renderLayerIn) -> Tile* {
		renderLayer = renderLayerIn;
		return this;
	}

	auto setTint(Tint tintIn) -> Tile* {
		tint = tintIn;
		return this;
	}

	static void initTiles();

	Tint tint = Tint::None;
	RenderType renderType = RenderType::Block;
	RenderLayer renderLayer = RenderLayer::Opaque;

	TextureAtlasTextureItem* topTexture;
	TextureAtlasTextureItem* bottomTexture;
	TextureAtlasTextureItem* southTexture;
	TextureAtlasTextureItem* northTexture;
	TextureAtlasTextureItem* eastTexture;
	TextureAtlasTextureItem* westTexture;
};