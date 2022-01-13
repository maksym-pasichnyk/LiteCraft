#include "Blocks.hpp"
#include "AbstractBlock.hpp"
#include "AirBlock.hpp"
#include "AnvilBlock.hpp"
#include "AttachedStemBlock.hpp"
#include "BambooBlock.hpp"
#include "BambooSaplingBlock.hpp"
#include "BannerBlock.hpp"
#include "BarrelBlock.hpp"
#include "BarrierBlock.hpp"
#include "BeaconBlock.hpp"
#include "BedBlock.hpp"
#include "BeehiveBlock.hpp"
#include "BeetrootBlock.hpp"
#include "BellBlock.hpp"
#include "BlastFurnaceBlock.hpp"
#include "BreakableBlock.hpp"
#include "BrewingStandBlock.hpp"
#include "BubbleColumnBlock.hpp"
#include "CactusBlock.hpp"
#include "CakeBlock.hpp"
#include "CampfireBlock.hpp"
#include "CarpetBlock.hpp"
#include "CarrotBlock.hpp"
#include "CartographyTableBlock.hpp"
#include "CarvedPumpkinBlock.hpp"
#include "CauldronBlock.hpp"
#include "ChainBlock.hpp"
#include "ChestBlock.hpp"
#include "ChorusFlowerBlock.hpp"
#include "ChorusPlantBlock.hpp"
#include "CocoaBlock.hpp"
#include "CommandBlockBlock.hpp"
#include "ComparatorBlock.hpp"
#include "ComposterBlock.hpp"
#include "ConcretePowderBlock.hpp"
#include "ConduitBlock.hpp"
#include "CoralBlock.hpp"
#include "CoralFanBlock.hpp"
#include "CoralFinBlock.hpp"
#include "CoralPlantBlock.hpp"
#include "CoralWallFanBlock.hpp"
#include "CraftingTableBlock.hpp"
#include "CryingObsidianBlock.hpp"
#include "DaylightDetectorBlock.hpp"
#include "DeadBushBlock.hpp"
#include "DeadCoralPlantBlock.hpp"
#include "DetectorRailBlock.hpp"
#include "DispenserBlock.hpp"
#include "DoorBlock.hpp"
#include "DoublePlantBlock.hpp"
#include "DragonEggBlock.hpp"
#include "DropperBlock.hpp"
#include "EnchantingTableBlock.hpp"
#include "EndGatewayBlock.hpp"
#include "EndPortalBlock.hpp"
#include "EndPortalFrameBlock.hpp"
#include "EndRodBlock.hpp"
#include "EnderChestBlock.hpp"
#include "FarmlandBlock.hpp"
#include "FenceBlock.hpp"
#include "FenceGateBlock.hpp"
#include "FireBlock.hpp"
#include "FletchingTableBlock.hpp"
#include "FlowerBlock.hpp"
#include "FlowerPotBlock.hpp"
#include "FlowingFluidBlock.hpp"
#include "FrostedIceBlock.hpp"
#include "FungusBlock.hpp"
#include "FurnaceBlock.hpp"
#include "GlassBlock.hpp"
#include "GlazedTerracottaBlock.hpp"
#include "GrassBlock.hpp"
#include "GrassPathBlock.hpp"
#include "GravelBlock.hpp"
#include "GrindstoneBlock.hpp"
#include "HayBlock.hpp"
#include "HoneyBlock.hpp"
#include "HopperBlock.hpp"
#include "HugeMushroomBlock.hpp"
#include "JigsawBlock.hpp"
#include "JukeboxBlock.hpp"
#include "KelpBlock.hpp"
#include "KelpTopBlock.hpp"
#include "LadderBlock.hpp"
#include "LanternBlock.hpp"
#include "LeavesBlock.hpp"
#include "LecternBlock.hpp"
#include "LeverBlock.hpp"
#include "LilyPadBlock.hpp"
#include "LoomBlock.hpp"
#include "MagmaBlock.hpp"
#include "MelonBlock.hpp"
#include "MovingPistonBlock.hpp"
#include "MushroomBlock.hpp"
#include "MyceliumBlock.hpp"
#include "NetherPortalBlock.hpp"
#include "NetherRootsBlock.hpp"
#include "NetherSproutsBlock.hpp"
#include "NetherWartBlock.hpp"
#include "NetherrackBlock.hpp"
#include "NoteBlock.hpp"
#include "NyliumBlock.hpp"
#include "ObserverBlock.hpp"
#include "OreBlock.hpp"
#include "PaneBlock.hpp"
#include "PistonBlock.hpp"
#include "PistonHeadBlock.hpp"
#include "PotatoBlock.hpp"
#include "PoweredRailBlock.hpp"
#include "PressurePlateBlock.hpp"
#include "PumpkinBlock.hpp"
#include "RailBlock.hpp"
#include "RedstoneBlock.hpp"
#include "RedstoneLampBlock.hpp"
#include "RedstoneOreBlock.hpp"
#include "RedstoneTorchBlock.hpp"
#include "RedstoneWallTorchBlock.hpp"
#include "RedstoneWireBlock.hpp"
#include "RepeaterBlock.hpp"
#include "RespawnAnchorBlock.hpp"
#include "SandBlock.hpp"
#include "SaplingBlock.hpp"
#include "ScaffoldingBlock.hpp"
#include "SeaGrassBlock.hpp"
#include "SeaPickleBlock.hpp"
#include "SilverfishBlock.hpp"
#include "SkullBlock.hpp"
#include "SkullPlayerBlock.hpp"
#include "SkullWallPlayerBlock.hpp"
#include "SlabBlock.hpp"
#include "SlimeBlock.hpp"
#include "SmithingTableBlock.hpp"
#include "SmokerBlock.hpp"
#include "SnowBlock.hpp"
#include "SoulFireBlock.hpp"
#include "SoulSandBlock.hpp"
#include "SpawnerBlock.hpp"
#include "SpongeBlock.hpp"
#include "StainedGlassBlock.hpp"
#include "StainedGlassPaneBlock.hpp"
#include "StairsBlock.hpp"
#include "StandingSignBlock.hpp"
#include "StemBlock.hpp"
#include "StoneButtonBlock.hpp"
#include "StonecutterBlock.hpp"
#include "StructureBlock.hpp"
#include "StructureVoidBlock.hpp"
#include "SugarCaneBlock.hpp"
#include "SweetBerryBushBlock.hpp"
#include "TNTBlock.hpp"
#include "TallFlowerBlock.hpp"
#include "TallGrassBlock.hpp"
#include "TallSeaGrassBlock.hpp"
#include "TargetBlock.hpp"
#include "TrapDoorBlock.hpp"
#include "TrappedChestBlock.hpp"
#include "TripWireBlock.hpp"
#include "TripWireHookBlock.hpp"
#include "TurtleEggBlock.hpp"
#include "TwistingVinesBlock.hpp"
#include "TwistingVinesTopBlock.hpp"
#include "VineBlock.hpp"
#include "WallBannerBlock.hpp"
#include "WallBlock.hpp"
#include "WallSignBlock.hpp"
#include "WallTorchBlock.hpp"
#include "WebBlock.hpp"
#include "WeepingVinesBlock.hpp"
#include "WeepingVinesTopBlock.hpp"
#include "WeightedPressurePlateBlock.hpp"
#include "WetSpongeBlock.hpp"
#include "WitherRoseBlock.hpp"
#include "WitherSkeletonSkullBlock.hpp"
#include "WitherSkeletonWallSkullBlock.hpp"
#include "WoodButtonBlock.hpp"

#include "BlockTable.hpp"
#include "ShulkerBoxBlock.hpp"
#include "material/Materials.hpp"

#include <spdlog/spdlog.h>

BlockTable Blocks::pallete{};
Registry<Block> Blocks::blocks{};

