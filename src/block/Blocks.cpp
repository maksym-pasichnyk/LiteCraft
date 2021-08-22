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
#include "Block.hpp"
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
#include "ContainerBlock.hpp"
#include "CoralBlock.hpp"
#include "CoralFanBlock.hpp"
#include "CoralFinBlock.hpp"
#include "CoralPlantBlock.hpp"
#include "CoralWallFanBlock.hpp"
#include "CraftingTableBlock.hpp"
#include "CropsBlock.hpp"
#include "CryingObsidianBlock.hpp"
#include "DaylightDetectorBlock.hpp"
#include "DeadBushBlock.hpp"
#include "DeadCoralPlantBlock.hpp"
#include "DeadCoralWallFanBlock.hpp"
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
#include "IceBlock.hpp"
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
#include "RotatedPillarBlock.hpp"
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
#include "SnowyDirtBlock.hpp"
#include "SoulFireBlock.hpp"
#include "SoulSandBlock.hpp"
#include "SpawnerBlock.hpp"
#include "SpongeBlock.hpp"
#include "StainedGlassBlock.hpp"
#include "StainedGlassPaneBlock.hpp"
#include "StairsBlock.hpp"
#include "StandingSignBlock.hpp"
#include "StemBlock.hpp"
#include "StemGrownBlock.hpp"
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
#include "TorchBlock.hpp"
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
#include "WallSkullBlock.hpp"
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
#include "WoodType.hpp"

#include "BlockGraphics.hpp"
#include "BlockTable.hpp"
#include "ShulkerBoxBlock.hpp"
#include "material/DyeColors.hpp"
#include "material/Materials.hpp"

#include <fmt/format.h>


using Properties = AbstractBlock::Properties;

BlockTable Blocks::pallete;
std::vector<Block *> Blocks::blocks;

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

//private static ShulkerBoxBlock createShulkerBox(@Nullable DyeColor color, AbstractBlock.Properties properties) {
//        AbstractBlock.IPositionPredicate abstractblock$ipositionpredicate = (p_235444_0_, p_235444_1_, p_235444_2_) -> {
//            TileEntity tileentity = p_235444_1_.getTileEntity(p_235444_2_);
//            if (!(tileentity instanceof ShulkerBoxTileEntity)) {
//                return true;
//            } else {
//                ShulkerBoxTileEntity shulkerboxtileentity = (ShulkerBoxTileEntity)tileentity;
//                return shulkerboxtileentity.func_235676_l_();
//            }
//        };
//        return new ShulkerBoxBlock(color, properties.hardnessAndResistance(2.0F).setVariableOpacity().notSolid().setSuffocates(abstractblock$ipositionpredicate).setBlocksVision(abstractblock$ipositionpredicate));
//    }
//private static Block createBlock(String key, Block blockIn) {
//        return Registry.createBlock(Registry.BLOCK, key, blockIn);
//    }

static auto getLightValueLit(int value) {
    return [value](const BlockData &data) -> int32_t {
        return value;// data.get(BlockStateProperty::LIT) ? lightValue : 0;
    };
}

