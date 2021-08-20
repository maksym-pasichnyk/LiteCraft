#include "ConfiguredFeatures.hpp"
#include "ConfiguredFeature.hpp"
#include "Feature.hpp"
#include "Features.hpp"
#include "FlowersFeature.hpp"
#include "config/FeatureConfig.hpp"
#include "../placement/Placement.hpp"
#include "../placement/Placements.hpp"
#include "../blockplacer/SimpleBlockPlacer.hpp"
#include "../blockplacer/ColumnBlockPlacer.hpp"
#include "../blockplacer/DoublePlantBlockPlacer.hpp"
#include "../blockstateprovider/SimpleBlockStateProvider.hpp"
#include "../blockstateprovider/WeightedBlockStateProvider.hpp"
#include "../blockstateprovider/PlainFlowerBlockStateProvider.hpp"
#include "../blockstateprovider/ForestFlowerBlockStateProvider.hpp"
#include "../blockstateprovider/AxisRotatingBlockStateProvider.hpp"
#include "../foliageplacer/BlobFoliagePlacer.hpp"
#include "../foliageplacer/PineFoliagePlacer.hpp"
#include "../foliageplacer/BushFoliagePlacer.hpp"
#include "../foliageplacer/FancyFoliagePlacer.hpp"
#include "../foliageplacer/JungleFoliagePlacer.hpp"
#include "../foliageplacer/SpruceFoliagePlacer.hpp"
#include "../foliageplacer/AcaciaFoliagePlacer.hpp"
#include "../foliageplacer/DarkOakFoliagePlacer.hpp"
#include "../foliageplacer/MegaPineFoliagePlacer.hpp"
#include "../trunkplacer/FancyTrunkPlacer.hpp"
#include "../trunkplacer/ForkyTrunkPlacer.hpp"
#include "../trunkplacer/DarkOakTrunkPlacer.hpp"
#include "../trunkplacer/StraightTrunkPlacer.hpp"
#include "../trunkplacer/MegaJungleTrunkPlacer.hpp"
#include "../treedecorator/CocoaTreeDecorator.hpp"
#include "../treedecorator/BeehiveTreeDecorator.hpp"
#include "../treedecorator/LeaveVineTreeDecorator.hpp"
#include "../treedecorator/TrunkVineTreeDecorator.hpp"
#include "../treedecorator/AlterGroundTreeDecorator.hpp"
#include "../../../block/Blocks.hpp"

Registry<ConfiguredFeature> ConfiguredFeatures::features{};
ConfiguredFeature* ConfiguredFeatures::END_SPIKE;
ConfiguredFeature* ConfiguredFeatures::END_GATEWAY;
ConfiguredFeature* ConfiguredFeatures::END_GATEWAY_DELAYED;
ConfiguredFeature* ConfiguredFeatures::CHORUS_PLANT;
ConfiguredFeature* ConfiguredFeatures::END_ISLAND;
ConfiguredFeature* ConfiguredFeatures::END_ISLAND_DECORATED;
ConfiguredFeature* ConfiguredFeatures::DELTA;
ConfiguredFeature* ConfiguredFeatures::SMALL_BASALT_COLUMNS;
ConfiguredFeature* ConfiguredFeatures::LARGE_BASALT_COLUMNS;
ConfiguredFeature* ConfiguredFeatures::BASALT_BLOBS;
ConfiguredFeature* ConfiguredFeatures::BLACKSTONE_BLOBS;
ConfiguredFeature* ConfiguredFeatures::GLOWSTONE_EXTRA;
ConfiguredFeature* ConfiguredFeatures::GLOWSTONE;
ConfiguredFeature* ConfiguredFeatures::CRIMSON_FOREST_VEGETATION;
ConfiguredFeature* ConfiguredFeatures::WARPED_FOREST_VEGETATION;
ConfiguredFeature* ConfiguredFeatures::NETHER_SPROUTS;
ConfiguredFeature* ConfiguredFeatures::TWISTING_VINES;
ConfiguredFeature* ConfiguredFeatures::WEEPING_VINES;
ConfiguredFeature* ConfiguredFeatures::BASALT_PILLAR;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_COLD;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_DEEP_COLD;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_NORMAL;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_RIVER;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_DEEP;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_SWAMP;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_WARM;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_DEEP_WARM;
ConfiguredFeature* ConfiguredFeatures::SEA_PICKLE;
ConfiguredFeature* ConfiguredFeatures::ICE_SPIKE;
ConfiguredFeature* ConfiguredFeatures::ICE_PATCH;
ConfiguredFeature* ConfiguredFeatures::FOREST_ROCK;
ConfiguredFeature* ConfiguredFeatures::SEAGRASS_SIMPLE;
ConfiguredFeature* ConfiguredFeatures::ICEBERG_PACKED;
ConfiguredFeature* ConfiguredFeatures::ICEBERG_BLUE;
ConfiguredFeature* ConfiguredFeatures::KELP_COLD;
ConfiguredFeature* ConfiguredFeatures::KELP_WARM;
ConfiguredFeature* ConfiguredFeatures::BLUE_ICE;
ConfiguredFeature* ConfiguredFeatures::BAMBOO_LIGHT;
ConfiguredFeature* ConfiguredFeatures::BAMBOO;
ConfiguredFeature* ConfiguredFeatures::VINES;
ConfiguredFeature* ConfiguredFeatures::LAKE_WATER;
ConfiguredFeature* ConfiguredFeatures::LAKE_LAVA;
ConfiguredFeature* ConfiguredFeatures::DISK_CLAY;
ConfiguredFeature* ConfiguredFeatures::DISK_GRAVEL;
ConfiguredFeature* ConfiguredFeatures::DISK_SAND;
ConfiguredFeature* ConfiguredFeatures::FREEZE_TOP_LAYER;
ConfiguredFeature* ConfiguredFeatures::BONUS_CHEST;
ConfiguredFeature* ConfiguredFeatures::VOID_START_PLATFORM;
ConfiguredFeature* ConfiguredFeatures::MONSTER_ROOM;
ConfiguredFeature* ConfiguredFeatures::DESERT_WELL;
ConfiguredFeature* ConfiguredFeatures::FOSSIL;
ConfiguredFeature* ConfiguredFeatures::SPRING_LAVA_DOUBLE;
ConfiguredFeature* ConfiguredFeatures::SPRING_LAVA;
ConfiguredFeature* ConfiguredFeatures::SPRING_DELTA;
ConfiguredFeature* ConfiguredFeatures::SPRING_CLOSED;
ConfiguredFeature* ConfiguredFeatures::SPRING_CLOSED_DOUBLE;
ConfiguredFeature* ConfiguredFeatures::SPRING_OPEN;
ConfiguredFeature* ConfiguredFeatures::SPRING_WATER;
ConfiguredFeature* ConfiguredFeatures::PILE_HAY;
ConfiguredFeature* ConfiguredFeatures::PILE_MELON;
ConfiguredFeature* ConfiguredFeatures::PILE_SNOW;
ConfiguredFeature* ConfiguredFeatures::PILE_ICE;
ConfiguredFeature* ConfiguredFeatures::PILE_PUMPKIN;
ConfiguredFeature* ConfiguredFeatures::PATCH_FIRE;
ConfiguredFeature* ConfiguredFeatures::PATCH_SOUL_FIRE;
ConfiguredFeature* ConfiguredFeatures::PATCH_BROWN_MUSHROOM;
ConfiguredFeature* ConfiguredFeatures::PATCH_RED_MUSHROOM;
ConfiguredFeature* ConfiguredFeatures::PATCH_CRIMSON_ROOTS;
ConfiguredFeature* ConfiguredFeatures::PATCH_SUNFLOWER;
ConfiguredFeature* ConfiguredFeatures::PATCH_PUMPKIN;
ConfiguredFeature* ConfiguredFeatures::PATCH_TAIGA_GRASS;
ConfiguredFeature* ConfiguredFeatures::PATCH_BERRY_BUSH;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_PLAIN;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_FOREST;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_BADLANDS;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_SAVANNA;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_NORMAL;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_TAIGA_2;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_TAIGA;
ConfiguredFeature* ConfiguredFeatures::PATCH_GRASS_JUNGLE;
ConfiguredFeature* ConfiguredFeatures::PATCH_DEAD_BUSH_2;
ConfiguredFeature* ConfiguredFeatures::PATCH_DEAD_BUSH;
ConfiguredFeature* ConfiguredFeatures::PATCH_DEAD_BUSH_BADLANDS;
ConfiguredFeature* ConfiguredFeatures::PATCH_MELON;
ConfiguredFeature* ConfiguredFeatures::PATCH_BERRY_SPARSE;
ConfiguredFeature* ConfiguredFeatures::PATCH_BERRY_DECORATED;
ConfiguredFeature* ConfiguredFeatures::PATCH_WATERLILLY;
ConfiguredFeature* ConfiguredFeatures::PATCH_TALL_GRASS_2;
ConfiguredFeature* ConfiguredFeatures::PATCH_TALL_GRASS;
ConfiguredFeature* ConfiguredFeatures::PATCH_LARGE_FERN;
ConfiguredFeature* ConfiguredFeatures::PATCH_CACTUS;
ConfiguredFeature* ConfiguredFeatures::PATCH_CACTUS_DESERT;
ConfiguredFeature* ConfiguredFeatures::PATCH_CACTUS_DECORATED;
ConfiguredFeature* ConfiguredFeatures::PATCH_SUGAR_CANE_SWAMP;
ConfiguredFeature* ConfiguredFeatures::PATCH_SUGAR_CANE_DESERT;
ConfiguredFeature* ConfiguredFeatures::PATCH_SUGAR_CANE_BADLANDS;
ConfiguredFeature* ConfiguredFeatures::PATCH_SUGAR_CANE;
ConfiguredFeature* ConfiguredFeatures::BROWN_MUSHROOM_NETHER;
ConfiguredFeature* ConfiguredFeatures::RED_MUSHROOM_NETHER;
ConfiguredFeature* ConfiguredFeatures::BROWN_MUSHROOM_NORMAL;
ConfiguredFeature* ConfiguredFeatures::RED_MUSHROOM_NORMAL;
ConfiguredFeature* ConfiguredFeatures::BROWN_MUSHROOM_TAIGA;
ConfiguredFeature* ConfiguredFeatures::RED_MUSHROOM_TAIGA;
ConfiguredFeature* ConfiguredFeatures::BROWN_MUSHROOM_GIANT;
ConfiguredFeature* ConfiguredFeatures::RED_MUSHROOM_GIANT;
ConfiguredFeature* ConfiguredFeatures::BROWN_MUSHROOM_SWAMP;
ConfiguredFeature* ConfiguredFeatures::RED_MUSHROOM_SWAMP;
ConfiguredFeature* ConfiguredFeatures::ORE_MAGMA;
ConfiguredFeature* ConfiguredFeatures::ORE_SOUL_SAND;
ConfiguredFeature* ConfiguredFeatures::ORE_GOLD_DELTAS;
ConfiguredFeature* ConfiguredFeatures::ORE_QUARTZ_DELTAS;
ConfiguredFeature* ConfiguredFeatures::ORE_GOLD_NETHER;
ConfiguredFeature* ConfiguredFeatures::ORE_QUARTZ_NETHER;
ConfiguredFeature* ConfiguredFeatures::ORE_GRAVEL_NETHER;
ConfiguredFeature* ConfiguredFeatures::ORE_BLACKSTONE;
ConfiguredFeature* ConfiguredFeatures::ORE_DIRT;
ConfiguredFeature* ConfiguredFeatures::ORE_GRAVEL;
ConfiguredFeature* ConfiguredFeatures::ORE_GRANITE;
ConfiguredFeature* ConfiguredFeatures::ORE_DIORITE;
ConfiguredFeature* ConfiguredFeatures::ORE_ANDESITE;
ConfiguredFeature* ConfiguredFeatures::ORE_COAL;
ConfiguredFeature* ConfiguredFeatures::ORE_IRON;
ConfiguredFeature* ConfiguredFeatures::ORE_GOLD_EXTRA;
ConfiguredFeature* ConfiguredFeatures::ORE_GOLD;
ConfiguredFeature* ConfiguredFeatures::ORE_REDSTONE;
ConfiguredFeature* ConfiguredFeatures::ORE_DIAMOND;
ConfiguredFeature* ConfiguredFeatures::ORE_LAPIS;
ConfiguredFeature* ConfiguredFeatures::ORE_INFESTED;
ConfiguredFeature* ConfiguredFeatures::ORE_EMERALD;
ConfiguredFeature* ConfiguredFeatures::ORE_DEBRIS_LARGE;
ConfiguredFeature* ConfiguredFeatures::ORE_DEBRIS_SMALL;
ConfiguredFeature* ConfiguredFeatures::CRIMSON_FUNGI;
ConfiguredFeature* ConfiguredFeatures::CRIMSON_FUNGI_PLANTED;
ConfiguredFeature* ConfiguredFeatures::WARPED_FUNGI;
ConfiguredFeature* ConfiguredFeatures::WARPED_FUNGI_PLANTED;
ConfiguredFeature* ConfiguredFeatures::HUGE_BROWN_MUSHROOM;
ConfiguredFeature* ConfiguredFeatures::HUGE_RED_MUSHROOM;
ConfiguredFeature* ConfiguredFeatures::OAK;
ConfiguredFeature* ConfiguredFeatures::DARK_OAK;
ConfiguredFeature* ConfiguredFeatures::BIRCH;
ConfiguredFeature* ConfiguredFeatures::ACACIA;
ConfiguredFeature* ConfiguredFeatures::SPRUCE;
ConfiguredFeature* ConfiguredFeatures::PINE;
ConfiguredFeature* ConfiguredFeatures::JUNGLE_TREE;
ConfiguredFeature* ConfiguredFeatures::FANCY_OAK;
ConfiguredFeature* ConfiguredFeatures::JUNGLE_TREE_NO_VINE;
ConfiguredFeature* ConfiguredFeatures::MEGA_JUNGLE_TREE;
ConfiguredFeature* ConfiguredFeatures::MEGA_SPRUCE;
ConfiguredFeature* ConfiguredFeatures::MEGA_PINE;
ConfiguredFeature* ConfiguredFeatures::SUPER_BIRCH_BEES_0002;
ConfiguredFeature* ConfiguredFeatures::SWAMP_TREE;
ConfiguredFeature* ConfiguredFeatures::JUNGLE_BUSH;
ConfiguredFeature* ConfiguredFeatures::OAK_BEES_0002;
ConfiguredFeature* ConfiguredFeatures::OAK_BEES_002;
ConfiguredFeature* ConfiguredFeatures::OAK_BEES_005;
ConfiguredFeature* ConfiguredFeatures::BIRCH_BEES_0002;
ConfiguredFeature* ConfiguredFeatures::BIRCH_BEES_002;
ConfiguredFeature* ConfiguredFeatures::BIRCH_BEES_005;
ConfiguredFeature* ConfiguredFeatures::FANCY_OAK_BEES_0002;
ConfiguredFeature* ConfiguredFeatures::FANCY_OAK_BEES_002;
ConfiguredFeature* ConfiguredFeatures::FANCY_OAK_BEES_005;
ConfiguredFeature* ConfiguredFeatures::OAK_BADLANDS;
ConfiguredFeature* ConfiguredFeatures::SPRUCE_SNOWY;
ConfiguredFeature* ConfiguredFeatures::FLOWER_WARM;
ConfiguredFeature* ConfiguredFeatures::FLOWER_DEFAULT;
ConfiguredFeature* ConfiguredFeatures::FLOWER_FOREST;
ConfiguredFeature* ConfiguredFeatures::FLOWER_SWAMP;
ConfiguredFeature* ConfiguredFeatures::FLOWER_PLAIN;
ConfiguredFeature* ConfiguredFeatures::FLOWER_PLAIN_DECORATED;
ConfiguredFeature* ConfiguredFeatures::FOREST_FLOWER_VEGETATION_COMMON;
ConfiguredFeature* ConfiguredFeatures::FOREST_FLOWER_VEGETATION;
ConfiguredFeature* ConfiguredFeatures::DARK_FOREST_VEGETATION_BROWN;
ConfiguredFeature* ConfiguredFeatures::DARK_FOREST_VEGETATION_RED;
ConfiguredFeature* ConfiguredFeatures::WARM_OCEAN_VEGETATION;
ConfiguredFeature* ConfiguredFeatures::FOREST_FLOWER_TREES;
ConfiguredFeature* ConfiguredFeatures::TAIGA_VEGETATION;
ConfiguredFeature* ConfiguredFeatures::TREES_SHATTERED_SAVANNA;
ConfiguredFeature* ConfiguredFeatures::TREES_SAVANNA;
ConfiguredFeature* ConfiguredFeatures::BIRCH_TALL;
ConfiguredFeature* ConfiguredFeatures::TREES_BIRCH;
ConfiguredFeature* ConfiguredFeatures::TREES_MOUNTAIN_EDGE;
ConfiguredFeature* ConfiguredFeatures::TREES_MOUNTAIN;
ConfiguredFeature* ConfiguredFeatures::TREES_WATER;
ConfiguredFeature* ConfiguredFeatures::BIRCH_OTHER;
ConfiguredFeature* ConfiguredFeatures::PLAIN_VEGETATION;
ConfiguredFeature* ConfiguredFeatures::TREES_JUNGLE_EDGE;
ConfiguredFeature* ConfiguredFeatures::TREES_GIANT_SPRUCE;
ConfiguredFeature* ConfiguredFeatures::TREES_GIANT;
ConfiguredFeature* ConfiguredFeatures::TREES_JUNGLE;
ConfiguredFeature* ConfiguredFeatures::BAMBOO_VEGETATION;
ConfiguredFeature* ConfiguredFeatures::MUSHROOM_FIELD_VEGETATION;