Block *Blocks::AIR;
Block *Blocks::STONE;
Block *Blocks::GRANITE;
Block *Blocks::POLISHED_GRANITE;
Block *Blocks::DIORITE;
Block *Blocks::POLISHED_DIORITE;
Block *Blocks::ANDESITE;
Block *Blocks::POLISHED_ANDESITE;
Block *Blocks::GRASS_BLOCK;
Block *Blocks::DIRT;
Block *Blocks::COARSE_DIRT;
Block *Blocks::PODZOL;
Block *Blocks::COBBLESTONE;
/*Block* Blocks::PLANKS;*/
Block *Blocks::OAK_PLANKS;
Block *Blocks::SPRUCE_PLANKS;
Block *Blocks::BIRCH_PLANKS;
Block *Blocks::JUNGLE_PLANKS;
Block *Blocks::ACACIA_PLANKS;
Block *Blocks::DARK_OAK_PLANKS;
Block *Blocks::OAK_SAPLING;
Block *Blocks::SPRUCE_SAPLING;
Block *Blocks::BIRCH_SAPLING;
Block *Blocks::JUNGLE_SAPLING;
Block *Blocks::ACACIA_SAPLING;
Block *Blocks::DARK_OAK_SAPLING;
Block *Blocks::BEDROCK;
Block *Blocks::WATER;
Block *Blocks::LAVA;
Block *Blocks::SAND;
Block *Blocks::RED_SAND;
Block *Blocks::GRAVEL;
Block *Blocks::GOLD_ORE;
Block *Blocks::IRON_ORE;
Block *Blocks::COAL_ORE;
Block *Blocks::NETHER_GOLD_ORE;
Block *Blocks::OAK_LOG;
Block *Blocks::SPRUCE_LOG;
Block *Blocks::BIRCH_LOG;
Block *Blocks::JUNGLE_LOG;
Block *Blocks::ACACIA_LOG;
Block *Blocks::DARK_OAK_LOG;
Block *Blocks::STRIPPED_SPRUCE_LOG;
Block *Blocks::STRIPPED_BIRCH_LOG;
Block *Blocks::STRIPPED_JUNGLE_LOG;
Block *Blocks::STRIPPED_ACACIA_LOG;
Block *Blocks::STRIPPED_DARK_OAK_LOG;
Block *Blocks::STRIPPED_OAK_LOG;
Block *Blocks::OAK_WOOD;
Block *Blocks::SPRUCE_WOOD;
Block *Blocks::BIRCH_WOOD;
Block *Blocks::JUNGLE_WOOD;
Block *Blocks::ACACIA_WOOD;
Block *Blocks::DARK_OAK_WOOD;
Block *Blocks::STRIPPED_OAK_WOOD;
Block *Blocks::STRIPPED_SPRUCE_WOOD;
Block *Blocks::STRIPPED_BIRCH_WOOD;
Block *Blocks::STRIPPED_JUNGLE_WOOD;
Block *Blocks::STRIPPED_ACACIA_WOOD;
Block *Blocks::STRIPPED_DARK_OAK_WOOD;
Block *Blocks::OAK_LEAVES;
Block *Blocks::SPRUCE_LEAVES;
Block *Blocks::BIRCH_LEAVES;
Block *Blocks::JUNGLE_LEAVES;
Block *Blocks::ACACIA_LEAVES;
Block *Blocks::DARK_OAK_LEAVES;
Block *Blocks::SPONGE;
Block *Blocks::WET_SPONGE;
Block *Blocks::GLASS;
Block *Blocks::LAPIS_ORE;
Block *Blocks::LAPIS_BLOCK;
Block *Blocks::DISPENSER;
Block *Blocks::SANDSTONE;
Block *Blocks::CHISELED_SANDSTONE;
Block *Blocks::CUT_SANDSTONE;
Block *Blocks::NOTE_BLOCK;
Block *Blocks::WHITE_BED;
Block *Blocks::ORANGE_BED;
Block *Blocks::MAGENTA_BED;
Block *Blocks::LIGHT_BLUE_BED;
Block *Blocks::YELLOW_BED;
Block *Blocks::LIME_BED;
Block *Blocks::PINK_BED;
Block *Blocks::GRAY_BED;
Block *Blocks::LIGHT_GRAY_BED;
Block *Blocks::CYAN_BED;
Block *Blocks::PURPLE_BED;
Block *Blocks::BLUE_BED;
Block *Blocks::BROWN_BED;
Block *Blocks::GREEN_BED;
Block *Blocks::RED_BED;
Block *Blocks::BLACK_BED;
Block *Blocks::POWERED_RAIL;
Block *Blocks::DETECTOR_RAIL;
Block *Blocks::STICKY_PISTON;
Block *Blocks::COBWEB;
Block *Blocks::GRASS;
Block *Blocks::FERN;
Block *Blocks::DEAD_BUSH;
Block *Blocks::SEAGRASS;
Block *Blocks::TALL_SEAGRASS;
Block *Blocks::PISTON;
Block *Blocks::PISTON_HEAD;
Block *Blocks::WHITE_WOOL;
Block *Blocks::ORANGE_WOOL;
Block *Blocks::MAGENTA_WOOL;
Block *Blocks::LIGHT_BLUE_WOOL;
Block *Blocks::YELLOW_WOOL;
Block *Blocks::LIME_WOOL;
Block *Blocks::PINK_WOOL;
Block *Blocks::GRAY_WOOL;
Block *Blocks::LIGHT_GRAY_WOOL;
Block *Blocks::CYAN_WOOL;
Block *Blocks::PURPLE_WOOL;
Block *Blocks::BLUE_WOOL;
Block *Blocks::BROWN_WOOL;
Block *Blocks::GREEN_WOOL;
Block *Blocks::RED_WOOL;
Block *Blocks::BLACK_WOOL;
Block *Blocks::MOVING_PISTON;
Block *Blocks::DANDELION;
Block *Blocks::POPPY;
Block *Blocks::BLUE_ORCHID;
Block *Blocks::ALLIUM;
Block *Blocks::AZURE_BLUET;
Block *Blocks::RED_TULIP;
Block *Blocks::ORANGE_TULIP;
Block *Blocks::WHITE_TULIP;
Block *Blocks::PINK_TULIP;
Block *Blocks::OXEYE_DAISY;
Block *Blocks::CORNFLOWER;
Block *Blocks::WITHER_ROSE;
Block *Blocks::LILY_OF_THE_VALLEY;
Block *Blocks::BROWN_MUSHROOM;
Block *Blocks::RED_MUSHROOM;
Block *Blocks::GOLD_BLOCK;
Block *Blocks::IRON_BLOCK;
Block *Blocks::BRICKS;
Block *Blocks::TNT;
Block *Blocks::BOOKSHELF;
Block *Blocks::MOSSY_COBBLESTONE;
Block *Blocks::OBSIDIAN;
Block *Blocks::TORCH;
Block *Blocks::WALL_TORCH;
Block *Blocks::FIRE;
Block *Blocks::SOUL_FIRE;
Block *Blocks::SPAWNER;
Block *Blocks::OAK_STAIRS;
Block *Blocks::CHEST;
Block *Blocks::REDSTONE_WIRE;
Block *Blocks::DIAMOND_ORE;
Block *Blocks::DIAMOND_BLOCK;
Block *Blocks::CRAFTING_TABLE;
Block *Blocks::WHEAT;
Block *Blocks::FARMLAND;
Block *Blocks::FURNACE;
Block *Blocks::OAK_SIGN;
Block *Blocks::SPRUCE_SIGN;
Block *Blocks::BIRCH_SIGN;
Block *Blocks::ACACIA_SIGN;
Block *Blocks::JUNGLE_SIGN;
Block *Blocks::DARK_OAK_SIGN;
Block *Blocks::OAK_DOOR;
Block *Blocks::LADDER;
Block *Blocks::RAIL;
Block *Blocks::COBBLESTONE_STAIRS;
Block *Blocks::OAK_WALL_SIGN;
Block *Blocks::SPRUCE_WALL_SIGN;
Block *Blocks::BIRCH_WALL_SIGN;
Block *Blocks::ACACIA_WALL_SIGN;
Block *Blocks::JUNGLE_WALL_SIGN;
Block *Blocks::DARK_OAK_WALL_SIGN;
Block *Blocks::LEVER;
Block *Blocks::STONE_PRESSURE_PLATE;
Block *Blocks::IRON_DOOR;
Block *Blocks::OAK_PRESSURE_PLATE;
Block *Blocks::SPRUCE_PRESSURE_PLATE;
Block *Blocks::BIRCH_PRESSURE_PLATE;
Block *Blocks::JUNGLE_PRESSURE_PLATE;
Block *Blocks::ACACIA_PRESSURE_PLATE;
Block *Blocks::DARK_OAK_PRESSURE_PLATE;
Block *Blocks::REDSTONE_ORE;
Block *Blocks::REDSTONE_TORCH;
Block *Blocks::REDSTONE_WALL_TORCH;
Block *Blocks::STONE_BUTTON;
Block *Blocks::SNOW;
Block *Blocks::ICE;
Block *Blocks::SNOW_BLOCK;
Block *Blocks::CACTUS;
Block *Blocks::CLAY;
Block *Blocks::SUGAR_CANE;
Block *Blocks::JUKEBOX;
Block *Blocks::OAK_FENCE;
Block *Blocks::PUMPKIN;
Block *Blocks::NETHERRACK;
Block *Blocks::SOUL_SAND;
Block *Blocks::SOUL_SOIL;
Block *Blocks::BASALT;
Block *Blocks::POLISHED_BASALT;
Block *Blocks::SOUL_TORCH;
Block *Blocks::SOUL_WALL_TORCH;
Block *Blocks::GLOWSTONE;
Block *Blocks::NETHER_PORTAL;
Block *Blocks::CARVED_PUMPKIN;
Block *Blocks::JACK_O_LANTERN;
Block *Blocks::CAKE;
Block *Blocks::REPEATER;
Block *Blocks::WHITE_STAINED_GLASS;
Block *Blocks::ORANGE_STAINED_GLASS;
Block *Blocks::MAGENTA_STAINED_GLASS;
Block *Blocks::LIGHT_BLUE_STAINED_GLASS;
Block *Blocks::YELLOW_STAINED_GLASS;
Block *Blocks::LIME_STAINED_GLASS;
Block *Blocks::PINK_STAINED_GLASS;
Block *Blocks::GRAY_STAINED_GLASS;
Block *Blocks::LIGHT_GRAY_STAINED_GLASS;
Block *Blocks::CYAN_STAINED_GLASS;
Block *Blocks::PURPLE_STAINED_GLASS;
Block *Blocks::BLUE_STAINED_GLASS;
Block *Blocks::BROWN_STAINED_GLASS;
Block *Blocks::GREEN_STAINED_GLASS;
Block *Blocks::RED_STAINED_GLASS;
Block *Blocks::BLACK_STAINED_GLASS;
Block *Blocks::OAK_TRAPDOOR;
Block *Blocks::SPRUCE_TRAPDOOR;
Block *Blocks::BIRCH_TRAPDOOR;
Block *Blocks::JUNGLE_TRAPDOOR;
Block *Blocks::ACACIA_TRAPDOOR;
Block *Blocks::DARK_OAK_TRAPDOOR;
Block *Blocks::STONE_BRICKS;
Block *Blocks::MOSSY_STONE_BRICKS;
Block *Blocks::CRACKED_STONE_BRICKS;
Block *Blocks::CHISELED_STONE_BRICKS;
Block *Blocks::INFESTED_STONE;
Block *Blocks::INFESTED_COBBLESTONE;
Block *Blocks::INFESTED_STONE_BRICKS;
Block *Blocks::INFESTED_MOSSY_STONE_BRICKS;
Block *Blocks::INFESTED_CRACKED_STONE_BRICKS;
Block *Blocks::INFESTED_CHISELED_STONE_BRICKS;
Block *Blocks::BROWN_MUSHROOM_BLOCK;
Block *Blocks::RED_MUSHROOM_BLOCK;
Block *Blocks::MUSHROOM_STEM;
Block *Blocks::IRON_BARS;
Block *Blocks::CHAIN;
Block *Blocks::GLASS_PANE;
Block *Blocks::MELON;
Block *Blocks::ATTACHED_PUMPKIN_STEM;
Block *Blocks::ATTACHED_MELON_STEM;
Block *Blocks::PUMPKIN_STEM;
Block *Blocks::MELON_STEM;
Block *Blocks::VINE;
Block *Blocks::OAK_FENCE_GATE;
Block *Blocks::BRICK_STAIRS;
Block *Blocks::STONE_BRICK_STAIRS;
Block *Blocks::MYCELIUM;
Block *Blocks::LILY_PAD;
Block *Blocks::NETHER_BRICKS;
Block *Blocks::NETHER_BRICK_FENCE;
Block *Blocks::NETHER_BRICK_STAIRS;
Block *Blocks::NETHER_WART;
Block *Blocks::ENCHANTING_TABLE;
Block *Blocks::BREWING_STAND;
Block *Blocks::CAULDRON;
Block *Blocks::END_PORTAL;
Block *Blocks::END_PORTAL_FRAME;
Block *Blocks::END_STONE;
Block *Blocks::DRAGON_EGG;
Block *Blocks::REDSTONE_LAMP;
Block *Blocks::COCOA;
Block *Blocks::SANDSTONE_STAIRS;
Block *Blocks::EMERALD_ORE;
Block *Blocks::ENDER_CHEST;
Block *Blocks::TRIPWIRE_HOOK;
Block *Blocks::TRIPWIRE;
Block *Blocks::EMERALD_BLOCK;
Block *Blocks::SPRUCE_STAIRS;
Block *Blocks::BIRCH_STAIRS;
Block *Blocks::JUNGLE_STAIRS;
Block *Blocks::COMMAND_BLOCK;
Block *Blocks::BEACON;
Block *Blocks::COBBLESTONE_WALL;
Block *Blocks::MOSSY_COBBLESTONE_WALL;
Block *Blocks::FLOWER_POT;
Block *Blocks::POTTED_OAK_SAPLING;
Block *Blocks::POTTED_SPRUCE_SAPLING;
Block *Blocks::POTTED_BIRCH_SAPLING;
Block *Blocks::POTTED_JUNGLE_SAPLING;
Block *Blocks::POTTED_ACACIA_SAPLING;
Block *Blocks::POTTED_DARK_OAK_SAPLING;
Block *Blocks::POTTED_FERN;
Block *Blocks::POTTED_DANDELION;
Block *Blocks::POTTED_POPPY;
Block *Blocks::POTTED_BLUE_ORCHID;
Block *Blocks::POTTED_ALLIUM;
Block *Blocks::POTTED_AZURE_BLUET;
Block *Blocks::POTTED_RED_TULIP;
Block *Blocks::POTTED_ORANGE_TULIP;
Block *Blocks::POTTED_WHITE_TULIP;
Block *Blocks::POTTED_PINK_TULIP;
Block *Blocks::POTTED_OXEYE_DAISY;
Block *Blocks::POTTED_CORNFLOWER;
Block *Blocks::POTTED_LILY_OF_THE_VALLEY;
Block *Blocks::POTTED_WITHER_ROSE;
Block *Blocks::POTTED_RED_MUSHROOM;
Block *Blocks::POTTED_BROWN_MUSHROOM;
Block *Blocks::POTTED_DEAD_BUSH;
Block *Blocks::POTTED_CACTUS;
Block *Blocks::CARROTS;
Block *Blocks::POTATOES;
Block *Blocks::OAK_BUTTON;
Block *Blocks::SPRUCE_BUTTON;
Block *Blocks::BIRCH_BUTTON;
Block *Blocks::JUNGLE_BUTTON;
Block *Blocks::ACACIA_BUTTON;
Block *Blocks::DARK_OAK_BUTTON;
Block *Blocks::SKELETON_SKULL;
Block *Blocks::SKELETON_WALL_SKULL;
Block *Blocks::WITHER_SKELETON_SKULL;
Block *Blocks::WITHER_SKELETON_WALL_SKULL;
Block *Blocks::ZOMBIE_HEAD;
Block *Blocks::ZOMBIE_WALL_HEAD;
Block *Blocks::PLAYER_HEAD;
Block *Blocks::PLAYER_WALL_HEAD;
Block *Blocks::CREEPER_HEAD;
Block *Blocks::CREEPER_WALL_HEAD;
Block *Blocks::DRAGON_HEAD;
Block *Blocks::DRAGON_WALL_HEAD;
Block *Blocks::ANVIL;
Block *Blocks::CHIPPED_ANVIL;
Block *Blocks::DAMAGED_ANVIL;
Block *Blocks::TRAPPED_CHEST;
Block *Blocks::LIGHT_WEIGHTED_PRESSURE_PLATE;
Block *Blocks::HEAVY_WEIGHTED_PRESSURE_PLATE;
Block *Blocks::COMPARATOR;
Block *Blocks::DAYLIGHT_DETECTOR;
Block *Blocks::REDSTONE_BLOCK;
Block *Blocks::NETHER_QUARTZ_ORE;
Block *Blocks::HOPPER;
Block *Blocks::QUARTZ_BLOCK;
Block *Blocks::CHISELED_QUARTZ_BLOCK;
Block *Blocks::QUARTZ_PILLAR;
Block *Blocks::QUARTZ_STAIRS;
Block *Blocks::ACTIVATOR_RAIL;
Block *Blocks::DROPPER;
Block *Blocks::WHITE_TERRACOTTA;
Block *Blocks::ORANGE_TERRACOTTA;
Block *Blocks::MAGENTA_TERRACOTTA;
Block *Blocks::LIGHT_BLUE_TERRACOTTA;
Block *Blocks::YELLOW_TERRACOTTA;
Block *Blocks::LIME_TERRACOTTA;
Block *Blocks::PINK_TERRACOTTA;
Block *Blocks::GRAY_TERRACOTTA;
Block *Blocks::LIGHT_GRAY_TERRACOTTA;
Block *Blocks::CYAN_TERRACOTTA;
Block *Blocks::PURPLE_TERRACOTTA;
Block *Blocks::BLUE_TERRACOTTA;
Block *Blocks::BROWN_TERRACOTTA;
Block *Blocks::GREEN_TERRACOTTA;
Block *Blocks::RED_TERRACOTTA;
Block *Blocks::BLACK_TERRACOTTA;
Block *Blocks::WHITE_STAINED_GLASS_PANE;
Block *Blocks::ORANGE_STAINED_GLASS_PANE;
Block *Blocks::MAGENTA_STAINED_GLASS_PANE;
Block *Blocks::LIGHT_BLUE_STAINED_GLASS_PANE;
Block *Blocks::YELLOW_STAINED_GLASS_PANE;
Block *Blocks::LIME_STAINED_GLASS_PANE;
Block *Blocks::PINK_STAINED_GLASS_PANE;
Block *Blocks::GRAY_STAINED_GLASS_PANE;
Block *Blocks::LIGHT_GRAY_STAINED_GLASS_PANE;
Block *Blocks::CYAN_STAINED_GLASS_PANE;
Block *Blocks::PURPLE_STAINED_GLASS_PANE;
Block *Blocks::BLUE_STAINED_GLASS_PANE;
Block *Blocks::BROWN_STAINED_GLASS_PANE;
Block *Blocks::GREEN_STAINED_GLASS_PANE;
Block *Blocks::RED_STAINED_GLASS_PANE;
Block *Blocks::BLACK_STAINED_GLASS_PANE;
Block *Blocks::ACACIA_STAIRS;
Block *Blocks::DARK_OAK_STAIRS;
Block *Blocks::SLIME_BLOCK;
Block *Blocks::BARRIER;
Block *Blocks::IRON_TRAPDOOR;
Block *Blocks::PRISMARINE;
Block *Blocks::PRISMARINE_BRICKS;
Block *Blocks::DARK_PRISMARINE;
Block *Blocks::PRISMARINE_STAIRS;
Block *Blocks::PRISMARINE_BRICK_STAIRS;
Block *Blocks::DARK_PRISMARINE_STAIRS;
Block *Blocks::PRISMARINE_SLAB;
Block *Blocks::PRISMARINE_BRICK_SLAB;
Block *Blocks::DARK_PRISMARINE_SLAB;
Block *Blocks::SEA_LANTERN;
Block *Blocks::HAY_BLOCK;
Block *Blocks::WHITE_CARPET;
Block *Blocks::ORANGE_CARPET;
Block *Blocks::MAGENTA_CARPET;
Block *Blocks::LIGHT_BLUE_CARPET;
Block *Blocks::YELLOW_CARPET;
Block *Blocks::LIME_CARPET;
Block *Blocks::PINK_CARPET;
Block *Blocks::GRAY_CARPET;
Block *Blocks::LIGHT_GRAY_CARPET;
Block *Blocks::CYAN_CARPET;
Block *Blocks::PURPLE_CARPET;
Block *Blocks::BLUE_CARPET;
Block *Blocks::BROWN_CARPET;
Block *Blocks::GREEN_CARPET;
Block *Blocks::RED_CARPET;
Block *Blocks::BLACK_CARPET;
Block *Blocks::TERRACOTTA;
Block *Blocks::COAL_BLOCK;
Block *Blocks::PACKED_ICE;
Block *Blocks::SUNFLOWER;
Block *Blocks::LILAC;
Block *Blocks::ROSE_BUSH;
Block *Blocks::PEONY;
Block *Blocks::TALL_GRASS;
Block *Blocks::LARGE_FERN;
Block *Blocks::WHITE_BANNER;
Block *Blocks::ORANGE_BANNER;
Block *Blocks::MAGENTA_BANNER;
Block *Blocks::LIGHT_BLUE_BANNER;
Block *Blocks::YELLOW_BANNER;
Block *Blocks::LIME_BANNER;
Block *Blocks::PINK_BANNER;
Block *Blocks::GRAY_BANNER;
Block *Blocks::LIGHT_GRAY_BANNER;
Block *Blocks::CYAN_BANNER;
Block *Blocks::PURPLE_BANNER;
Block *Blocks::BLUE_BANNER;
Block *Blocks::BROWN_BANNER;
Block *Blocks::GREEN_BANNER;
Block *Blocks::RED_BANNER;
Block *Blocks::BLACK_BANNER;
Block *Blocks::WHITE_WALL_BANNER;
Block *Blocks::ORANGE_WALL_BANNER;
Block *Blocks::MAGENTA_WALL_BANNER;
Block *Blocks::LIGHT_BLUE_WALL_BANNER;
Block *Blocks::YELLOW_WALL_BANNER;
Block *Blocks::LIME_WALL_BANNER;
Block *Blocks::PINK_WALL_BANNER;
Block *Blocks::GRAY_WALL_BANNER;
Block *Blocks::LIGHT_GRAY_WALL_BANNER;
Block *Blocks::CYAN_WALL_BANNER;
Block *Blocks::PURPLE_WALL_BANNER;
Block *Blocks::BLUE_WALL_BANNER;
Block *Blocks::BROWN_WALL_BANNER;
Block *Blocks::GREEN_WALL_BANNER;
Block *Blocks::RED_WALL_BANNER;
Block *Blocks::BLACK_WALL_BANNER;
Block *Blocks::RED_SANDSTONE;
Block *Blocks::CHISELED_RED_SANDSTONE;
Block *Blocks::CUT_RED_SANDSTONE;
Block *Blocks::RED_SANDSTONE_STAIRS;
Block *Blocks::OAK_SLAB;
Block *Blocks::SPRUCE_SLAB;
Block *Blocks::BIRCH_SLAB;
Block *Blocks::JUNGLE_SLAB;
Block *Blocks::ACACIA_SLAB;
Block *Blocks::DARK_OAK_SLAB;
Block *Blocks::STONE_SLAB;
Block *Blocks::SMOOTH_STONE_SLAB;
Block *Blocks::SANDSTONE_SLAB;
Block *Blocks::CUT_SANDSTONE_SLAB;
Block *Blocks::PETRIFIED_OAK_SLAB;
Block *Blocks::COBBLESTONE_SLAB;
Block *Blocks::BRICK_SLAB;
Block *Blocks::STONE_BRICK_SLAB;
Block *Blocks::NETHER_BRICK_SLAB;
Block *Blocks::QUARTZ_SLAB;
Block *Blocks::RED_SANDSTONE_SLAB;
Block *Blocks::CUT_RED_SANDSTONE_SLAB;
Block *Blocks::PURPUR_SLAB;
Block *Blocks::SMOOTH_STONE;
Block *Blocks::SMOOTH_SANDSTONE;
Block *Blocks::SMOOTH_QUARTZ;
Block *Blocks::SMOOTH_RED_SANDSTONE;
Block *Blocks::SPRUCE_FENCE_GATE;
Block *Blocks::BIRCH_FENCE_GATE;
Block *Blocks::JUNGLE_FENCE_GATE;
Block *Blocks::ACACIA_FENCE_GATE;
Block *Blocks::DARK_OAK_FENCE_GATE;
Block *Blocks::SPRUCE_FENCE;
Block *Blocks::BIRCH_FENCE;
Block *Blocks::JUNGLE_FENCE;
Block *Blocks::ACACIA_FENCE;
Block *Blocks::DARK_OAK_FENCE;
Block *Blocks::SPRUCE_DOOR;
Block *Blocks::BIRCH_DOOR;
Block *Blocks::JUNGLE_DOOR;
Block *Blocks::ACACIA_DOOR;
Block *Blocks::DARK_OAK_DOOR;
Block *Blocks::END_ROD;
Block *Blocks::CHORUS_PLANT;
Block *Blocks::CHORUS_FLOWER;
Block *Blocks::PURPUR_BLOCK;
Block *Blocks::PURPUR_PILLAR;
Block *Blocks::PURPUR_STAIRS;
Block *Blocks::END_STONE_BRICKS;
Block *Blocks::BEETROOTS;
Block *Blocks::GRASS_PATH;
Block *Blocks::END_GATEWAY;
Block *Blocks::REPEATING_COMMAND_BLOCK;
Block *Blocks::CHAIN_COMMAND_BLOCK;
Block *Blocks::FROSTED_ICE;
Block *Blocks::MAGMA_BLOCK;
Block *Blocks::NETHER_WART_BLOCK;
Block *Blocks::RED_NETHER_BRICKS;
Block *Blocks::BONE_BLOCK;
Block *Blocks::STRUCTURE_VOID;
Block *Blocks::OBSERVER;
Block *Blocks::SHULKER_BOX;
Block *Blocks::WHITE_SHULKER_BOX;
Block *Blocks::ORANGE_SHULKER_BOX;
Block *Blocks::MAGENTA_SHULKER_BOX;
Block *Blocks::LIGHT_BLUE_SHULKER_BOX;
Block *Blocks::YELLOW_SHULKER_BOX;
Block *Blocks::LIME_SHULKER_BOX;
Block *Blocks::PINK_SHULKER_BOX;
Block *Blocks::GRAY_SHULKER_BOX;
Block *Blocks::LIGHT_GRAY_SHULKER_BOX;
Block *Blocks::CYAN_SHULKER_BOX;
Block *Blocks::PURPLE_SHULKER_BOX;
Block *Blocks::BLUE_SHULKER_BOX;
Block *Blocks::BROWN_SHULKER_BOX;
Block *Blocks::GREEN_SHULKER_BOX;
Block *Blocks::RED_SHULKER_BOX;
Block *Blocks::BLACK_SHULKER_BOX;
Block *Blocks::WHITE_GLAZED_TERRACOTTA;
Block *Blocks::ORANGE_GLAZED_TERRACOTTA;
Block *Blocks::MAGENTA_GLAZED_TERRACOTTA;
Block *Blocks::LIGHT_BLUE_GLAZED_TERRACOTTA;
Block *Blocks::YELLOW_GLAZED_TERRACOTTA;
Block *Blocks::LIME_GLAZED_TERRACOTTA;
Block *Blocks::PINK_GLAZED_TERRACOTTA;
Block *Blocks::GRAY_GLAZED_TERRACOTTA;
Block *Blocks::LIGHT_GRAY_GLAZED_TERRACOTTA;
Block *Blocks::CYAN_GLAZED_TERRACOTTA;
Block *Blocks::PURPLE_GLAZED_TERRACOTTA;
Block *Blocks::BLUE_GLAZED_TERRACOTTA;
Block *Blocks::BROWN_GLAZED_TERRACOTTA;
Block *Blocks::GREEN_GLAZED_TERRACOTTA;
Block *Blocks::RED_GLAZED_TERRACOTTA;
Block *Blocks::BLACK_GLAZED_TERRACOTTA;
Block *Blocks::WHITE_CONCRETE;
Block *Blocks::ORANGE_CONCRETE;
Block *Blocks::MAGENTA_CONCRETE;
Block *Blocks::LIGHT_BLUE_CONCRETE;
Block *Blocks::YELLOW_CONCRETE;
Block *Blocks::LIME_CONCRETE;
Block *Blocks::PINK_CONCRETE;
Block *Blocks::GRAY_CONCRETE;
Block *Blocks::LIGHT_GRAY_CONCRETE;
Block *Blocks::CYAN_CONCRETE;
Block *Blocks::PURPLE_CONCRETE;
Block *Blocks::BLUE_CONCRETE;
Block *Blocks::BROWN_CONCRETE;
Block *Blocks::GREEN_CONCRETE;
Block *Blocks::RED_CONCRETE;
Block *Blocks::BLACK_CONCRETE;
Block *Blocks::WHITE_CONCRETE_POWDER;
Block *Blocks::ORANGE_CONCRETE_POWDER;
Block *Blocks::MAGENTA_CONCRETE_POWDER;
Block *Blocks::LIGHT_BLUE_CONCRETE_POWDER;
Block *Blocks::YELLOW_CONCRETE_POWDER;
Block *Blocks::LIME_CONCRETE_POWDER;
Block *Blocks::PINK_CONCRETE_POWDER;
Block *Blocks::GRAY_CONCRETE_POWDER;
Block *Blocks::LIGHT_GRAY_CONCRETE_POWDER;
Block *Blocks::CYAN_CONCRETE_POWDER;
Block *Blocks::PURPLE_CONCRETE_POWDER;
Block *Blocks::BLUE_CONCRETE_POWDER;
Block *Blocks::BROWN_CONCRETE_POWDER;
Block *Blocks::GREEN_CONCRETE_POWDER;
Block *Blocks::RED_CONCRETE_POWDER;
Block *Blocks::BLACK_CONCRETE_POWDER;
Block *Blocks::KELP;
Block *Blocks::KELP_PLANT;
Block *Blocks::DRIED_KELP_BLOCK;
Block *Blocks::TURTLE_EGG;
Block *Blocks::DEAD_TUBE_CORAL_BLOCK;
Block *Blocks::DEAD_BRAIN_CORAL_BLOCK;
Block *Blocks::DEAD_BUBBLE_CORAL_BLOCK;
Block *Blocks::DEAD_FIRE_CORAL_BLOCK;
Block *Blocks::DEAD_HORN_CORAL_BLOCK;
Block *Blocks::TUBE_CORAL_BLOCK;
Block *Blocks::BRAIN_CORAL_BLOCK;
Block *Blocks::BUBBLE_CORAL_BLOCK;
Block *Blocks::FIRE_CORAL_BLOCK;
Block *Blocks::HORN_CORAL_BLOCK;
Block *Blocks::DEAD_TUBE_CORAL;
Block *Blocks::DEAD_BRAIN_CORAL;
Block *Blocks::DEAD_BUBBLE_CORAL;
Block *Blocks::DEAD_FIRE_CORAL;
Block *Blocks::DEAD_HORN_CORAL;
Block *Blocks::TUBE_CORAL;
Block *Blocks::BRAIN_CORAL;
Block *Blocks::BUBBLE_CORAL;
Block *Blocks::FIRE_CORAL;
Block *Blocks::HORN_CORAL;
Block *Blocks::DEAD_TUBE_CORAL_FAN;
Block *Blocks::DEAD_BRAIN_CORAL_FAN;
Block *Blocks::DEAD_BUBBLE_CORAL_FAN;
Block *Blocks::DEAD_FIRE_CORAL_FAN;
Block *Blocks::DEAD_HORN_CORAL_FAN;
Block *Blocks::TUBE_CORAL_FAN;
Block *Blocks::BRAIN_CORAL_FAN;
Block *Blocks::BUBBLE_CORAL_FAN;
Block *Blocks::FIRE_CORAL_FAN;
Block *Blocks::HORN_CORAL_FAN;
Block *Blocks::DEAD_TUBE_CORAL_WALL_FAN;
Block *Blocks::DEAD_BRAIN_CORAL_WALL_FAN;
Block *Blocks::DEAD_BUBBLE_CORAL_WALL_FAN;
Block *Blocks::DEAD_FIRE_CORAL_WALL_FAN;
Block *Blocks::DEAD_HORN_CORAL_WALL_FAN;
Block *Blocks::TUBE_CORAL_WALL_FAN;
Block *Blocks::BRAIN_CORAL_WALL_FAN;
Block *Blocks::BUBBLE_CORAL_WALL_FAN;
Block *Blocks::FIRE_CORAL_WALL_FAN;
Block *Blocks::HORN_CORAL_WALL_FAN;
Block *Blocks::SEA_PICKLE;
Block *Blocks::BLUE_ICE;
Block *Blocks::CONDUIT;
Block *Blocks::BAMBOO_SAPLING;
Block *Blocks::BAMBOO;
Block *Blocks::POTTED_BAMBOO;
Block *Blocks::VOID_AIR;
Block *Blocks::CAVE_AIR;
Block *Blocks::BUBBLE_COLUMN;
Block *Blocks::POLISHED_GRANITE_STAIRS;
Block *Blocks::SMOOTH_RED_SANDSTONE_STAIRS;
Block *Blocks::MOSSY_STONE_BRICK_STAIRS;
Block *Blocks::POLISHED_DIORITE_STAIRS;
Block *Blocks::MOSSY_COBBLESTONE_STAIRS;
Block *Blocks::END_STONE_BRICK_STAIRS;
Block *Blocks::STONE_STAIRS;
Block *Blocks::SMOOTH_SANDSTONE_STAIRS;
Block *Blocks::SMOOTH_QUARTZ_STAIRS;
Block *Blocks::GRANITE_STAIRS;
Block *Blocks::ANDESITE_STAIRS;
Block *Blocks::RED_NETHER_BRICK_STAIRS;
Block *Blocks::POLISHED_ANDESITE_STAIRS;
Block *Blocks::DIORITE_STAIRS;
Block *Blocks::POLISHED_GRANITE_SLAB;
Block *Blocks::SMOOTH_RED_SANDSTONE_SLAB;
Block *Blocks::MOSSY_STONE_BRICK_SLAB;
Block *Blocks::POLISHED_DIORITE_SLAB;
Block *Blocks::MOSSY_COBBLESTONE_SLAB;
Block *Blocks::END_STONE_BRICK_SLAB;
Block *Blocks::SMOOTH_SANDSTONE_SLAB;
Block *Blocks::SMOOTH_QUARTZ_SLAB;
Block *Blocks::GRANITE_SLAB;
Block *Blocks::ANDESITE_SLAB;
Block *Blocks::RED_NETHER_BRICK_SLAB;
Block *Blocks::POLISHED_ANDESITE_SLAB;
Block *Blocks::DIORITE_SLAB;
Block *Blocks::BRICK_WALL;
Block *Blocks::PRISMARINE_WALL;
Block *Blocks::RED_SANDSTONE_WALL;
Block *Blocks::MOSSY_STONE_BRICK_WALL;
Block *Blocks::GRANITE_WALL;
Block *Blocks::STONE_BRICK_WALL;
Block *Blocks::NETHER_BRICK_WALL;
Block *Blocks::ANDESITE_WALL;
Block *Blocks::RED_NETHER_BRICK_WALL;
Block *Blocks::SANDSTONE_WALL;
Block *Blocks::END_STONE_BRICK_WALL;
Block *Blocks::DIORITE_WALL;
Block *Blocks::SCAFFOLDING;
Block *Blocks::LOOM;
Block *Blocks::BARREL;
Block *Blocks::SMOKER;
Block *Blocks::BLAST_FURNACE;
Block *Blocks::CARTOGRAPHY_TABLE;
Block *Blocks::FLETCHING_TABLE;
Block *Blocks::GRINDSTONE;
Block *Blocks::LECTERN;
Block *Blocks::SMITHING_TABLE;
Block *Blocks::STONECUTTER;
Block *Blocks::BELL;
Block *Blocks::LANTERN;
Block *Blocks::SOUL_LANTERN;
Block *Blocks::CAMPFIRE;
Block *Blocks::SOUL_CAMPFIRE;
Block *Blocks::SWEET_BERRY_BUSH;
Block *Blocks::WARPED_STEM;
Block *Blocks::STRIPPED_WARPED_STEM;
Block *Blocks::WARPED_HYPHAE;
Block *Blocks::STRIPPED_WARPED_HYPHAE;
Block *Blocks::WARPED_NYLIUM;
Block *Blocks::WARPED_FUNGUS;
Block *Blocks::WARPED_WART_BLOCK;
Block *Blocks::WARPED_ROOTS;
Block *Blocks::NETHER_SPROUTS;
Block *Blocks::CRIMSON_STEM;
Block *Blocks::STRIPPED_CRIMSON_STEM;
Block *Blocks::CRIMSON_HYPHAE;
Block *Blocks::STRIPPED_CRIMSON_HYPHAE;
Block *Blocks::CRIMSON_NYLIUM;
Block *Blocks::CRIMSON_FUNGUS;
Block *Blocks::SHROOMLIGHT;
Block *Blocks::WEEPING_VINES;
Block *Blocks::WEEPING_VINES_PLANT;
Block *Blocks::TWISTING_VINES;
Block *Blocks::TWISTING_VINES_PLANT;
Block *Blocks::CRIMSON_ROOTS;
Block *Blocks::CRIMSON_PLANKS;
Block *Blocks::WARPED_PLANKS;
Block *Blocks::CRIMSON_SLAB;
Block *Blocks::WARPED_SLAB;
Block *Blocks::CRIMSON_PRESSURE_PLATE;
Block *Blocks::WARPED_PRESSURE_PLATE;
Block *Blocks::CRIMSON_FENCE;
Block *Blocks::WARPED_FENCE;
Block *Blocks::CRIMSON_TRAPDOOR;
Block *Blocks::WARPED_TRAPDOOR;
Block *Blocks::CRIMSON_FENCE_GATE;
Block *Blocks::WARPED_FENCE_GATE;
Block *Blocks::CRIMSON_STAIRS;
Block *Blocks::WARPED_STAIRS;
Block *Blocks::CRIMSON_BUTTON;
Block *Blocks::WARPED_BUTTON;
Block *Blocks::CRIMSON_DOOR;
Block *Blocks::WARPED_DOOR;
Block *Blocks::CRIMSON_SIGN;
Block *Blocks::WARPED_SIGN;
Block *Blocks::CRIMSON_WALL_SIGN;
Block *Blocks::WARPED_WALL_SIGN;
Block *Blocks::STRUCTURE_BLOCK;
Block *Blocks::JIGSAW;
Block *Blocks::COMPOSTER;
Block *Blocks::TARGET;
Block *Blocks::BEE_NEST;
Block *Blocks::BEEHIVE;
Block *Blocks::HONEY_BLOCK;
Block *Blocks::HONEYCOMB_BLOCK;
Block *Blocks::NETHERITE_BLOCK;
Block *Blocks::ANCIENT_DEBRIS;
Block *Blocks::CRYING_OBSIDIAN;
Block *Blocks::RESPAWN_ANCHOR;
Block *Blocks::POTTED_CRIMSON_FUNGUS;
Block *Blocks::POTTED_WARPED_FUNGUS;
Block *Blocks::POTTED_CRIMSON_ROOTS;
Block *Blocks::POTTED_WARPED_ROOTS;
Block *Blocks::LODESTONE;
Block *Blocks::BLACKSTONE;
Block *Blocks::BLACKSTONE_STAIRS;
Block *Blocks::BLACKSTONE_WALL;
Block *Blocks::BLACKSTONE_SLAB;
Block *Blocks::POLISHED_BLACKSTONE;
Block *Blocks::POLISHED_BLACKSTONE_BRICKS;
Block *Blocks::CRACKED_POLISHED_BLACKSTONE_BRICKS;
Block *Blocks::CHISELED_POLISHED_BLACKSTONE;
Block *Blocks::POLISHED_BLACKSTONE_BRICK_SLAB;
Block *Blocks::POLISHED_BLACKSTONE_BRICK_STAIRS;
Block *Blocks::POLISHED_BLACKSTONE_BRICK_WALL;
Block *Blocks::GILDED_BLACKSTONE;
Block *Blocks::POLISHED_BLACKSTONE_STAIRS;
Block *Blocks::POLISHED_BLACKSTONE_SLAB;
Block *Blocks::POLISHED_BLACKSTONE_PRESSURE_PLATE;
Block *Blocks::POLISHED_BLACKSTONE_BUTTON;
Block *Blocks::POLISHED_BLACKSTONE_WALL;
Block *Blocks::CHISELED_NETHER_BRICKS;
Block *Blocks::CRACKED_NETHER_BRICKS;
Block *Blocks::QUARTZ_BRICKS;