static auto getLightValue(int value) {
    return [value](const BlockData &data) -> int32_t { return value; };
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
static T* createBlock(const std::string& name, Args &&...args) {
    const auto id = static_cast<int>(Blocks::pallete.getId(name));
    if (Blocks::blocks.size() < id + 1) {
        Blocks::blocks.resize(id + 1);
    }

    auto block = new T(id, std::forward<Args>(args)...);
    if (auto it = BlockGraphics::mBlockLookupMap.find(name); it != BlockGraphics::mBlockLookupMap.end()) {
        block->graphics = it->second;
    } else {
        fmt::print("missing block graphics: {}\n", name);
        block->graphics = BlockGraphics::mMissingTexture;
    }

    Blocks::blocks[id] = block;
    block->fillStateContainer();
    return block;
}

static Block *createLogBlock(const std::string& name, MaterialColor topColor, MaterialColor barkColor) {
    return createBlock<RotatedPillarBlock>(name, Properties::create(Materials::WOOD,
        [topColor, barkColor](const BlockData &data) -> MaterialColor {
            return topColor;// data.get(RotatedPillarBlock::AXIS) == Direction::Axis::Y ? topColor : barkColor;
        })
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
}

static Block *createPiston(const std::string& name, bool sticky) {
    return createBlock<PistonBlock>(name, sticky, Properties::create(Materials::PISTON)
         .setHardnessAndResistance(1.5F)
         .setOpaque(isntSolid)
         .setSuffocates(isntExtended)
         .setBlocksVision(isntExtended));
}

static Block *createLeavesBlock(const std::string& name) {
    return createBlock<LeavesBlock>(name, Properties::create(Materials::LEAVES)
        .setHardnessAndResistance(0.2F)
        .setTickRandomly()
        .setSound(SoundType::PLANT)
        .notSolid()
        .setAllowsSpawn(allowsSpawnOnLeaves)
        .setSuffocates(isntSolid)
        .setBlocksVision(isntSolid));
}

static Block *createBed(const std::string& name, DyeColors color) {
    return createBlock<BedBlock>(name, color, Properties::create(Materials::WOOL,
        [](const BlockData &data) -> MaterialColor {
            return MaterialColors::WOOL;// data.get(BedBlock::PART) == BedPart::FOOT ? color.getMapColor() : MaterialColors::WOOL;
        }).setSound(SoundType::WOOD)
        .setHardnessAndResistance(0.2F)
        .notSolid());
}

static Block *createStainedGlass(const std::string& name, DyeColors color) {
    return createBlock<StainedGlassBlock>(name, color, Properties::create(Materials::GLASS, color)
          .setHardnessAndResistance(0.3F)
          .setSound(SoundType::GLASS)
          .notSolid()
          .setAllowsSpawn(neverAllowSpawn)
          .setOpaque(isntSolid)
          .setSuffocates(isntSolid)
          .setBlocksVision(isntSolid));
}

static Block *createShulkerBox(const std::string& name, std::optional<DyeColors> color, Properties properties) {
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
    return createBlock<ShulkerBoxBlock>(name, color, std::move(properties).setHardnessAndResistance(2.0F).setVariableOpacity().notSolid().setSuffocates(isBlocksVision).setBlocksVision(isBlocksVision));
}

static Block *createRotatableNetherBlock(const std::string& name, MaterialColor color) {
    return createBlock<RotatedPillarBlock>(name, Properties::create(Materials::NETHER_WOOD, getMaterialColor(color))
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
}

static Block* createBanner(const std::string& name, DyeColors color) {
    return createBlock<BannerBlock>(name, color, Properties::create(Materials::WOOD).doesNotBlockMovement().setHardnessAndResistance(1.0F).setSound(SoundType::WOOD));
}

void Blocks::registerBlocks() {
    using namespace std::string_literals;

    AIR = createBlock<AirBlock>("air", Properties::create(Materials::AIR)
        .doesNotBlockMovement()
        .noDrops()
        .setAir());
    STONE = createBlock<Block>("stone", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    GRANITE = createBlock<Block>("granite", Properties::create(Materials::ROCK, MaterialColors::DIRT)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_GRANITE = createBlock<Block>("polished_granite", Properties::create(Materials::ROCK, MaterialColors::DIRT)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DIORITE = createBlock<Block>("diorite", Properties::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_DIORITE = createBlock<Block>("polished_diorite", Properties::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    ANDESITE = createBlock<Block>("andesite", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_ANDESITE = createBlock<Block>("polished_andesite", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    GRASS_BLOCK = createBlock<GrassBlock>("grass_block", Properties::create(Materials::ORGANIC)
        .setTickRandomly()
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    DIRT = createBlock<Block>("dirt", Properties::create(Materials::EARTH, MaterialColors::DIRT)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GROUND));
    COARSE_DIRT = createBlock<Block>("coarse_dirt", Properties::create(Materials::EARTH, MaterialColors::DIRT)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GROUND));
    PODZOL = createBlock<SnowyDirtBlock>("podzol", Properties::create(Materials::EARTH, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GROUND));
    COBBLESTONE = createBlock<Block>("cobblestone", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    OAK_PLANKS = createBlock<Block>("oak_planks", Properties::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_PLANKS = createBlock<Block>("spruce_planks", Properties::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_PLANKS = createBlock<Block>("birch_planks", Properties::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_PLANKS = createBlock<Block>("jungle_planks", Properties::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_PLANKS = createBlock<Block>("acacia_planks", Properties::create(Materials::WOOD, MaterialColors::ADOBE)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_PLANKS = createBlock<Block>("dark_oak_planks", Properties::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    OAK_SAPLING = createBlock<SaplingBlock>("oak_sapling", new OakTree(), Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    SPRUCE_SAPLING = createBlock<SaplingBlock>("spruce_sapling", new SpruceTree(), Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BIRCH_SAPLING = createBlock<SaplingBlock>("birch_sapling", new BirchTree(), Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    JUNGLE_SAPLING = createBlock<SaplingBlock>("jungle_sapling", new JungleTree(), Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ACACIA_SAPLING = createBlock<SaplingBlock>("acacia_sapling", new AcaciaTree(), Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    DARK_OAK_SAPLING = createBlock<SaplingBlock>("dark_oak_sapling", new DarkOakTree(), Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BEDROCK = createBlock<Block>("bedrock", Properties::create(Materials::ROCK)
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops()
        .setAllowsSpawn(neverAllowSpawn));
    WATER = createBlock<FlowingFluidBlock>("water", Fluids::WATER, Properties::create(Materials::WATER).doesNotBlockMovement().setHardnessAndResistance(100.0F).noDrops());
    LAVA = createBlock<FlowingFluidBlock>("lava", Fluids::LAVA, Properties::create(Materials::LAVA).doesNotBlockMovement().setTickRandomly().setHardnessAndResistance(100.0F).setLightLevel(getLightValue(15)).noDrops());
    SAND = createBlock<SandBlock>("sand", 14406560, Properties::create(Materials::SAND, MaterialColors::SAND).setHardnessAndResistance(0.5F).setSound(SoundType::SAND));
    RED_SAND = createBlock<SandBlock>("red_sand", 11098145, Properties::create(Materials::SAND, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    GRAVEL = createBlock<GravelBlock>("gravel", Properties::create(Materials::SAND, MaterialColors::STONE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::GROUND));
    GOLD_ORE = createBlock<OreBlock>("gold_ore", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    IRON_ORE = createBlock<OreBlock>("iron_ore", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    COAL_ORE = createBlock<OreBlock>("coal_ore", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    NETHER_GOLD_ORE = createBlock<OreBlock>("nether_gold_ore", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
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
    OAK_WOOD = createBlock<RotatedPillarBlock>("oak_wood", Properties::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_WOOD = createBlock<RotatedPillarBlock>("spruce_wood", Properties::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    BIRCH_WOOD = createBlock<RotatedPillarBlock>("birch_wood", Properties::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_WOOD = createBlock<RotatedPillarBlock>("jungle_wood", Properties::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    ACACIA_WOOD = createBlock<RotatedPillarBlock>("acacia_wood", Properties::create(Materials::WOOD, MaterialColors::GRAY)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_WOOD = createBlock<RotatedPillarBlock>("dark_oak_wood", Properties::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_OAK_WOOD = createBlock<RotatedPillarBlock>("stripped_oak_wood", Properties::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_SPRUCE_WOOD = createBlock<RotatedPillarBlock>("stripped_spruce_wood", Properties::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_BIRCH_WOOD = createBlock<RotatedPillarBlock>("stripped_birch_wood", Properties::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_JUNGLE_WOOD = createBlock<RotatedPillarBlock>("stripped_jungle_wood", Properties::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_ACACIA_WOOD = createBlock<RotatedPillarBlock>("stripped_acacia_wood", Properties::create(Materials::WOOD, MaterialColors::ADOBE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    STRIPPED_DARK_OAK_WOOD = createBlock<RotatedPillarBlock>("stripped_dark_oak_wood", Properties::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD));
    OAK_LEAVES = createLeavesBlock("oak_leaves");
    SPRUCE_LEAVES = createLeavesBlock("spruce_leaves");
    BIRCH_LEAVES = createLeavesBlock("birch_leaves");
    JUNGLE_LEAVES = createLeavesBlock("jungle_leaves");
    ACACIA_LEAVES = createLeavesBlock("acacia_leaves");
    DARK_OAK_LEAVES = createLeavesBlock("dark_oak_leaves");
    SPONGE = createBlock<SpongeBlock>("sponge", Properties::create(Materials::SPONGE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    WET_SPONGE = createBlock<WetSpongeBlock>("wet_sponge", Properties::create(Materials::SPONGE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    GLASS = createBlock<GlassBlock>("glass", Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn)
        .setOpaque(isntSolid)
        .setSuffocates(isntSolid)
        .setBlocksVision(isntSolid));
    LAPIS_ORE = createBlock<OreBlock>("lapis_ore", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    LAPIS_BLOCK = createBlock<Block>("lapis_block", Properties::create(Materials::IRON, MaterialColors::LAPIS)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    DISPENSER = createBlock<DispenserBlock>("dispenser", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F));
    SANDSTONE = createBlock<Block>("sandstone", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CHISELED_SANDSTONE = createBlock<Block>("chiseled_sandstone", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CUT_SANDSTONE = createBlock<Block>("cut_sandstone", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    NOTE_BLOCK = createBlock<NoteBlock>("note_block", Properties::create(Materials::WOOD)
        .setSound(SoundType::WOOD)
        .setHardnessAndResistance(0.8F));
    WHITE_BED = createBed("white_bed", (DyeColors::WHITE));
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
    POWERED_RAIL = createBlock<PoweredRailBlock>("powered_rail", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    DETECTOR_RAIL = createBlock<DetectorRailBlock>("detector_rail", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    STICKY_PISTON = createPiston("sticky_piston", true);
    COBWEB = createBlock<WebBlock>("cobweb", Properties::create(Materials::WEB)
        .doesNotBlockMovement()
        .setRequiresTool()
        .setHardnessAndResistance(4.0F));
    GRASS = createBlock<TallGrassBlock>("grass", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    FERN = createBlock<TallGrassBlock>("fern", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    DEAD_BUSH = createBlock<DeadBushBlock>("dead_bush", Properties::create(Materials::TALL_PLANTS, MaterialColors::WOOD)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    SEAGRASS = createBlock<SeaGrassBlock>("seagrass", Properties::create(Materials::SEA_GRASS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    TALL_SEAGRASS = createBlock<TallSeaGrassBlock>("tall_seagrass", Properties::create(Materials::SEA_GRASS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    PISTON = createPiston("piston", false);
    PISTON_HEAD = createBlock<PistonHeadBlock>("piston_head", Properties::create(Materials::PISTON)
        .setHardnessAndResistance(1.5F)
        .noDrops());
    WHITE_WOOL = createBlock<Block>("white_wool", Properties::create(Materials::WOOL, MaterialColors::SNOW)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    ORANGE_WOOL = createBlock<Block>("orange_wool", Properties::create(Materials::WOOL, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    MAGENTA_WOOL = createBlock<Block>("magenta_wool", Properties::create(Materials::WOOL, MaterialColors::MAGENTA)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    LIGHT_BLUE_WOOL = createBlock<Block>("light_blue_wool", Properties::create(Materials::WOOL, MaterialColors::LIGHT_BLUE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    YELLOW_WOOL = createBlock<Block>("yellow_wool", Properties::create(Materials::WOOL, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    LIME_WOOL = createBlock<Block>("lime_wool", Properties::create(Materials::WOOL, MaterialColors::LIME)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    PINK_WOOL = createBlock<Block>("pink_wool", Properties::create(Materials::WOOL, MaterialColors::PINK)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    GRAY_WOOL = createBlock<Block>("gray_wool", Properties::create(Materials::WOOL, MaterialColors::GRAY)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    LIGHT_GRAY_WOOL = createBlock<Block>("light_gray_wool", Properties::create(Materials::WOOL, MaterialColors::LIGHT_GRAY)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    CYAN_WOOL = createBlock<Block>("cyan_wool", Properties::create(Materials::WOOL, MaterialColors::CYAN)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    PURPLE_WOOL = createBlock<Block>("purple_wool", Properties::create(Materials::WOOL, MaterialColors::PURPLE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    BLUE_WOOL = createBlock<Block>("blue_wool", Properties::create(Materials::WOOL, MaterialColors::BLUE)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    BROWN_WOOL = createBlock<Block>("brown_wool", Properties::create(Materials::WOOL, MaterialColors::BROWN)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    GREEN_WOOL = createBlock<Block>("green_wool", Properties::create(Materials::WOOL, MaterialColors::GREEN)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    RED_WOOL = createBlock<Block>("red_wool", Properties::create(Materials::WOOL, MaterialColors::RED)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    BLACK_WOOL = createBlock<Block>("black_wool", Properties::create(Materials::WOOL, MaterialColors::BLACK)
        .setHardnessAndResistance(0.8F)
        .setSound(SoundType::CLOTH));
    MOVING_PISTON = createBlock<MovingPistonBlock>("moving_piston", Properties::create(Materials::PISTON)
        .setHardnessAndResistance(-1.0F)
        .setVariableOpacity()
        .noDrops()
        .notSolid()
        .setOpaque(isntSolid)
        .setSuffocates(isntSolid)
        .setBlocksVision(isntSolid));
    DANDELION = createBlock<FlowerBlock>("dandelion", Effects::SATURATION, 7, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    POPPY = createBlock<FlowerBlock>("poppy", Effects::NIGHT_VISION, 5, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BLUE_ORCHID = createBlock<FlowerBlock>("blue_orchid", Effects::SATURATION, 7, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ALLIUM = createBlock<FlowerBlock>("allium", Effects::FIRE_RESISTANCE, 4, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    AZURE_BLUET = createBlock<FlowerBlock>("azure_bluet", Effects::BLINDNESS, 8, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    RED_TULIP = createBlock<FlowerBlock>("red_tulip", Effects::WEAKNESS, 9, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ORANGE_TULIP = createBlock<FlowerBlock>("orange_tulip", Effects::WEAKNESS, 9, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    WHITE_TULIP = createBlock<FlowerBlock>("white_tulip", Effects::WEAKNESS, 9, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    PINK_TULIP = createBlock<FlowerBlock>("pink_tulip", Effects::WEAKNESS, 9, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
        OXEYE_DAISY = createBlock<FlowerBlock>("oxeye_daisy", Effects::REGENERATION, 8, Properties::create(Materials::PLANTS)
    .doesNotBlockMovement()
    .zeroHardnessAndResistance()
    .setSound(SoundType::PLANT));
    CORNFLOWER = createBlock<FlowerBlock>("cornflower", Effects::JUMP_BOOST, 6, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    WITHER_ROSE = createBlock<WitherRoseBlock>("wither_rose", Effects::WITHER, Properties::create(Materials::PLANTS).doesNotBlockMovement().zeroHardnessAndResistance().setSound(SoundType::PLANT));
    LILY_OF_THE_VALLEY = createBlock<FlowerBlock>("lily_of_the_valley", Effects::POISON, 12, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BROWN_MUSHROOM = createBlock<MushroomBlock>("brown_mushroom", Properties::create(Materials::PLANTS, MaterialColors::BROWN)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT)
        .setLightLevel(getLightValue(1))
        .setNeedsPostProcessing(needsPostProcessing));
    RED_MUSHROOM = createBlock<MushroomBlock>("red_mushroom", Properties::create(Materials::PLANTS, MaterialColors::RED)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT)
        .setNeedsPostProcessing(needsPostProcessing));
    GOLD_BLOCK = createBlock<Block>("gold_block", Properties::create(Materials::IRON, MaterialColors::GOLD)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 6.0F)
        .setSound(SoundType::METAL));
    IRON_BLOCK = createBlock<Block>("iron_block", Properties::create(Materials::IRON, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL));
    BRICKS = createBlock<Block>("bricks", Properties::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    TNT = createBlock<TNTBlock>("tnt", Properties::create(Materials::TNT)
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    BOOKSHELF = createBlock<Block>("bookshelf", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(1.5F)
        .setSound(SoundType::WOOD));
    MOSSY_COBBLESTONE = createBlock<Block>("mossy_cobblestone", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    OBSIDIAN = createBlock<Block>("obsidian", Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F));
    TORCH = createBlock<TorchBlock>("torch", Properties::create(Materials::MISCELLANEOUS).doesNotBlockMovement().zeroHardnessAndResistance().setLightLevel(getLightValue(14)).setSound(SoundType::WOOD), ParticleTypes::FLAME);
    WALL_TORCH = createBlock<WallTorchBlock>("wall_torch", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightValue(14))
        .setSound(SoundType::WOOD)
        .setLootFrom(TORCH), ParticleTypes::FLAME);
    FIRE = createBlock<FireBlock>("fire", Properties::create(Materials::FIRE, MaterialColors::TNT)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightValue(15))
        .setSound(SoundType::CLOTH));
    SOUL_FIRE = createBlock<SoulFireBlock>("soul_fire", Properties::create(Materials::FIRE, MaterialColors::LIGHT_BLUE)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightValue(10))
        .setSound(SoundType::CLOTH));
    SPAWNER = createBlock<SpawnerBlock>("spawner", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::METAL)
        .notSolid());
    OAK_STAIRS = createBlock<StairsBlock>("oak_stairs", OAK_PLANKS->getDefaultState(), Properties::from(OAK_PLANKS));
    CHEST = createBlock<ChestBlock>("chest", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD) /*,
        []() -> {
        return TileEntityType::CHEST;
        }*/
    );
    REDSTONE_WIRE = createBlock<RedstoneWireBlock>("redstone_wire", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DIAMOND_ORE = createBlock<OreBlock>("diamond_ore", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    DIAMOND_BLOCK = createBlock<Block>("diamond_block", Properties::create(Materials::IRON, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL));
    CRAFTING_TABLE = createBlock<CraftingTableBlock>("crafting_table", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    WHEAT = createBlock<CropsBlock>("wheat", Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    FARMLAND = createBlock<FarmlandBlock>("farmland", Properties::create(Materials::EARTH)
        .setTickRandomly()
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::GROUND)
        .setBlocksVision(needsPostProcessing)
        .setSuffocates(needsPostProcessing));
    FURNACE = createBlock<FurnaceBlock>("furnace", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setLightLevel(getLightValueLit(13)));
    OAK_SIGN = createBlock<StandingSignBlock>("oak_sign", Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::OAK);
    SPRUCE_SIGN = createBlock<StandingSignBlock>("spruce_sign", Properties::create(Materials::WOOD, SPRUCE_LOG->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::SPRUCE);
    BIRCH_SIGN = createBlock<StandingSignBlock>("birch_sign", Properties::create(Materials::WOOD, MaterialColors::SAND)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::BIRCH);
    ACACIA_SIGN = createBlock<StandingSignBlock>("acacia_sign", Properties::create(Materials::WOOD, MaterialColors::ADOBE)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::ACACIA);
    JUNGLE_SIGN = createBlock<StandingSignBlock>("jungle_sign", Properties::create(Materials::WOOD, JUNGLE_LOG->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::JUNGLE);
    DARK_OAK_SIGN = createBlock<StandingSignBlock>("dark_oak_sign", Properties::create(Materials::WOOD, DARK_OAK_LOG->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD), WoodType::DARK_OAK);
    OAK_DOOR = createBlock<DoorBlock>("oak_door", Properties::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    LADDER = createBlock<LadderBlock>("ladder", Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::LADDER)
        .notSolid());
    RAIL = createBlock<RailBlock>("rail", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    COBBLESTONE_STAIRS = createBlock<StairsBlock>("cobblestone_stairs", COBBLESTONE->getDefaultState(), Properties::from(COBBLESTONE));
    OAK_WALL_SIGN = createBlock<WallSignBlock>("oak_wall_sign", Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(OAK_SIGN), WoodType::OAK);
    SPRUCE_WALL_SIGN = createBlock<WallSignBlock>("spruce_wall_sign", Properties::create(Materials::WOOD, SPRUCE_LOG->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(SPRUCE_SIGN), WoodType::SPRUCE);
    BIRCH_WALL_SIGN = createBlock<WallSignBlock>("birch_wall_sign", Properties::create(Materials::WOOD, MaterialColors::SAND)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BIRCH_SIGN), WoodType::BIRCH);
    ACACIA_WALL_SIGN = createBlock<WallSignBlock>("acacia_wall_sign", Properties::create(Materials::WOOD, MaterialColors::ADOBE)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(ACACIA_SIGN), WoodType::ACACIA);
    JUNGLE_WALL_SIGN = createBlock<WallSignBlock>("jungle_wall_sign", Properties::create(Materials::WOOD, JUNGLE_LOG->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(JUNGLE_SIGN), WoodType::JUNGLE);
    DARK_OAK_WALL_SIGN = createBlock<WallSignBlock>("dark_oak_wall_sign", Properties::create(Materials::WOOD, DARK_OAK_LOG->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(DARK_OAK_SIGN), WoodType::DARK_OAK);
    LEVER = createBlock<LeverBlock>("lever", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    STONE_PRESSURE_PLATE = createBlock<PressurePlateBlock>("stone_pressure_plate", PressurePlateBlock::Sensitivity::MOBS, Properties::create(Materials::ROCK)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    IRON_DOOR = createBlock<DoorBlock>("iron_door", Properties::create(Materials::IRON, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::METAL)
        .notSolid());
    OAK_PRESSURE_PLATE = createBlock<PressurePlateBlock>("oak_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    SPRUCE_PRESSURE_PLATE = createBlock<PressurePlateBlock>("spruce_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    BIRCH_PRESSURE_PLATE = createBlock<PressurePlateBlock>("birch_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    JUNGLE_PRESSURE_PLATE = createBlock<PressurePlateBlock>("jungle_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    ACACIA_PRESSURE_PLATE = createBlock<PressurePlateBlock>("acacia_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    DARK_OAK_PRESSURE_PLATE = createBlock<PressurePlateBlock>("dark_oak_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    REDSTONE_ORE = createBlock<RedstoneOreBlock>("redstone_ore", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setTickRandomly()
        .setLightLevel(getLightValueLit(9))
        .setHardnessAndResistance(3.0F, 3.0F));
    REDSTONE_TORCH = createBlock<RedstoneTorchBlock>("redstone_torch", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightValueLit(7))
        .setSound(SoundType::WOOD));
    REDSTONE_WALL_TORCH = createBlock<RedstoneWallTorchBlock>("redstone_wall_torch", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightValueLit(7))
        .setSound(SoundType::WOOD)
        .setLootFrom(REDSTONE_TORCH));
    STONE_BUTTON = createBlock<StoneButtonBlock>("stone_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    SNOW = createBlock<SnowBlock>("snow", Properties::create(Materials::SNOW)
        .setTickRandomly()
        .setHardnessAndResistance(0.1F)
        .setRequiresTool()
        .setSound(SoundType::SNOW));
    ICE = createBlock<IceBlock>("ice", Properties::create(Materials::ICE)
        .setSlipperiness(0.98F)
        .setTickRandomly()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GLASS)
        .notSolid()
        .setAllowsSpawn([](BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) -> bool {
            return false;//p_235450_3_ == EntityType.POLAR_BEAR;
        }));
    SNOW_BLOCK = createBlock<Block>("snow_block", Properties::create(Materials::SNOW_BLOCK)
        .setRequiresTool()
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::SNOW));
    CACTUS = createBlock<CactusBlock>("cactus", Properties::create(Materials::CACTUS)
        .setTickRandomly()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::CLOTH));
    CLAY = createBlock<Block>("clay", Properties::create(Materials::CLAY)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::GROUND));
    SUGAR_CANE = createBlock<SugarCaneBlock>("sugar_cane", Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    JUKEBOX = createBlock<JukeboxBlock>("jukebox", Properties::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F, 6.0F));
    OAK_FENCE = createBlock<FenceBlock>("oak_fence", Properties::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    PUMPKIN = createBlock<PumpkinBlock>("pumpkin", Properties::create(Materials::GOURD, MaterialColors::ADOBE)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD));
    NETHERRACK = createBlock<NetherrackBlock>("netherrack", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::NETHERRACK));
    SOUL_SAND = createBlock<SoulSandBlock>("soul_sand", Properties::create(Materials::SAND, MaterialColors::BROWN)
        .setHardnessAndResistance(0.5F)
        .setSpeedFactor(0.4F)
        .setSound(SoundType::SOUL_SAND)
        .setAllowsSpawn(alwaysAllowSpawn)
        .setOpaque(needsPostProcessing)
        .setBlocksVision(needsPostProcessing)
        .setSuffocates(needsPostProcessing));
    SOUL_SOIL = createBlock<Block>("soul_soil", Properties::create(Materials::EARTH, MaterialColors::BROWN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SOUL_SOIL));
    BASALT = createBlock<RotatedPillarBlock>("basalt", Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F)
        .setSound(SoundType::BASALT));
    POLISHED_BASALT = createBlock<RotatedPillarBlock>("polished_basalt", Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F)
        .setSound(SoundType::BASALT));
    SOUL_TORCH = createBlock<TorchBlock>("soul_torch", Properties::create(Materials::MISCELLANEOUS).doesNotBlockMovement().zeroHardnessAndResistance().setLightLevel(getLightValue(10)).setSound(SoundType::WOOD), ParticleTypes::SOUL_FIRE_FLAME);
    SOUL_WALL_TORCH = createBlock<WallTorchBlock>("soul_wall_torch", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLightLevel(getLightValue(10))
        .setSound(SoundType::WOOD)
        .setLootFrom(SOUL_TORCH), ParticleTypes::SOUL_FIRE_FLAME);
    GLOWSTONE = createBlock<Block>("glowstone", Properties::create(Materials::GLASS, MaterialColors::SAND)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .setLightLevel(getLightValue(15)));
    NETHER_PORTAL = createBlock<NetherPortalBlock>("nether_portal", Properties::create(Materials::PORTAL)
        .doesNotBlockMovement()
        .setTickRandomly()
        .setHardnessAndResistance(-1.0F)
        .setSound(SoundType::GLASS)
        .setLightLevel(getLightValue(11)));
    CARVED_PUMPKIN = createBlock<CarvedPumpkinBlock>("carved_pumpkin", Properties::create(Materials::GOURD, MaterialColors::ADOBE)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setAllowsSpawn(alwaysAllowSpawn));
    JACK_O_LANTERN = createBlock<CarvedPumpkinBlock>("jack_o_lantern", Properties::create(Materials::GOURD, MaterialColors::ADOBE)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLightLevel(getLightValue(15))
        .setAllowsSpawn(alwaysAllowSpawn));
    CAKE = createBlock<CakeBlock>("cake", Properties::create(Materials::CAKE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::CLOTH));
    REPEATER = createBlock<RepeaterBlock>("repeater", Properties::create(Materials::MISCELLANEOUS)
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
    OAK_TRAPDOOR = createBlock<TrapDoorBlock>("oak_trapdoor", Properties::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    SPRUCE_TRAPDOOR = createBlock<TrapDoorBlock>("spruce_trapdoor", Properties::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    BIRCH_TRAPDOOR = createBlock<TrapDoorBlock>("birch_trapdoor", Properties::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    JUNGLE_TRAPDOOR = createBlock<TrapDoorBlock>("jungle_trapdoor", Properties::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    ACACIA_TRAPDOOR = createBlock<TrapDoorBlock>("acacia_trapdoor", Properties::create(Materials::WOOD, MaterialColors::ADOBE)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    DARK_OAK_TRAPDOOR = createBlock<TrapDoorBlock>("dark_oak_trapdoor", Properties::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    STONE_BRICKS = createBlock<Block>("stone_bricks", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    MOSSY_STONE_BRICKS = createBlock<Block>("mossy_stone_bricks", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    CRACKED_STONE_BRICKS = createBlock<Block>("cracked_stone_bricks", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    CHISELED_STONE_BRICKS = createBlock<Block>("chiseled_stone_bricks", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    INFESTED_STONE = createBlock<SilverfishBlock>("infested_stone", STONE, Properties::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_COBBLESTONE = createBlock<SilverfishBlock>("infested_cobblestone", COBBLESTONE, Properties::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_STONE_BRICKS = createBlock<SilverfishBlock>("infested_stone_bricks", STONE_BRICKS, Properties::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_MOSSY_STONE_BRICKS = createBlock<SilverfishBlock>("infested_mossy_stone_bricks", MOSSY_STONE_BRICKS, Properties::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_CRACKED_STONE_BRICKS = createBlock<SilverfishBlock>("infested_cracked_stone_bricks", CRACKED_STONE_BRICKS, Properties::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    INFESTED_CHISELED_STONE_BRICKS = createBlock<SilverfishBlock>("infested_chiseled_stone_bricks", CHISELED_STONE_BRICKS, Properties::create(Materials::CLAY)
        .setHardnessAndResistance(0.0F, 0.75F));
    BROWN_MUSHROOM_BLOCK = createBlock<HugeMushroomBlock>("brown_mushroom_block", Properties::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));

    RED_MUSHROOM_BLOCK = createBlock<HugeMushroomBlock>("red_mushroom_block", Properties::create(Materials::WOOD, MaterialColors::RED)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));
    MUSHROOM_STEM = createBlock<HugeMushroomBlock>("mushroom_stem", Properties::create(Materials::WOOD, MaterialColors::WOOL)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));
    IRON_BARS = createBlock<PaneBlock>("iron_bars", Properties::create(Materials::IRON, MaterialColors::AIR)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL)
        .notSolid());
    CHAIN = createBlock<ChainBlock>("chain", Properties::create(Materials::IRON, MaterialColors::AIR)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::CHAIN)
        .notSolid());
    GLASS_PANE = createBlock<PaneBlock>("glass_pane", Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    MELON = createBlock<MelonBlock>("melon", Properties::create(Materials::GOURD, MaterialColors::LIME)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD));
    ATTACHED_PUMPKIN_STEM = createBlock<AttachedStemBlock>("attached_pumpkin_stem", (StemGrownBlock*)PUMPKIN, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WOOD));
    ATTACHED_MELON_STEM = createBlock<AttachedStemBlock>("attached_melon_stem", (StemGrownBlock*)MELON, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WOOD));
    PUMPKIN_STEM = createBlock<StemBlock>("pumpkin_stem", (StemGrownBlock*)PUMPKIN, Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::STEM));
    MELON_STEM = createBlock<StemBlock>("melon_stem", (StemGrownBlock*)MELON, Properties::create(Materials::PLANTS).doesNotBlockMovement().setTickRandomly().zeroHardnessAndResistance().setSound(SoundType::STEM));
    VINE = createBlock<VineBlock>("vine", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::VINE));
    OAK_FENCE_GATE = createBlock<FenceGateBlock>("oak_fence_gate", Properties::create(Materials::WOOD, OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BRICK_STAIRS = createBlock<StairsBlock>("brick_stairs", BRICKS->getDefaultState(), Properties::from(BRICKS));
    STONE_BRICK_STAIRS = createBlock<StairsBlock>("stone_brick_stairs", STONE_BRICKS->getDefaultState(), Properties::from(STONE_BRICKS));
    MYCELIUM = createBlock<MyceliumBlock>("mycelium", Properties::create(Materials::ORGANIC, MaterialColors::PURPLE)
        .setTickRandomly()
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::PLANT));
    LILY_PAD = createBlock<LilyPadBlock>("lily_pad", Properties::create(Materials::PLANTS)
        .zeroHardnessAndResistance()
        .setSound(SoundType::LILY_PADS)
        .notSolid());
    NETHER_BRICKS = createBlock<Block>("nether_bricks", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    NETHER_BRICK_FENCE = createBlock<FenceBlock>("nether_brick_fence", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    NETHER_BRICK_STAIRS = createBlock<StairsBlock>("nether_brick_stairs", NETHER_BRICKS->getDefaultState(), Properties::from(NETHER_BRICKS));
    NETHER_WART = createBlock<NetherWartBlock>("nether_wart", Properties::create(Materials::PLANTS, MaterialColors::RED)
        .doesNotBlockMovement()
        .setTickRandomly()
        .setSound(SoundType::NETHER_WART));
    ENCHANTING_TABLE = createBlock<EnchantingTableBlock>("enchanting_table", Properties::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F));
    BREWING_STAND = createBlock<BrewingStandBlock>("brewing_stand", Properties::create(Materials::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(0.5F)
        .setLightLevel(getLightValue(1))
        .notSolid());
    CAULDRON = createBlock<CauldronBlock>("cauldron", Properties::create(Materials::IRON, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F)
        .notSolid());
    END_PORTAL = createBlock<EndPortalBlock>("end_portal", Properties::create(Materials::PORTAL, MaterialColors::BLACK)
        .doesNotBlockMovement()
        .setLightLevel(getLightValue(15))
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    END_PORTAL_FRAME = createBlock<EndPortalFrameBlock>("end_portal_frame", Properties::create(Materials::ROCK, MaterialColors::GREEN)
        .setSound(SoundType::GLASS)
        .setLightLevel(getLightValue(1))
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    END_STONE = createBlock<Block>("end_stone", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 9.0F));
    DRAGON_EGG = createBlock<DragonEggBlock>("dragon_egg", Properties::create(Materials::DRAGON_EGG, MaterialColors::BLACK)
        .setHardnessAndResistance(3.0F, 9.0F)
        .setLightLevel(getLightValue(1))
        .notSolid());
    REDSTONE_LAMP = createBlock<RedstoneLampBlock>("redstone_lamp", Properties::create(Materials::REDSTONE_LIGHT)
        .setLightLevel(getLightValueLit(15))
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .setAllowsSpawn(alwaysAllowSpawn));
    COCOA = createBlock<CocoaBlock>("cocoa", Properties::create(Materials::PLANTS)
        .setTickRandomly()
        .setHardnessAndResistance(0.2F, 3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    SANDSTONE_STAIRS = createBlock<StairsBlock>("sandstone_stairs", SANDSTONE->getDefaultState(), Properties::from(SANDSTONE));
    EMERALD_ORE = createBlock<OreBlock>("emerald_ore", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F));
    ENDER_CHEST = createBlock<EnderChestBlock>("ender_chest", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(22.5F, 600.0F)
        .setLightLevel(getLightValue(7)));
    TRIPWIRE_HOOK = createBlock<TripWireHookBlock>("tripwire_hook", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement());
    TRIPWIRE = createBlock<TripWireBlock>("tripwire", (TripWireHookBlock *) TRIPWIRE_HOOK, Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement());
    EMERALD_BLOCK = createBlock<Block>("emerald_block", Properties::create(Materials::IRON, MaterialColors::EMERALD)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL));
    SPRUCE_STAIRS = createBlock<StairsBlock>("spruce_stairs", SPRUCE_PLANKS->getDefaultState(), Properties::from(SPRUCE_PLANKS));
    BIRCH_STAIRS = createBlock<StairsBlock>("birch_stairs", BIRCH_PLANKS->getDefaultState(), Properties::from(BIRCH_PLANKS));
    JUNGLE_STAIRS = createBlock<StairsBlock>("jungle_stairs", JUNGLE_PLANKS->getDefaultState(), Properties::from(JUNGLE_PLANKS));
    COMMAND_BLOCK = createBlock<CommandBlockBlock>("command_block", Properties::create(Materials::IRON, MaterialColors::BROWN)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    BEACON = createBlock<BeaconBlock>("beacon", Properties::create(Materials::GLASS, MaterialColors::DIAMOND)
        .setHardnessAndResistance(3.0F)
        .setLightLevel(getLightValue(15))
        .notSolid()
        .setOpaque(isntSolid));
    COBBLESTONE_WALL = createBlock<WallBlock>("cobblestone_wall", Properties::from(COBBLESTONE));
    MOSSY_COBBLESTONE_WALL = createBlock<WallBlock>("mossy_cobblestone_wall", Properties::from(COBBLESTONE));
    FLOWER_POT = createBlock<FlowerPotBlock>("flower_pot", AIR, Properties::create(Materials::MISCELLANEOUS).zeroHardnessAndResistance().notSolid());
    POTTED_OAK_SAPLING = createBlock<FlowerPotBlock>("potted_oak_sapling", OAK_SAPLING, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_SPRUCE_SAPLING = createBlock<FlowerPotBlock>("potted_spruce_sapling", SPRUCE_SAPLING, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_BIRCH_SAPLING = createBlock<FlowerPotBlock>("potted_birch_sapling", BIRCH_SAPLING, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_JUNGLE_SAPLING = createBlock<FlowerPotBlock>("potted_jungle_sapling", JUNGLE_SAPLING, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_ACACIA_SAPLING = createBlock<FlowerPotBlock>("potted_acacia_sapling", ACACIA_SAPLING, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_DARK_OAK_SAPLING = createBlock<FlowerPotBlock>("potted_dark_oak_sapling", DARK_OAK_SAPLING, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_FERN = createBlock<FlowerPotBlock>("potted_fern", FERN, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_DANDELION = createBlock<FlowerPotBlock>("potted_dandelion", DANDELION, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_POPPY = createBlock<FlowerPotBlock>("potted_poppy", POPPY, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_BLUE_ORCHID = createBlock<FlowerPotBlock>("potted_blue_orchid", BLUE_ORCHID, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_ALLIUM = createBlock<FlowerPotBlock>("potted_allium", ALLIUM, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_AZURE_BLUET = createBlock<FlowerPotBlock>("potted_azure_bluet", AZURE_BLUET, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_RED_TULIP = createBlock<FlowerPotBlock>("potted_red_tulip", RED_TULIP, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_ORANGE_TULIP = createBlock<FlowerPotBlock>("potted_orange_tulip", ORANGE_TULIP, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WHITE_TULIP = createBlock<FlowerPotBlock>("potted_white_tulip", WHITE_TULIP, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_PINK_TULIP = createBlock<FlowerPotBlock>("potted_pink_tulip", PINK_TULIP, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_OXEYE_DAISY = createBlock<FlowerPotBlock>("potted_oxeye_daisy", OXEYE_DAISY, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_CORNFLOWER = createBlock<FlowerPotBlock>("potted_cornflower", CORNFLOWER, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_LILY_OF_THE_VALLEY = createBlock<FlowerPotBlock>("potted_lily_of_the_valley", LILY_OF_THE_VALLEY, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WITHER_ROSE = createBlock<FlowerPotBlock>("potted_wither_rose", WITHER_ROSE, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_RED_MUSHROOM = createBlock<FlowerPotBlock>("potted_red_mushroom", RED_MUSHROOM, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_BROWN_MUSHROOM = createBlock<FlowerPotBlock>("potted_brown_mushroom", BROWN_MUSHROOM, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_DEAD_BUSH = createBlock<FlowerPotBlock>("potted_dead_bush", DEAD_BUSH, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_CACTUS = createBlock<FlowerPotBlock>("potted_cactus", CACTUS, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    CARROTS = createBlock<CarrotBlock>("carrots", Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    POTATOES = createBlock<PotatoBlock>("potatoes", Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    OAK_BUTTON = createBlock<WoodButtonBlock>("oak_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    SPRUCE_BUTTON = createBlock<WoodButtonBlock>("spruce_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    BIRCH_BUTTON = createBlock<WoodButtonBlock>("birch_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    JUNGLE_BUTTON = createBlock<WoodButtonBlock>("jungle_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    ACACIA_BUTTON = createBlock<WoodButtonBlock>("acacia_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    DARK_OAK_BUTTON = createBlock<WoodButtonBlock>("dark_oak_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    SKELETON_SKULL = createBlock<SkullBlock>("skeleton_skull", SkullBlock::Type::SKELETON, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F));
    SKELETON_WALL_SKULL = createBlock<WallSkullBlock>("skeleton_wall_skull", SkullBlock::Type::SKELETON, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(SKELETON_SKULL));
    WITHER_SKELETON_SKULL = createBlock<WitherSkeletonSkullBlock>("wither_skeleton_skull", Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F));
    WITHER_SKELETON_WALL_SKULL = createBlock<WitherSkeletonWallSkullBlock>("wither_skeleton_wall_skull", Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(WITHER_SKELETON_SKULL));
    ZOMBIE_HEAD = createBlock<SkullBlock>("zombie_head", SkullBlock::Type::ZOMBIE, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F));
    ZOMBIE_WALL_HEAD = createBlock<WallSkullBlock>("zombie_wall_head", SkullBlock::Type::ZOMBIE, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(ZOMBIE_HEAD));
    PLAYER_HEAD = createBlock<SkullPlayerBlock>("player_head", Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F));
    PLAYER_WALL_HEAD = createBlock<SkullWallPlayerBlock>("player_wall_head", Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(PLAYER_HEAD));
    CREEPER_HEAD = createBlock<SkullBlock>("creeper_head", SkullBlock::Type::CREEPER, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F));
    CREEPER_WALL_HEAD = createBlock<WallSkullBlock>("creeper_wall_head", SkullBlock::Type::CREEPER, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(CREEPER_HEAD));
    DRAGON_HEAD = createBlock<SkullBlock>("dragon_head", SkullBlock::Type::DRAGON, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F));
    DRAGON_WALL_HEAD = createBlock<WallSkullBlock>("dragon_wall_head", SkullBlock::Type::DRAGON, Properties::create(Materials::MISCELLANEOUS)
        .setHardnessAndResistance(1.0F)
        .setLootFrom(DRAGON_HEAD));
    ANVIL = createBlock<AnvilBlock>("anvil", Properties::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F)
        .setSound(SoundType::ANVIL));
    CHIPPED_ANVIL = createBlock<AnvilBlock>("chipped_anvil", Properties::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F)
        .setSound(SoundType::ANVIL));
    DAMAGED_ANVIL = createBlock<AnvilBlock>("damaged_anvil", Properties::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 1200.0F)
        .setSound(SoundType::ANVIL));
    TRAPPED_CHEST = createBlock<TrappedChestBlock>("trapped_chest", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    LIGHT_WEIGHTED_PRESSURE_PLATE = createBlock<WeightedPressurePlateBlock>("light_weighted_pressure_plate", 15, Properties::create(Materials::IRON, MaterialColors::GOLD)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    HEAVY_WEIGHTED_PRESSURE_PLATE = createBlock<WeightedPressurePlateBlock>("heavy_weighted_pressure_plate", 150, Properties::create(Materials::IRON)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    COMPARATOR = createBlock<ComparatorBlock>("comparator", Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .setSound(SoundType::WOOD));
    DAYLIGHT_DETECTOR = createBlock<DaylightDetectorBlock>("daylight_detector", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(0.2F)
        .setSound(SoundType::WOOD));
    REDSTONE_BLOCK = createBlock<RedstoneBlock>("redstone_block", Properties::create(Materials::IRON, MaterialColors::TNT)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F)
        .setSound(SoundType::METAL)
        .setOpaque(isntSolid));
    NETHER_QUARTZ_ORE = createBlock<OreBlock>("nether_quartz_ore", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 3.0F)
        .setSound(SoundType::NETHER_ORE));
    HOPPER = createBlock<HopperBlock>("hopper", Properties::create(Materials::IRON, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 4.8F)
        .setSound(SoundType::METAL)
        .notSolid());
    QUARTZ_BLOCK = createBlock<Block>("quartz_block", Properties::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CHISELED_QUARTZ_BLOCK = createBlock<Block>("chiseled_quartz_block", Properties::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    QUARTZ_PILLAR = createBlock<RotatedPillarBlock>("quartz_pillar", Properties::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    QUARTZ_STAIRS = createBlock<StairsBlock>("quartz_stairs", QUARTZ_BLOCK->getDefaultState(), Properties::from(QUARTZ_BLOCK));
    ACTIVATOR_RAIL = createBlock<PoweredRailBlock>("activator_rail", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.7F)
        .setSound(SoundType::METAL));
    DROPPER = createBlock<DropperBlock>("dropper", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F));
    WHITE_TERRACOTTA = createBlock<Block>("white_terracotta", Properties::create(Materials::ROCK, MaterialColors::WHITE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    ORANGE_TERRACOTTA = createBlock<Block>("orange_terracotta", Properties::create(Materials::ROCK, MaterialColors::ORANGE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    MAGENTA_TERRACOTTA = createBlock<Block>("magenta_terracotta", Properties::create(Materials::ROCK, MaterialColors::MAGENTA_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    LIGHT_BLUE_TERRACOTTA = createBlock<Block>("light_blue_terracotta", Properties::create(Materials::ROCK, MaterialColors::LIGHT_BLUE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    YELLOW_TERRACOTTA = createBlock<Block>("yellow_terracotta", Properties::create(Materials::ROCK, MaterialColors::YELLOW_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    LIME_TERRACOTTA = createBlock<Block>("lime_terracotta", Properties::create(Materials::ROCK, MaterialColors::LIME_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    PINK_TERRACOTTA = createBlock<Block>("pink_terracotta", Properties::create(Materials::ROCK, MaterialColors::PINK_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    GRAY_TERRACOTTA = createBlock<Block>("gray_terracotta", Properties::create(Materials::ROCK, MaterialColors::GRAY_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    LIGHT_GRAY_TERRACOTTA = createBlock<Block>("light_gray_terracotta", Properties::create(Materials::ROCK, MaterialColors::LIGHT_GRAY_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    CYAN_TERRACOTTA = createBlock<Block>("cyan_terracotta", Properties::create(Materials::ROCK, MaterialColors::CYAN_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    PURPLE_TERRACOTTA = createBlock<Block>("purple_terracotta", Properties::create(Materials::ROCK, MaterialColors::PURPLE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    BLUE_TERRACOTTA = createBlock<Block>("blue_terracotta", Properties::create(Materials::ROCK, MaterialColors::BLUE_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    BROWN_TERRACOTTA = createBlock<Block>("brown_terracotta", Properties::create(Materials::ROCK, MaterialColors::BROWN_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    GREEN_TERRACOTTA = createBlock<Block>("green_terracotta", Properties::create(Materials::ROCK, MaterialColors::GREEN_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    RED_TERRACOTTA = createBlock<Block>("red_terracotta", Properties::create(Materials::ROCK, MaterialColors::RED_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    BLACK_TERRACOTTA = createBlock<Block>("black_terracotta", Properties::create(Materials::ROCK, MaterialColors::BLACK_TERRACOTTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    WHITE_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("white_stained_glass_pane", DyeColors::WHITE, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    ORANGE_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("orange_stained_glass_pane", DyeColors::ORANGE, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    MAGENTA_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("magenta_stained_glass_pane", DyeColors::MAGENTA, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    LIGHT_BLUE_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("light_blue_stained_glass_pane", DyeColors::LIGHT_BLUE, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    YELLOW_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("yellow_stained_glass_pane", DyeColors::YELLOW, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    LIME_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("lime_stained_glass_pane", DyeColors::LIME, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    PINK_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("pink_stained_glass_pane", DyeColors::PINK, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    GRAY_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("gray_stained_glass_pane", DyeColors::GRAY, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    LIGHT_GRAY_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("light_gray_stained_glass_pane", DyeColors::LIGHT_GRAY, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    CYAN_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("cyan_stained_glass_pane", DyeColors::CYAN, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    PURPLE_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("purple_stained_glass_pane", DyeColors::PURPLE, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    BLUE_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("blue_stained_glass_pane", DyeColors::BLUE, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    BROWN_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("brown_stained_glass_pane", DyeColors::BROWN, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    GREEN_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("green_stained_glass_pane", DyeColors::GREEN, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    RED_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("red_stained_glass_pane", DyeColors::RED, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    BLACK_STAINED_GLASS_PANE = createBlock<StainedGlassPaneBlock>("black_stained_glass_pane", DyeColors::BLACK, Properties::create(Materials::GLASS)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .notSolid());
    ACACIA_STAIRS = createBlock<StairsBlock>("acacia_stairs", ACACIA_PLANKS->getDefaultState(), Properties::from(ACACIA_PLANKS));
    DARK_OAK_STAIRS = createBlock<StairsBlock>("dark_oak_stairs", DARK_OAK_PLANKS->getDefaultState(), Properties::from(DARK_OAK_PLANKS));
    SLIME_BLOCK = createBlock<SlimeBlock>("slime_block", Properties::create(Materials::CLAY, MaterialColors::GRASS)
        .setSlipperiness(0.8F)
        .setSound(SoundType::SLIME)
        .notSolid());
    BARRIER = createBlock<BarrierBlock>("barrier", Properties::create(Materials::BARRIER)
        .setHardnessAndResistance(-1.0F, 3600000.8F)
        .noDrops()
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    IRON_TRAPDOOR = createBlock<TrapDoorBlock>("iron_trapdoor", Properties::create(Materials::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::METAL)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    PRISMARINE = createBlock<Block>("prismarine", Properties::create(Materials::ROCK, MaterialColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PRISMARINE_BRICKS = createBlock<Block>("prismarine_bricks", Properties::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DARK_PRISMARINE = createBlock<Block>("dark_prismarine", Properties::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PRISMARINE_STAIRS = createBlock<StairsBlock>("prismarine_stairs", PRISMARINE->getDefaultState(), Properties::from(PRISMARINE));
    PRISMARINE_BRICK_STAIRS = createBlock<StairsBlock>("prismarine_brick_stairs", PRISMARINE_BRICKS->getDefaultState(), Properties::from(PRISMARINE_BRICKS));
    DARK_PRISMARINE_STAIRS = createBlock<StairsBlock>("dark_prismarine_stairs", DARK_PRISMARINE->getDefaultState(), Properties::from(DARK_PRISMARINE));
    PRISMARINE_SLAB = createBlock<SlabBlock>("prismarine_slab", Properties::create(Materials::ROCK, MaterialColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PRISMARINE_BRICK_SLAB = createBlock<SlabBlock>("prismarine_brick_slab", Properties::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DARK_PRISMARINE_SLAB = createBlock<SlabBlock>("dark_prismarine_slab", Properties::create(Materials::ROCK, MaterialColors::DIAMOND)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    SEA_LANTERN = createBlock<Block>("sea_lantern", Properties::create(Materials::GLASS, MaterialColors::QUARTZ)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::GLASS)
        .setLightLevel(getLightValue(15)));
    HAY_BLOCK = createBlock<HayBlock>("hay_block", Properties::create(Materials::ORGANIC, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::PLANT));
    WHITE_CARPET = createBlock<CarpetBlock>("white_carpet", DyeColors::WHITE, Properties::create(Materials::CARPET, MaterialColors::SNOW)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    ORANGE_CARPET = createBlock<CarpetBlock>("orange_carpet", DyeColors::ORANGE, Properties::create(Materials::CARPET, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    MAGENTA_CARPET = createBlock<CarpetBlock>("magenta_carpet", DyeColors::MAGENTA, Properties::create(Materials::CARPET, MaterialColors::MAGENTA)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    LIGHT_BLUE_CARPET = createBlock<CarpetBlock>("light_blue_carpet", DyeColors::LIGHT_BLUE, Properties::create(Materials::CARPET, MaterialColors::LIGHT_BLUE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    YELLOW_CARPET = createBlock<CarpetBlock>("yellow_carpet", DyeColors::YELLOW, Properties::create(Materials::CARPET, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    LIME_CARPET = createBlock<CarpetBlock>("lime_carpet", DyeColors::LIME, Properties::create(Materials::CARPET, MaterialColors::LIME)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    PINK_CARPET = createBlock<CarpetBlock>("pink_carpet", DyeColors::PINK, Properties::create(Materials::CARPET, MaterialColors::PINK)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    GRAY_CARPET = createBlock<CarpetBlock>("gray_carpet", DyeColors::GRAY, Properties::create(Materials::CARPET, MaterialColors::GRAY)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    LIGHT_GRAY_CARPET = createBlock<CarpetBlock>("light_gray_carpet", DyeColors::LIGHT_GRAY, Properties::create(Materials::CARPET, MaterialColors::LIGHT_GRAY)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    CYAN_CARPET = createBlock<CarpetBlock>("cyan_carpet", DyeColors::CYAN, Properties::create(Materials::CARPET, MaterialColors::CYAN)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    PURPLE_CARPET = createBlock<CarpetBlock>("purple_carpet", DyeColors::PURPLE, Properties::create(Materials::CARPET, MaterialColors::PURPLE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    BLUE_CARPET = createBlock<CarpetBlock>("blue_carpet", DyeColors::BLUE, Properties::create(Materials::CARPET, MaterialColors::BLUE)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    BROWN_CARPET = createBlock<CarpetBlock>("brown_carpet", DyeColors::BROWN, Properties::create(Materials::CARPET, MaterialColors::BROWN)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    GREEN_CARPET = createBlock<CarpetBlock>("green_carpet", DyeColors::GREEN, Properties::create(Materials::CARPET, MaterialColors::GREEN)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    RED_CARPET = createBlock<CarpetBlock>("red_carpet", DyeColors::RED, Properties::create(Materials::CARPET, MaterialColors::RED)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    BLACK_CARPET = createBlock<CarpetBlock>("black_carpet", DyeColors::BLACK, Properties::create(Materials::CARPET, MaterialColors::BLACK)
        .setHardnessAndResistance(0.1F)
        .setSound(SoundType::CLOTH));
    TERRACOTTA = createBlock<Block>("terracotta", Properties::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(1.25F, 4.2F));
    COAL_BLOCK = createBlock<Block>("coal_block", Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F, 6.0F));
    PACKED_ICE = createBlock<Block>("packed_ice", Properties::create(Materials::PACKED_ICE)
        .setSlipperiness(0.98F)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GLASS));
    SUNFLOWER = createBlock<TallFlowerBlock>("sunflower", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    LILAC = createBlock<TallFlowerBlock>("lilac", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    ROSE_BUSH = createBlock<TallFlowerBlock>("rose_bush", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    PEONY = createBlock<TallFlowerBlock>("peony", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    TALL_GRASS = createBlock<DoublePlantBlock>("tall_grass", Properties::create(Materials::TALL_PLANTS)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::PLANT));
    LARGE_FERN = createBlock<DoublePlantBlock>("large_fern", Properties::create(Materials::TALL_PLANTS)
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
    WHITE_WALL_BANNER = createBlock<WallBannerBlock>("white_wall_banner", DyeColors::WHITE, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(WHITE_BANNER));
    ORANGE_WALL_BANNER = createBlock<WallBannerBlock>("orange_wall_banner", DyeColors::ORANGE, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(ORANGE_BANNER));
    MAGENTA_WALL_BANNER = createBlock<WallBannerBlock>("magenta_wall_banner", DyeColors::MAGENTA, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(MAGENTA_BANNER));
    LIGHT_BLUE_WALL_BANNER = createBlock<WallBannerBlock>("light_blue_wall_banner", DyeColors::LIGHT_BLUE, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(LIGHT_BLUE_BANNER));
    YELLOW_WALL_BANNER = createBlock<WallBannerBlock>("yellow_wall_banner", DyeColors::YELLOW, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(YELLOW_BANNER));
    LIME_WALL_BANNER = createBlock<WallBannerBlock>("lime_wall_banner", DyeColors::LIME, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(LIME_BANNER));
    PINK_WALL_BANNER = createBlock<WallBannerBlock>("pink_wall_banner", DyeColors::PINK, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(PINK_BANNER));
    GRAY_WALL_BANNER = createBlock<WallBannerBlock>("gray_wall_banner", DyeColors::GRAY, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(GRAY_BANNER));
    LIGHT_GRAY_WALL_BANNER = createBlock<WallBannerBlock>("light_gray_wall_banner", DyeColors::LIGHT_GRAY, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(LIGHT_GRAY_BANNER));
    CYAN_WALL_BANNER = createBlock<WallBannerBlock>("cyan_wall_banner", DyeColors::CYAN, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(CYAN_BANNER));
    PURPLE_WALL_BANNER = createBlock<WallBannerBlock>("purple_wall_banner", DyeColors::PURPLE, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(PURPLE_BANNER));
    BLUE_WALL_BANNER = createBlock<WallBannerBlock>("blue_wall_banner", DyeColors::BLUE, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BLUE_BANNER));
    BROWN_WALL_BANNER = createBlock<WallBannerBlock>("brown_wall_banner", DyeColors::BROWN, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BROWN_BANNER));
    GREEN_WALL_BANNER = createBlock<WallBannerBlock>("green_wall_banner", DyeColors::GREEN, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(GREEN_BANNER));
    RED_WALL_BANNER = createBlock<WallBannerBlock>("red_wall_banner", DyeColors::RED, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(RED_BANNER));
    BLACK_WALL_BANNER = createBlock<WallBannerBlock>("black_wall_banner", DyeColors::BLACK, Properties::create(Materials::WOOD)
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WOOD)
        .setLootFrom(BLACK_BANNER));
    RED_SANDSTONE = createBlock<Block>("red_sandstone", Properties::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CHISELED_RED_SANDSTONE = createBlock<Block>("chiseled_red_sandstone", Properties::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    CUT_RED_SANDSTONE = createBlock<Block>("cut_red_sandstone", Properties::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(0.8F));
    RED_SANDSTONE_STAIRS = createBlock<StairsBlock>("red_sandstone_stairs", RED_SANDSTONE->getDefaultState(), Properties::from(RED_SANDSTONE));
    OAK_SLAB = createBlock<SlabBlock>("oak_slab", Properties::create(Materials::WOOD, MaterialColors::WOOD)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_SLAB = createBlock<SlabBlock>("spruce_slab", Properties::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_SLAB = createBlock<SlabBlock>("birch_slab", Properties::create(Materials::WOOD, MaterialColors::SAND)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_SLAB = createBlock<SlabBlock>("jungle_slab", Properties::create(Materials::WOOD, MaterialColors::DIRT)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_SLAB = createBlock<SlabBlock>("acacia_slab", Properties::create(Materials::WOOD, MaterialColors::ADOBE)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_SLAB = createBlock<SlabBlock>("dark_oak_slab", Properties::create(Materials::WOOD, MaterialColors::BROWN)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    STONE_SLAB = createBlock<SlabBlock>("stone_slab", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_STONE_SLAB = createBlock<SlabBlock>("smooth_stone_slab", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SANDSTONE_SLAB = createBlock<SlabBlock>("sandstone_slab", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    CUT_SANDSTONE_SLAB = createBlock<SlabBlock>("cut_sandstone_slab", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    PETRIFIED_OAK_SLAB = createBlock<SlabBlock>("petrified_oak_slab", Properties::create(Materials::ROCK, MaterialColors::WOOD)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    COBBLESTONE_SLAB = createBlock<SlabBlock>("cobblestone_slab", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    BRICK_SLAB = createBlock<SlabBlock>("brick_slab", Properties::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    STONE_BRICK_SLAB = createBlock<SlabBlock>("stone_brick_slab", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    NETHER_BRICK_SLAB = createBlock<SlabBlock>("nether_brick_slab", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    QUARTZ_SLAB = createBlock<SlabBlock>("quartz_slab", Properties::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    RED_SANDSTONE_SLAB = createBlock<SlabBlock>("red_sandstone_slab", Properties::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    CUT_RED_SANDSTONE_SLAB = createBlock<SlabBlock>("cut_red_sandstone_slab", Properties::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    PURPUR_SLAB = createBlock<SlabBlock>("purpur_slab", Properties::create(Materials::ROCK, MaterialColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_STONE = createBlock<Block>("smooth_stone", Properties::create(Materials::ROCK, MaterialColors::STONE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_SANDSTONE = createBlock<Block>("smooth_sandstone", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_QUARTZ = createBlock<Block>("smooth_quartz", Properties::create(Materials::ROCK, MaterialColors::QUARTZ)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SMOOTH_RED_SANDSTONE = createBlock<Block>("smooth_red_sandstone", Properties::create(Materials::ROCK, MaterialColors::ADOBE)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F));
    SPRUCE_FENCE_GATE = createBlock<FenceGateBlock>("spruce_fence_gate", Properties::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_FENCE_GATE = createBlock<FenceGateBlock>("birch_fence_gate", Properties::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_FENCE_GATE = createBlock<FenceGateBlock>("jungle_fence_gate", Properties::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_FENCE_GATE = createBlock<FenceGateBlock>("acacia_fence_gate", Properties::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_FENCE_GATE = createBlock<FenceGateBlock>("dark_oak_fence_gate", Properties::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_FENCE = createBlock<FenceBlock>("spruce_fence", Properties::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    BIRCH_FENCE = createBlock<FenceBlock>("birch_fence", Properties::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    JUNGLE_FENCE = createBlock<FenceBlock>("jungle_fence", Properties::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    ACACIA_FENCE = createBlock<FenceBlock>("acacia_fence", Properties::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    DARK_OAK_FENCE = createBlock<FenceBlock>("dark_oak_fence", Properties::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    SPRUCE_DOOR = createBlock<DoorBlock>("spruce_door", Properties::create(Materials::WOOD, SPRUCE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    BIRCH_DOOR = createBlock<DoorBlock>("birch_door", Properties::create(Materials::WOOD, BIRCH_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    JUNGLE_DOOR = createBlock<DoorBlock>("jungle_door", Properties::create(Materials::WOOD, JUNGLE_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    ACACIA_DOOR = createBlock<DoorBlock>("acacia_door", Properties::create(Materials::WOOD, ACACIA_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    DARK_OAK_DOOR = createBlock<DoorBlock>("dark_oak_door", Properties::create(Materials::WOOD, DARK_OAK_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    END_ROD = createBlock<EndRodBlock>("end_rod", Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .setLightLevel(getLightValue(14))
        .setSound(SoundType::WOOD)
        .notSolid());
    CHORUS_PLANT = createBlock<ChorusPlantBlock>("chorus_plant", Properties::create(Materials::PLANTS, MaterialColors::PURPLE)
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::WOOD)
        .notSolid());
    CHORUS_FLOWER = createBlock<ChorusFlowerBlock>("chorus_flower", (ChorusPlantBlock *) CHORUS_PLANT, Properties::create(Materials::PLANTS, MaterialColors::PURPLE)
        .setTickRandomly()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::WOOD)
        .notSolid());
    PURPUR_BLOCK = createBlock<Block>("purpur_block", Properties::create(Materials::ROCK, MaterialColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PURPUR_PILLAR = createBlock<RotatedPillarBlock>("purpur_pillar", Properties::create(Materials::ROCK, MaterialColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    PURPUR_STAIRS = createBlock<StairsBlock>("purpur_stairs", PURPUR_BLOCK->getDefaultState(), Properties::from(PURPUR_BLOCK));
    END_STONE_BRICKS = createBlock<Block>("end_stone_bricks", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(3.0F, 9.0F));
    BEETROOTS = createBlock<BeetrootBlock>("beetroots", Properties::create(Materials::PLANTS)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::CROP));
    GRASS_PATH = createBlock<GrassPathBlock>("grass_path", Properties::create(Materials::EARTH)
        .setHardnessAndResistance(0.65F)
        .setSound(SoundType::PLANT)
        .setBlocksVision(needsPostProcessing)
        .setSuffocates(needsPostProcessing));
    END_GATEWAY = createBlock<EndGatewayBlock>("end_gateway", Properties::create(Materials::PORTAL, MaterialColors::BLACK)
        .doesNotBlockMovement()
        .setLightLevel(getLightValue(15))
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    REPEATING_COMMAND_BLOCK = createBlock<CommandBlockBlock>("repeating_command_block", Properties::create(Materials::IRON, MaterialColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    CHAIN_COMMAND_BLOCK = createBlock<CommandBlockBlock>("chain_command_block", Properties::create(Materials::IRON, MaterialColors::GREEN)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    FROSTED_ICE = createBlock<FrostedIceBlock>("frosted_ice", Properties::create(Materials::ICE)
        .setSlipperiness(0.98F)
        .setTickRandomly()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::GLASS)
        .notSolid()
        .setAllowsSpawn([](BlockReader &reader, const BlockData &data, const BlockPos &pos, const EntityType &type) -> bool {
            return false;//p_235448_3_ == EntityType.POLAR_BEAR;
        }));
    MAGMA_BLOCK = createBlock<MagmaBlock>("magma_block", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setLightLevel(getLightValue(3))
        .setTickRandomly()
        .setHardnessAndResistance(0.5F)
        .setAllowsSpawn(allowsSpawnImmuneToFire)
        .setNeedsPostProcessing(needsPostProcessing)
        .setEmmisiveRendering(needsPostProcessing));
    NETHER_WART_BLOCK = createBlock<Block>("nether_wart_block", Properties::create(Materials::ORGANIC, MaterialColors::RED)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WART));
    RED_NETHER_BRICKS = createBlock<Block>("red_nether_bricks", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    BONE_BLOCK = createBlock<RotatedPillarBlock>("bone_block", Properties::create(Materials::ROCK, MaterialColors::SAND)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::BONE));
    STRUCTURE_VOID = createBlock<StructureVoidBlock>("structure_void", Properties::create(Materials::STRUCTURE_VOID)
        .doesNotBlockMovement()
        .noDrops());
    OBSERVER = createBlock<ObserverBlock>("observer", Properties::create(Materials::ROCK)
        .setHardnessAndResistance(3.0F)
        .setRequiresTool()
        .setOpaque(isntSolid));
    SHULKER_BOX = createShulkerBox("shulker_box", std::nullopt, Properties::create(Materials::SHULKER));
    WHITE_SHULKER_BOX = createShulkerBox("white_shulker_box", DyeColors::WHITE, Properties::create(Materials::SHULKER, MaterialColors::SNOW));
    ORANGE_SHULKER_BOX = createShulkerBox("orange_shulker_box", DyeColors::ORANGE, Properties::create(Materials::SHULKER, MaterialColors::ADOBE));
    MAGENTA_SHULKER_BOX = createShulkerBox("magenta_shulker_box", DyeColors::MAGENTA, Properties::create(Materials::SHULKER, MaterialColors::MAGENTA));
    LIGHT_BLUE_SHULKER_BOX = createShulkerBox("light_blue_shulker_box", DyeColors::LIGHT_BLUE, Properties::create(Materials::SHULKER, MaterialColors::LIGHT_BLUE));
    YELLOW_SHULKER_BOX = createShulkerBox("yellow_shulker_box", DyeColors::YELLOW, Properties::create(Materials::SHULKER, MaterialColors::YELLOW));
    LIME_SHULKER_BOX = createShulkerBox("lime_shulker_box", DyeColors::LIME, Properties::create(Materials::SHULKER, MaterialColors::LIME));
    PINK_SHULKER_BOX = createShulkerBox("pink_shulker_box", DyeColors::PINK, Properties::create(Materials::SHULKER, MaterialColors::PINK));
    GRAY_SHULKER_BOX = createShulkerBox("gray_shulker_box", DyeColors::GRAY, Properties::create(Materials::SHULKER, MaterialColors::GRAY));
    LIGHT_GRAY_SHULKER_BOX = createShulkerBox("light_gray_shulker_box", DyeColors::LIGHT_GRAY, Properties::create(Materials::SHULKER, MaterialColors::LIGHT_GRAY));
    CYAN_SHULKER_BOX = createShulkerBox("cyan_shulker_box", DyeColors::CYAN, Properties::create(Materials::SHULKER, MaterialColors::CYAN));
    PURPLE_SHULKER_BOX = createShulkerBox("purple_shulker_box", DyeColors::PURPLE, Properties::create(Materials::SHULKER, MaterialColors::PURPLE_TERRACOTTA));
    BLUE_SHULKER_BOX = createShulkerBox("blue_shulker_box", DyeColors::BLUE, Properties::create(Materials::SHULKER, MaterialColors::BLUE));
    BROWN_SHULKER_BOX = createShulkerBox("brown_shulker_box", DyeColors::BROWN, Properties::create(Materials::SHULKER, MaterialColors::BROWN));
    GREEN_SHULKER_BOX = createShulkerBox("green_shulker_box", DyeColors::GREEN, Properties::create(Materials::SHULKER, MaterialColors::GREEN));
    RED_SHULKER_BOX = createShulkerBox("red_shulker_box", DyeColors::RED, Properties::create(Materials::SHULKER, MaterialColors::RED));
    BLACK_SHULKER_BOX = createShulkerBox("black_shulker_box", DyeColors::BLACK, Properties::create(Materials::SHULKER, MaterialColors::BLACK));
    WHITE_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("white_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::WHITE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    ORANGE_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("orange_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::ORANGE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    MAGENTA_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("magenta_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    LIGHT_BLUE_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("light_blue_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::LIGHT_BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    YELLOW_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("yellow_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::YELLOW)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    LIME_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("lime_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::LIME)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    PINK_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("pink_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::PINK)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    GRAY_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("gray_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    LIGHT_GRAY_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("light_gray_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    CYAN_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("cyan_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    PURPLE_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("purple_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    BLUE_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("blue_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    BROWN_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("brown_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::BROWN)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    GREEN_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("green_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::GREEN)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    RED_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("red_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    BLACK_GLAZED_TERRACOTTA = createBlock<GlazedTerracottaBlock>("black_glazed_terracotta", Properties::create(Materials::ROCK, DyeColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.4F));
    WHITE_CONCRETE = createBlock<Block>("white_concrete", Properties::create(Materials::ROCK, DyeColors::WHITE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    ORANGE_CONCRETE = createBlock<Block>("orange_concrete", Properties::create(Materials::ROCK, DyeColors::ORANGE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    MAGENTA_CONCRETE = createBlock<Block>("magenta_concrete", Properties::create(Materials::ROCK, DyeColors::MAGENTA)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    LIGHT_BLUE_CONCRETE = createBlock<Block>("light_blue_concrete", Properties::create(Materials::ROCK, DyeColors::LIGHT_BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    YELLOW_CONCRETE = createBlock<Block>("yellow_concrete", Properties::create(Materials::ROCK, DyeColors::YELLOW)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    LIME_CONCRETE = createBlock<Block>("lime_concrete", Properties::create(Materials::ROCK, DyeColors::LIME)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    PINK_CONCRETE = createBlock<Block>("pink_concrete", Properties::create(Materials::ROCK, DyeColors::PINK)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    GRAY_CONCRETE = createBlock<Block>("gray_concrete", Properties::create(Materials::ROCK, DyeColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    LIGHT_GRAY_CONCRETE = createBlock<Block>("light_gray_concrete", Properties::create(Materials::ROCK, DyeColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    CYAN_CONCRETE = createBlock<Block>("cyan_concrete", Properties::create(Materials::ROCK, DyeColors::CYAN)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    PURPLE_CONCRETE = createBlock<Block>("purple_concrete", Properties::create(Materials::ROCK, DyeColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    BLUE_CONCRETE = createBlock<Block>("blue_concrete", Properties::create(Materials::ROCK, DyeColors::BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    BROWN_CONCRETE = createBlock<Block>("brown_concrete", Properties::create(Materials::ROCK, DyeColors::BROWN)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    GREEN_CONCRETE = createBlock<Block>("green_concrete", Properties::create(Materials::ROCK, DyeColors::GREEN)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    RED_CONCRETE = createBlock<Block>("red_concrete", Properties::create(Materials::ROCK, DyeColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    BLACK_CONCRETE = createBlock<Block>("black_concrete", Properties::create(Materials::ROCK, DyeColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.8F));
    WHITE_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("white_concrete_powder", WHITE_CONCRETE, Properties::create(Materials::SAND, DyeColors::WHITE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    ORANGE_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("orange_concrete_powder", ORANGE_CONCRETE, Properties::create(Materials::SAND, DyeColors::ORANGE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    MAGENTA_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("magenta_concrete_powder", MAGENTA_CONCRETE, Properties::create(Materials::SAND, DyeColors::MAGENTA)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    LIGHT_BLUE_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("light_blue_concrete_powder", LIGHT_BLUE_CONCRETE, Properties::create(Materials::SAND, DyeColors::LIGHT_BLUE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    YELLOW_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("yellow_concrete_powder", YELLOW_CONCRETE, Properties::create(Materials::SAND, DyeColors::YELLOW)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    LIME_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("lime_concrete_powder", LIME_CONCRETE, Properties::create(Materials::SAND, DyeColors::LIME)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    PINK_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("pink_concrete_powder", PINK_CONCRETE, Properties::create(Materials::SAND, DyeColors::PINK)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    GRAY_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("gray_concrete_powder", GRAY_CONCRETE, Properties::create(Materials::SAND, DyeColors::GRAY)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    LIGHT_GRAY_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("light_gray_concrete_powder", LIGHT_GRAY_CONCRETE, Properties::create(Materials::SAND, DyeColors::LIGHT_GRAY)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    CYAN_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("cyan_concrete_powder", CYAN_CONCRETE, Properties::create(Materials::SAND, DyeColors::CYAN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    PURPLE_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("purple_concrete_powder", PURPLE_CONCRETE, Properties::create(Materials::SAND, DyeColors::PURPLE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    BLUE_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("blue_concrete_powder", BLUE_CONCRETE, Properties::create(Materials::SAND, DyeColors::BLUE)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    BROWN_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("brown_concrete_powder", BROWN_CONCRETE, Properties::create(Materials::SAND, DyeColors::BROWN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    GREEN_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("green_concrete_powder", GREEN_CONCRETE, Properties::create(Materials::SAND, DyeColors::GREEN)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    RED_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("red_concrete_powder", RED_CONCRETE, Properties::create(Materials::SAND, DyeColors::RED)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    BLACK_CONCRETE_POWDER = createBlock<ConcretePowderBlock>("black_concrete_powder", BLACK_CONCRETE, Properties::create(Materials::SAND, DyeColors::BLACK)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::SAND));
    KELP = createBlock<KelpTopBlock>("kelp", Properties::create(Materials::OCEAN_PLANT)
        .doesNotBlockMovement()
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    KELP_PLANT = createBlock<KelpBlock>("kelp_plant", Properties::create(Materials::OCEAN_PLANT)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    DRIED_KELP_BLOCK = createBlock<Block>("dried_kelp_block", Properties::create(Materials::ORGANIC, MaterialColors::GREEN)
        .setHardnessAndResistance(0.5F, 2.5F)
        .setSound(SoundType::PLANT));
    TURTLE_EGG = createBlock<TurtleEggBlock>("turtle_egg", Properties::create(Materials::DRAGON_EGG, MaterialColors::SAND)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::METAL)
        .setTickRandomly()
        .notSolid());
    DEAD_TUBE_CORAL_BLOCK = createBlock<Block>("dead_tube_coral_block", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_BRAIN_CORAL_BLOCK = createBlock<Block>("dead_brain_coral_block", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_BUBBLE_CORAL_BLOCK = createBlock<Block>("dead_bubble_coral_block", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_FIRE_CORAL_BLOCK = createBlock<Block>("dead_fire_coral_block", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    DEAD_HORN_CORAL_BLOCK = createBlock<Block>("dead_horn_coral_block", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    TUBE_CORAL_BLOCK = createBlock<CoralBlock>("tube_coral_block", DEAD_TUBE_CORAL_BLOCK, Properties::create(Materials::ROCK, MaterialColors::BLUE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    BRAIN_CORAL_BLOCK = createBlock<CoralBlock>("brain_coral_block", DEAD_BRAIN_CORAL_BLOCK, Properties::create(Materials::ROCK, MaterialColors::PINK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    BUBBLE_CORAL_BLOCK = createBlock<CoralBlock>("bubble_coral_block", DEAD_BUBBLE_CORAL_BLOCK, Properties::create(Materials::ROCK, MaterialColors::PURPLE)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    FIRE_CORAL_BLOCK = createBlock<CoralBlock>("fire_coral_block", DEAD_FIRE_CORAL_BLOCK, Properties::create(Materials::ROCK, MaterialColors::RED)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    HORN_CORAL_BLOCK = createBlock<CoralBlock>("horn_coral_block", DEAD_HORN_CORAL_BLOCK, Properties::create(Materials::ROCK, MaterialColors::YELLOW)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F)
        .setSound(SoundType::CORAL));
    DEAD_TUBE_CORAL = createBlock<DeadCoralPlantBlock>("dead_tube_coral", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BRAIN_CORAL = createBlock<DeadCoralPlantBlock>("dead_brain_coral", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BUBBLE_CORAL = createBlock<DeadCoralPlantBlock>("dead_bubble_coral", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_FIRE_CORAL = createBlock<DeadCoralPlantBlock>("dead_fire_coral", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_HORN_CORAL = createBlock<DeadCoralPlantBlock>("dead_horn_coral", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    TUBE_CORAL = createBlock<CoralPlantBlock>("tube_coral", DEAD_TUBE_CORAL, Properties::create(Materials::OCEAN_PLANT, MaterialColors::BLUE)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BRAIN_CORAL = createBlock<CoralPlantBlock>("brain_coral", DEAD_BRAIN_CORAL, Properties::create(Materials::OCEAN_PLANT, MaterialColors::PINK)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BUBBLE_CORAL = createBlock<CoralPlantBlock>("bubble_coral", DEAD_BUBBLE_CORAL, Properties::create(Materials::OCEAN_PLANT, MaterialColors::PURPLE)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    FIRE_CORAL = createBlock<CoralPlantBlock>("fire_coral", DEAD_FIRE_CORAL, Properties::create(Materials::OCEAN_PLANT, MaterialColors::RED)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    HORN_CORAL = createBlock<CoralPlantBlock>("horn_coral", DEAD_HORN_CORAL, Properties::create(Materials::OCEAN_PLANT, MaterialColors::YELLOW)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    DEAD_TUBE_CORAL_FAN = createBlock<CoralFanBlock>("dead_tube_coral_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BRAIN_CORAL_FAN = createBlock<CoralFanBlock>("dead_brain_coral_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_BUBBLE_CORAL_FAN = createBlock<CoralFanBlock>("dead_bubble_coral_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_FIRE_CORAL_FAN = createBlock<CoralFanBlock>("dead_fire_coral_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    DEAD_HORN_CORAL_FAN = createBlock<CoralFanBlock>("dead_horn_coral_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance());
    TUBE_CORAL_FAN = createBlock<CoralFinBlock>("tube_coral_fan", DEAD_TUBE_CORAL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::BLUE)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BRAIN_CORAL_FAN = createBlock<CoralFinBlock>("brain_coral_fan", DEAD_BRAIN_CORAL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::PINK)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    BUBBLE_CORAL_FAN = createBlock<CoralFinBlock>("bubble_coral_fan", DEAD_BUBBLE_CORAL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::PURPLE)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    FIRE_CORAL_FAN = createBlock<CoralFinBlock>("fire_coral_fan", DEAD_FIRE_CORAL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::RED)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    HORN_CORAL_FAN = createBlock<CoralFinBlock>("horn_coral_fan", DEAD_HORN_CORAL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::YELLOW)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS));
    DEAD_TUBE_CORAL_WALL_FAN = createBlock<DeadCoralWallFanBlock>("dead_tube_coral_wall_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_TUBE_CORAL_FAN));
    DEAD_BRAIN_CORAL_WALL_FAN = createBlock<DeadCoralWallFanBlock>("dead_brain_coral_wall_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_BRAIN_CORAL_FAN));
    DEAD_BUBBLE_CORAL_WALL_FAN = createBlock<DeadCoralWallFanBlock>("dead_bubble_coral_wall_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_BUBBLE_CORAL_FAN));
    DEAD_FIRE_CORAL_WALL_FAN = createBlock<DeadCoralWallFanBlock>("dead_fire_coral_wall_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_FIRE_CORAL_FAN));
    DEAD_HORN_CORAL_WALL_FAN = createBlock<DeadCoralWallFanBlock>("dead_horn_coral_wall_fan", Properties::create(Materials::ROCK, MaterialColors::GRAY)
        .setRequiresTool()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setLootFrom(DEAD_HORN_CORAL_FAN));
    TUBE_CORAL_WALL_FAN = createBlock<CoralWallFanBlock>("tube_coral_wall_fan", DEAD_TUBE_CORAL_WALL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::BLUE)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(TUBE_CORAL_FAN));
    BRAIN_CORAL_WALL_FAN = createBlock<CoralWallFanBlock>("brain_coral_wall_fan", DEAD_BRAIN_CORAL_WALL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::PINK)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(BRAIN_CORAL_FAN));
    BUBBLE_CORAL_WALL_FAN = createBlock<CoralWallFanBlock>("bubble_coral_wall_fan", DEAD_BUBBLE_CORAL_WALL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::PURPLE)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(BUBBLE_CORAL_FAN));
    FIRE_CORAL_WALL_FAN = createBlock<CoralWallFanBlock>("fire_coral_wall_fan", DEAD_FIRE_CORAL_WALL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::RED)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(FIRE_CORAL_FAN));
    HORN_CORAL_WALL_FAN = createBlock<CoralWallFanBlock>("horn_coral_wall_fan", DEAD_HORN_CORAL_WALL_FAN, Properties::create(Materials::OCEAN_PLANT, MaterialColors::YELLOW)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::WET_GRASS)
        .setLootFrom(HORN_CORAL_FAN));
    SEA_PICKLE = createBlock<SeaPickleBlock>("sea_pickle", Properties::create(Materials::OCEAN_PLANT, MaterialColors::GREEN)
        .setLightLevel([](const BlockData &data) -> int32_t {
            return 0;//SeaPickleBlock::isInBadEnvironment(data) ? 0 : 3 + 3 * data.get(SeaPickleBlock::PICKLES);
        })
        .setSound(SoundType::SLIME)
        .notSolid());
    BLUE_ICE = createBlock<BreakableBlock>("blue_ice", Properties::create(Materials::PACKED_ICE)
        .setHardnessAndResistance(2.8F)
        .setSlipperiness(0.989F)
        .setSound(SoundType::GLASS));
    CONDUIT = createBlock<ConduitBlock>("conduit", Properties::create(Materials::GLASS, MaterialColors::DIAMOND)
        .setHardnessAndResistance(3.0F)
        .setLightLevel(getLightValue(15))
        .notSolid());
    BAMBOO_SAPLING = createBlock<BambooSaplingBlock>("bamboo_sapling", Properties::create(Materials::BAMBOO_SAPLING)
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .doesNotBlockMovement()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::BAMBOO_SAPLING));
    BAMBOO = createBlock<BambooBlock>("bamboo", Properties::create(Materials::BAMBOO, MaterialColors::FOLIAGE)
        .setTickRandomly()
        .zeroHardnessAndResistance()
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::BAMBOO)
        .notSolid());
    POTTED_BAMBOO = createBlock<FlowerPotBlock>("potted_bamboo", BAMBOO, Properties::create(Materials::MISCELLANEOUS).zeroHardnessAndResistance().notSolid());
    VOID_AIR = createBlock<AirBlock>("void_air", Properties::create(Materials::AIR)
        .doesNotBlockMovement()
        .noDrops()
        .setAir());
    CAVE_AIR = createBlock<AirBlock>("cave_air", Properties::create(Materials::AIR)
        .doesNotBlockMovement()
        .noDrops()
        .setAir());
    BUBBLE_COLUMN = createBlock<BubbleColumnBlock>("bubble_column", Properties::create(Materials::BUBBLE_COLUMN)
        .doesNotBlockMovement()
        .noDrops());
    POLISHED_GRANITE_STAIRS = createBlock<StairsBlock>("polished_granite_stairs", POLISHED_GRANITE->getDefaultState(), Properties::from(POLISHED_GRANITE));
    SMOOTH_RED_SANDSTONE_STAIRS = createBlock<StairsBlock>("smooth_red_sandstone_stairs", SMOOTH_RED_SANDSTONE->getDefaultState(), Properties::from(SMOOTH_RED_SANDSTONE));
    MOSSY_STONE_BRICK_STAIRS = createBlock<StairsBlock>("mossy_stone_brick_stairs", MOSSY_STONE_BRICKS->getDefaultState(), Properties::from(MOSSY_STONE_BRICKS));
    POLISHED_DIORITE_STAIRS = createBlock<StairsBlock>("polished_diorite_stairs", POLISHED_DIORITE->getDefaultState(), Properties::from(POLISHED_DIORITE));
    MOSSY_COBBLESTONE_STAIRS = createBlock<StairsBlock>("mossy_cobblestone_stairs", MOSSY_COBBLESTONE->getDefaultState(), Properties::from(MOSSY_COBBLESTONE));
    END_STONE_BRICK_STAIRS = createBlock<StairsBlock>("end_stone_brick_stairs", END_STONE_BRICKS->getDefaultState(), Properties::from(END_STONE_BRICKS));
    STONE_STAIRS = createBlock<StairsBlock>("stone_stairs", STONE->getDefaultState(), Properties::from(STONE));
    SMOOTH_SANDSTONE_STAIRS = createBlock<StairsBlock>("smooth_sandstone_stairs", SMOOTH_SANDSTONE->getDefaultState(), Properties::from(SMOOTH_SANDSTONE));
    SMOOTH_QUARTZ_STAIRS = createBlock<StairsBlock>("smooth_quartz_stairs", SMOOTH_QUARTZ->getDefaultState(), Properties::from(SMOOTH_QUARTZ));
    GRANITE_STAIRS = createBlock<StairsBlock>("granite_stairs", GRANITE->getDefaultState(), Properties::from(GRANITE));
    ANDESITE_STAIRS = createBlock<StairsBlock>("andesite_stairs", ANDESITE->getDefaultState(), Properties::from(ANDESITE));
    RED_NETHER_BRICK_STAIRS = createBlock<StairsBlock>("red_nether_brick_stairs", RED_NETHER_BRICKS->getDefaultState(), Properties::from(RED_NETHER_BRICKS));
    POLISHED_ANDESITE_STAIRS = createBlock<StairsBlock>("polished_andesite_stairs", POLISHED_ANDESITE->getDefaultState(), Properties::from(POLISHED_ANDESITE));
    DIORITE_STAIRS = createBlock<StairsBlock>("diorite_stairs", DIORITE->getDefaultState(), Properties::from(DIORITE));
    POLISHED_GRANITE_SLAB = createBlock<SlabBlock>("polished_granite_slab", Properties::from(POLISHED_GRANITE));
    SMOOTH_RED_SANDSTONE_SLAB = createBlock<SlabBlock>("smooth_red_sandstone_slab", Properties::from(SMOOTH_RED_SANDSTONE));
    MOSSY_STONE_BRICK_SLAB = createBlock<SlabBlock>("mossy_stone_brick_slab", Properties::from(MOSSY_STONE_BRICKS));
    POLISHED_DIORITE_SLAB = createBlock<SlabBlock>("polished_diorite_slab", Properties::from(POLISHED_DIORITE));
    MOSSY_COBBLESTONE_SLAB = createBlock<SlabBlock>("mossy_cobblestone_slab", Properties::from(MOSSY_COBBLESTONE));
    END_STONE_BRICK_SLAB = createBlock<SlabBlock>("end_stone_brick_slab", Properties::from(END_STONE_BRICKS));
    SMOOTH_SANDSTONE_SLAB = createBlock<SlabBlock>("smooth_sandstone_slab", Properties::from(SMOOTH_SANDSTONE));
    SMOOTH_QUARTZ_SLAB = createBlock<SlabBlock>("smooth_quartz_slab", Properties::from(SMOOTH_QUARTZ));
    GRANITE_SLAB = createBlock<SlabBlock>("granite_slab", Properties::from(GRANITE));
    ANDESITE_SLAB = createBlock<SlabBlock>("andesite_slab", Properties::from(ANDESITE));
    RED_NETHER_BRICK_SLAB = createBlock<SlabBlock>("red_nether_brick_slab", Properties::from(RED_NETHER_BRICKS));
    POLISHED_ANDESITE_SLAB = createBlock<SlabBlock>("polished_andesite_slab", Properties::from(POLISHED_ANDESITE));
    DIORITE_SLAB = createBlock<SlabBlock>("diorite_slab", Properties::from(DIORITE));
    BRICK_WALL = createBlock<WallBlock>("brick_wall", Properties::from(BRICKS));
    PRISMARINE_WALL = createBlock<WallBlock>("prismarine_wall", Properties::from(PRISMARINE));
    RED_SANDSTONE_WALL = createBlock<WallBlock>("red_sandstone_wall", Properties::from(RED_SANDSTONE));
    MOSSY_STONE_BRICK_WALL = createBlock<WallBlock>("mossy_stone_brick_wall", Properties::from(MOSSY_STONE_BRICKS));
    GRANITE_WALL = createBlock<WallBlock>("granite_wall", Properties::from(GRANITE));
    STONE_BRICK_WALL = createBlock<WallBlock>("stone_brick_wall", Properties::from(STONE_BRICKS));
    NETHER_BRICK_WALL = createBlock<WallBlock>("nether_brick_wall", Properties::from(NETHER_BRICKS));
    ANDESITE_WALL = createBlock<WallBlock>("andesite_wall", Properties::from(ANDESITE));
    RED_NETHER_BRICK_WALL = createBlock<WallBlock>("red_nether_brick_wall", Properties::from(RED_NETHER_BRICKS));
    SANDSTONE_WALL = createBlock<WallBlock>("sandstone_wall", Properties::from(SANDSTONE));
    END_STONE_BRICK_WALL = createBlock<WallBlock>("end_stone_brick_wall", Properties::from(END_STONE_BRICKS));
//    DIORITE_WALL = createBlock<WallBlock>("diorite_wall", Properties::from(DIORITE));
    SCAFFOLDING = createBlock<ScaffoldingBlock>("scaffolding", Properties::create(Materials::MISCELLANEOUS, MaterialColors::SAND)
        .doesNotBlockMovement()
        .setSound(SoundType::SCAFFOLDING)
        .setVariableOpacity());
    LOOM = createBlock<LoomBlock>("loom", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    BARREL = createBlock<BarrelBlock>("barrel", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    SMOKER = createBlock<SmokerBlock>("smoker", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setLightLevel(getLightValueLit(13)));
    BLAST_FURNACE = createBlock<BlastFurnaceBlock>("blast_furnace", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setLightLevel(getLightValueLit(13)));
    CARTOGRAPHY_TABLE = createBlock<CartographyTableBlock>("cartography_table", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    FLETCHING_TABLE = createBlock<FletchingTableBlock>("fletching_table", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    GRINDSTONE = createBlock<GrindstoneBlock>("grindstone", Properties::create(Materials::ANVIL, MaterialColors::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::STONE));
    LECTERN = createBlock<LecternBlock>("lectern", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    SMITHING_TABLE = createBlock<SmithingTableBlock>("smithing_table", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(2.5F)
        .setSound(SoundType::WOOD));
    STONECUTTER = createBlock<StonecutterBlock>("stonecutter", Properties::create(Materials::ROCK)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F));
    BELL = createBlock<BellBlock>("bell", Properties::create(Materials::IRON, MaterialColors::GOLD)
        .setRequiresTool()
        .setHardnessAndResistance(5.0F)
        .setSound(SoundType::ANVIL));
    LANTERN = createBlock<LanternBlock>("lantern", Properties::create(Materials::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setSound(SoundType::LANTERN)
        .setLightLevel(getLightValue(15))
        .notSolid());
    SOUL_LANTERN = createBlock<LanternBlock>("soul_lantern", Properties::create(Materials::IRON)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setSound(SoundType::LANTERN)
        .setLightLevel(getLightValue(10))
        .notSolid());
    CAMPFIRE = createBlock<CampfireBlock>("campfire", true, 1, Properties::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD)
        .setLightLevel(getLightValueLit(15))
        .notSolid());
    SOUL_CAMPFIRE = createBlock<CampfireBlock>("soul_campfire", false, 2, Properties::create(Materials::WOOD, MaterialColors::OBSIDIAN)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::WOOD)
        .setLightLevel(getLightValueLit(10))
        .notSolid());
    SWEET_BERRY_BUSH = createBlock<SweetBerryBushBlock>("sweet_berry_bush", Properties::create(Materials::PLANTS)
        .setTickRandomly()
        .doesNotBlockMovement()
        .setSound(SoundType::SWEET_BERRY_BUSH));
    WARPED_STEM = createRotatableNetherBlock("warped_stem", MaterialColors::WARPED_STEM);
    STRIPPED_WARPED_STEM = createRotatableNetherBlock("stripped_warped_stem", MaterialColors::WARPED_STEM);
    WARPED_HYPHAE = createBlock<RotatedPillarBlock>("warped_hyphae", Properties::create(Materials::NETHER_WOOD, MaterialColors::WARPED_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    STRIPPED_WARPED_HYPHAE = createBlock<RotatedPillarBlock>("stripped_warped_hyphae", Properties::create(Materials::NETHER_WOOD, MaterialColors::WARPED_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    WARPED_NYLIUM = createBlock<NyliumBlock>("warped_nylium", Properties::create(Materials::ROCK, MaterialColors::WARPED_NYLIUM)
        .setRequiresTool()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::NYLIUM)
        .setTickRandomly());
    WARPED_FUNGUS = createBlock<FungusBlock>("warped_fungus", Properties::create(Materials::PLANTS, MaterialColors::CYAN)
        .zeroHardnessAndResistance()
        .doesNotBlockMovement()
        .setSound(SoundType::FUNGUS) 
        /*, []() {
            return Features.WARPED_FUNGI_PLANTED;
        }*/);
    WARPED_WART_BLOCK = createBlock<Block>("warped_wart_block", Properties::create(Materials::ORGANIC, MaterialColors::WARPED_WART)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::WART));
    WARPED_ROOTS = createBlock<NetherRootsBlock>("warped_roots", Properties::create(Materials::NETHER_PLANTS, MaterialColors::CYAN)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::ROOT));
    NETHER_SPROUTS = createBlock<NetherSproutsBlock>("nether_sprouts", Properties::create(Materials::NETHER_PLANTS, MaterialColors::CYAN)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_SPROUT));
    CRIMSON_STEM = createRotatableNetherBlock("crimson_stem", MaterialColors::CRIMSON_STEM);
    STRIPPED_CRIMSON_STEM = createRotatableNetherBlock("stripped_crimson_stem", MaterialColors::CRIMSON_STEM);
    CRIMSON_HYPHAE = createBlock<RotatedPillarBlock>("crimson_hyphae", Properties::create(Materials::NETHER_WOOD, MaterialColors::CRIMSON_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    STRIPPED_CRIMSON_HYPHAE = createBlock<RotatedPillarBlock>("stripped_crimson_hyphae", Properties::create(Materials::NETHER_WOOD, MaterialColors::CRIMSON_HYPHAE)
        .setHardnessAndResistance(2.0F)
        .setSound(SoundType::HYPHAE));
    CRIMSON_NYLIUM = createBlock<NyliumBlock>("crimson_nylium", Properties::create(Materials::ROCK, MaterialColors::CRIMSON_NYLIUM)
        .setRequiresTool()
        .setHardnessAndResistance(0.4F)
        .setSound(SoundType::NYLIUM)
        .setTickRandomly());
    CRIMSON_FUNGUS = createBlock<FungusBlock>("crimson_fungus", Properties::create(Materials::PLANTS, MaterialColors::NETHERRACK)
        .zeroHardnessAndResistance()
        .doesNotBlockMovement()
        .setSound(SoundType::FUNGUS)
        /*, []() {
            return Features::CRIMSON_FUNGI_PLANTED;
        }*/);
    SHROOMLIGHT = createBlock<Block>("shroomlight", Properties::create(Materials::ORGANIC, MaterialColors::RED)
        .setHardnessAndResistance(1.0F)
        .setSound(SoundType::SHROOMLIGHT)
        .setLightLevel(getLightValue(15)));
    WEEPING_VINES = createBlock<WeepingVinesTopBlock>("weeping_vines", Properties::create(Materials::PLANTS, MaterialColors::NETHERRACK)
        .setTickRandomly()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    WEEPING_VINES_PLANT = createBlock<WeepingVinesBlock>("weeping_vines_plant", Properties::create(Materials::PLANTS, MaterialColors::NETHERRACK)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    TWISTING_VINES = createBlock<TwistingVinesTopBlock>("twisting_vines", Properties::create(Materials::PLANTS, MaterialColors::CYAN)
        .setTickRandomly()
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    TWISTING_VINES_PLANT = createBlock<TwistingVinesBlock>("twisting_vines_plant", Properties::create(Materials::PLANTS, MaterialColors::CYAN)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::NETHER_VINE));
    CRIMSON_ROOTS = createBlock<NetherRootsBlock>("crimson_roots", Properties::create(Materials::NETHER_PLANTS, MaterialColors::NETHERRACK)
        .doesNotBlockMovement()
        .zeroHardnessAndResistance()
        .setSound(SoundType::ROOT));
    CRIMSON_PLANKS = createBlock<Block>("crimson_planks", Properties::create(Materials::NETHER_WOOD, MaterialColors::CRIMSON_STEM)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_PLANKS = createBlock<Block>("warped_planks", Properties::create(Materials::NETHER_WOOD, MaterialColors::WARPED_STEM)
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_SLAB = createBlock<SlabBlock>("crimson_slab", Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_SLAB = createBlock<SlabBlock>("warped_slab", Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_PRESSURE_PLATE = createBlock<PressurePlateBlock>("crimson_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    WARPED_PRESSURE_PLATE = createBlock<PressurePlateBlock>("warped_pressure_plate", PressurePlateBlock::Sensitivity::EVERYTHING, Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    CRIMSON_FENCE = createBlock<FenceBlock>("crimson_fence", Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_FENCE = createBlock<FenceBlock>("warped_fence", Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_TRAPDOOR = createBlock<TrapDoorBlock>("crimson_trapdoor", Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    WARPED_TRAPDOOR = createBlock<TrapDoorBlock>("warped_trapdoor", Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid()
        .setAllowsSpawn(neverAllowSpawn));
    CRIMSON_FENCE_GATE = createBlock<FenceGateBlock>("crimson_fence_gate", Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    WARPED_FENCE_GATE = createBlock<FenceGateBlock>("warped_fence_gate", Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(2.0F, 3.0F)
        .setSound(SoundType::WOOD));
    CRIMSON_STAIRS = createBlock<StairsBlock>("crimson_stairs", CRIMSON_PLANKS->getDefaultState(), Properties::from(CRIMSON_PLANKS));
    WARPED_STAIRS = createBlock<StairsBlock>("warped_stairs", WARPED_PLANKS->getDefaultState(), Properties::from(WARPED_PLANKS));
    CRIMSON_BUTTON = createBlock<WoodButtonBlock>("crimson_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    WARPED_BUTTON = createBlock<WoodButtonBlock>("warped_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::WOOD));
    CRIMSON_DOOR = createBlock<DoorBlock>("crimson_door", Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    WARPED_DOOR = createBlock<DoorBlock>("warped_door", Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor())
        .setHardnessAndResistance(3.0F)
        .setSound(SoundType::WOOD)
        .notSolid());
    CRIMSON_SIGN = createBlock<StandingSignBlock>("crimson_sign", Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor()).doesNotBlockMovement().setHardnessAndResistance(1.0F).setSound(SoundType::WOOD), WoodType::CRIMSON);
    WARPED_SIGN = createBlock<StandingSignBlock>("warped_sign", Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor()).doesNotBlockMovement().setHardnessAndResistance(1.0F).setSound(SoundType::WOOD), WoodType::WARPED);
    CRIMSON_WALL_SIGN = createBlock<WallSignBlock>("crimson_wall_sign", Properties::create(Materials::NETHER_WOOD, CRIMSON_PLANKS->getMaterialColor()).doesNotBlockMovement().setHardnessAndResistance(1.0F).setSound(SoundType::WOOD).setLootFrom(CRIMSON_SIGN), WoodType::CRIMSON);
    WARPED_WALL_SIGN = createBlock<WallSignBlock>("warped_wall_sign", Properties::create(Materials::NETHER_WOOD, WARPED_PLANKS->getMaterialColor()).doesNotBlockMovement().setHardnessAndResistance(1.0F).setSound(SoundType::WOOD).setLootFrom(WARPED_SIGN), WoodType::WARPED);
    STRUCTURE_BLOCK = createBlock<StructureBlock>("structure_block", Properties::create(Materials::IRON, MaterialColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    JIGSAW = createBlock<JigsawBlock>("jigsaw", Properties::create(Materials::IRON, MaterialColors::LIGHT_GRAY)
        .setRequiresTool()
        .setHardnessAndResistance(-1.0F, 3600000.0F)
        .noDrops());
    COMPOSTER = createBlock<ComposterBlock>("composter", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::WOOD));
    TARGET = createBlock<TargetBlock>("target", Properties::create(Materials::ORGANIC, MaterialColors::QUARTZ)
        .setHardnessAndResistance(0.5F)
        .setSound(SoundType::PLANT));
    BEE_NEST = createBlock<BeehiveBlock>("bee_nest", Properties::create(Materials::WOOD, MaterialColors::YELLOW)
        .setHardnessAndResistance(0.3F)
        .setSound(SoundType::WOOD));
    BEEHIVE = createBlock<BeehiveBlock>("beehive", Properties::create(Materials::WOOD)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::WOOD));
    HONEY_BLOCK = createBlock<HoneyBlock>("honey_block", Properties::create(Materials::CLAY, MaterialColors::ADOBE)
        .setSpeedFactor(0.4F)
        .setJumpFactor(0.5F)
        .notSolid()
        .setSound(SoundType::HONEY));
    HONEYCOMB_BLOCK = createBlock<Block>("honeycomb_block", Properties::create(Materials::CLAY, MaterialColors::ADOBE)
        .setHardnessAndResistance(0.6F)
        .setSound(SoundType::CORAL));
    NETHERITE_BLOCK = createBlock<Block>("netherite_block", Properties::create(Materials::IRON, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F)
        .setSound(SoundType::NETHERITE));
    ANCIENT_DEBRIS = createBlock<Block>("ancient_debris", Properties::create(Materials::IRON, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(30.0F, 1200.0F)
        .setSound(SoundType::ANCIENT_DEBRIS));
    CRYING_OBSIDIAN = createBlock<CryingObsidianBlock>("crying_obsidian", Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F)
        .setLightLevel(getLightValue(10)));
    RESPAWN_ANCHOR = createBlock<RespawnAnchorBlock>("respawn_anchor", Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(50.0F, 1200.0F)
        .setLightLevel([](const BlockData &data) -> int32_t {
            return 0;//RespawnAnchorBlock::getChargeScale(data, 15);
        }));
    POTTED_CRIMSON_FUNGUS = createBlock<FlowerPotBlock>("potted_crimson_fungus", CRIMSON_FUNGUS, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WARPED_FUNGUS = createBlock<FlowerPotBlock>("potted_warped_fungus", WARPED_FUNGUS, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_CRIMSON_ROOTS = createBlock<FlowerPotBlock>("potted_crimson_roots", CRIMSON_ROOTS, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    POTTED_WARPED_ROOTS = createBlock<FlowerPotBlock>("potted_warped_roots", WARPED_ROOTS, Properties::create(Materials::MISCELLANEOUS)
        .zeroHardnessAndResistance()
        .notSolid());
    LODESTONE = createBlock<Block>("lodestone", Properties::create(Materials::ANVIL)
        .setRequiresTool()
        .setHardnessAndResistance(3.5F)
        .setSound(SoundType::LODESTONE));
    BLACKSTONE = createBlock<Block>("blackstone", Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .setHardnessAndResistance(1.5F, 6.0F));
    BLACKSTONE_STAIRS = createBlock<StairsBlock>("blackstone_stairs", BLACKSTONE->getDefaultState(), Properties::from(BLACKSTONE));
    BLACKSTONE_WALL = createBlock<WallBlock>("blackstone_wall", Properties::from(BLACKSTONE));
    BLACKSTONE_SLAB = createBlock<SlabBlock>("blackstone_slab", Properties::from(BLACKSTONE)
        .setHardnessAndResistance(2.0F, 6.0F));
    POLISHED_BLACKSTONE = createBlock<Block>("polished_blackstone", Properties::from(BLACKSTONE)
        .setHardnessAndResistance(2.0F, 6.0F));
    POLISHED_BLACKSTONE_BRICKS = createBlock<Block>("polished_blackstone_bricks", Properties::from(POLISHED_BLACKSTONE)
        .setHardnessAndResistance(1.5F, 6.0F));
    CRACKED_POLISHED_BLACKSTONE_BRICKS = createBlock<Block>("cracked_polished_blackstone_bricks", Properties::from(POLISHED_BLACKSTONE_BRICKS));
    CHISELED_POLISHED_BLACKSTONE = createBlock<Block>("chiseled_polished_blackstone", Properties::from(POLISHED_BLACKSTONE)
        .setHardnessAndResistance(1.5F, 6.0F));
    POLISHED_BLACKSTONE_BRICK_SLAB = createBlock<SlabBlock>("polished_blackstone_brick_slab", Properties::from(POLISHED_BLACKSTONE_BRICKS)
        .setHardnessAndResistance(2.0F, 6.0F));
    POLISHED_BLACKSTONE_BRICK_STAIRS = createBlock<StairsBlock>("polished_blackstone_brick_stairs", POLISHED_BLACKSTONE_BRICKS->getDefaultState(), Properties::from(POLISHED_BLACKSTONE_BRICKS));
    POLISHED_BLACKSTONE_BRICK_WALL = createBlock<WallBlock>("polished_blackstone_brick_wall", Properties::from(POLISHED_BLACKSTONE_BRICKS));
    GILDED_BLACKSTONE = createBlock<Block>("gilded_blackstone", Properties::from(BLACKSTONE).setSound(SoundType::GILDED_BLACKSTONE));
    POLISHED_BLACKSTONE_STAIRS = createBlock<StairsBlock>("polished_blackstone_stairs", POLISHED_BLACKSTONE->getDefaultState(), Properties::from(POLISHED_BLACKSTONE));
    POLISHED_BLACKSTONE_SLAB = createBlock<SlabBlock>("polished_blackstone_slab", Properties::from(POLISHED_BLACKSTONE));
    POLISHED_BLACKSTONE_PRESSURE_PLATE = createBlock<PressurePlateBlock>("polished_blackstone_pressure_plate", PressurePlateBlock::Sensitivity::MOBS, Properties::create(Materials::ROCK, MaterialColors::BLACK)
        .setRequiresTool()
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    POLISHED_BLACKSTONE_BUTTON = createBlock<StoneButtonBlock>("polished_blackstone_button", Properties::create(Materials::MISCELLANEOUS)
        .doesNotBlockMovement()
        .setHardnessAndResistance(0.5F));
    POLISHED_BLACKSTONE_WALL = createBlock<WallBlock>("polished_blackstone_wall", Properties::from(POLISHED_BLACKSTONE));
    CHISELED_NETHER_BRICKS = createBlock<Block>("chiseled_nether_bricks", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    CRACKED_NETHER_BRICKS = createBlock<Block>("cracked_nether_bricks", Properties::create(Materials::ROCK, MaterialColors::NETHERRACK)
        .setRequiresTool()
        .setHardnessAndResistance(2.0F, 6.0F)
        .setSound(SoundType::NETHER_BRICK));
    QUARTZ_BRICKS = createBlock<Block>("quartz_bricks", Properties::from(QUARTZ_BLOCK));
}