static ConfiguredFeature* registerFeature(std::string name, ConfiguredFeature* feature) {
	return ConfiguredFeatures::features.add(std::move(name), std::unique_ptr<ConfiguredFeature>(feature));
}

void ConfiguredFeatures::configureFeatures() {
    auto BEES_0002_PLACEMENT = new BeehiveTreeDecorator(0.002F);
    auto BEES_002_PLACEMENT = new BeehiveTreeDecorator(0.02F);
    auto BEES_005_PLACEMENT = new BeehiveTreeDecorator(0.05F);
    auto FIRE_PLACEMENT = Placements::FIRE->withConfiguration(FeatureSpreadConfig{10});
    auto FLOWER_TALL_GRASS_PLACEMENT = Placements::HEIGHTMAP->withConfiguration(NoPlacementConfig{});
    auto TOP_SOLID_PLACEMENT = Placements::TOP_SOLID_HEIGHTMAP->withConfiguration(NoPlacementConfig{});
    auto BAMBOO_PLACEMENT = Placements::HEIGHTMAP_WORLD_SURFACE->withConfiguration(NoPlacementConfig{});
    auto HEIGHTMAP_SPREAD_DOUBLE_PLACEMENT = Placements::HEIGHTMAP_SPREAD_DOUBLE->withConfiguration(NoPlacementConfig{});
    auto SPRING_CLOSED_PLACEMENT = Placements::RANGE->withConfiguration(TopSolidRangeConfig{10, 20, 128});
    auto SPRING_PLACEMENT = Placements::RANGE->withConfiguration(TopSolidRangeConfig{4, 8, 128});
    auto VEGETATION_PLACEMENT = Placements::SPREAD_32_ABOVE->withConfiguration(NoPlacementConfig{});
    auto HEIGHTMAP_PLACEMENT = FLOWER_TALL_GRASS_PLACEMENT->square();
    auto PATCH_PLACEMENT = HEIGHTMAP_SPREAD_DOUBLE_PLACEMENT->square();
    auto DISK_PLACEMENT = TOP_SOLID_PLACEMENT->square();

    static BlockClusterFeatureConfig GRASS_PATCH_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::GRASS->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 32,
    };
    static BlockClusterFeatureConfig TAIGA_GRASS_CONFIG {
        .stateProvider = new WeightedBlockStateProvider(WeightedList<BlockData>()
            .add(Blocks::GRASS->getDefaultState(), 1)
            .add(Blocks::FERN->getDefaultState(), 4)),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 32,
    };
    static BlockClusterFeatureConfig JUNGLE_VEGETATION_CONFIG {
        .stateProvider = new WeightedBlockStateProvider(WeightedList<BlockData>()
            .add(Blocks::GRASS->getDefaultState(), 3)
            .add(Blocks::FERN->getDefaultState(), 1)),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 32
    };
    static BlockClusterFeatureConfig NORMAL_FLOWER_CONFIG {
        .stateProvider = new WeightedBlockStateProvider(WeightedList<BlockData>()
            .add(Blocks::POPPY->getDefaultState(), 2)
            .add(Blocks::DANDELION->getDefaultState(), 1)),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64
    };
    static BlockClusterFeatureConfig FLOWER_FOREST_CONFIG {
        .stateProvider = new ForestFlowerBlockStateProvider(),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64
    };
    static BlockClusterFeatureConfig FLOWER_SWAMP_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::BLUE_ORCHID->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64
    };
    static BlockClusterFeatureConfig DEAD_BUSH_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::DEAD_BUSH->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 4
    };
    static BlockClusterFeatureConfig BERRY_BUSH_PATCH_CONFIG {
        .whitelist = {Blocks::GRASS_BLOCK},
        .stateProvider = new SimpleBlockStateProvider(Blocks::SWEET_BERRY_BUSH->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64,
        .project = false
    };
    static BlockClusterFeatureConfig TALL_GRASS_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::TALL_GRASS->getDefaultState()),
        .blockPlacer = new DoublePlantBlockPlacer(),
        .tries = 64,
        .project = false
    };
    static BlockClusterFeatureConfig LARGE_FERN_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::LARGE_FERN->getDefaultState()),
        .blockPlacer = new DoublePlantBlockPlacer(),
        .tries = 64,
        .project = false
    };
    static BlockClusterFeatureConfig SUGAR_CANE_PATCH_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::SUGAR_CANE->getDefaultState()),
        .blockPlacer = new ColumnBlockPlacer(2, 2),
        .tries = 20,
        .xspread = 4,
        .yspread = 0,
        .zspread = 4,
        .project = false,
        .requiresWater = true
    };

    static LiquidsConfig LAVA_SPRING_CONFIG{
        .state = Blocks::LAVA->getDefaultState(),
        .needsBlockBelow = true,
        .rockAmount = 4,
        .holeAmount = 1,
        .acceptedBlocks = {
            Blocks::STONE,
            Blocks::GRANITE,
            Blocks::DIORITE,
            Blocks::ANDESITE
        }
    };
    static LiquidsConfig CLOSED_SPRING_CONFIG{
        .state = Blocks::LAVA->getDefaultState(),
        .needsBlockBelow = false,
        .rockAmount = 5,
        .holeAmount = 0,
        .acceptedBlocks = {
            Blocks::NETHERRACK
        }
    };