//private static ShulkerBoxBlock createShulkerBox(@Nullable DyeColor color, AbstractBlock.BlockBehaviour behaviour) {
//        AbstractBlock.IPositionPredicate abstractblock$ipositionpredicate = (p_235444_0_, p_235444_1_, p_235444_2_) -> {
//            TileEntity tileentity = p_235444_1_.getTileEntity(p_235444_2_);
//            if (!(tileentity instanceof ShulkerBoxTileEntity)) {
//                return true;
//            } else {
//                ShulkerBoxTileEntity shulkerboxtileentity = (ShulkerBoxTileEntity)tileentity;
//                return shulkerboxtileentity.func_235676_l_();
//            }
//        };
//        return new ShulkerBoxBlock(color, behaviour.hardnessAndResistance(2.0F).setVariableOpacity().notSolid().setSuffocates(abstractblock$ipositionpredicate).setBlocksVision(abstractblock$ipositionpredicate));
//    }
//private static Block create(String key, Block blockIn) {
//        return Registry.create(Registry.BLOCK, key, blockIn);
//    }

template <int32_t light>
static auto getLightLevelLit() {
    return [](const BlockData& state) -> int32_t {
        return state.get<Property::LIT>() ? light : 0;
    };
}

template <int32_t light>
static auto getLightValue() {
    return [](const BlockData& state) -> int32_t {
        return light;
    };
}

static auto getMaterialColor(const MaterialColor &value) {
    return [value](const BlockData &data) -> MaterialColor { return value; };
}

static bool neverAllowSpawn(BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) {
    return false;
}

static bool alwaysAllowSpawn(BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) {
    return true;
}

static bool allowsSpawnOnLeaves(BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) {
    return false;// entity == EntityType.OCELOT || entity == EntityType.PARROT;
}

static bool allowsSpawnImmuneToFire(BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) {
    return false;// entity.isImmuneToFire();
}

static bool needsPostProcessing(BlockReader &reader, const BlockData &data, const BlockPos &pos) {
    return true;
}

static bool isntSolid(BlockReader &reader, const BlockData &data, const BlockPos &pos) {
    return false;
}

static bool isntExtended(BlockReader &reader, const BlockData &data, const BlockPos &pos) {
    return true;//!data.get(PistonBlock::EXTENDED);
};

template<typename T, typename... Args>
static auto create(const std::string& name, Args &&...args) -> T* {
    const auto id = Blocks::pallete.getId(name);
    auto block = Blocks::blocks.add(static_cast<size_t>(id), name, std::make_unique<T>(id, std::forward<Args>(args)...));

    block->fillStateContainer();
    block->setDefaultState();
    block->fillValidStates();
    return dynamic_cast<T*>(block);
}

static auto createLogBlock(const std::string& name, MaterialColor topColor, MaterialColor barkColor) -> Block* {
    return create<RotatedPillarBlock>(name, BlockBehaviourUtil::create(Materials::WOOD,
        [topColor, barkColor](const BlockData &data) -> MaterialColor {
            return topColor;// data.get(RotatedPillarBlock::AXIS) == DirectionAxis::Y ? topColor : barkColor;
        })
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
}

static auto createPiston(const std::string& name, bool sticky) -> Block* {
    return create<PistonBlock>(name, sticky, BlockBehaviourUtil::create(Materials::PISTON)
         .setHardnessAndResistance(1.5F)
         .setOpaque(isntSolid)
         .setSuffocates(isntExtended)
         .setBlocksVision(isntExtended));
}

static auto createLeavesBlock(const std::string& name) -> Block* {
    return create<LeavesBlock>(name, BlockBehaviourUtil::create(Materials::LEAVES)
        .setTintType(TintType::Foliage)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(0.2F)
        .setTickRandomly()
        .setSound(SoundType::PLANT)
        .notSolid()
        .setAllowsSpawn(allowsSpawnOnLeaves)
        .setSuffocates(isntSolid)
        .setBlocksVision(isntSolid));
}

static auto createBed(const std::string& name, DyeColors color) -> Block* {
    return create<BedBlock>(name, color, BlockBehaviourUtil::create(Materials::WOOL,
        [](const BlockData &data) -> MaterialColor {
            return MaterialColors::WOOL;// data.get(BedBlock::PART) == BedPart::FOOT ? color.getMapColor() : MaterialColors::WOOL;
        }).setSound(SoundType::WOOD)
        .setRenderType(RenderType::Cutout)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(0.2F)
        .notSolid());
}

static auto createStainedGlass(const std::string& name, DyeColors color) -> Block* {
    return create<StainedGlassBlock>(name, color, BlockBehaviourUtil::create(Materials::GLASS, color)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn)
        .setOpaque(isntSolid)
        .setSuffocates(isntSolid)
        .setBlocksVision(isntSolid));
}

static auto createShulkerBox(const std::string& name, tl::optional<DyeColors> color, BlockBehaviour behaviour) -> Block* {
    static constexpr auto isBlocksVision = [](BlockReader &reader, const BlockData &data, const BlockPos &pos) -> bool {
//        TileEntity tileentity = p_235444_1_.getTileEntity(p_235444_2_);
//        if (!(tileentity instanceof ShulkerBoxTileEntity)) {
//            return true;
//        } else {
//            ShulkerBoxTileEntity shulkerboxtileentity = (ShulkerBoxTileEntity)tileentity;
//            return shulkerboxtileentity.func_235676_l_();
//        }
        return true;
    };
    return create<ShulkerBoxBlock>(name, color, std::move(behaviour)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(2.0F)
        .setVariableOpacity()
        .notSolid()
        .setSuffocates(isBlocksVision)
        .setBlocksVision(isBlocksVision));
}

static auto createRotatableNetherBlock(const std::string& name, MaterialColor color) -> Block* {
    return create<RotatedPillarBlock>(name, BlockBehaviourUtil::create(Materials::NETHER_WOOD, getMaterialColor(color))
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
}

static auto createBanner(const std::string& name, DyeColors color) -> Block* {
    return create<BannerBlock>(name, color, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD));
}