//static BlockStateProvidingFeatureConfig CRIMSON_FOREST_VEGETATION_CONFIG = new BlockStateProvidingFeatureConfig((new WeightedBlockStateProvider()).addWeightedBlockstate(Features.States.CRIMSON_ROOTS, 87).addWeightedBlockstate(Features.States.CRIMSON_FUNGUS, 11).addWeightedBlockstate(Features.States.WARPED_FUNGUS, 1));
//static BlockStateProvidingFeatureConfig WARPED_FOREST_VEGETATION_CONFIG = new BlockStateProvidingFeatureConfig((new WeightedBlockStateProvider()).addWeightedBlockstate(Features.States.WARPED_ROOTS, 85).addWeightedBlockstate(Features.States.CRIMSON_ROOTS, 1).addWeightedBlockstate(Features.States.WARPED_FUNGUS, 13).addWeightedBlockstate(Features.States.CRIMSON_FUNGUS, 1));
//static BlockStateProvidingFeatureConfig NETHER_SPROUTS_CONFIG = new BlockStateProvidingFeatureConfig(new SimpleBlockStateProvider(Features.States.NETHER_SPROUTS));
    static BlockClusterFeatureConfig PLAINS_FLOWER_CONFIG {
        .stateProvider = new PlainFlowerBlockStateProvider(),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64
    };
    static BlockClusterFeatureConfig PATCH_CACTUS_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::CACTUS->getDefaultState()),
        .blockPlacer = new ColumnBlockPlacer(1, 2),
        .tries = 10,
        .project = false
    };
    static BlockClusterFeatureConfig PATCH_BROWN_MUSHROOM_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::BROWN_MUSHROOM->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64,
        .project = false
    };
    static BlockClusterFeatureConfig PATCH_RED_MUSHROOM_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::RED_MUSHROOM->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64,
        .project = false
    };
//    (new BlockClusterFeatureConfig.Builder(new SimpleBlockStateProvider(Blocks::SUNFLOWER->getDefaultState()), new DoublePlantBlockPlacer())).tries(64).project().build()
    static BlockClusterFeatureConfig PATCH_SUNFLOWER_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::SUNFLOWER->getDefaultState()),
        .blockPlacer = new DoublePlantBlockPlacer(),
        .tries = 64,
        .project = false
    };
    static BlockClusterFeatureConfig PATCH_MELON_CONFIG {
        .whitelist = {Blocks::GRASS_BLOCK},
        .stateProvider = new SimpleBlockStateProvider(Blocks::MELON->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64,
        .can_replace = true,
        .project = false
    };
    static BlockClusterFeatureConfig PATCH_WATERLILLY_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::LILY_PAD->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 10
    };
    static BlockClusterFeatureConfig PATCH_PUMKIN_CONFIG {
        .whitelist = {Blocks::GRASS_BLOCK},
        .stateProvider = new SimpleBlockStateProvider(Blocks::PUMPKIN->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64,
        .can_replace = true,
        .project = false
    };
    static BigMushroomFeatureConfig HUGE_BROWN_MUSHROOM_CONFIG {
        .capProvider = new SimpleBlockStateProvider(Blocks::BROWN_MUSHROOM_BLOCK->getStateWithMeta(14)), //.with(HugeMushroomBlock.UP, true).with(HugeMushroomBlock.DOWN, false)
        .stemProvider = new SimpleBlockStateProvider(Blocks::BROWN_MUSHROOM_BLOCK->getStateWithMeta(15)),
        .foliageRadius = 3
    };
    static BigMushroomFeatureConfig HUGE_RED_MUSHROOM_CONFIG {
        .capProvider = new SimpleBlockStateProvider(Blocks::RED_MUSHROOM_BLOCK->getStateWithMeta(14)), //.with(HugeMushroomBlock.UP, true).with(HugeMushroomBlock.DOWN, false)
        .stemProvider = new SimpleBlockStateProvider(Blocks::RED_MUSHROOM_BLOCK->getStateWithMeta(15)),
        .foliageRadius = 2
    };
    static BlockStateFeatureConfig LAKE_WATER_CONFIG {
        .state = Blocks::WATER->getDefaultState()
    };
    static BlockStateFeatureConfig LAKE_LAVA_CONFIG {
        .state = Blocks::LAVA->getDefaultState()
    };
    static BaseTreeFeatureConfig OAK_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::OAK_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::OAK_LEAVES->getDefaultState()),
        .foliagePlacer = new BlobFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{0, 0}, 3),
        .trunkPlacer = new StraightTrunkPlacer(4, 2, 0),
        .minimumSize = TwoLayerFeature{1, 0, 1, std::nullopt},
        .ignoreVines = true
    };
    static BaseTreeFeatureConfig DARK_OAK_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::DARK_OAK_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::DARK_OAK_LEAVES->getDefaultState()),
        .foliagePlacer = new DarkOakFoliagePlacer(FeatureSpread{0, 0}, FeatureSpread{0, 0}),
        .trunkPlacer = new DarkOakTrunkPlacer(6, 2, 1),
        .minimumSize = ThreeLayerFeature{1, 1, 0, 1, 2, std::nullopt},
        .maxWaterDepth = std::numeric_limits<int>::max(),
        .ignoreVines = true,
        .heightmap = HeightmapType::MOTION_BLOCKING
    };
    static BaseTreeFeatureConfig BIRCH_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::BIRCH_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::BIRCH_LEAVES->getDefaultState()),
        .foliagePlacer = new BlobFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{0, 0}, 3),
        .trunkPlacer = new StraightTrunkPlacer(5, 2, 0),
        .minimumSize = TwoLayerFeature{1, 0, 1, std::nullopt},
        .ignoreVines = true
    };
    static BaseTreeFeatureConfig ACACIA_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::ACACIA_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::ACACIA_LEAVES->getDefaultState()),
        .foliagePlacer = new AcaciaFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{0, 0}),
        .trunkPlacer = new ForkyTrunkPlacer(5, 2, 2),
        .minimumSize = TwoLayerFeature{1, 0, 2, std::nullopt},
        .ignoreVines = true,
    };
    static BaseTreeFeatureConfig SPRUCE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LEAVES->getDefaultState()),
        .foliagePlacer = new SpruceFoliagePlacer(FeatureSpread{2, 1}, FeatureSpread{0, 2}, FeatureSpread{1, 1}),
        .trunkPlacer = new StraightTrunkPlacer(5, 2, 1),
        .minimumSize = TwoLayerFeature{2, 0, 2, std::nullopt},
        .ignoreVines = true,
    };
    static BaseTreeFeatureConfig PINE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LEAVES->getDefaultState()),
        .foliagePlacer = new PineFoliagePlacer(FeatureSpread{1, 0}, FeatureSpread{1, 0}, FeatureSpread{3, 1}),
        .trunkPlacer = new StraightTrunkPlacer(6, 4, 0),
        .minimumSize = TwoLayerFeature{2, 0, 2, std::nullopt},
        .ignoreVines = true,
    };
    static BaseTreeFeatureConfig JUNGLE_TREE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LEAVES->getDefaultState()),
        .decorators {
            new CocoaTreeDecorator(0.2F),
            new TrunkVineTreeDecorator(),
            new LeaveVineTreeDecorator()
        },
        .foliagePlacer = new BlobFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{0, 0}, 3),
        .trunkPlacer = new StraightTrunkPlacer(4, 8, 0),
        .minimumSize = TwoLayerFeature{1, 0, 1, std::nullopt},
        .ignoreVines = true,
    };

    static BaseTreeFeatureConfig FANCY_OAK_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::OAK_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::OAK_LEAVES->getDefaultState()),
        .foliagePlacer = new FancyFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{4, 0}, 4),
        .trunkPlacer = new FancyTrunkPlacer(3, 11, 0),
        .minimumSize = TwoLayerFeature{0, 0, 0, 4},
        .ignoreVines = true,
        .heightmap = HeightmapType::MOTION_BLOCKING
    };

    static BaseTreeFeatureConfig JUNGLE_TREE_NO_VINE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LEAVES->getDefaultState()),
        .foliagePlacer = new BlobFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{0, 0}, 3),
        .trunkPlacer = new StraightTrunkPlacer(4, 8, 0),
        .minimumSize = TwoLayerFeature{1, 0, 1, std::nullopt},
        .ignoreVines = true,
    };

    static BaseTreeFeatureConfig MEGA_JUNGLE_TREE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LEAVES->getDefaultState()),
        .decorators {
            new TrunkVineTreeDecorator(),
            new LeaveVineTreeDecorator()
        },
        .foliagePlacer = new JungleFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{0, 0}, 2),
        .trunkPlacer = new MegaJungleTrunkPlacer(10, 2, 19),
        .minimumSize = TwoLayerFeature{1, 1, 2, std::nullopt}
    };

    static BaseTreeFeatureConfig MEGA_SPRUCE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LEAVES->getDefaultState()),
        .decorators {
            new AlterGroundTreeDecorator(new SimpleBlockStateProvider(Blocks::PODZOL->getDefaultState()))
        },
        .foliagePlacer = new MegaPineFoliagePlacer(FeatureSpread{0, 0}, FeatureSpread{0, 0}, FeatureSpread{13, 4}),
        .trunkPlacer = new GiantTrunkPlacer(13, 2, 14),
        .minimumSize = TwoLayerFeature{1, 1, 2, std::nullopt}
    };

    static BaseTreeFeatureConfig MEGA_PINE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::SPRUCE_LEAVES->getDefaultState()),
        .decorators {
            new AlterGroundTreeDecorator(new SimpleBlockStateProvider(Blocks::PODZOL->getDefaultState()))
        },
        .foliagePlacer = new MegaPineFoliagePlacer(FeatureSpread{0, 0}, FeatureSpread{0, 0}, FeatureSpread{3, 4}),
        .trunkPlacer = new GiantTrunkPlacer(13, 2, 14),
        .minimumSize = TwoLayerFeature{1, 1, 2, std::nullopt}
    };

    static BaseTreeFeatureConfig SUPER_BIRCH_BEES_0002_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::BIRCH_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::BIRCH_LEAVES->getDefaultState()),
        .decorators {
            BEES_0002_PLACEMENT
        },
        .foliagePlacer = new BlobFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{0, 0}, 3),
        .trunkPlacer = new StraightTrunkPlacer(5, 2, 6),
        .minimumSize = TwoLayerFeature{1, 0, 1, std::nullopt},
        .ignoreVines = true
    };

    static BaseTreeFeatureConfig SWAMP_TREE_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::OAK_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::OAK_LEAVES->getDefaultState()),
        .decorators {
            new LeaveVineTreeDecorator()
        },
        .foliagePlacer = new BlobFoliagePlacer(FeatureSpread{3, 0}, FeatureSpread{0, 0}, 3),
        .trunkPlacer = new StraightTrunkPlacer(5, 3, 0),
        .minimumSize = TwoLayerFeature{1, 0, 1, std::nullopt},
        .maxWaterDepth = 1,
        .heightmap = HeightmapType::MOTION_BLOCKING_NO_LEAVES,
    };

    static BaseTreeFeatureConfig JUNGLE_BUSH_CONFIG {
        .trunkProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LOG->getDefaultState()),
        .leavesProvider = new SimpleBlockStateProvider(Blocks::JUNGLE_LEAVES->getDefaultState()),
        .foliagePlacer = new BushFoliagePlacer(FeatureSpread{2, 0}, FeatureSpread{1, 0}, 2),
        .trunkPlacer = new StraightTrunkPlacer(1, 0, 0),
        .minimumSize = TwoLayerFeature{0, 0, 0, std::nullopt},
        .heightmap = HeightmapType::MOTION_BLOCKING_NO_LEAVES
    };

    static BlockStateProvidingFeatureConfig PILE_HAY_CONFIG {
        .stateProvider = new AxisRotatingBlockStateProvider(Blocks::HAY_BLOCK)
    };

    static BlockStateProvidingFeatureConfig PILE_MELON_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::MELON->getDefaultState())
    };

    static BlockStateProvidingFeatureConfig PILE_SNOW_CONFIG {
        .stateProvider = new SimpleBlockStateProvider(Blocks::SNOW->getDefaultState())
    };

    static BlockStateProvidingFeatureConfig PILE_ICE_CONFIG {
        .stateProvider = new WeightedBlockStateProvider(WeightedList<BlockData>()
            .add(Blocks::BLUE_ICE->getDefaultState(), 1)
            .add(Blocks::PACKED_ICE->getDefaultState(), 5))
    };
    static BlockStateProvidingFeatureConfig PILE_PUMPKIN_CONFIG {
        .stateProvider = new WeightedBlockStateProvider(WeightedList<BlockData>()
            .add(Blocks::PUMPKIN->getDefaultState(), 19)
            .add(Blocks::JACK_O_LANTERN->getDefaultState(), 1))
    };
    static BlockClusterFeatureConfig PILE_FIRE_CONFIG {
        .whitelist = {Blocks::NETHERRACK},
        .stateProvider = new SimpleBlockStateProvider(Blocks::FIRE->getDefaultState()),
        .blockPlacer = new SimpleBlockPlacer(),
        .tries = 64,
        .project = false
    };

    RuleTest BASE_STONE_OVERWORLD = TagMatchRuleTest{BlockTags::BASE_STONE_OVERWORLD};
    RuleTest NETHERRACK = BlockMatchRuleTest{Blocks::NETHERRACK};
    RuleTest BASE_STONE_NETHER = TagMatchRuleTest{BlockTags::BASE_STONE_NETHER};
    
// END_SPIKE = registerFeature("end_spike", Features::END_SPIKE->withConfiguration(new EndSpikeFeatureConfig(false, ImmutableList.of(), null)));
// END_GATEWAY = registerFeature("end_gateway", Features::END_GATEWAY->withConfiguration(EndGatewayConfig.func_214702_a(ServerWorld.field_241108_a_, true))->withPlacement(Placements::END_GATEWAY->withConfiguration(IPlacementConfig.NO_PLACEMENT_CONFIG)));
// END_GATEWAY_DELAYED = registerFeature("end_gateway_delayed", Features::END_GATEWAY->withConfiguration(EndGatewayConfig.func_214698_a()));
// CHORUS_PLANT = registerFeature("chorus_plant", Features::CHORUS_PLANT->withConfiguration(NoFeatureConfig{})->withPlacement(HEIGHTMAP_PLACEMENT)->func_242732_c(4));
// END_ISLAND = registerFeature("end_island", Features::END_ISLAND->withConfiguration(NoFeatureConfig{}));
// END_ISLAND_DECORATED = registerFeature("end_island_decorated", END_ISLAND->withPlacement(Placements::END_ISLAND->withConfiguration(IPlacementConfig.NO_PLACEMENT_CONFIG)));
// DELTA = registerFeature("delta", Features::DELTA_FEATURE::withConfiguration(new BasaltDeltasFeature(Features.States.LAVA_BLOCK, Features.States.MAGMA_BLOCK, FeatureSpread.create(3, 4), FeatureSpread.create(0, 2)))->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(40))));
// SMALL_BASALT_COLUMNS = registerFeature("small_basalt_columns", Features::BASALT_COLUMNS->withConfiguration(new ColumnConfig(FeatureSpread.create(1), FeatureSpread.create(1, 3)))->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(4))));
// LARGE_BASALT_COLUMNS = registerFeature("large_basalt_columns", Features::BASALT_COLUMNS->withConfiguration(new ColumnConfig(FeatureSpread.create(2, 1), FeatureSpread.create(5, 5)))->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(2))));
// BASALT_BLOBS = registerFeature("basalt_blobs", Features::NETHERRACK_REPLACE_BLOBS->withConfiguration(new BlobReplacementConfig(Features.States.NETHERRACK, Features.States.BASALT, FeatureSpread.create(3, 4)))->range(128)->square()->withSpreadPlacement(75));
// BLACKSTONE_BLOBS = registerFeature("blackstone_blobs", Features::NETHERRACK_REPLACE_BLOBS->withConfiguration(new BlobReplacementConfig(Features.States.NETHERRACK, Features.States.BLACKSTONE, FeatureSpread.create(3, 4)))->range(128)->square()->withSpreadPlacement(25));
// GLOWSTONE_EXTRA = registerFeature("glowstone_extra", Features::GLOWSTONE_BLOB->withConfiguration(NoFeatureConfig{})->withPlacement(Placements::GLOWSTONE->withConfiguration(new FeatureSpreadConfig(10))));
// GLOWSTONE = registerFeature("glowstone", Features::GLOWSTONE_BLOB->withConfiguration(NoFeatureConfig{})->range(128)->square()->withSpreadPlacement(10));
// CRIMSON_FOREST_VEGETATION = registerFeature("crimson_forest_vegetation", Features::NETHER_FOREST_VEGETATION->withConfiguration(CRIMSON_FOREST_VEGETATION_CONFIG)->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(6))));
// WARPED_FOREST_VEGETATION = registerFeature("warped_forest_vegetation", Features::NETHER_FOREST_VEGETATION->withConfiguration(WARPED_FOREST_VEGETATION_CONFIG)->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(5))));
// NETHER_SPROUTS = registerFeature("nether_sprouts", Features::NETHER_FOREST_VEGETATION->withConfiguration(NETHER_SPROUTS_CONFIG)->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(4))));
// TWISTING_VINES = registerFeature("twisting_vines", Features::TWISTING_VINES->withConfiguration(NoFeatureConfig{})->range(128)->square()->withSpreadPlacement(10));
// WEEPING_VINES = registerFeature("weeping_vines", Features::WEEPING_VINES->withConfiguration(NoFeatureConfig{})->range(128)->square()->withSpreadPlacement(10));
// BASALT_PILLAR = registerFeature("basalt_pillar", Features::BASALT_PILLAR->withConfiguration(NoFeatureConfig{})->range(128)->square()->withSpreadPlacement(10));
// SEAGRASS_COLD = registerFeature("seagrass_cold", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.3F))->withSpreadPlacement(32)->withPlacement(DISK_PLACEMENT));
// SEAGRASS_DEEP_COLD = registerFeature("seagrass_deep_cold", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.8F))->withSpreadPlacement(40)->withPlacement(DISK_PLACEMENT));
// SEAGRASS_NORMAL = registerFeature("seagrass_normal", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.3F))->withSpreadPlacement(48)->withPlacement(DISK_PLACEMENT));
// SEAGRASS_RIVER = registerFeature("seagrass_river", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.4F))->withSpreadPlacement(48)->withPlacement(DISK_PLACEMENT));
// SEAGRASS_DEEP = registerFeature("seagrass_deep", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.8F))->withSpreadPlacement(48)->withPlacement(DISK_PLACEMENT));
// SEAGRASS_SWAMP = registerFeature("seagrass_swamp", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.6F))->withSpreadPlacement(64)->withPlacement(DISK_PLACEMENT));
// SEAGRASS_WARM = registerFeature("seagrass_warm", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.3F))->withSpreadPlacement(80)->withPlacement(DISK_PLACEMENT));
// SEAGRASS_DEEP_WARM = registerFeature("seagrass_deep_warm", Features::SEAGRASS->withConfiguration(new ProbabilityConfig(0.8F))->withSpreadPlacement(80)->withPlacement(DISK_PLACEMENT));
// SEA_PICKLE = registerFeature("sea_pickle", Features::SEA_PICKLE->withConfiguration(new FeatureSpreadConfig(20))->withPlacement(DISK_PLACEMENT)->chance(16));
    ICE_SPIKE = registerFeature("ice_spike", Features::ICE_SPIKE->withConfiguration(NoFeatureConfig{})->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(3));
    ICE_PATCH = registerFeature("ice_patch", Features::ICE_PATCH->withConfiguration(SphereReplaceConfig{Blocks::PACKED_ICE->getDefaultState(), FeatureSpread{2, 1}, 1, {Blocks::DIRT->getDefaultState(), Blocks::GRASS_BLOCK->getDefaultState(), Blocks::PODZOL->getDefaultState(), Blocks::COARSE_DIRT->getDefaultState(), Blocks::MYCELIUM->getDefaultState(), Blocks::SNOW_BLOCK->getDefaultState(), Blocks::ICE->getDefaultState()}})->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(2));
    FOREST_ROCK = registerFeature("forest_rock", Features::FOREST_ROCK->withConfiguration(BlockStateFeatureConfig{Blocks::MOSSY_COBBLESTONE->getDefaultState()})->withPlacement(HEIGHTMAP_PLACEMENT)->func_242732_c(2));