void Blocks::init() {
    using namespace std::string_literals;

    AIR = create<AirBlock>("air", BlockBehaviourUtil::create(Materials::AIR)
        .setRenderShape(BlockRenderShape::INVISIBLE)
        .doesNotBlockMovement()
        .noDrops()
        .setAir());
    STONE = create<Block>("stone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    GRANITE = create<Block>("granite", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::DIRT)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_GRANITE = create<Block>("polished_granite", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::DIRT)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DIORITE = create<Block>("diorite", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_DIORITE = create<Block>("polished_diorite", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    ANDESITE = create<Block>("andesite", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_ANDESITE = create<Block>("polished_andesite", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    GRASS_BLOCK = create<GrassBlock>("grass_block", BlockBehaviourUtil::create(Materials::ORGANIC)
        .setTintType(TintType::Grass)
        .setTickRandomly()
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    DIRT = create<Block>("dirt", BlockBehaviourUtil::create(Materials::EARTH, MaterialColors::DIRT)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GROUND));
    COARSE_DIRT = create<Block>("coarse_dirt", BlockBehaviourUtil::create(Materials::EARTH, MaterialColors::DIRT)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GROUND));
    PODZOL = create<SnowyDirtBlock>("podzol", BlockBehaviourUtil::create(Materials::EARTH, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GROUND));
    COBBLESTONE = create<Block>("cobblestone", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    OAK_PLANKS = create<Block>("oak_planks", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_PLANKS = create<Block>("spruce_planks", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_PLANKS = create<Block>("birch_planks", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_PLANKS = create<Block>("jungle_planks", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_PLANKS = create<Block>("acacia_planks", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::ADOBE)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_PLANKS = create<Block>("dark_oak_planks", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    OAK_SAPLING = create<SaplingBlock>("oak_sapling", new OakTree(), BlockBehaviourUtil::create(Materials::PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    SPRUCE_SAPLING = create<SaplingBlock>("spruce_sapling", new SpruceTree(), BlockBehaviourUtil::create(Materials::PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BIRCH_SAPLING = create<SaplingBlock>("birch_sapling", new BirchTree(), BlockBehaviourUtil::create(Materials::PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    JUNGLE_SAPLING = create<SaplingBlock>("jungle_sapling", new JungleTree(), BlockBehaviourUtil::create(Materials::PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ACACIA_SAPLING = create<SaplingBlock>("acacia_sapling", new AcaciaTree(), BlockBehaviourUtil::create(Materials::PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    DARK_OAK_SAPLING = create<SaplingBlock>("dark_oak_sapling", new DarkOakTree(), BlockBehaviourUtil::create(Materials::PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BEDROCK = create<Block>("bedrock", BlockBehaviourUtil::create(Materials::ROCK)
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops()
        .setAllowsSpawn(neverAllowSpawn));
    WATER = create<FlowingFluidBlock>("water", Fluids::WATER, BlockBehaviourUtil::create(Materials::WATER)
        .setRenderType(RenderType::Transparent)
        .doesNotBlockMovement()
        .setHardnessAndResistance(100.0F)
        .noDrops());
    LAVA = create<FlowingFluidBlock>("lava", Fluids::LAVA, BlockBehaviourUtil::create(Materials::LAVA)
        .setRenderType(RenderType::Transparent)
        .doesNotBlockMovement()
        .setTickRandomly()
        .setHardnessAndResistance(100.0F)
        .setLightLevel([](auto) -> int32_t { return 15; })
        .noDrops());
    SAND = create<SandBlock>("sand", 14406560, BlockBehaviourUtil::create(Materials::SAND, MaterialColors::SAND)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    RED_SAND = create<SandBlock>("red_sand", 11098145, BlockBehaviourUtil::create(Materials::SAND, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    GRAVEL = create<GravelBlock>("gravel", BlockBehaviourUtil::create(Materials::SAND, MaterialColors::STONE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::GROUND));
    GOLD_ORE = create<OreBlock>("gold_ore", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    IRON_ORE = create<OreBlock>("iron_ore", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    COAL_ORE = create<OreBlock>("coal_ore", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    NETHER_GOLD_ORE = create<OreBlock>("nether_gold_ore", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F)
        .setSound(SoundType::NETHER_GOLD));
    OAK_LOG = createLogBlock("oak_log", MaterialColors::WOOD, MaterialColors::OBSIDIAN);
    SPRUCE_LOG = createLogBlock("spruce_log", MaterialColors::OBSIDIAN, MaterialColors::BROWN);
    BIRCH_LOG = createLogBlock("birch_log", MaterialColors::SAND, MaterialColors::QUARTZ);
    JUNGLE_LOG = createLogBlock("jungle_log", MaterialColors::DIRT, MaterialColors::OBSIDIAN);
    ACACIA_LOG = createLogBlock("acacia_log", MaterialColors::ADOBE, MaterialColors::STONE);
    DARK_OAK_LOG = createLogBlock("dark_oak_log", MaterialColors::BROWN, MaterialColors::BROWN);
    STRIPPED_SPRUCE_LOG = createLogBlock("stripped_spruce_log", MaterialColors::OBSIDIAN, MaterialColors::OBSIDIAN);
    STRIPPED_BIRCH_LOG = createLogBlock("stripped_birch_log", MaterialColors::SAND, MaterialColors::SAND);
    STRIPPED_JUNGLE_LOG = createLogBlock("stripped_jungle_log", MaterialColors::DIRT, MaterialColors::DIRT);
    STRIPPED_ACACIA_LOG = createLogBlock("stripped_acacia_log", MaterialColors::ADOBE, MaterialColors::ADOBE);
    STRIPPED_DARK_OAK_LOG = createLogBlock("stripped_dark_oak_log", MaterialColors::BROWN, MaterialColors::BROWN);
    STRIPPED_OAK_LOG = createLogBlock("stripped_oak_log", MaterialColors::WOOD, MaterialColors::WOOD);
    OAK_WOOD = create<RotatedPillarBlock>("oak_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_WOOD = create<RotatedPillarBlock>("spruce_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    BIRCH_WOOD = create<RotatedPillarBlock>("birch_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_WOOD = create<RotatedPillarBlock>("jungle_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    ACACIA_WOOD = create<RotatedPillarBlock>("acacia_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::GRAY)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_WOOD = create<RotatedPillarBlock>("dark_oak_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_OAK_WOOD = create<RotatedPillarBlock>("stripped_oak_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_SPRUCE_WOOD = create<RotatedPillarBlock>("stripped_spruce_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_BIRCH_WOOD = create<RotatedPillarBlock>("stripped_birch_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_JUNGLE_WOOD = create<RotatedPillarBlock>("stripped_jungle_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_ACACIA_WOOD = create<RotatedPillarBlock>("stripped_acacia_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::ADOBE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_DARK_OAK_WOOD = create<RotatedPillarBlock>("stripped_dark_oak_wood", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    OAK_LEAVES = createLeavesBlock("oak_leaves");
    SPRUCE_LEAVES = createLeavesBlock("spruce_leaves");
    BIRCH_LEAVES = createLeavesBlock("birch_leaves");
    JUNGLE_LEAVES = createLeavesBlock("jungle_leaves");
    ACACIA_LEAVES = createLeavesBlock("acacia_leaves");
    DARK_OAK_LEAVES = createLeavesBlock("dark_oak_leaves");
    SPONGE = create<SpongeBlock>("sponge", BlockBehaviourUtil::create(Materials::SPONGE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    WET_SPONGE = create<WetSpongeBlock>("wet_sponge", BlockBehaviourUtil::create(Materials::SPONGE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    GLASS = create<GlassBlock>("glass", BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn)
        .setOpaque(isntSolid)
        .setSuffocates(isntSolid)
        .setBlocksVision(isntSolid));
    LAPIS_ORE = create<OreBlock>("lapis_ore", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    LAPIS_BLOCK = create<Block>("lapis_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::LAPIS)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    DISPENSER = create<DispenserBlock>("dispenser", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F));
    SANDSTONE = create<Block>("sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CHISELED_SANDSTONE = create<Block>("chiseled_sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CUT_SANDSTONE = create<Block>("cut_sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    NOTE_BLOCK = create<NoteBlock>("note_block", BlockBehaviourUtil::create(Materials::WOOD)
        .setSound(SoundType::WOOD)
        .setHardnessAndResistance(0.8F));
    WHITE_BED = createBed("white_bed", DyeColors::WHITE);
    ORANGE_BED = createBed("orange_bed", DyeColors::ORANGE);
    MAGENTA_BED = createBed("magenta_bed", DyeColors::MAGENTA);
    LIGHT_BLUE_BED = createBed("light_blue_bed", DyeColors::LIGHT_BLUE);
    YELLOW_BED = createBed("yellow_bed", DyeColors::YELLOW);
    LIME_BED = createBed("lime_bed", DyeColors::LIME);
    PINK_BED = createBed("pink_bed", DyeColors::PINK);
    GRAY_BED = createBed("gray_bed", DyeColors::GRAY);
    LIGHT_GRAY_BED = createBed("light_gray_bed", DyeColors::LIGHT_GRAY);
    CYAN_BED = createBed("cyan_bed", DyeColors::CYAN);
    PURPLE_BED = createBed("purple_bed", DyeColors::PURPLE);
    BLUE_BED = createBed("blue_bed", DyeColors::BLUE);
    BROWN_BED = createBed("brown_bed", DyeColors::BROWN);
    GREEN_BED = createBed("green_bed", DyeColors::GREEN);
    RED_BED = createBed("red_bed", DyeColors::RED);
    BLACK_BED = createBed("black_bed", DyeColors::BLACK);
    POWERED_RAIL = create<PoweredRailBlock>("powered_rail", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    DETECTOR_RAIL = create<DetectorRailBlock>("detector_rail", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    STICKY_PISTON = createPiston("sticky_piston", true);
    COBWEB = create<WebBlock>("cobweb", BlockBehaviourUtil::create(Materials::WEB)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setRequiresTool()
        .setHardnessAndResistance(4.0F));
    GRASS = create<TallGrassBlock>("grass", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    FERN = create<TallGrassBlock>("fern", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    DEAD_BUSH = create<DeadBushBlock>("dead_bush", BlockBehaviourUtil::create(Materials::TALL_PLANTS, MaterialColors::WOOD)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    SEAGRASS = create<SeaGrassBlock>("seagrass", BlockBehaviourUtil::create(Materials::SEA_GRASS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    TALL_SEAGRASS = create<TallSeaGrassBlock>("tall_seagrass", BlockBehaviourUtil::create(Materials::SEA_GRASS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    PISTON = createPiston("piston", false);
    PISTON_HEAD = create<PistonHeadBlock>("piston_head", BlockBehaviourUtil::create(Materials::PISTON)
        .setHardnessAndResistance(1.5F)
        .noDrops());
    WHITE_WOOL = create<Block>("white_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::SNOW)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    ORANGE_WOOL = create<Block>("orange_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    MAGENTA_WOOL = create<Block>("magenta_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::MAGENTA)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    LIGHT_BLUE_WOOL = create<Block>("light_blue_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::LIGHT_BLUE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    YELLOW_WOOL = create<Block>("yellow_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    LIME_WOOL = create<Block>("lime_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::LIME)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    PINK_WOOL = create<Block>("pink_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::PINK)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    GRAY_WOOL = create<Block>("gray_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::GRAY)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    LIGHT_GRAY_WOOL = create<Block>("light_gray_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::LIGHT_GRAY)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    CYAN_WOOL = create<Block>("cyan_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::CYAN)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    PURPLE_WOOL = create<Block>("purple_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::PURPLE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    BLUE_WOOL = create<Block>("blue_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::BLUE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    BROWN_WOOL = create<Block>("brown_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::BROWN)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    GREEN_WOOL = create<Block>("green_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::GREEN)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    RED_WOOL = create<Block>("red_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::RED)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    BLACK_WOOL = create<Block>("black_wool", BlockBehaviourUtil::create(Materials::WOOL, MaterialColors::BLACK)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    MOVING_PISTON = create<MovingPistonBlock>("moving_piston", BlockBehaviourUtil::create(Materials::PISTON)
        .setHardnessAndResistance(-1.0F)
        .setVariableOpacity()
        .noDrops()
        .notSolid()
        .setOpaque(isntSolid)
        .setSuffocates(isntSolid)
        .setBlocksVision(isntSolid));
    DANDELION = create<FlowerBlock>("dandelion", Effects::SATURATION, 7, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    POPPY = create<FlowerBlock>("poppy", Effects::NIGHT_VISION, 5, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BLUE_ORCHID = create<FlowerBlock>("blue_orchid", Effects::SATURATION, 7, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ALLIUM = create<FlowerBlock>("allium", Effects::FIRE_RESISTANCE, 4, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    AZURE_BLUET = create<FlowerBlock>("azure_bluet", Effects::BLINDNESS, 8, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    RED_TULIP = create<FlowerBlock>("red_tulip", Effects::WEAKNESS, 9, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ORANGE_TULIP = create<FlowerBlock>("orange_tulip", Effects::WEAKNESS, 9, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    WHITE_TULIP = create<FlowerBlock>("white_tulip", Effects::WEAKNESS, 9, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    PINK_TULIP = create<FlowerBlock>("pink_tulip", Effects::WEAKNESS, 9, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    OXEYE_DAISY = create<FlowerBlock>("oxeye_daisy", Effects::REGENERATION, 8, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    CORNFLOWER = create<FlowerBlock>("cornflower", Effects::JUMP_BOOST, 6, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    WITHER_ROSE = create<WitherRoseBlock>("wither_rose", Effects::WITHER, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    LILY_OF_THE_VALLEY = create<FlowerBlock>("lily_of_the_valley", Effects::POISON, 12, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BROWN_MUSHROOM = create<MushroomBlock>("brown_mushroom", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::BROWN)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT)
        .setLightLevel([](auto) -> int32_t { return 1; })
        .setNeedsPostProcessing(needsPostProcessing));
    RED_MUSHROOM = create<MushroomBlock>("red_mushroom", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::RED)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT)
        .setNeedsPostProcessing(needsPostProcessing));
    GOLD_BLOCK = create<Block>("gold_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::GOLD)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 6.0F)
        .setSound(SoundType::METAL));
    IRON_BLOCK = create<Block>("iron_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL));
    BRICKS = create<Block>("bricks", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    TNT = create<TNTBlock>("tnt", BlockBehaviourUtil::create(Materials::TNT)
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BOOKSHELF = create<Block>("bookshelf", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(1.5F)
        .setSound(SoundType::WOOD));
    MOSSY_COBBLESTONE = create<Block>("mossy_cobblestone", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    OBSIDIAN = create<Block>("obsidian", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F));
    TORCH = create<TorchBlock>("torch", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel([](auto) -> int32_t { return 14; })
        .setSound(SoundType::WOOD), ParticleType::FLAME);
    WALL_TORCH = create<WallTorchBlock>("wall_torch", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel([](auto) -> int32_t { return 14; })
        .setSound(SoundType::WOOD)
        .setLootFrom(TORCH), ParticleType::FLAME);
    FIRE = create<FireBlock>("fire", BlockBehaviourUtil::create(Materials::FIRE, MaterialColors::TNT)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel([](auto) -> int32_t { return 15; })
        .setSound(SoundType::CLOTH));
    SOUL_FIRE = create<SoulFireBlock>("soul_fire", BlockBehaviourUtil::create(Materials::FIRE, MaterialColors::LIGHT_BLUE)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel([](auto) -> int32_t { return 10; })
        .setSound(SoundType::CLOTH));
    SPAWNER = create<SpawnerBlock>("spawner", BlockBehaviourUtil::create(Materials::ROCK)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::METAL)
        .notSolid());
    OAK_STAIRS = create<StairsBlock>("oak_stairs", OAK_PLANKS->getDefaultState(), BlockBehaviourUtil::from(OAK_PLANKS));
    CHEST = create<ChestBlock>("chest", BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD) /*,
        []() -> {
        return TileEntityType::CHEST;
        }*/
    );
    REDSTONE_WIRE = create<RedstoneWireBlock>("redstone_wire", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DIAMOND_ORE = create<OreBlock>("diamond_ore", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    DIAMOND_BLOCK = create<Block>("diamond_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL));
    CRAFTING_TABLE = create<CraftingTableBlock>("crafting_table", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    WHEAT = create<CropsBlock>("wheat", BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    FARMLAND = create<FarmlandBlock>("farmland", BlockBehaviourUtil::create(Materials::EARTH)
        .setTickRandomly()
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::GROUND)
        .setBlocksVision(needsPostProcessing)
        .setSuffocates(needsPostProcessing));
    FURNACE = create<FurnaceBlock>("furnace", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setLightLevel(getLightLevelLit<13>()));
    OAK_SIGN = create<StandingSignBlock>("oak_sign", BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::OAK);
    SPRUCE_SIGN = create<StandingSignBlock>("spruce_sign", BlockBehaviourUtil::create(Materials::WOOD, SPRUCE_LOG->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::SPRUCE);
    BIRCH_SIGN = create<StandingSignBlock>("birch_sign", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::SAND)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::BIRCH);
    ACACIA_SIGN = create<StandingSignBlock>("acacia_sign", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::ADOBE)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::ACACIA);
    JUNGLE_SIGN = create<StandingSignBlock>("jungle_sign", BlockBehaviourUtil::create(Materials::WOOD, JUNGLE_LOG->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::JUNGLE);
    DARK_OAK_SIGN = create<StandingSignBlock>("dark_oak_sign", BlockBehaviourUtil::create(Materials::WOOD, DARK_OAK_LOG->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::DARK_OAK);
    OAK_DOOR = create<DoorBlock>("oak_door", BlockBehaviourUtil::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    LADDER = create<LadderBlock>("ladder", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::LADDER)
        .notSolid());
    RAIL = create<RailBlock>("rail", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    COBBLESTONE_STAIRS = create<StairsBlock>("cobblestone_stairs", COBBLESTONE->getDefaultState(), BlockBehaviourUtil::from(COBBLESTONE));
    OAK_WALL_SIGN = create<WallSignBlock>("oak_wall_sign", BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(OAK_SIGN), WoodType::OAK);
    SPRUCE_WALL_SIGN = create<WallSignBlock>("spruce_wall_sign", BlockBehaviourUtil::create(Materials::WOOD, SPRUCE_LOG->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(SPRUCE_SIGN), WoodType::SPRUCE);
    BIRCH_WALL_SIGN = create<WallSignBlock>("birch_wall_sign", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::SAND)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BIRCH_SIGN), WoodType::BIRCH);
    ACACIA_WALL_SIGN = create<WallSignBlock>("acacia_wall_sign", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::ADOBE)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(ACACIA_SIGN), WoodType::ACACIA);
    JUNGLE_WALL_SIGN = create<WallSignBlock>("jungle_wall_sign", BlockBehaviourUtil::create(Materials::WOOD, JUNGLE_LOG->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(JUNGLE_SIGN), WoodType::JUNGLE);
    DARK_OAK_WALL_SIGN = create<WallSignBlock>("dark_oak_wall_sign", BlockBehaviourUtil::create(Materials::WOOD, DARK_OAK_LOG->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(DARK_OAK_SIGN), WoodType::DARK_OAK);
    LEVER = create<LeverBlock>("lever", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    STONE_PRESSURE_PLATE = create<PressurePlateBlock>("stone_pressure_plate", PressurePlateBlock::Sensitivity::MOBS, BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    IRON_DOOR = create<DoorBlock>("iron_door", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::IRON)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::METAL)
        .notSolid());
    OAK_PRESSURE_PLATE = create<PressurePlateBlock>("oak_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    SPRUCE_PRESSURE_PLATE = create<PressurePlateBlock>("spruce_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    BIRCH_PRESSURE_PLATE = create<PressurePlateBlock>("birch_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    JUNGLE_PRESSURE_PLATE = create<PressurePlateBlock>("jungle_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    ACACIA_PRESSURE_PLATE = create<PressurePlateBlock>("acacia_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    DARK_OAK_PRESSURE_PLATE = create<PressurePlateBlock>("dark_oak_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    REDSTONE_ORE = create<RedstoneOreBlock>("redstone_ore", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setTickRandomly()
        .setLightLevel(getLightLevelLit<9>())
        .setHardnessAndResistance(3.0F, 3.0F));
    REDSTONE_TORCH = create<RedstoneTorchBlock>("redstone_torch", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightLevelLit<7>())
        .setSound(SoundType::WOOD));
    REDSTONE_WALL_TORCH = create<RedstoneWallTorchBlock>("redstone_wall_torch", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightLevelLit<7>())
        .setSound(SoundType::WOOD)
        .setLootFrom(REDSTONE_TORCH));
    STONE_BUTTON = create<StoneButtonBlock>("stone_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    SNOW = create<SnowBlock>("snow", BlockBehaviourUtil::create(Materials::SNOW)
        .setTickRandomly()
        .setHardnessAndResistance(0.1F)
        .setRequiresTool()
        .setSound(SoundType::SNOW));
    ICE = create<IceBlock>("ice", BlockBehaviourUtil::create(Materials::ICE)
        .setRenderType(RenderType::Transparent)
        .setSlipperiness(0.98F)
        .setTickRandomly()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GLASS)
        .notSolid()
        .setAllowsSpawn([](BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) -> bool {
            return false;//p_235450_3_ == EntityType.POLAR_BEAR;
        }));
    SNOW_BLOCK = create<Block>("snow_block", BlockBehaviourUtil::create(Materials::SNOW_BLOCK)
        .setRequiresTool()
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::SNOW));
    CACTUS = create<CactusBlock>("cactus", BlockBehaviourUtil::create(Materials::CACTUS)
        .setRenderType(RenderType::Cutout)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::CLOTH));
    CLAY = create<Block>("clay", BlockBehaviourUtil::create(Materials::CLAY)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::GROUND));
    SUGAR_CANE = create<SugarCaneBlock>("sugar_cane", BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    JUKEBOX = create<JukeboxBlock>("jukebox", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F, 6.0F));
    OAK_FENCE = create<FenceBlock>("oak_fence", BlockBehaviourUtil::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    PUMPKIN = create<PumpkinBlock>("pumpkin", BlockBehaviourUtil::create(Materials::GOURD, MaterialColors::ADOBE)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD));
    NETHERRACK = create<NetherrackBlock>("netherrack", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::NETHERRACK));
    SOUL_SAND = create<SoulSandBlock>("soul_sand", BlockBehaviourUtil::create(Materials::SAND, MaterialColors::BROWN)
        .setHardnessAndResistance(0.5F)
        .setSpeedFactor(0.4F)
        .setSound(SoundType::SOUL_SAND)
        .setAllowsSpawn(alwaysAllowSpawn)
        .setOpaque(needsPostProcessing)
        .setBlocksVision(needsPostProcessing)
        .setSuffocates(needsPostProcessing));
    SOUL_SOIL = create<Block>("soul_soil", BlockBehaviourUtil::create(Materials::EARTH, MaterialColors::BROWN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SOUL_SOIL));
    BASALT = create<RotatedPillarBlock>("basalt", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F)
        .setSound(SoundType::BASALT));
    POLISHED_BASALT = create<RotatedPillarBlock>("polished_basalt", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F)
        .setSound(SoundType::BASALT));
    SOUL_TORCH = create<TorchBlock>("soul_torch", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel([](auto) -> int32_t { return 10; })
        .setSound(SoundType::WOOD), ParticleType::SOUL_FIRE_FLAME);
    SOUL_WALL_TORCH = create<WallTorchBlock>("soul_wall_torch", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel([](auto) -> int32_t { return 10; })
        .setSound(SoundType::WOOD)
        .setLootFrom(SOUL_TORCH), ParticleType::SOUL_FIRE_FLAME);
    GLOWSTONE = create<Block>("glowstone", BlockBehaviourUtil::create(Materials::GLASS, MaterialColors::SAND)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .setLightLevel([](auto) -> int32_t { return 15; }));
    NETHER_PORTAL = create<NetherPortalBlock>("nether_portal", BlockBehaviourUtil::create(Materials::PORTAL)
        .setRenderType(RenderType::Transparent)
        .doesNotBlockMovement()
        .setTickRandomly()
        .setHardnessAndResistance(-1.0F)
        .setSound(SoundType::GLASS)
        .setLightLevel([](auto) -> int32_t { return 11; }));
    CARVED_PUMPKIN = create<CarvedPumpkinBlock>("carved_pumpkin", BlockBehaviourUtil::create(Materials::GOURD, MaterialColors::ADOBE)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setAllowsSpawn(alwaysAllowSpawn));
    JACK_O_LANTERN = create<CarvedPumpkinBlock>("jack_o_lantern", BlockBehaviourUtil::create(Materials::GOURD, MaterialColors::ADOBE)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLightLevel([](auto) -> int32_t { return 15; })
        .setAllowsSpawn(alwaysAllowSpawn));
    CAKE = create<CakeBlock>("cake", BlockBehaviourUtil::create(Materials::CAKE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::CLOTH));
    REPEATER = create<RepeaterBlock>("repeater", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .setSound(SoundType::WOOD));
    WHITE_STAINED_GLASS = createStainedGlass("white_stained_glass", DyeColors::WHITE);
    ORANGE_STAINED_GLASS = createStainedGlass("orange_stained_glass", DyeColors::ORANGE);
    MAGENTA_STAINED_GLASS = createStainedGlass("magenta_stained_glass", DyeColors::MAGENTA);
    LIGHT_BLUE_STAINED_GLASS = createStainedGlass("light_blue_stained_glass", DyeColors::LIGHT_BLUE);
    YELLOW_STAINED_GLASS = createStainedGlass("yellow_stained_glass", DyeColors::YELLOW);
    LIME_STAINED_GLASS = createStainedGlass("lime_stained_glass", DyeColors::LIME);
    PINK_STAINED_GLASS = createStainedGlass("pink_stained_glass", DyeColors::PINK);
    GRAY_STAINED_GLASS = createStainedGlass("gray_stained_glass", DyeColors::GRAY);
    LIGHT_GRAY_STAINED_GLASS = createStainedGlass("light_gray_stained_glass", DyeColors::LIGHT_GRAY);
    CYAN_STAINED_GLASS = createStainedGlass("cyan_stained_glass", DyeColors::CYAN);
    PURPLE_STAINED_GLASS = createStainedGlass("purple_stained_glass", DyeColors::PURPLE);
    BLUE_STAINED_GLASS = createStainedGlass("blue_stained_glass", DyeColors::BLUE);
    BROWN_STAINED_GLASS = createStainedGlass("brown_stained_glass", DyeColors::BROWN);
    GREEN_STAINED_GLASS = createStainedGlass("green_stained_glass", DyeColors::GREEN);
    RED_STAINED_GLASS = createStainedGlass("red_stained_glass", DyeColors::RED);
    BLACK_STAINED_GLASS = createStainedGlass("black_stained_glass", DyeColors::BLACK);
    OAK_TRAPDOOR = create<TrapDoorBlock>("oak_trapdoor", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::WOOD)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    SPRUCE_TRAPDOOR = create<TrapDoorBlock>("spruce_trapdoor", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    BIRCH_TRAPDOOR = create<TrapDoorBlock>("birch_trapdoor", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::SAND)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    JUNGLE_TRAPDOOR = create<TrapDoorBlock>("jungle_trapdoor", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::DIRT)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    ACACIA_TRAPDOOR = create<TrapDoorBlock>("acacia_trapdoor", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::ADOBE)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    DARK_OAK_TRAPDOOR = create<TrapDoorBlock>("dark_oak_trapdoor", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::BROWN)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    STONE_BRICKS = create<Block>("stone_bricks", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    MOSSY_STONE_BRICKS = create<Block>("mossy_stone_bricks", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    CRACKED_STONE_BRICKS = create<Block>("cracked_stone_bricks", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    CHISELED_STONE_BRICKS = create<Block>("chiseled_stone_bricks", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    INFESTED_STONE = create<SilverfishBlock>("infested_stone", STONE, BlockBehaviourUtil::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_COBBLESTONE = create<SilverfishBlock>("infested_cobblestone", COBBLESTONE, BlockBehaviourUtil::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_STONE_BRICKS = create<SilverfishBlock>("infested_stone_bricks", STONE_BRICKS, BlockBehaviourUtil::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_MOSSY_STONE_BRICKS = create<SilverfishBlock>("infested_mossy_stone_bricks", MOSSY_STONE_BRICKS, BlockBehaviourUtil::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_CRACKED_STONE_BRICKS = create<SilverfishBlock>("infested_cracked_stone_bricks", CRACKED_STONE_BRICKS, BlockBehaviourUtil::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_CHISELED_STONE_BRICKS = create<SilverfishBlock>("infested_chiseled_stone_bricks", CHISELED_STONE_BRICKS, BlockBehaviourUtil::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    BROWN_MUSHROOM_BLOCK = create<HugeMushroomBlock>("brown_mushroom_block", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));

    RED_MUSHROOM_BLOCK = create<HugeMushroomBlock>("red_mushroom_block", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::RED)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));
    MUSHROOM_STEM = create<HugeMushroomBlock>("mushroom_stem", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::WOOL)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));
    IRON_BARS = create<PaneBlock>("iron_bars", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::AIR)

        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL)
        .notSolid());
    CHAIN = create<ChainBlock>("chain", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::AIR)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::CHAIN)
        .notSolid());
    GLASS_PANE = create<PaneBlock>("glass_pane", BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    MELON = create<MelonBlock>("melon", BlockBehaviourUtil::create(Materials::GOURD, MaterialColors::LIME)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD));
    ATTACHED_PUMPKIN_STEM = create<AttachedStemBlock>("attached_pumpkin_stem", (StemGrownBlock*)PUMPKIN, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout).doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WOOD));
    ATTACHED_MELON_STEM = create<AttachedStemBlock>("attached_melon_stem", (StemGrownBlock*)MELON, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WOOD));
    PUMPKIN_STEM = create<StemBlock>("pumpkin_stem", (StemGrownBlock*)PUMPKIN, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::STEM));
    MELON_STEM = create<StemBlock>("melon_stem", (StemGrownBlock*)MELON, BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::STEM));
    VINE = create<VineBlock>("vine", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .doesNotBlockMovement()
        .setTickRandomly()
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::VINE));
    OAK_FENCE_GATE = create<FenceGateBlock>("oak_fence_gate", BlockBehaviourUtil::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BRICK_STAIRS = create<StairsBlock>("brick_stairs", BRICKS->getDefaultState(), BlockBehaviourUtil::from(BRICKS));
    STONE_BRICK_STAIRS = create<StairsBlock>("stone_brick_stairs", STONE_BRICKS->getDefaultState(), BlockBehaviourUtil::from(STONE_BRICKS));
    MYCELIUM = create<MyceliumBlock>("mycelium", BlockBehaviourUtil::create(Materials::ORGANIC, MaterialColors::PURPLE)
        .setTickRandomly()
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    LILY_PAD = create<LilyPadBlock>("lily_pad", BlockBehaviourUtil::create(Materials::PLANTS)
        .setTintType(TintType::Grass)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .setSound(SoundType::LILY_PADS)
        .notSolid());
    NETHER_BRICKS = create<Block>("nether_bricks", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    NETHER_BRICK_FENCE = create<FenceBlock>("nether_brick_fence", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    NETHER_BRICK_STAIRS = create<StairsBlock>("nether_brick_stairs", NETHER_BRICKS->getDefaultState(), BlockBehaviourUtil::from(NETHER_BRICKS));
    NETHER_WART = create<NetherWartBlock>("nether_wart", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::RED)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .setSound(SoundType::NETHER_WART));
    ENCHANTING_TABLE = create<EnchantingTableBlock>("enchanting_table", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F));
    BREWING_STAND = create<BrewingStandBlock>("brewing_stand", BlockBehaviourUtil::create(Materials::IRON)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .setHardnessAndResistance(0.5F)
        .setLightLevel([](auto) -> int32_t { return 1; })
        .notSolid());
    CAULDRON = create<CauldronBlock>("cauldron", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F)
        .notSolid());
    END_PORTAL = create<EndPortalBlock>("end_portal", BlockBehaviourUtil::create(Materials::PORTAL, MaterialColors::BLACK)
        .doesNotBlockMovement()
        .setLightLevel([](auto) -> int32_t { return 15; })
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    END_PORTAL_FRAME = create<EndPortalFrameBlock>("end_portal_frame", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GREEN)
        .setSound(SoundType::GLASS)
        .setLightLevel([](auto) -> int32_t { return 1; })
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    END_STONE = create<Block>("end_stone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 9.0F));
    DRAGON_EGG = create<DragonEggBlock>("dragon_egg", BlockBehaviourUtil::create(Materials::DRAGON_EGG, MaterialColors::BLACK)
        .setHardnessAndResistance(3.0F, 9.0F)
        .setLightLevel([](auto) -> int32_t { return 1; })
        .notSolid());
    REDSTONE_LAMP = create<RedstoneLampBlock>("redstone_lamp", BlockBehaviourUtil::create(Materials::REDSTONE_LIGHT)
        .setLightLevel(getLightLevelLit<15>())
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .setAllowsSpawn(alwaysAllowSpawn));
    COCOA = create<CocoaBlock>("cocoa", BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .setHardnessAndResistance(0.2F, 3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    SANDSTONE_STAIRS = create<StairsBlock>("sandstone_stairs", SANDSTONE->getDefaultState(), BlockBehaviourUtil::from(SANDSTONE));
    EMERALD_ORE = create<OreBlock>("emerald_ore", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    ENDER_CHEST = create<EnderChestBlock>("ender_chest", BlockBehaviourUtil::create(Materials::ROCK)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setRequiresTool()
        .setHardnessAndResistance(22.5F, 600.0F)
        .setLightLevel([](auto) -> int32_t { return 7; }));
    TRIPWIRE_HOOK = create<TripWireHookBlock>("tripwire_hook", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement());
    TRIPWIRE = create<TripWireBlock>("tripwire", (TripWireHookBlock *) TRIPWIRE_HOOK, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement());
    EMERALD_BLOCK = create<Block>("emerald_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::EMERALD)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL));
    SPRUCE_STAIRS = create<StairsBlock>("spruce_stairs", SPRUCE_PLANKS->getDefaultState(), BlockBehaviourUtil::from(SPRUCE_PLANKS));
    BIRCH_STAIRS = create<StairsBlock>("birch_stairs", BIRCH_PLANKS->getDefaultState(), BlockBehaviourUtil::from(BIRCH_PLANKS));
    JUNGLE_STAIRS = create<StairsBlock>("jungle_stairs", JUNGLE_PLANKS->getDefaultState(), BlockBehaviourUtil::from(JUNGLE_PLANKS));
    COMMAND_BLOCK = create<CommandBlockBlock>("command_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::BROWN)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    BEACON = create<BeaconBlock>("beacon", BlockBehaviourUtil::create(Materials::GLASS, MaterialColors::DIAMOND)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setLightLevel([](auto) -> int32_t { return 15; })
        .notSolid()
        .setOpaque(isntSolid));
    COBBLESTONE_WALL = create<WallBlock>("cobblestone_wall", BlockBehaviourUtil::from(COBBLESTONE));
    MOSSY_COBBLESTONE_WALL = create<WallBlock>("mossy_cobblestone_wall", BlockBehaviourUtil::from(COBBLESTONE));
    FLOWER_POT = create<FlowerPotBlock>("flower_pot", AIR, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_OAK_SAPLING = create<FlowerPotBlock>("potted_oak_sapling", OAK_SAPLING, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_SPRUCE_SAPLING = create<FlowerPotBlock>("potted_spruce_sapling", SPRUCE_SAPLING, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_BIRCH_SAPLING = create<FlowerPotBlock>("potted_birch_sapling", BIRCH_SAPLING, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_JUNGLE_SAPLING = create<FlowerPotBlock>("potted_jungle_sapling", JUNGLE_SAPLING, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_ACACIA_SAPLING = create<FlowerPotBlock>("potted_acacia_sapling", ACACIA_SAPLING, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_DARK_OAK_SAPLING = create<FlowerPotBlock>("potted_dark_oak_sapling", DARK_OAK_SAPLING, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_FERN = create<FlowerPotBlock>("potted_fern", FERN, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_DANDELION = create<FlowerPotBlock>("potted_dandelion", DANDELION, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_POPPY = create<FlowerPotBlock>("potted_poppy", POPPY, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_BLUE_ORCHID = create<FlowerPotBlock>("potted_blue_orchid", BLUE_ORCHID, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_ALLIUM = create<FlowerPotBlock>("potted_allium", ALLIUM, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_AZURE_BLUET = create<FlowerPotBlock>("potted_azure_bluet", AZURE_BLUET, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_RED_TULIP = create<FlowerPotBlock>("potted_red_tulip", RED_TULIP, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_ORANGE_TULIP = create<FlowerPotBlock>("potted_orange_tulip", ORANGE_TULIP, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WHITE_TULIP = create<FlowerPotBlock>("potted_white_tulip", WHITE_TULIP, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_PINK_TULIP = create<FlowerPotBlock>("potted_pink_tulip", PINK_TULIP, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_OXEYE_DAISY = create<FlowerPotBlock>("potted_oxeye_daisy", OXEYE_DAISY, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_CORNFLOWER = create<FlowerPotBlock>("potted_cornflower", CORNFLOWER, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_LILY_OF_THE_VALLEY = create<FlowerPotBlock>("potted_lily_of_the_valley", LILY_OF_THE_VALLEY, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WITHER_ROSE = create<FlowerPotBlock>("potted_wither_rose", WITHER_ROSE, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_RED_MUSHROOM = create<FlowerPotBlock>("potted_red_mushroom", RED_MUSHROOM, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_BROWN_MUSHROOM = create<FlowerPotBlock>("potted_brown_mushroom", BROWN_MUSHROOM, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_DEAD_BUSH = create<FlowerPotBlock>("potted_dead_bush", DEAD_BUSH, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_CACTUS = create<FlowerPotBlock>("potted_cactus", CACTUS, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    CARROTS = create<CarrotBlock>("carrots", BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    POTATOES = create<PotatoBlock>("potatoes", BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    OAK_BUTTON = create<WoodButtonBlock>("oak_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    SPRUCE_BUTTON = create<WoodButtonBlock>("spruce_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    BIRCH_BUTTON = create<WoodButtonBlock>("birch_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    JUNGLE_BUTTON = create<WoodButtonBlock>("jungle_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    ACACIA_BUTTON = create<WoodButtonBlock>("acacia_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    DARK_OAK_BUTTON = create<WoodButtonBlock>("dark_oak_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    SKELETON_SKULL = create<SkullBlock>("skeleton_skull", SkullBlock::Type::SKELETON, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F));
    SKELETON_WALL_SKULL = create<WallSkullBlock>("skeleton_wall_skull", SkullBlock::Type::SKELETON, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(SKELETON_SKULL));
    WITHER_SKELETON_SKULL = create<WitherSkeletonSkullBlock>("wither_skeleton_skull", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F));
    WITHER_SKELETON_WALL_SKULL = create<WitherSkeletonWallSkullBlock>("wither_skeleton_wall_skull", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(WITHER_SKELETON_SKULL));
    ZOMBIE_HEAD = create<SkullBlock>("zombie_head", SkullBlock::Type::ZOMBIE, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F));
    ZOMBIE_WALL_HEAD = create<WallSkullBlock>("zombie_wall_head", SkullBlock::Type::ZOMBIE, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(ZOMBIE_HEAD));
    PLAYER_HEAD = create<SkullPlayerBlock>("player_head", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F));
    PLAYER_WALL_HEAD = create<SkullWallPlayerBlock>("player_wall_head", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(PLAYER_HEAD));
    CREEPER_HEAD = create<SkullBlock>("creeper_head", SkullBlock::Type::CREEPER, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F));
    CREEPER_WALL_HEAD = create<WallSkullBlock>("creeper_wall_head", SkullBlock::Type::CREEPER, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(CREEPER_HEAD));
    DRAGON_HEAD = create<SkullBlock>("dragon_head", SkullBlock::Type::DRAGON, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F));
    DRAGON_WALL_HEAD = create<WallSkullBlock>("dragon_wall_head", SkullBlock::Type::DRAGON, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(DRAGON_HEAD));
    ANVIL = create<AnvilBlock>("anvil", BlockBehaviourUtil::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F)
        .setSound(SoundType::ANVIL));
    CHIPPED_ANVIL = create<AnvilBlock>("chipped_anvil", BlockBehaviourUtil::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F)
        .setSound(SoundType::ANVIL));
    DAMAGED_ANVIL = create<AnvilBlock>("damaged_anvil", BlockBehaviourUtil::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F)
        .setSound(SoundType::ANVIL));
    TRAPPED_CHEST = create<TrappedChestBlock>("trapped_chest", BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    LIGHT_WEIGHTED_PRESSURE_PLATE = create<WeightedPressurePlateBlock>("light_weighted_pressure_plate", 15, BlockBehaviourUtil::create(Materials::IRON, MaterialColors::GOLD)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    HEAVY_WEIGHTED_PRESSURE_PLATE = create<WeightedPressurePlateBlock>("heavy_weighted_pressure_plate", 150, BlockBehaviourUtil::create(Materials::IRON)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    COMPARATOR = create<ComparatorBlock>("comparator", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .setSound(SoundType::WOOD));
    DAYLIGHT_DETECTOR = create<DaylightDetectorBlock>("daylight_detector", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));
    REDSTONE_BLOCK = create<RedstoneBlock>("redstone_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::TNT)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL)
        .setOpaque(isntSolid));
    NETHER_QUARTZ_ORE = create<OreBlock>("nether_quartz_ore", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F)
        .setSound(SoundType::NETHER_ORE));
    HOPPER = create<HopperBlock>("hopper", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 4.8F)
        .setSound(SoundType::METAL)
        .notSolid());
    QUARTZ_BLOCK = create<Block>("quartz_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CHISELED_QUARTZ_BLOCK = create<Block>("chiseled_quartz_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    QUARTZ_PILLAR = create<RotatedPillarBlock>("quartz_pillar", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    QUARTZ_STAIRS = create<StairsBlock>("quartz_stairs", QUARTZ_BLOCK->getDefaultState(), BlockBehaviourUtil::from(QUARTZ_BLOCK));
    ACTIVATOR_RAIL = create<PoweredRailBlock>("activator_rail", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    DROPPER = create<DropperBlock>("dropper", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F));
    WHITE_TERRACOTTA = create<Block>("white_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::WHITE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    ORANGE_TERRACOTTA = create<Block>("orange_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ORANGE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    MAGENTA_TERRACOTTA = create<Block>("magenta_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::MAGENTA_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    LIGHT_BLUE_TERRACOTTA = create<Block>("light_blue_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::LIGHT_BLUE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    YELLOW_TERRACOTTA = create<Block>("yellow_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::YELLOW_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    LIME_TERRACOTTA = create<Block>("lime_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::LIME_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    PINK_TERRACOTTA = create<Block>("pink_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::PINK_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    GRAY_TERRACOTTA = create<Block>("gray_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    LIGHT_GRAY_TERRACOTTA = create<Block>("light_gray_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::LIGHT_GRAY_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    CYAN_TERRACOTTA = create<Block>("cyan_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::CYAN_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    PURPLE_TERRACOTTA = create<Block>("purple_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::PURPLE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    BLUE_TERRACOTTA = create<Block>("blue_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLUE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    BROWN_TERRACOTTA = create<Block>("brown_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BROWN_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    GREEN_TERRACOTTA = create<Block>("green_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GREEN_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    RED_TERRACOTTA = create<Block>("red_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::RED_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    BLACK_TERRACOTTA = create<Block>("black_terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    WHITE_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("white_stained_glass_pane", DyeColors::WHITE, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    ORANGE_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("orange_stained_glass_pane", DyeColors::ORANGE, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    MAGENTA_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("magenta_stained_glass_pane", DyeColors::MAGENTA, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    LIGHT_BLUE_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("light_blue_stained_glass_pane", DyeColors::LIGHT_BLUE, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    YELLOW_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("yellow_stained_glass_pane", DyeColors::YELLOW, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    LIME_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("lime_stained_glass_pane", DyeColors::LIME, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    PINK_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("pink_stained_glass_pane", DyeColors::PINK, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    GRAY_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("gray_stained_glass_pane", DyeColors::GRAY, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    LIGHT_GRAY_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("light_gray_stained_glass_pane", DyeColors::LIGHT_GRAY, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    CYAN_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("cyan_stained_glass_pane", DyeColors::CYAN, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    PURPLE_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("purple_stained_glass_pane", DyeColors::PURPLE, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    BLUE_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("blue_stained_glass_pane", DyeColors::BLUE, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    BROWN_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("brown_stained_glass_pane", DyeColors::BROWN, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    GREEN_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("green_stained_glass_pane", DyeColors::GREEN, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    RED_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("red_stained_glass_pane", DyeColors::RED, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    BLACK_STAINED_GLASS_PANE = create<StainedGlassPaneBlock>("black_stained_glass_pane", DyeColors::BLACK, BlockBehaviourUtil::create(Materials::GLASS)
        .setRenderType(RenderType::Transparent)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    ACACIA_STAIRS = create<StairsBlock>("acacia_stairs", ACACIA_PLANKS->getDefaultState(), BlockBehaviourUtil::from(ACACIA_PLANKS));
    DARK_OAK_STAIRS = create<StairsBlock>("dark_oak_stairs", DARK_OAK_PLANKS->getDefaultState(), BlockBehaviourUtil::from(DARK_OAK_PLANKS));
    SLIME_BLOCK = create<SlimeBlock>("slime_block", BlockBehaviourUtil::create(Materials::CLAY, MaterialColors::GRASS)
        .setRenderType(RenderType::Transparent)
        .setSlipperiness(0.8F)
        .setSound(SoundType::SLIME)
        .notSolid());
    BARRIER = create<BarrierBlock>("barrier", BlockBehaviourUtil::create(Materials::BARRIER)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(-1.0F, 3600000.8F)
        .noDrops()
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    IRON_TRAPDOOR = create<TrapDoorBlock>("iron_trapdoor", BlockBehaviourUtil::create(Materials::IRON)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::METAL)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    PRISMARINE = create<Block>("prismarine", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PRISMARINE_BRICKS = create<Block>("prismarine_bricks", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DARK_PRISMARINE = create<Block>("dark_prismarine", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PRISMARINE_STAIRS = create<StairsBlock>("prismarine_stairs", PRISMARINE->getDefaultState(), BlockBehaviourUtil::from(PRISMARINE));
    PRISMARINE_BRICK_STAIRS = create<StairsBlock>("prismarine_brick_stairs", PRISMARINE_BRICKS->getDefaultState(), BlockBehaviourUtil::from(PRISMARINE_BRICKS));
    DARK_PRISMARINE_STAIRS = create<StairsBlock>("dark_prismarine_stairs", DARK_PRISMARINE->getDefaultState(), BlockBehaviourUtil::from(DARK_PRISMARINE));
    PRISMARINE_SLAB = create<SlabBlock>("prismarine_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PRISMARINE_BRICK_SLAB = create<SlabBlock>("prismarine_brick_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DARK_PRISMARINE_SLAB = create<SlabBlock>("dark_prismarine_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    SEA_LANTERN = create<Block>("sea_lantern", BlockBehaviourUtil::create(Materials::GLASS, MaterialColors::QUARTZ)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .setLightLevel([](auto) -> int32_t { return 15; }));
    HAY_BLOCK = create<HayBlock>("hay_block", BlockBehaviourUtil::create(Materials::ORGANIC, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::PLANT));
    WHITE_CARPET = create<CarpetBlock>("white_carpet", DyeColors::WHITE, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::SNOW)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    ORANGE_CARPET = create<CarpetBlock>("orange_carpet", DyeColors::ORANGE, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    MAGENTA_CARPET = create<CarpetBlock>("magenta_carpet", DyeColors::MAGENTA, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::MAGENTA)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    LIGHT_BLUE_CARPET = create<CarpetBlock>("light_blue_carpet", DyeColors::LIGHT_BLUE, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::LIGHT_BLUE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    YELLOW_CARPET = create<CarpetBlock>("yellow_carpet", DyeColors::YELLOW, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    LIME_CARPET = create<CarpetBlock>("lime_carpet", DyeColors::LIME, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::LIME)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    PINK_CARPET = create<CarpetBlock>("pink_carpet", DyeColors::PINK, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::PINK)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    GRAY_CARPET = create<CarpetBlock>("gray_carpet", DyeColors::GRAY, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::GRAY)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    LIGHT_GRAY_CARPET = create<CarpetBlock>("light_gray_carpet", DyeColors::LIGHT_GRAY, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::LIGHT_GRAY)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    CYAN_CARPET = create<CarpetBlock>("cyan_carpet", DyeColors::CYAN, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::CYAN)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    PURPLE_CARPET = create<CarpetBlock>("purple_carpet", DyeColors::PURPLE, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::PURPLE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    BLUE_CARPET = create<CarpetBlock>("blue_carpet", DyeColors::BLUE, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::BLUE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    BROWN_CARPET = create<CarpetBlock>("brown_carpet", DyeColors::BROWN, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::BROWN)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    GREEN_CARPET = create<CarpetBlock>("green_carpet", DyeColors::GREEN, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::GREEN)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    RED_CARPET = create<CarpetBlock>("red_carpet", DyeColors::RED, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::RED)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    BLACK_CARPET = create<CarpetBlock>("black_carpet", DyeColors::BLACK, BlockBehaviourUtil::create(Materials::CARPET, MaterialColors::BLACK)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    TERRACOTTA = create<Block>("terracotta", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    COAL_BLOCK = create<Block>("coal_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F));
    PACKED_ICE = create<Block>("packed_ice", BlockBehaviourUtil::create(Materials::PACKED_ICE)
        .setSlipperiness(0.98F)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GLASS));
    SUNFLOWER = create<TallFlowerBlock>("sunflower", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    LILAC = create<TallFlowerBlock>("lilac", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ROSE_BUSH = create<TallFlowerBlock>("rose_bush", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    PEONY = create<TallFlowerBlock>("peony", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    TALL_GRASS = create<DoublePlantBlock>("tall_grass", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    LARGE_FERN = create<DoublePlantBlock>("large_fern", BlockBehaviourUtil::create(Materials::TALL_PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    WHITE_BANNER = createBanner("white_banner", DyeColors::WHITE);
    ORANGE_BANNER = createBanner("orange_banner", DyeColors::ORANGE);
    MAGENTA_BANNER = createBanner("magenta_banner", DyeColors::MAGENTA);
    LIGHT_BLUE_BANNER = createBanner("light_blue_banner", DyeColors::LIGHT_BLUE);
    YELLOW_BANNER = createBanner("yellow_banner", DyeColors::YELLOW);
    LIME_BANNER = createBanner("lime_banner", DyeColors::LIME);
    PINK_BANNER = createBanner("pink_banner", DyeColors::PINK);
    GRAY_BANNER = createBanner("gray_banner", DyeColors::GRAY);
    LIGHT_GRAY_BANNER = createBanner("light_gray_banner", DyeColors::LIGHT_GRAY);
    CYAN_BANNER = createBanner("cyan_banner", DyeColors::CYAN);
    PURPLE_BANNER = createBanner("purple_banner", DyeColors::PURPLE);
    BLUE_BANNER = createBanner("blue_banner", DyeColors::BLUE);
    BROWN_BANNER = createBanner("brown_banner", DyeColors::BROWN);
    GREEN_BANNER = createBanner("green_banner", DyeColors::GREEN);
    RED_BANNER = createBanner("red_banner", DyeColors::RED);
    BLACK_BANNER = createBanner("black_banner", DyeColors::BLACK);
    WHITE_WALL_BANNER = create<WallBannerBlock>("white_wall_banner", DyeColors::WHITE, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(WHITE_BANNER));
    ORANGE_WALL_BANNER = create<WallBannerBlock>("orange_wall_banner", DyeColors::ORANGE, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(ORANGE_BANNER));
    MAGENTA_WALL_BANNER = create<WallBannerBlock>("magenta_wall_banner", DyeColors::MAGENTA, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(MAGENTA_BANNER));
    LIGHT_BLUE_WALL_BANNER = create<WallBannerBlock>("light_blue_wall_banner", DyeColors::LIGHT_BLUE, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(LIGHT_BLUE_BANNER));
    YELLOW_WALL_BANNER = create<WallBannerBlock>("yellow_wall_banner", DyeColors::YELLOW, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(YELLOW_BANNER));
    LIME_WALL_BANNER = create<WallBannerBlock>("lime_wall_banner", DyeColors::LIME, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(LIME_BANNER));
    PINK_WALL_BANNER = create<WallBannerBlock>("pink_wall_banner", DyeColors::PINK, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(PINK_BANNER));
    GRAY_WALL_BANNER = create<WallBannerBlock>("gray_wall_banner", DyeColors::GRAY, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(GRAY_BANNER));
    LIGHT_GRAY_WALL_BANNER = create<WallBannerBlock>("light_gray_wall_banner", DyeColors::LIGHT_GRAY, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(LIGHT_GRAY_BANNER));
    CYAN_WALL_BANNER = create<WallBannerBlock>("cyan_wall_banner", DyeColors::CYAN, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(CYAN_BANNER));
    PURPLE_WALL_BANNER = create<WallBannerBlock>("purple_wall_banner", DyeColors::PURPLE, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(PURPLE_BANNER));
    BLUE_WALL_BANNER = create<WallBannerBlock>("blue_wall_banner", DyeColors::BLUE, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BLUE_BANNER));
    BROWN_WALL_BANNER = create<WallBannerBlock>("brown_wall_banner", DyeColors::BROWN, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BROWN_BANNER));
    GREEN_WALL_BANNER = create<WallBannerBlock>("green_wall_banner", DyeColors::GREEN, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(GREEN_BANNER));
    RED_WALL_BANNER = create<WallBannerBlock>("red_wall_banner", DyeColors::RED, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(RED_BANNER));
    BLACK_WALL_BANNER = create<WallBannerBlock>("black_wall_banner", DyeColors::BLACK, BlockBehaviourUtil::create(Materials::WOOD)
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BLACK_BANNER));
    RED_SANDSTONE = create<Block>("red_sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CHISELED_RED_SANDSTONE = create<Block>("chiseled_red_sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CUT_RED_SANDSTONE = create<Block>("cut_red_sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    RED_SANDSTONE_STAIRS = create<StairsBlock>("red_sandstone_stairs", RED_SANDSTONE->getDefaultState(), BlockBehaviourUtil::from(RED_SANDSTONE));
    OAK_SLAB = create<SlabBlock>("oak_slab", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_SLAB = create<SlabBlock>("spruce_slab", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_SLAB = create<SlabBlock>("birch_slab", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_SLAB = create<SlabBlock>("jungle_slab", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_SLAB = create<SlabBlock>("acacia_slab", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::ADOBE)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_SLAB = create<SlabBlock>("dark_oak_slab", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    STONE_SLAB = create<SlabBlock>("stone_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_STONE_SLAB = create<SlabBlock>("smooth_stone_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SANDSTONE_SLAB = create<SlabBlock>("sandstone_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    CUT_SANDSTONE_SLAB = create<SlabBlock>("cut_sandstone_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    PETRIFIED_OAK_SLAB = create<SlabBlock>("petrified_oak_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::WOOD)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    COBBLESTONE_SLAB = create<SlabBlock>("cobblestone_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    BRICK_SLAB = create<SlabBlock>("brick_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    STONE_BRICK_SLAB = create<SlabBlock>("stone_brick_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    NETHER_BRICK_SLAB = create<SlabBlock>("nether_brick_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    QUARTZ_SLAB = create<SlabBlock>("quartz_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    RED_SANDSTONE_SLAB = create<SlabBlock>("red_sandstone_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    CUT_RED_SANDSTONE_SLAB = create<SlabBlock>("cut_red_sandstone_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    PURPUR_SLAB = create<SlabBlock>("purpur_slab", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_STONE = create<Block>("smooth_stone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_SANDSTONE = create<Block>("smooth_sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_QUARTZ = create<Block>("smooth_quartz", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_RED_SANDSTONE = create<Block>("smooth_red_sandstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SPRUCE_FENCE_GATE = create<FenceGateBlock>("spruce_fence_gate", BlockBehaviourUtil::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_FENCE_GATE = create<FenceGateBlock>("birch_fence_gate", BlockBehaviourUtil::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_FENCE_GATE = create<FenceGateBlock>("jungle_fence_gate", BlockBehaviourUtil::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_FENCE_GATE = create<FenceGateBlock>("acacia_fence_gate", BlockBehaviourUtil::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_FENCE_GATE = create<FenceGateBlock>("dark_oak_fence_gate", BlockBehaviourUtil::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_FENCE = create<FenceBlock>("spruce_fence", BlockBehaviourUtil::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_FENCE = create<FenceBlock>("birch_fence", BlockBehaviourUtil::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_FENCE = create<FenceBlock>("jungle_fence", BlockBehaviourUtil::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_FENCE = create<FenceBlock>("acacia_fence", BlockBehaviourUtil::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_FENCE = create<FenceBlock>("dark_oak_fence", BlockBehaviourUtil::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_DOOR = create<DoorBlock>("spruce_door", BlockBehaviourUtil::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    BIRCH_DOOR = create<DoorBlock>("birch_door", BlockBehaviourUtil::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    JUNGLE_DOOR = create<DoorBlock>("jungle_door", BlockBehaviourUtil::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    ACACIA_DOOR = create<DoorBlock>("acacia_door", BlockBehaviourUtil::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    DARK_OAK_DOOR = create<DoorBlock>("dark_oak_door", BlockBehaviourUtil::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    END_ROD = create<EndRodBlock>("end_rod", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .setLightLevel([](auto) -> int32_t { return 14; })
        .setSound(SoundType::WOOD)
        .notSolid());
    CHORUS_PLANT = create<ChorusPlantBlock>("chorus_plant", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::PURPLE)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::WOOD)
        .notSolid());
    CHORUS_FLOWER = create<ChorusFlowerBlock>("chorus_flower", (ChorusPlantBlock *) CHORUS_PLANT, BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::PURPLE)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::WOOD)
        .notSolid());
    PURPUR_BLOCK = create<Block>("purpur_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PURPUR_PILLAR = create<RotatedPillarBlock>("purpur_pillar", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PURPUR_STAIRS = create<StairsBlock>("purpur_stairs", PURPUR_BLOCK->getDefaultState(), BlockBehaviourUtil::from(PURPUR_BLOCK));
    END_STONE_BRICKS = create<Block>("end_stone_bricks", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 9.0F));
    BEETROOTS = create<BeetrootBlock>("beetroots", BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    GRASS_PATH = create<GrassPathBlock>("grass_path", BlockBehaviourUtil::create(Materials::EARTH)
        .setHardnessAndResistance(0.65F)
        .setSound(SoundType::PLANT)
        .setBlocksVision(needsPostProcessing)
        .setSuffocates(needsPostProcessing));
    END_GATEWAY = create<EndGatewayBlock>("end_gateway", BlockBehaviourUtil::create(Materials::PORTAL, MaterialColors::BLACK)
        .doesNotBlockMovement()
        .setLightLevel([](auto) -> int32_t { return 15; })
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    REPEATING_COMMAND_BLOCK = create<CommandBlockBlock>("repeating_command_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    CHAIN_COMMAND_BLOCK = create<CommandBlockBlock>("chain_command_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::GREEN)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    FROSTED_ICE = create<FrostedIceBlock>("frosted_ice", BlockBehaviourUtil::create(Materials::ICE)
        .setRenderType(RenderType::Transparent)
        .setSlipperiness(0.98F)
        .setTickRandomly()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GLASS)
        .notSolid()
        .setAllowsSpawn([](BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) -> bool {
            return false;//p_235448_3_ == EntityType.POLAR_BEAR;
        }));
    MAGMA_BLOCK = create<MagmaBlock>("magma_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setLightLevel([](auto) -> int32_t { return 3; })
        .setTickRandomly()
        .setHardnessAndResistance(0.5F)
        .setAllowsSpawn(allowsSpawnImmuneToFire)
        .setNeedsPostProcessing(needsPostProcessing)
        .setEmmisiveRendering(needsPostProcessing));
    NETHER_WART_BLOCK = create<Block>("nether_wart_block", BlockBehaviourUtil::create(Materials::ORGANIC, MaterialColors::RED)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WART));
    RED_NETHER_BRICKS = create<Block>("red_nether_bricks", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    BONE_BLOCK = create<RotatedPillarBlock>("bone_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::BONE));
    STRUCTURE_VOID = create<StructureVoidBlock>("structure_void", BlockBehaviourUtil::create(Materials::STRUCTURE_VOID)
        .doesNotBlockMovement()
        .noDrops());
    OBSERVER = create<ObserverBlock>("observer", BlockBehaviourUtil::create(Materials::ROCK)
        .setHardnessAndResistance(3.0F)
        .setRequiresTool()
        .setOpaque(isntSolid));
    SHULKER_BOX = createShulkerBox("shulker_box", tl::nullopt, BlockBehaviourUtil::create(Materials::SHULKER));
    WHITE_SHULKER_BOX = createShulkerBox("white_shulker_box", DyeColors::WHITE, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::SNOW));
    ORANGE_SHULKER_BOX = createShulkerBox("orange_shulker_box", DyeColors::ORANGE, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::ADOBE));
    MAGENTA_SHULKER_BOX = createShulkerBox("magenta_shulker_box", DyeColors::MAGENTA, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::MAGENTA));
    LIGHT_BLUE_SHULKER_BOX = createShulkerBox("light_blue_shulker_box", DyeColors::LIGHT_BLUE, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::LIGHT_BLUE));
    YELLOW_SHULKER_BOX = createShulkerBox("yellow_shulker_box", DyeColors::YELLOW, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::YELLOW));
    LIME_SHULKER_BOX = createShulkerBox("lime_shulker_box", DyeColors::LIME, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::LIME));
    PINK_SHULKER_BOX = createShulkerBox("pink_shulker_box", DyeColors::PINK, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::PINK));
    GRAY_SHULKER_BOX = createShulkerBox("gray_shulker_box", DyeColors::GRAY, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::GRAY));
    LIGHT_GRAY_SHULKER_BOX = createShulkerBox("light_gray_shulker_box", DyeColors::LIGHT_GRAY, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::LIGHT_GRAY));
    CYAN_SHULKER_BOX = createShulkerBox("cyan_shulker_box", DyeColors::CYAN, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::CYAN));
    PURPLE_SHULKER_BOX = createShulkerBox("purple_shulker_box", DyeColors::PURPLE, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::PURPLE_TERRACOTTA));
    BLUE_SHULKER_BOX = createShulkerBox("blue_shulker_box", DyeColors::BLUE, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::BLUE));
    BROWN_SHULKER_BOX = createShulkerBox("brown_shulker_box", DyeColors::BROWN, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::BROWN));
    GREEN_SHULKER_BOX = createShulkerBox("green_shulker_box", DyeColors::GREEN, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::GREEN));
    RED_SHULKER_BOX = createShulkerBox("red_shulker_box", DyeColors::RED, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::RED));
    BLACK_SHULKER_BOX = createShulkerBox("black_shulker_box", DyeColors::BLACK, BlockBehaviourUtil::create(Materials::SHULKER, MaterialColors::BLACK));
    WHITE_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("white_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::WHITE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    ORANGE_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("orange_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::ORANGE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    MAGENTA_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("magenta_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    LIGHT_BLUE_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("light_blue_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::LIGHT_BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    YELLOW_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("yellow_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::YELLOW)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    LIME_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("lime_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::LIME)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    PINK_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("pink_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::PINK)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    GRAY_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("gray_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    LIGHT_GRAY_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("light_gray_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    CYAN_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("cyan_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    PURPLE_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("purple_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    BLUE_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("blue_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    BROWN_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("brown_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::BROWN)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    GREEN_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("green_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::GREEN)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    RED_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("red_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    BLACK_GLAZED_TERRACOTTA = create<GlazedTerracottaBlock>("black_glazed_terracotta", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    WHITE_CONCRETE = create<Block>("white_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::WHITE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    ORANGE_CONCRETE = create<Block>("orange_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::ORANGE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    MAGENTA_CONCRETE = create<Block>("magenta_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    LIGHT_BLUE_CONCRETE = create<Block>("light_blue_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::LIGHT_BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    YELLOW_CONCRETE = create<Block>("yellow_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::YELLOW)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    LIME_CONCRETE = create<Block>("lime_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::LIME)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    PINK_CONCRETE = create<Block>("pink_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::PINK)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    GRAY_CONCRETE = create<Block>("gray_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    LIGHT_GRAY_CONCRETE = create<Block>("light_gray_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    CYAN_CONCRETE = create<Block>("cyan_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    PURPLE_CONCRETE = create<Block>("purple_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    BLUE_CONCRETE = create<Block>("blue_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    BROWN_CONCRETE = create<Block>("brown_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::BROWN)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    GREEN_CONCRETE = create<Block>("green_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::GREEN)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    RED_CONCRETE = create<Block>("red_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    BLACK_CONCRETE = create<Block>("black_concrete", BlockBehaviourUtil::create(Materials::ROCK, DyeColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    WHITE_CONCRETE_POWDER = create<ConcretePowderBlock>("white_concrete_powder", WHITE_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::WHITE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    ORANGE_CONCRETE_POWDER = create<ConcretePowderBlock>("orange_concrete_powder", ORANGE_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::ORANGE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    MAGENTA_CONCRETE_POWDER = create<ConcretePowderBlock>("magenta_concrete_powder", MAGENTA_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::MAGENTA)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    LIGHT_BLUE_CONCRETE_POWDER = create<ConcretePowderBlock>("light_blue_concrete_powder", LIGHT_BLUE_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::LIGHT_BLUE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    YELLOW_CONCRETE_POWDER = create<ConcretePowderBlock>("yellow_concrete_powder", YELLOW_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::YELLOW)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    LIME_CONCRETE_POWDER = create<ConcretePowderBlock>("lime_concrete_powder", LIME_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::LIME)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    PINK_CONCRETE_POWDER = create<ConcretePowderBlock>("pink_concrete_powder", PINK_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::PINK)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    GRAY_CONCRETE_POWDER = create<ConcretePowderBlock>("gray_concrete_powder", GRAY_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::GRAY)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    LIGHT_GRAY_CONCRETE_POWDER = create<ConcretePowderBlock>("light_gray_concrete_powder", LIGHT_GRAY_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::LIGHT_GRAY)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    CYAN_CONCRETE_POWDER = create<ConcretePowderBlock>("cyan_concrete_powder", CYAN_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::CYAN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    PURPLE_CONCRETE_POWDER = create<ConcretePowderBlock>("purple_concrete_powder", PURPLE_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::PURPLE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    BLUE_CONCRETE_POWDER = create<ConcretePowderBlock>("blue_concrete_powder", BLUE_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::BLUE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    BROWN_CONCRETE_POWDER = create<ConcretePowderBlock>("brown_concrete_powder", BROWN_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::BROWN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    GREEN_CONCRETE_POWDER = create<ConcretePowderBlock>("green_concrete_powder", GREEN_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::GREEN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    RED_CONCRETE_POWDER = create<ConcretePowderBlock>("red_concrete_powder", RED_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::RED)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    BLACK_CONCRETE_POWDER = create<ConcretePowderBlock>("black_concrete_powder", BLACK_CONCRETE, BlockBehaviourUtil::create(Materials::SAND, DyeColors::BLACK)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    KELP = create<KelpTopBlock>("kelp", BlockBehaviourUtil::create(Materials::OCEAN_PLANT)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    KELP_PLANT = create<KelpBlock>("kelp_plant", BlockBehaviourUtil::create(Materials::OCEAN_PLANT)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    DRIED_KELP_BLOCK = create<Block>("dried_kelp_block", BlockBehaviourUtil::create(Materials::ORGANIC, MaterialColors::GREEN)
        .setHardnessAndResistance(0.5F, 2.5F)
        .setSound(SoundType::PLANT));
    TURTLE_EGG = create<TurtleEggBlock>("turtle_egg", BlockBehaviourUtil::create(Materials::DRAGON_EGG, MaterialColors::SAND)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::METAL)
        .setTickRandomly()
        .notSolid());
    DEAD_TUBE_CORAL_BLOCK = create<Block>("dead_tube_coral_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_BRAIN_CORAL_BLOCK = create<Block>("dead_brain_coral_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_BUBBLE_CORAL_BLOCK = create<Block>("dead_bubble_coral_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_FIRE_CORAL_BLOCK = create<Block>("dead_fire_coral_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_HORN_CORAL_BLOCK = create<Block>("dead_horn_coral_block", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    TUBE_CORAL_BLOCK = create<CoralBlock>("tube_coral_block", DEAD_TUBE_CORAL_BLOCK, BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    BRAIN_CORAL_BLOCK = create<CoralBlock>("brain_coral_block", DEAD_BRAIN_CORAL_BLOCK, BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::PINK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    BUBBLE_CORAL_BLOCK = create<CoralBlock>("bubble_coral_block", DEAD_BUBBLE_CORAL_BLOCK, BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    FIRE_CORAL_BLOCK = create<CoralBlock>("fire_coral_block", DEAD_FIRE_CORAL_BLOCK, BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    HORN_CORAL_BLOCK = create<CoralBlock>("horn_coral_block", DEAD_HORN_CORAL_BLOCK, BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::YELLOW)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    DEAD_TUBE_CORAL = create<DeadCoralPlantBlock>("dead_tube_coral", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BRAIN_CORAL = create<DeadCoralPlantBlock>("dead_brain_coral", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BUBBLE_CORAL = create<DeadCoralPlantBlock>("dead_bubble_coral", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_FIRE_CORAL = create<DeadCoralPlantBlock>("dead_fire_coral", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_HORN_CORAL = create<DeadCoralPlantBlock>("dead_horn_coral", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    TUBE_CORAL = create<CoralPlantBlock>("tube_coral", DEAD_TUBE_CORAL, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::BLUE)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BRAIN_CORAL = create<CoralPlantBlock>("brain_coral", DEAD_BRAIN_CORAL, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::PINK)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BUBBLE_CORAL = create<CoralPlantBlock>("bubble_coral", DEAD_BUBBLE_CORAL, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::PURPLE)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    FIRE_CORAL = create<CoralPlantBlock>("fire_coral", DEAD_FIRE_CORAL, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::RED)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    HORN_CORAL = create<CoralPlantBlock>("horn_coral", DEAD_HORN_CORAL, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::YELLOW)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    DEAD_TUBE_CORAL_FAN = create<CoralFanBlock>("dead_tube_coral_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BRAIN_CORAL_FAN = create<CoralFanBlock>("dead_brain_coral_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BUBBLE_CORAL_FAN = create<CoralFanBlock>("dead_bubble_coral_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_FIRE_CORAL_FAN = create<CoralFanBlock>("dead_fire_coral_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_HORN_CORAL_FAN = create<CoralFanBlock>("dead_horn_coral_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    TUBE_CORAL_FAN = create<CoralFinBlock>("tube_coral_fan", DEAD_TUBE_CORAL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::BLUE)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BRAIN_CORAL_FAN = create<CoralFinBlock>("brain_coral_fan", DEAD_BRAIN_CORAL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::PINK)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BUBBLE_CORAL_FAN = create<CoralFinBlock>("bubble_coral_fan", DEAD_BUBBLE_CORAL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::PURPLE)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    FIRE_CORAL_FAN = create<CoralFinBlock>("fire_coral_fan", DEAD_FIRE_CORAL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::RED)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    HORN_CORAL_FAN = create<CoralFinBlock>("horn_coral_fan", DEAD_HORN_CORAL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::YELLOW)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    DEAD_TUBE_CORAL_WALL_FAN = create<DeadCoralWallFanBlock>("dead_tube_coral_wall_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_TUBE_CORAL_FAN));
    DEAD_BRAIN_CORAL_WALL_FAN = create<DeadCoralWallFanBlock>("dead_brain_coral_wall_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_BRAIN_CORAL_FAN));
    DEAD_BUBBLE_CORAL_WALL_FAN = create<DeadCoralWallFanBlock>("dead_bubble_coral_wall_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_BUBBLE_CORAL_FAN));
    DEAD_FIRE_CORAL_WALL_FAN = create<DeadCoralWallFanBlock>("dead_fire_coral_wall_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_FIRE_CORAL_FAN));
    DEAD_HORN_CORAL_WALL_FAN = create<DeadCoralWallFanBlock>("dead_horn_coral_wall_fan", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::GRAY)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_HORN_CORAL_FAN));
    TUBE_CORAL_WALL_FAN = create<CoralWallFanBlock>("tube_coral_wall_fan", DEAD_TUBE_CORAL_WALL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::BLUE)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(TUBE_CORAL_FAN));
    BRAIN_CORAL_WALL_FAN = create<CoralWallFanBlock>("brain_coral_wall_fan", DEAD_BRAIN_CORAL_WALL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::PINK)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(BRAIN_CORAL_FAN));
    BUBBLE_CORAL_WALL_FAN = create<CoralWallFanBlock>("bubble_coral_wall_fan", DEAD_BUBBLE_CORAL_WALL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::PURPLE)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(BUBBLE_CORAL_FAN));
    FIRE_CORAL_WALL_FAN = create<CoralWallFanBlock>("fire_coral_wall_fan", DEAD_FIRE_CORAL_WALL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::RED)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(FIRE_CORAL_FAN));
    HORN_CORAL_WALL_FAN = create<CoralWallFanBlock>("horn_coral_wall_fan", DEAD_HORN_CORAL_WALL_FAN, BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::YELLOW)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(HORN_CORAL_FAN));
    SEA_PICKLE = create<SeaPickleBlock>("sea_pickle", BlockBehaviourUtil::create(Materials::OCEAN_PLANT, MaterialColors::GREEN)
        .setRenderType(RenderType::Cutout)
        .setLightLevel([](const BlockData &data) -> int32_t {
            return 0;//SeaPickleBlock::isInBadEnvironment(data) ? 0 : 3 + 3 * data.get(SeaPickleBlock::PICKLES);
        })
        .setSound(SoundType::SLIME)
        .notSolid());
    BLUE_ICE = create<BreakableBlock>("blue_ice", BlockBehaviourUtil::create(Materials::PACKED_ICE)
        .setHardnessAndResistance(2.8F)
        .setSlipperiness(0.989F)
        .setSound(SoundType::GLASS));
    CONDUIT = create<ConduitBlock>("conduit", BlockBehaviourUtil::create(Materials::GLASS, MaterialColors::DIAMOND)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setLightLevel([](auto) -> int32_t { return 15; })
        .notSolid());
    BAMBOO_SAPLING = create<BambooSaplingBlock>("bamboo_sapling", BlockBehaviourUtil::create(Materials::BAMBOO_SAPLING)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::BAMBOO_SAPLING));
    BAMBOO = create<BambooBlock>("bamboo", BlockBehaviourUtil::create(Materials::BAMBOO, MaterialColors::FOLIAGE)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::BAMBOO)
        .notSolid());
    POTTED_BAMBOO = create<FlowerPotBlock>("potted_bamboo", BAMBOO, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    VOID_AIR = create<AirBlock>("void_air", BlockBehaviourUtil::create(Materials::AIR)
        .setRenderShape(BlockRenderShape::INVISIBLE)
        .doesNotBlockMovement()
        .noDrops()
        .setAir());
    CAVE_AIR = create<AirBlock>("cave_air", BlockBehaviourUtil::create(Materials::AIR)
        .setRenderShape(BlockRenderShape::INVISIBLE)
        .doesNotBlockMovement()
        .noDrops()
        .setAir());
    BUBBLE_COLUMN = create<BubbleColumnBlock>("bubble_column", BlockBehaviourUtil::create(Materials::BUBBLE_COLUMN)
        .setRenderType(RenderType::Transparent)
        .doesNotBlockMovement()
        .noDrops());
    POLISHED_GRANITE_STAIRS = create<StairsBlock>("polished_granite_stairs", POLISHED_GRANITE->getDefaultState(), BlockBehaviourUtil::from(POLISHED_GRANITE));
    SMOOTH_RED_SANDSTONE_STAIRS = create<StairsBlock>("smooth_red_sandstone_stairs", SMOOTH_RED_SANDSTONE->getDefaultState(), BlockBehaviourUtil::from(SMOOTH_RED_SANDSTONE));
    MOSSY_STONE_BRICK_STAIRS = create<StairsBlock>("mossy_stone_brick_stairs", MOSSY_STONE_BRICKS->getDefaultState(), BlockBehaviourUtil::from(MOSSY_STONE_BRICKS));
    POLISHED_DIORITE_STAIRS = create<StairsBlock>("polished_diorite_stairs", POLISHED_DIORITE->getDefaultState(), BlockBehaviourUtil::from(POLISHED_DIORITE));
    MOSSY_COBBLESTONE_STAIRS = create<StairsBlock>("mossy_cobblestone_stairs", MOSSY_COBBLESTONE->getDefaultState(), BlockBehaviourUtil::from(MOSSY_COBBLESTONE));
    END_STONE_BRICK_STAIRS = create<StairsBlock>("end_stone_brick_stairs", END_STONE_BRICKS->getDefaultState(), BlockBehaviourUtil::from(END_STONE_BRICKS));
    STONE_STAIRS = create<StairsBlock>("stone_stairs", STONE->getDefaultState(), BlockBehaviourUtil::from(STONE));
    SMOOTH_SANDSTONE_STAIRS = create<StairsBlock>("smooth_sandstone_stairs", SMOOTH_SANDSTONE->getDefaultState(), BlockBehaviourUtil::from(SMOOTH_SANDSTONE));
    SMOOTH_QUARTZ_STAIRS = create<StairsBlock>("smooth_quartz_stairs", SMOOTH_QUARTZ->getDefaultState(), BlockBehaviourUtil::from(SMOOTH_QUARTZ));
    GRANITE_STAIRS = create<StairsBlock>("granite_stairs", GRANITE->getDefaultState(), BlockBehaviourUtil::from(GRANITE));
    ANDESITE_STAIRS = create<StairsBlock>("andesite_stairs", ANDESITE->getDefaultState(), BlockBehaviourUtil::from(ANDESITE));
    RED_NETHER_BRICK_STAIRS = create<StairsBlock>("red_nether_brick_stairs", RED_NETHER_BRICKS->getDefaultState(), BlockBehaviourUtil::from(RED_NETHER_BRICKS));
    POLISHED_ANDESITE_STAIRS = create<StairsBlock>("polished_andesite_stairs", POLISHED_ANDESITE->getDefaultState(), BlockBehaviourUtil::from(POLISHED_ANDESITE));
    DIORITE_STAIRS = create<StairsBlock>("diorite_stairs", DIORITE->getDefaultState(), BlockBehaviourUtil::from(DIORITE));
    POLISHED_GRANITE_SLAB = create<SlabBlock>("polished_granite_slab", BlockBehaviourUtil::from(POLISHED_GRANITE));
    SMOOTH_RED_SANDSTONE_SLAB = create<SlabBlock>("smooth_red_sandstone_slab", BlockBehaviourUtil::from(SMOOTH_RED_SANDSTONE));
    MOSSY_STONE_BRICK_SLAB = create<SlabBlock>("mossy_stone_brick_slab", BlockBehaviourUtil::from(MOSSY_STONE_BRICKS));
    POLISHED_DIORITE_SLAB = create<SlabBlock>("polished_diorite_slab", BlockBehaviourUtil::from(POLISHED_DIORITE));
    MOSSY_COBBLESTONE_SLAB = create<SlabBlock>("mossy_cobblestone_slab", BlockBehaviourUtil::from(MOSSY_COBBLESTONE));
    END_STONE_BRICK_SLAB = create<SlabBlock>("end_stone_brick_slab", BlockBehaviourUtil::from(END_STONE_BRICKS));
    SMOOTH_SANDSTONE_SLAB = create<SlabBlock>("smooth_sandstone_slab", BlockBehaviourUtil::from(SMOOTH_SANDSTONE));
    SMOOTH_QUARTZ_SLAB = create<SlabBlock>("smooth_quartz_slab", BlockBehaviourUtil::from(SMOOTH_QUARTZ));
    GRANITE_SLAB = create<SlabBlock>("granite_slab", BlockBehaviourUtil::from(GRANITE));
    ANDESITE_SLAB = create<SlabBlock>("andesite_slab", BlockBehaviourUtil::from(ANDESITE));
    RED_NETHER_BRICK_SLAB = create<SlabBlock>("red_nether_brick_slab", BlockBehaviourUtil::from(RED_NETHER_BRICKS));
    POLISHED_ANDESITE_SLAB = create<SlabBlock>("polished_andesite_slab", BlockBehaviourUtil::from(POLISHED_ANDESITE));
    DIORITE_SLAB = create<SlabBlock>("diorite_slab", BlockBehaviourUtil::from(DIORITE));
    BRICK_WALL = create<WallBlock>("brick_wall", BlockBehaviourUtil::from(BRICKS));
    PRISMARINE_WALL = create<WallBlock>("prismarine_wall", BlockBehaviourUtil::from(PRISMARINE));
    RED_SANDSTONE_WALL = create<WallBlock>("red_sandstone_wall", BlockBehaviourUtil::from(RED_SANDSTONE));
    MOSSY_STONE_BRICK_WALL = create<WallBlock>("mossy_stone_brick_wall", BlockBehaviourUtil::from(MOSSY_STONE_BRICKS));
    GRANITE_WALL = create<WallBlock>("granite_wall", BlockBehaviourUtil::from(GRANITE));
    STONE_BRICK_WALL = create<WallBlock>("stone_brick_wall", BlockBehaviourUtil::from(STONE_BRICKS));
    NETHER_BRICK_WALL = create<WallBlock>("nether_brick_wall", BlockBehaviourUtil::from(NETHER_BRICKS));
    ANDESITE_WALL = create<WallBlock>("andesite_wall", BlockBehaviourUtil::from(ANDESITE));
    RED_NETHER_BRICK_WALL = create<WallBlock>("red_nether_brick_wall", BlockBehaviourUtil::from(RED_NETHER_BRICKS));
    SANDSTONE_WALL = create<WallBlock>("sandstone_wall", BlockBehaviourUtil::from(SANDSTONE));
    END_STONE_BRICK_WALL = create<WallBlock>("end_stone_brick_wall", BlockBehaviourUtil::from(END_STONE_BRICKS));
    DIORITE_WALL = create<WallBlock>("diorite_wall", BlockBehaviourUtil::from(DIORITE));
    SCAFFOLDING = create<ScaffoldingBlock>("scaffolding", BlockBehaviourUtil::create(Materials::MISCELLANEOUS, MaterialColors::SAND)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .setSound(SoundType::SCAFFOLDING)
        .setVariableOpacity());
    LOOM = create<LoomBlock>("loom", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    BARREL = create<BarrelBlock>("barrel", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    SMOKER = create<SmokerBlock>("smoker", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setLightLevel(getLightLevelLit<13>()));
    BLAST_FURNACE = create<BlastFurnaceBlock>("blast_furnace", BlockBehaviourUtil::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setLightLevel(getLightLevelLit<13>()));
    CARTOGRAPHY_TABLE = create<CartographyTableBlock>("cartography_table", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    FLETCHING_TABLE = create<FletchingTableBlock>("fletching_table", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    GRINDSTONE = create<GrindstoneBlock>("grindstone", BlockBehaviourUtil::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::STONE));
    LECTERN = create<LecternBlock>("lectern", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    SMITHING_TABLE = create<SmithingTableBlock>("smithing_table", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    STONECUTTER = create<StonecutterBlock>("stonecutter", BlockBehaviourUtil::create(Materials::ROCK)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F));
    BELL = create<BellBlock>("bell", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::GOLD)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::ANVIL));
    LANTERN = create<LanternBlock>("lantern", BlockBehaviourUtil::create(Materials::IRON)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setSound(SoundType::LANTERN)
        .setLightLevel([](auto) -> int32_t { return 15; })
        .notSolid());
    SOUL_LANTERN = create<LanternBlock>("soul_lantern", BlockBehaviourUtil::create(Materials::IRON)
        .setRenderType(RenderType::Cutout)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setSound(SoundType::LANTERN)
        .setLightLevel([](auto) -> int32_t { return 10; })
        .notSolid());
    CAMPFIRE = create<CampfireBlock>("campfire", true, 1, BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD)
        .setLightLevel(getLightLevelLit<15>())
        .notSolid());
    SOUL_CAMPFIRE = create<CampfireBlock>("soul_campfire", false, 2, BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD)
        .setLightLevel(getLightLevelLit<10>())
        .notSolid());
    SWEET_BERRY_BUSH = create<SweetBerryBushBlock>("sweet_berry_bush", BlockBehaviourUtil::create(Materials::PLANTS)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .doesNotBlockMovement()
        .setSound(SoundType::SWEET_BERRY_BUSH));
    WARPED_STEM = createRotatableNetherBlock("warped_stem", MaterialColors::WARPED_STEM);
    STRIPPED_WARPED_STEM = createRotatableNetherBlock("stripped_warped_stem", MaterialColors::WARPED_STEM);
    WARPED_HYPHAE = create<RotatedPillarBlock>("warped_hyphae", BlockBehaviourUtil::create(Materials::NETHER_WOOD, MaterialColors::WARPED_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    STRIPPED_WARPED_HYPHAE = create<RotatedPillarBlock>("stripped_warped_hyphae", BlockBehaviourUtil::create(Materials::NETHER_WOOD, MaterialColors::WARPED_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    WARPED_NYLIUM = create<NyliumBlock>("warped_nylium", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::WARPED_NYLIUM)
        .setRequiresTool()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::NYLIUM)
        .setTickRandomly());
    WARPED_FUNGUS = create<FungusBlock>("warped_fungus", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::CYAN)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .doesNotBlockMovement()
        .setSound(SoundType::FUNGUS)
        /*, []() {
            return Features.WARPED_FUNGI_PLANTED;
        }*/);
    WARPED_WART_BLOCK = create<Block>("warped_wart_block", BlockBehaviourUtil::create(Materials::ORGANIC, MaterialColors::WARPED_WART)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WART));
    WARPED_ROOTS = create<NetherRootsBlock>("warped_roots", BlockBehaviourUtil::create(Materials::NETHER_PLANTS, MaterialColors::CYAN)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::ROOT));
    NETHER_SPROUTS = create<NetherSproutsBlock>("nether_sprouts", BlockBehaviourUtil::create(Materials::NETHER_PLANTS, MaterialColors::CYAN)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_SPROUT));
    CRIMSON_STEM = createRotatableNetherBlock("crimson_stem", MaterialColors::CRIMSON_STEM);
    STRIPPED_CRIMSON_STEM = createRotatableNetherBlock("stripped_crimson_stem", MaterialColors::CRIMSON_STEM);
    CRIMSON_HYPHAE = create<RotatedPillarBlock>("crimson_hyphae", BlockBehaviourUtil::create(Materials::NETHER_WOOD, MaterialColors::CRIMSON_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    STRIPPED_CRIMSON_HYPHAE = create<RotatedPillarBlock>("stripped_crimson_hyphae", BlockBehaviourUtil::create(Materials::NETHER_WOOD, MaterialColors::CRIMSON_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    CRIMSON_NYLIUM = create<NyliumBlock>("crimson_nylium", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::CRIMSON_NYLIUM)
        .setRequiresTool()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::NYLIUM)
        .setTickRandomly());
    CRIMSON_FUNGUS = create<FungusBlock>("crimson_fungus", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::NETHERRACK)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .doesNotBlockMovement()
        .setSound(SoundType::FUNGUS)
        /*, []() {
            return Features::CRIMSON_FUNGI_PLANTED;
        }*/);
    SHROOMLIGHT = create<Block>("shroomlight", BlockBehaviourUtil::create(Materials::ORGANIC, MaterialColors::RED)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::SHROOMLIGHT)
        .setLightLevel([](auto) -> int32_t { return 15; }));
    WEEPING_VINES = create<WeepingVinesTopBlock>("weeping_vines", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::NETHERRACK)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    WEEPING_VINES_PLANT = create<WeepingVinesBlock>("weeping_vines_plant", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::NETHERRACK)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    TWISTING_VINES = create<TwistingVinesTopBlock>("twisting_vines", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::CYAN)
        .setRenderType(RenderType::Cutout)
        .setTickRandomly()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    TWISTING_VINES_PLANT = create<TwistingVinesBlock>("twisting_vines_plant", BlockBehaviourUtil::create(Materials::PLANTS, MaterialColors::CYAN)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    CRIMSON_ROOTS = create<NetherRootsBlock>("crimson_roots", BlockBehaviourUtil::create(Materials::NETHER_PLANTS, MaterialColors::NETHERRACK)
        .setRenderType(RenderType::Cutout)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::ROOT));
    CRIMSON_PLANKS = create<Block>("crimson_planks", BlockBehaviourUtil::create(Materials::NETHER_WOOD, MaterialColors::CRIMSON_STEM)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_PLANKS = create<Block>("warped_planks", BlockBehaviourUtil::create(Materials::NETHER_WOOD, MaterialColors::WARPED_STEM)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_SLAB = create<SlabBlock>("crimson_slab", BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_SLAB = create<SlabBlock>("warped_slab", BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_PRESSURE_PLATE = create<PressurePlateBlock>("crimson_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    WARPED_PRESSURE_PLATE = create<PressurePlateBlock>("warped_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    CRIMSON_FENCE = create<FenceBlock>("crimson_fence", BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_FENCE = create<FenceBlock>("warped_fence", BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_TRAPDOOR = create<TrapDoorBlock>("crimson_trapdoor", BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    WARPED_TRAPDOOR = create<TrapDoorBlock>("warped_trapdoor", BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    CRIMSON_FENCE_GATE = create<FenceGateBlock>("crimson_fence_gate", BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_FENCE_GATE = create<FenceGateBlock>("warped_fence_gate", BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_STAIRS = create<StairsBlock>("crimson_stairs", CRIMSON_PLANKS->getDefaultState(), BlockBehaviourUtil::from(CRIMSON_PLANKS));
    WARPED_STAIRS = create<StairsBlock>("warped_stairs", WARPED_PLANKS->getDefaultState(), BlockBehaviourUtil::from(WARPED_PLANKS));
    CRIMSON_BUTTON = create<WoodButtonBlock>("crimson_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    WARPED_BUTTON = create<WoodButtonBlock>("warped_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    CRIMSON_DOOR = create<DoorBlock>("crimson_door", BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    WARPED_DOOR = create<DoorBlock>("warped_door", BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setRenderType(RenderType::Cutout)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    CRIMSON_SIGN = create<StandingSignBlock>("crimson_sign", BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::CRIMSON);
    WARPED_SIGN = create<StandingSignBlock>("warped_sign", BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::WARPED);
    CRIMSON_WALL_SIGN = create<WallSignBlock>("crimson_wall_sign", BlockBehaviourUtil::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(CRIMSON_SIGN), WoodType::CRIMSON);
    WARPED_WALL_SIGN = create<WallSignBlock>("warped_wall_sign", BlockBehaviourUtil::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setRenderShape(BlockRenderShape::ENTITY)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(WARPED_SIGN), WoodType::WARPED);
    STRUCTURE_BLOCK = create<StructureBlock>("structure_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    JIGSAW = create<JigsawBlock>("jigsaw", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    COMPOSTER = create<ComposterBlock>("composter", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::WOOD));
    TARGET = create<TargetBlock>("target", BlockBehaviourUtil::create(Materials::ORGANIC, MaterialColors::QUARTZ)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::PLANT));
    BEE_NEST = create<BeehiveBlock>("bee_nest", BlockBehaviourUtil::create(Materials::WOOD, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::WOOD));
    BEEHIVE = create<BeehiveBlock>("beehive", BlockBehaviourUtil::create(Materials::WOOD)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::WOOD));
    HONEY_BLOCK = create<HoneyBlock>("honey_block", BlockBehaviourUtil::create(Materials::CLAY, MaterialColors::ADOBE)
        .setRenderType(RenderType::Transparent)
        .setSpeedFactor(0.4F)
        .setJumpFactor(0.5F)
        .notSolid()
        .setSound(SoundType::HONEY));
    HONEYCOMB_BLOCK = create<Block>("honeycomb_block", BlockBehaviourUtil::create(Materials::CLAY, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::CORAL));
    NETHERITE_BLOCK = create<Block>("netherite_block", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F)
        .setSound(SoundType::NETHERITE));
    ANCIENT_DEBRIS = create<Block>("ancient_debris", BlockBehaviourUtil::create(Materials::IRON, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(30.0F, 1200.0F)
        .setSound(SoundType::ANCIENT_DEBRIS));
    CRYING_OBSIDIAN = create<CryingObsidianBlock>("crying_obsidian", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F)
        .setLightLevel([](auto) -> int32_t { return 10; }));
    RESPAWN_ANCHOR = create<RespawnAnchorBlock>("respawn_anchor", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F)
        .setLightLevel([](const BlockData &data) -> int32_t {
            return 0;//RespawnAnchorBlock::getChargeScale(data, 15);
        }));
    POTTED_CRIMSON_FUNGUS = create<FlowerPotBlock>("potted_crimson_fungus", CRIMSON_FUNGUS, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WARPED_FUNGUS = create<FlowerPotBlock>("potted_warped_fungus", WARPED_FUNGUS, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_CRIMSON_ROOTS = create<FlowerPotBlock>("potted_crimson_roots", CRIMSON_ROOTS, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WARPED_ROOTS = create<FlowerPotBlock>("potted_warped_roots", WARPED_ROOTS, BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .setRenderType(RenderType::Cutout)
        .zeroHardnessAndResistance()
        .notSolid());
    LODESTONE = create<Block>("lodestone", BlockBehaviourUtil::create(Materials::ANVIL)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setSound(SoundType::LODESTONE));
    BLACKSTONE = create<Block>("blackstone", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    BLACKSTONE_STAIRS = create<StairsBlock>("blackstone_stairs", BLACKSTONE->getDefaultState(), BlockBehaviourUtil::from(BLACKSTONE));
    BLACKSTONE_WALL = create<WallBlock>("blackstone_wall", BlockBehaviourUtil::from(BLACKSTONE));
    BLACKSTONE_SLAB = create<SlabBlock>("blackstone_slab", BlockBehaviourUtil::from(BLACKSTONE)
        .setHardnessAndResistance(2.0F, 6.0F));
    POLISHED_BLACKSTONE = create<Block>("polished_blackstone", BlockBehaviourUtil::from(BLACKSTONE)
        .setHardnessAndResistance(2.0F, 6.0F));
    POLISHED_BLACKSTONE_BRICKS = create<Block>("polished_blackstone_bricks", BlockBehaviourUtil::from(POLISHED_BLACKSTONE)
        .setHardnessAndResistance(1.5F, 6.0F));
    CRACKED_POLISHED_BLACKSTONE_BRICKS = create<Block>("cracked_polished_blackstone_bricks", BlockBehaviourUtil::from(POLISHED_BLACKSTONE_BRICKS));
    CHISELED_POLISHED_BLACKSTONE = create<Block>("chiseled_polished_blackstone", BlockBehaviourUtil::from(POLISHED_BLACKSTONE)
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_BLACKSTONE_BRICK_SLAB = create<SlabBlock>("polished_blackstone_brick_slab", BlockBehaviourUtil::from(POLISHED_BLACKSTONE_BRICKS)
        .setHardnessAndResistance(2.0F, 6.0F));
    POLISHED_BLACKSTONE_BRICK_STAIRS = create<StairsBlock>("polished_blackstone_brick_stairs", POLISHED_BLACKSTONE_BRICKS->getDefaultState(), BlockBehaviourUtil::from(POLISHED_BLACKSTONE_BRICKS));
    POLISHED_BLACKSTONE_BRICK_WALL = create<WallBlock>("polished_blackstone_brick_wall", BlockBehaviourUtil::from(POLISHED_BLACKSTONE_BRICKS));
    GILDED_BLACKSTONE = create<Block>("gilded_blackstone", BlockBehaviourUtil::from(BLACKSTONE).setSound(SoundType::GILDED_BLACKSTONE));
    POLISHED_BLACKSTONE_STAIRS = create<StairsBlock>("polished_blackstone_stairs", POLISHED_BLACKSTONE->getDefaultState(), BlockBehaviourUtil::from(POLISHED_BLACKSTONE));
    POLISHED_BLACKSTONE_SLAB = create<SlabBlock>("polished_blackstone_slab", BlockBehaviourUtil::from(POLISHED_BLACKSTONE));
    POLISHED_BLACKSTONE_PRESSURE_PLATE = create<PressurePlateBlock>("polished_blackstone_pressure_plate", PressurePlateBlock::Sensitivity::MOBS, BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    POLISHED_BLACKSTONE_BUTTON = create<StoneButtonBlock>("polished_blackstone_button", BlockBehaviourUtil::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    POLISHED_BLACKSTONE_WALL = create<WallBlock>("polished_blackstone_wall", BlockBehaviourUtil::from(POLISHED_BLACKSTONE));
    CHISELED_NETHER_BRICKS = create<Block>("chiseled_nether_bricks", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    CRACKED_NETHER_BRICKS = create<Block>("cracked_nether_bricks", BlockBehaviourUtil::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    QUARTZ_BRICKS = create<Block>("quartz_bricks", BlockBehaviourUtil::from(QUARTZ_BLOCK));
}