// SEAGRASS_SIMPLE = registerFeature("seagrass_simple", Features::SIMPLE_BLOCK->withConfiguration(new BlockWithContextConfig(Blocks::SEAGRASS->getDefaultState(), ImmutableList.of(Blocks::STONE->getDefaultState()), ImmutableList.of(Blocks::WATER_BLOCK->getDefaultState()), ImmutableList.of(Blocks::WATER_BLOCK->getDefaultState())))->withPlacement(Placements::CARVING_MASK->withConfiguration(new CaveEdgeConfig(GenerationStage.Carving.LIQUID, 0.1F))));
    ICEBERG_PACKED = registerFeature("iceberg_packed", Features::ICEBERG->withConfiguration(BlockStateFeatureConfig{Blocks::PACKED_ICE->getDefaultState()})->withPlacement(Placements::ICEBERG->withConfiguration(NoPlacementConfig{}))->chance(16));
    ICEBERG_BLUE = registerFeature("iceberg_blue", Features::ICEBERG->withConfiguration(BlockStateFeatureConfig{Blocks::BLUE_ICE->getDefaultState()})->withPlacement(Placements::ICEBERG->withConfiguration(NoPlacementConfig{}))->chance(200));
// KELP_COLD = registerFeature("kelp_cold", Features::KELP->withConfiguration(NoFeatureConfig{})->withPlacement(TOP_SOLID_PLACEMENT)->square()->withPlacement(Placements::COUNT_NOISE_BIASED->withConfiguration(new TopSolidWithNoiseConfig(120, 80.0D, 0.0D))));
// KELP_WARM = registerFeature("kelp_warm", Features::KELP->withConfiguration(NoFeatureConfig{})->withPlacement(TOP_SOLID_PLACEMENT)->square()->withPlacement(Placements::COUNT_NOISE_BIASED->withConfiguration(new TopSolidWithNoiseConfig(80, 80.0D, 0.0D))));
    BLUE_ICE = registerFeature("blue_ice", Features::BLUE_ICE->withConfiguration(NoFeatureConfig{})->withPlacement(Placements::RANGE->withConfiguration(TopSolidRangeConfig{30, 32, 64}))->square()->func_242732_c(19));
    BAMBOO_LIGHT = registerFeature("bamboo_light", Features::BAMBOO->withConfiguration(ProbabilityConfig{0.0F})->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(16));
    BAMBOO = registerFeature("bamboo", Features::BAMBOO->withConfiguration(ProbabilityConfig{0.2F})->withPlacement(BAMBOO_PLACEMENT)->square()->withPlacement(Placements::COUNT_NOISE_BIASED->withConfiguration(TopSolidWithNoiseConfig{160, 80.0, 0.3})));
    VINES = registerFeature("vines", Features::VINES->withConfiguration(NoFeatureConfig{})->square()->withSpreadPlacement(50));
    LAKE_WATER = registerFeature("lake_water", Features::LAKE->withConfiguration(LAKE_WATER_CONFIG)->withPlacement(Placements::WATER_LAKE->withConfiguration(ChanceConfig{4})));
    LAKE_LAVA = registerFeature("lake_lava", Features::LAKE->withConfiguration(LAKE_LAVA_CONFIG)->withPlacement(Placements::LAVA_LAKE->withConfiguration(ChanceConfig{80})));
    DISK_CLAY = registerFeature("disk_clay", Features::DISK->withConfiguration(SphereReplaceConfig{Blocks::CLAY->getDefaultState(), FeatureSpread{2, 1}, 1, {Blocks::DIRT->getDefaultState(), Blocks::CLAY->getDefaultState()}})->withPlacement(DISK_PLACEMENT));
    DISK_GRAVEL = registerFeature("disk_gravel", Features::DISK->withConfiguration(SphereReplaceConfig{Blocks::GRAVEL->getDefaultState(), FeatureSpread{2, 3}, 2, {Blocks::DIRT->getDefaultState(), Blocks::GRASS_BLOCK->getDefaultState()}})->withPlacement(DISK_PLACEMENT));
    DISK_SAND = registerFeature("disk_sand", Features::DISK->withConfiguration(SphereReplaceConfig{Blocks::SAND->getDefaultState(), FeatureSpread{2, 4}, 2, {Blocks::DIRT->getDefaultState(), Blocks::GRASS_BLOCK->getDefaultState()}})->withPlacement(DISK_PLACEMENT)->withSpreadPlacement(3));
    FREEZE_TOP_LAYER = registerFeature("freeze_top_layer", Features::FREEZE_TOP_LAYER->withConfiguration(NoFeatureConfig{}));
    BONUS_CHEST = registerFeature("bonus_chest", Features::BONUS_CHEST->withConfiguration(NoFeatureConfig{}));
    VOID_START_PLATFORM = registerFeature("void_start_platform", Features::VOID_START_PLATFORM->withConfiguration(NoFeatureConfig{}));
    MONSTER_ROOM = registerFeature("monster_room", Features::MONSTER_ROOM->withConfiguration(NoFeatureConfig{})->range(256)->square()->withSpreadPlacement(8));
    DESERT_WELL = registerFeature("desert_well", Features::DESERT_WELL->withConfiguration(NoFeatureConfig{})->withPlacement(HEIGHTMAP_PLACEMENT)->chance(1000));
// FOSSIL = registerFeature("fossil", Features::FOSSIL->withConfiguration(NoFeatureConfig{})->chance(64));
    SPRING_LAVA_DOUBLE = registerFeature("spring_lava_double", Features::SPRING_FEATURE->withConfiguration(LAVA_SPRING_CONFIG)->withPlacement(Placements::RANGE_VERY_BIASED->withConfiguration(TopSolidRangeConfig{8, 16, 256}))->square()->withSpreadPlacement(40));
    SPRING_LAVA = registerFeature("spring_lava", Features::SPRING_FEATURE->withConfiguration(LAVA_SPRING_CONFIG)->withPlacement(Placements::RANGE_VERY_BIASED->withConfiguration(TopSolidRangeConfig{8, 16, 256}))->square()->withSpreadPlacement(20));
    SPRING_DELTA = registerFeature("spring_delta", Features::SPRING_FEATURE->withConfiguration(LiquidsConfig{Blocks::LAVA->getDefaultState(), true, 4, 1, { Blocks::NETHERRACK, Blocks::SOUL_SAND, Blocks::GRAVEL, Blocks::MAGMA_BLOCK, Blocks::BLACKSTONE}})->withPlacement(SPRING_PLACEMENT)->square()->withSpreadPlacement(16));
    SPRING_CLOSED = registerFeature("spring_closed", Features::SPRING_FEATURE->withConfiguration(CLOSED_SPRING_CONFIG)->withPlacement(SPRING_CLOSED_PLACEMENT)->square()->withSpreadPlacement(16));
    SPRING_CLOSED_DOUBLE = registerFeature("spring_closed_double", Features::SPRING_FEATURE->withConfiguration(CLOSED_SPRING_CONFIG)->withPlacement(SPRING_CLOSED_PLACEMENT)->square()->withSpreadPlacement(32));
    SPRING_OPEN = registerFeature("spring_open", Features::SPRING_FEATURE->withConfiguration(LiquidsConfig{Blocks::LAVA->getDefaultState(), false, 4, 1, {Blocks::NETHERRACK}})->withPlacement(SPRING_PLACEMENT)->square()->withSpreadPlacement(8));
    SPRING_WATER = registerFeature("spring_water", Features::SPRING_FEATURE->withConfiguration(LiquidsConfig{Blocks::WATER->getDefaultState(), true, 4, 1, {Blocks::STONE, Blocks::GRANITE, Blocks::DIORITE, Blocks::ANDESITE}})->withPlacement(Placements::RANGE_BIASED->withConfiguration(TopSolidRangeConfig{8, 8, 256}))->square()->withSpreadPlacement(50));
    PILE_HAY = registerFeature("pile_hay", Features::BLOCK_PILE->withConfiguration(PILE_HAY_CONFIG));
    PILE_MELON = registerFeature("pile_melon", Features::BLOCK_PILE->withConfiguration(PILE_MELON_CONFIG));
    PILE_SNOW = registerFeature("pile_snow", Features::BLOCK_PILE->withConfiguration(PILE_SNOW_CONFIG));
    PILE_ICE = registerFeature("pile_ice", Features::BLOCK_PILE->withConfiguration(PILE_ICE_CONFIG));
    PILE_PUMPKIN = registerFeature("pile_pumpkin", Features::BLOCK_PILE->withConfiguration(PILE_PUMPKIN_CONFIG));
    PATCH_FIRE = registerFeature("patch_fire", Features::RANDOM_PATCH->withConfiguration(PILE_FIRE_CONFIG)->withPlacement(FIRE_PLACEMENT));
// PATCH_SOUL_FIRE = registerFeature("patch_soul_fire", Features::RANDOM_PATCH->withConfiguration((new BlockClusterFeatureConfig.Builder(new SimpleBlockStateProvider(Blocks::SOUL_FIRE->getDefaultState()), new SimpleBlockPlacer())).tries(64).whitelist(ImmutableSet.of(Blocks::SOUL_SOIL->getDefaultState().getBlock())).project().build())->withPlacement(FIRE_PLACEMENT));
    PATCH_BROWN_MUSHROOM = registerFeature("patch_brown_mushroom", Features::RANDOM_PATCH->withConfiguration(PATCH_BROWN_MUSHROOM_CONFIG));
    PATCH_RED_MUSHROOM = registerFeature("patch_red_mushroom", Features::RANDOM_PATCH->withConfiguration(PATCH_RED_MUSHROOM_CONFIG));
// PATCH_CRIMSON_ROOTS = registerFeature("patch_crimson_roots", Features::RANDOM_PATCH->withConfiguration((new BlockClusterFeatureConfig.Builder(new SimpleBlockStateProvider(Blocks::CRIMSON_ROOTS->getDefaultState()), new SimpleBlockPlacer())).tries(64).project().build())->range(128));
    PATCH_SUNFLOWER = registerFeature("patch_sunflower", Features::RANDOM_PATCH->withConfiguration(PATCH_SUNFLOWER_CONFIG)->withPlacement( VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(10));
    PATCH_PUMPKIN = registerFeature("patch_pumpkin", Features::RANDOM_PATCH->withConfiguration(PATCH_PUMKIN_CONFIG)->withPlacement(PATCH_PLACEMENT)->chance(32));
    PATCH_TAIGA_GRASS = registerFeature("patch_taiga_grass", Features::RANDOM_PATCH->withConfiguration(TAIGA_GRASS_CONFIG));
    PATCH_BERRY_BUSH = registerFeature("patch_berry_bush", Features::RANDOM_PATCH->withConfiguration(BERRY_BUSH_PATCH_CONFIG));
    PATCH_GRASS_PLAIN = registerFeature("patch_grass_plain", Features::RANDOM_PATCH->withConfiguration(GRASS_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withPlacement(Placements::COUNT_NOISE->withConfiguration(NoiseDependantConfig{-0.8, 5, 10})));
    PATCH_GRASS_FOREST = registerFeature("patch_grass_forest", Features::RANDOM_PATCH->withConfiguration(GRASS_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(2));
    PATCH_GRASS_BADLANDS = registerFeature("patch_grass_badlands", Features::RANDOM_PATCH->withConfiguration(GRASS_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT));
    PATCH_GRASS_SAVANNA = registerFeature("patch_grass_savanna", Features::RANDOM_PATCH->withConfiguration(GRASS_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(20));
    PATCH_GRASS_NORMAL = registerFeature("patch_grass_normal", Features::RANDOM_PATCH->withConfiguration(GRASS_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(5));
    PATCH_GRASS_TAIGA_2 = registerFeature("patch_grass_taiga_2", Features::RANDOM_PATCH->withConfiguration(TAIGA_GRASS_CONFIG)->withPlacement(PATCH_PLACEMENT));
    PATCH_GRASS_TAIGA = registerFeature("patch_grass_taiga", Features::RANDOM_PATCH->withConfiguration(TAIGA_GRASS_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(7));
    PATCH_GRASS_JUNGLE = registerFeature("patch_grass_jungle", Features::RANDOM_PATCH->withConfiguration(JUNGLE_VEGETATION_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(25));
    PATCH_DEAD_BUSH_2 = registerFeature("patch_dead_bush_2", Features::RANDOM_PATCH->withConfiguration(DEAD_BUSH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(2));
    PATCH_DEAD_BUSH = registerFeature("patch_dead_bush", Features::RANDOM_PATCH->withConfiguration(DEAD_BUSH_CONFIG)->withPlacement(PATCH_PLACEMENT));
    PATCH_DEAD_BUSH_BADLANDS = registerFeature("patch_dead_bush_badlands", Features::RANDOM_PATCH->withConfiguration(DEAD_BUSH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(20));
    PATCH_MELON = registerFeature("patch_melon", Features::RANDOM_PATCH->withConfiguration(PATCH_MELON_CONFIG)->withPlacement(PATCH_PLACEMENT));
    PATCH_BERRY_SPARSE = registerFeature("patch_berry_sparse", PATCH_BERRY_BUSH->withPlacement(PATCH_PLACEMENT));
    PATCH_BERRY_DECORATED = registerFeature("patch_berry_decorated", PATCH_BERRY_BUSH->withPlacement(PATCH_PLACEMENT)->chance(12));
    PATCH_WATERLILLY = registerFeature("patch_waterlilly", Features::RANDOM_PATCH->withConfiguration(PATCH_WATERLILLY_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(4));
    PATCH_TALL_GRASS_2 = registerFeature("patch_tall_grass_2", Features::RANDOM_PATCH->withConfiguration(TALL_GRASS_CONFIG)->withPlacement(VEGETATION_PLACEMENT)->withPlacement(FLOWER_TALL_GRASS_PLACEMENT)->square()->withPlacement(Placements::COUNT_NOISE->withConfiguration(NoiseDependantConfig{-0.8, 0, 7})));
    PATCH_TALL_GRASS = registerFeature("patch_tall_grass", Features::RANDOM_PATCH->withConfiguration(TALL_GRASS_CONFIG)->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(7));
    PATCH_LARGE_FERN = registerFeature("patch_large_fern", Features::RANDOM_PATCH->withConfiguration(LARGE_FERN_CONFIG)->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(7));
    PATCH_CACTUS = registerFeature("patch_cactus", Features::RANDOM_PATCH->withConfiguration(PATCH_CACTUS_CONFIG));
    PATCH_CACTUS_DESERT = registerFeature("patch_cactus_desert", PATCH_CACTUS->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(10));
    PATCH_CACTUS_DECORATED = registerFeature("patch_cactus_decorated", PATCH_CACTUS->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(5));
    PATCH_SUGAR_CANE_SWAMP = registerFeature("patch_sugar_cane_swamp", Features::RANDOM_PATCH->withConfiguration(SUGAR_CANE_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(20));
    PATCH_SUGAR_CANE_DESERT = registerFeature("patch_sugar_cane_desert", Features::RANDOM_PATCH->withConfiguration(SUGAR_CANE_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(60));
    PATCH_SUGAR_CANE_BADLANDS = registerFeature("patch_sugar_cane_badlands", Features::RANDOM_PATCH->withConfiguration(SUGAR_CANE_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(13));
    PATCH_SUGAR_CANE = registerFeature("patch_sugar_cane", Features::RANDOM_PATCH->withConfiguration(SUGAR_CANE_PATCH_CONFIG)->withPlacement(PATCH_PLACEMENT)->withSpreadPlacement(10));
    BROWN_MUSHROOM_NETHER = registerFeature("brown_mushroom_nether", PATCH_BROWN_MUSHROOM->range(128)->chance(2));
    RED_MUSHROOM_NETHER = registerFeature("red_mushroom_nether", PATCH_RED_MUSHROOM->range(128)->chance(2));
    BROWN_MUSHROOM_NORMAL = registerFeature("brown_mushroom_normal", PATCH_BROWN_MUSHROOM->withPlacement(PATCH_PLACEMENT)->chance(4));
    RED_MUSHROOM_NORMAL = registerFeature("red_mushroom_normal", PATCH_RED_MUSHROOM->withPlacement(PATCH_PLACEMENT)->chance(8));
    BROWN_MUSHROOM_TAIGA = registerFeature("brown_mushroom_taiga", PATCH_BROWN_MUSHROOM->chance(4)->withPlacement(HEIGHTMAP_PLACEMENT));
    RED_MUSHROOM_TAIGA = registerFeature("red_mushroom_taiga", PATCH_RED_MUSHROOM->chance(8)->withPlacement(PATCH_PLACEMENT));
    BROWN_MUSHROOM_GIANT = registerFeature("brown_mushroom_giant", BROWN_MUSHROOM_TAIGA->withSpreadPlacement(3));
    RED_MUSHROOM_GIANT = registerFeature("red_mushroom_giant", RED_MUSHROOM_TAIGA->withSpreadPlacement(3));
    BROWN_MUSHROOM_SWAMP = registerFeature("brown_mushroom_swamp", BROWN_MUSHROOM_TAIGA->withSpreadPlacement(8));
    RED_MUSHROOM_SWAMP = registerFeature("red_mushroom_swamp", RED_MUSHROOM_TAIGA->withSpreadPlacement(8));
    ORE_MAGMA = registerFeature("ore_magma", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::MAGMA_BLOCK->getDefaultState(), 33})->withPlacement(Placements::MAGMA->withConfiguration(NoPlacementConfig{}))->square()->withSpreadPlacement(4));
    ORE_SOUL_SAND = registerFeature("ore_soul_sand", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::SOUL_SAND->getDefaultState(), 12})->range(32)->square()->withSpreadPlacement(12));
    ORE_GOLD_DELTAS = registerFeature("ore_gold_deltas", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::NETHER_GOLD_ORE->getDefaultState(), 10})->withPlacement(SPRING_CLOSED_PLACEMENT)->square()->withSpreadPlacement(20));
    ORE_QUARTZ_DELTAS = registerFeature("ore_quartz_deltas", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::NETHER_QUARTZ_ORE->getDefaultState(), 14})->withPlacement(SPRING_CLOSED_PLACEMENT)->square()->withSpreadPlacement(32));
    ORE_GOLD_NETHER = registerFeature("ore_gold_nether", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::NETHER_GOLD_ORE->getDefaultState(), 10})->withPlacement(SPRING_CLOSED_PLACEMENT)->square()->withSpreadPlacement(10));
    ORE_QUARTZ_NETHER = registerFeature("ore_quartz_nether", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::NETHER_QUARTZ_ORE->getDefaultState(), 14})->withPlacement(SPRING_CLOSED_PLACEMENT)->square()->withSpreadPlacement(16));
    ORE_GRAVEL_NETHER = registerFeature("ore_gravel_nether", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::GRAVEL->getDefaultState(), 33})->withPlacement(Placements::RANGE->withConfiguration(TopSolidRangeConfig{5, 0, 37}))->square()->withSpreadPlacement(2));
    ORE_BLACKSTONE = registerFeature("ore_blackstone", Features::ORE->withConfiguration(OreFeatureConfig{NETHERRACK, Blocks::BLACKSTONE->getDefaultState(), 33})->withPlacement(Placements::RANGE->withConfiguration(TopSolidRangeConfig{5, 10, 37}))->square()->withSpreadPlacement(2));
    ORE_DIRT = registerFeature("ore_dirt", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::DIRT->getDefaultState(), 33})->range(256)->square()->withSpreadPlacement(10));
    ORE_GRAVEL = registerFeature("ore_gravel", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::GRAVEL->getDefaultState(), 33})->range(256)->square()->withSpreadPlacement(8));
    ORE_GRANITE = registerFeature("ore_granite", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::GRANITE->getDefaultState(), 33})->range(80)->square()->withSpreadPlacement(10));
    ORE_DIORITE = registerFeature("ore_diorite", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::DIORITE->getDefaultState(), 33})->range(80)->square()->withSpreadPlacement(10));
    ORE_ANDESITE = registerFeature("ore_andesite", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::ANDESITE->getDefaultState(), 33})->range(80)->square()->withSpreadPlacement(10));
    ORE_COAL = registerFeature("ore_coal", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::COAL_ORE->getDefaultState(), 17})->range(128)->square()->withSpreadPlacement(20));
    ORE_IRON = registerFeature("ore_iron", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::IRON_ORE->getDefaultState(), 9})->range(64)->square()->withSpreadPlacement(20));
    ORE_GOLD_EXTRA = registerFeature("ore_gold_extra", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::GOLD_ORE->getDefaultState(), 9})->withPlacement(Placements::RANGE->withConfiguration(TopSolidRangeConfig{32, 32, 80}))->square()->withSpreadPlacement(20));
    ORE_GOLD = registerFeature("ore_gold", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::GOLD_ORE->getDefaultState(), 9})->range(32)->square()->withSpreadPlacement(2));
    ORE_REDSTONE = registerFeature("ore_redstone", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::REDSTONE_ORE->getDefaultState(), 8})->range(16)->square()->withSpreadPlacement(8));
    ORE_DIAMOND = registerFeature("ore_diamond", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::DIAMOND_ORE->getDefaultState(), 8})->range(16)->square());
    ORE_LAPIS = registerFeature("ore_lapis", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::LAPIS_ORE->getDefaultState(), 7})->withPlacement(Placements::DEPTH_AVERAGE->withConfiguration(DepthAverageConfig{16, 16}))->square());
    ORE_INFESTED = registerFeature("ore_infested", Features::ORE->withConfiguration(OreFeatureConfig{BASE_STONE_OVERWORLD, Blocks::INFESTED_STONE->getDefaultState(), 9})->range(64)->square()->withSpreadPlacement(7));
    ORE_EMERALD = registerFeature("ore_emerald", Features::EMERALD_ORE->withConfiguration(ReplaceBlockConfig{Blocks::STONE->getDefaultState(), Blocks::EMERALD_ORE->getDefaultState()})->withPlacement(Placements::EMERALD_ORE->withConfiguration(NoPlacementConfig{})));
// ORE_DEBRIS_LARGE = registerFeature("ore_debris_large", Features::NO_SURFACE_ORE->withConfiguration(new OreFeatureConfig(OreFeatureConfig.FillerBlockType.BASE_STONE_NETHER, Blocks::ANCIENT_DEBRIS->getDefaultState(), 3))->withPlacement(Placements::DEPTH_AVERAGE->withConfiguration(new DepthAverageConfig(16, 8)))->square());
// ORE_DEBRIS_SMALL = registerFeature("ore_debris_small", Features::NO_SURFACE_ORE->withConfiguration(new OreFeatureConfig(OreFeatureConfig.FillerBlockType.BASE_STONE_NETHER, Blocks::ANCIENT_DEBRIS->getDefaultState(), 2))->withPlacement(Placements::RANGE->withConfiguration(new TopSolidRangeConfig(8, 16, 128)))->square());
// CRIMSON_FUNGI = registerFeature("crimson_fungi", Features::HUGE_FUNGUS->withConfiguration(HugeFungusConfig.field_236300_c_)->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(8))));
// CRIMSON_FUNGI_PLANTED = registerFeature("crimson_fungi_planted", Features::HUGE_FUNGUS->withConfiguration(HugeFungusConfig.field_236299_b_));
// WARPED_FUNGI = registerFeature("warped_fungi", Features::HUGE_FUNGUS->withConfiguration(HugeFungusConfig.field_236302_e_)->withPlacement(Placements::COUNT_MULTILAYER->withConfiguration(new FeatureSpreadConfig(8))));
// WARPED_FUNGI_PLANTED = registerFeature("warped_fungi_planted", Features::HUGE_FUNGUS->withConfiguration(HugeFungusConfig.field_236301_d_));
    HUGE_BROWN_MUSHROOM = registerFeature("huge_brown_mushroom", Features::HUGE_BROWN_MUSHROOM->withConfiguration(HUGE_BROWN_MUSHROOM_CONFIG));
    HUGE_RED_MUSHROOM = registerFeature("huge_red_mushroom", Features::HUGE_RED_MUSHROOM->withConfiguration(HUGE_RED_MUSHROOM_CONFIG));
    OAK = registerFeature("oak", Features::TREE->withConfiguration(OAK_CONFIG));
    DARK_OAK = registerFeature("dark_oak", Features::TREE->withConfiguration(DARK_OAK_CONFIG));
    BIRCH = registerFeature("birch", Features::TREE->withConfiguration(BIRCH_CONFIG));
    ACACIA = registerFeature("acacia", Features::TREE->withConfiguration(ACACIA_CONFIG));
    SPRUCE = registerFeature("spruce", Features::TREE->withConfiguration(SPRUCE_CONFIG));
    PINE = registerFeature("pine", Features::TREE->withConfiguration(PINE_CONFIG));
    JUNGLE_TREE = registerFeature("jungle_tree", Features::TREE->withConfiguration(JUNGLE_TREE_CONFIG));
    FANCY_OAK = registerFeature("fancy_oak", Features::TREE->withConfiguration(FANCY_OAK_CONFIG));
    JUNGLE_TREE_NO_VINE = registerFeature("jungle_tree_no_vine", Features::TREE->withConfiguration(JUNGLE_TREE_NO_VINE_CONFIG));
    MEGA_JUNGLE_TREE = registerFeature("mega_jungle_tree", Features::TREE->withConfiguration(MEGA_JUNGLE_TREE_CONFIG));
    MEGA_SPRUCE = registerFeature("mega_spruce", Features::TREE->withConfiguration(MEGA_SPRUCE_CONFIG));
    MEGA_PINE = registerFeature("mega_pine", Features::TREE->withConfiguration(MEGA_PINE_CONFIG));
    SUPER_BIRCH_BEES_0002 = registerFeature("super_birch_bees_0002", Features::TREE->withConfiguration(SUPER_BIRCH_BEES_0002_CONFIG));
    SWAMP_TREE = registerFeature("swamp_tree", Features::TREE->withConfiguration(SWAMP_TREE_CONFIG)->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{2, 0.1F, 1})));
    JUNGLE_BUSH = registerFeature("jungle_bush", Features::TREE->withConfiguration(JUNGLE_BUSH_CONFIG));
    OAK_BEES_0002 = registerFeature("oak_bees_0002", Features::TREE->withConfiguration(OAK_CONFIG.withDecorators({BEES_0002_PLACEMENT})));
    OAK_BEES_002 = registerFeature("oak_bees_002", Features::TREE->withConfiguration(OAK_CONFIG.withDecorators({BEES_002_PLACEMENT})));
    OAK_BEES_005 = registerFeature("oak_bees_005", Features::TREE->withConfiguration(OAK_CONFIG.withDecorators({BEES_005_PLACEMENT})));
    BIRCH_BEES_0002 = registerFeature("birch_bees_0002", Features::TREE->withConfiguration(BIRCH_CONFIG.withDecorators({BEES_0002_PLACEMENT})));
    BIRCH_BEES_002 = registerFeature("birch_bees_002", Features::TREE->withConfiguration(BIRCH_CONFIG.withDecorators({BEES_002_PLACEMENT})));
    BIRCH_BEES_005 = registerFeature("birch_bees_005", Features::TREE->withConfiguration(BIRCH_CONFIG.withDecorators({BEES_005_PLACEMENT})));
    FANCY_OAK_BEES_0002 = registerFeature("fancy_oak_bees_0002", Features::TREE->withConfiguration(FANCY_OAK_CONFIG.withDecorators({BEES_0002_PLACEMENT})));
    FANCY_OAK_BEES_002 = registerFeature("fancy_oak_bees_002", Features::TREE->withConfiguration(FANCY_OAK_CONFIG.withDecorators({BEES_002_PLACEMENT})));
    FANCY_OAK_BEES_005 = registerFeature("fancy_oak_bees_005", Features::TREE->withConfiguration(FANCY_OAK_CONFIG.withDecorators({BEES_005_PLACEMENT})));
    OAK_BADLANDS = registerFeature("oak_badlands", OAK->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{5, 0.1F, 1})));
    SPRUCE_SNOWY = registerFeature("spruce_snowy", SPRUCE->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{0, 0.1F, 1})));
    FLOWER_WARM = registerFeature("flower_warm", Features::FLOWER->withConfiguration(NORMAL_FLOWER_CONFIG)->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(4));
    FLOWER_DEFAULT = registerFeature("flower_default", Features::FLOWER->withConfiguration(NORMAL_FLOWER_CONFIG)->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(2));
    FLOWER_FOREST = registerFeature("flower_forest", Features::FLOWER->withConfiguration(FLOWER_FOREST_CONFIG)->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(100));
    FLOWER_SWAMP = registerFeature("flower_swamp", Features::FLOWER->withConfiguration(FLOWER_SWAMP_CONFIG)->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT));
    FLOWER_PLAIN = registerFeature("flower_plain", Features::FLOWER->withConfiguration(PLAINS_FLOWER_CONFIG));
    FLOWER_PLAIN_DECORATED = registerFeature("flower_plain_decorated", FLOWER_PLAIN->withPlacement(VEGETATION_PLACEMENT)->withPlacement(FLOWER_TALL_GRASS_PLACEMENT)->square()->withPlacement(Placements::COUNT_NOISE->withConfiguration(NoiseDependantConfig{-0.8, 15, 4})));
    std::vector<ConfiguredFeature*> FOREST_FLOWER_VEGETATION_LIST {
        Features::RANDOM_PATCH->withConfiguration(BlockClusterFeatureConfig{
            .stateProvider = new SimpleBlockStateProvider(Blocks::LILAC->getDefaultState()),
            .blockPlacer = new DoublePlantBlockPlacer(),
            .tries = 64,
            .project = false,
        }),
        Features::RANDOM_PATCH->withConfiguration(BlockClusterFeatureConfig{
            .stateProvider = new SimpleBlockStateProvider(Blocks::ROSE_BUSH->getDefaultState()),
            .blockPlacer = new DoublePlantBlockPlacer(),
            .tries = 64,
            .project = false,
        }),
        Features::RANDOM_PATCH->withConfiguration(BlockClusterFeatureConfig{
            .stateProvider = new SimpleBlockStateProvider(Blocks::PEONY->getDefaultState()),
            .blockPlacer = new DoublePlantBlockPlacer(),
            .tries = 64,
            .project = false,
        }),
        Features::NO_BONEMEAL_FLOWER->withConfiguration(BlockClusterFeatureConfig{
            .stateProvider = new SimpleBlockStateProvider(Blocks::LILY_OF_THE_VALLEY->getDefaultState()),
            .blockPlacer = new SimpleBlockPlacer(),
            .tries = 64
        })
    };
    FOREST_FLOWER_VEGETATION_COMMON = registerFeature("forest_flower_vegetation_common", Features::SIMPLE_RANDOM_SELECTOR->withConfiguration(SingleRandomFeatureConfig{FOREST_FLOWER_VEGETATION_LIST})->withSpreadPlacement(FeatureSpread{-1, 4})->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(5));
    FOREST_FLOWER_VEGETATION = registerFeature("forest_flower_vegetation", Features::SIMPLE_RANDOM_SELECTOR->withConfiguration(SingleRandomFeatureConfig{FOREST_FLOWER_VEGETATION_LIST})->withSpreadPlacement(FeatureSpread{-3, 4})->withPlacement(VEGETATION_PLACEMENT)->withPlacement(HEIGHTMAP_PLACEMENT)->withSpreadPlacement(5));
    DARK_FOREST_VEGETATION_BROWN = registerFeature("dark_forest_vegetation_brown", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{HUGE_BROWN_MUSHROOM->withChance(0.025F), HUGE_RED_MUSHROOM->withChance(0.05F), DARK_OAK->withChance(0.6666667F), BIRCH->withChance(0.2F), FANCY_OAK->withChance(0.1F)}, OAK})->withPlacement(Placements::DARK_OAK_TREE->withConfiguration(NoPlacementConfig{})));
    DARK_FOREST_VEGETATION_RED = registerFeature("dark_forest_vegetation_red", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{HUGE_RED_MUSHROOM->withChance(0.025F), HUGE_BROWN_MUSHROOM->withChance(0.05F), DARK_OAK->withChance(0.6666667F), BIRCH->withChance(0.2F), FANCY_OAK->withChance(0.1F)}, OAK})->withPlacement(Placements::DARK_OAK_TREE->withConfiguration(NoPlacementConfig{})));
// WARM_OCEAN_VEGETATION = registerFeature("warm_ocean_vegetation", Features::SIMPLE_RANDOM_SELECTOR->withConfiguration(new SingleRandomFeature(ImmutableList.of(() -> {
//    return Features::CORAL_TREE->withConfiguration(NoFeatureConfig{});
// }, () -> {
//    return Features::CORAL_CLAW->withConfiguration(NoFeatureConfig{});
// }, () -> {
//    return Features::CORAL_MUSHROOM->withConfiguration(NoFeatureConfig{});
// })))->withPlacement(TOP_SOLID_PLACEMENT)->square()->withPlacement(Placements::COUNT_NOISE_BIASED->withConfiguration(new TopSolidWithNoiseConfig(20, 400.0D, 0.0D))));
    FOREST_FLOWER_TREES = registerFeature("forest_flower_trees", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{BIRCH_BEES_002->withChance(0.2F), FANCY_OAK_BEES_002->withChance(0.1F)}, OAK_BEES_002})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{6, 0.1F, 1})));
    TAIGA_VEGETATION = registerFeature("taiga_vegetation", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{PINE->withChance(0.33333334F)}, SPRUCE})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{10, 0.1F, 1})));
    TREES_SHATTERED_SAVANNA = registerFeature("trees_shattered_savanna", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{ACACIA->withChance(0.8F)}, OAK})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{2, 0.1F, 1})));
    TREES_SAVANNA = registerFeature("trees_savanna", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{ACACIA->withChance(0.8F)}, OAK})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{1, 0.1F, 1})));
    BIRCH_TALL = registerFeature("birch_tall", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{SUPER_BIRCH_BEES_0002->withChance(0.5F)}, BIRCH_BEES_0002})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{10, 0.1F, 1})));
    TREES_BIRCH = registerFeature("trees_birch", BIRCH_BEES_0002->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{10, 0.1F, 1})));
    TREES_MOUNTAIN_EDGE = registerFeature("trees_mountain_edge", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{SPRUCE->withChance(0.666F), FANCY_OAK->withChance(0.1F)}, OAK})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{3, 0.1F, 1})));
    TREES_MOUNTAIN = registerFeature("trees_mountain", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{SPRUCE->withChance(0.666F), FANCY_OAK->withChance(0.1F)}, OAK})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{0, 0.1F, 1})));
    TREES_WATER = registerFeature("trees_water", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{FANCY_OAK->withChance(0.1F)}, OAK})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{0, 0.1F, 1})));
    BIRCH_OTHER = registerFeature("birch_other", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{BIRCH_BEES_0002->withChance(0.2F), FANCY_OAK_BEES_0002->withChance(0.1F)}, OAK_BEES_0002})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{10, 0.1F, 1})));
    PLAIN_VEGETATION = registerFeature("plain_vegetation", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{FANCY_OAK_BEES_005->withChance(0.33333334F)}, OAK_BEES_005})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{0, 0.05F, 1})));
    TREES_JUNGLE_EDGE = registerFeature("trees_jungle_edge", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{FANCY_OAK->withChance(0.1F), JUNGLE_BUSH->withChance(0.5F)}, JUNGLE_TREE})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{2, 0.1F, 1})));
    TREES_GIANT_SPRUCE = registerFeature("trees_giant_spruce", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{MEGA_SPRUCE->withChance(0.33333334F), PINE->withChance(0.33333334F)}, SPRUCE})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{10, 0.1F, 1})));
    TREES_GIANT = registerFeature("trees_giant", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{MEGA_SPRUCE->withChance(0.025641026F), MEGA_PINE->withChance(0.30769232F), PINE->withChance(0.33333334F)}, SPRUCE})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{10, 0.1F, 1})));
    TREES_JUNGLE = registerFeature("trees_jungle", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{FANCY_OAK->withChance(0.1F), JUNGLE_BUSH->withChance(0.5F), MEGA_JUNGLE_TREE->withChance(0.33333334F)}, JUNGLE_TREE})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{50, 0.1F, 1})));
    BAMBOO_VEGETATION = registerFeature("bamboo_vegetation", Features::RANDOM_SELECTOR->withConfiguration(MultipleRandomFeatureConfig{{FANCY_OAK->withChance(0.05F), JUNGLE_BUSH->withChance(0.15F), MEGA_JUNGLE_TREE->withChance(0.7F)}, Features::RANDOM_PATCH->withConfiguration(JUNGLE_VEGETATION_CONFIG)})->withPlacement(HEIGHTMAP_PLACEMENT)->withPlacement(Placements::COUNT_EXTRA->withConfiguration(AtSurfaceWithExtraConfig{30, 0.1F, 1})));
    MUSHROOM_FIELD_VEGETATION = registerFeature("mushroom_field_vegetation", Features::RANDOM_BOOLEAN_SELECTOR->withConfiguration(TwoFeatureChoiceConfig{HUGE_RED_MUSHROOM, HUGE_BROWN_MUSHROOM})->withPlacement(HEIGHTMAP_PLACEMENT));
};