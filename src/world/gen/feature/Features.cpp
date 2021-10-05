#include "Features.hpp"
#include "OreFeature.hpp"
#include "TreeFeature.hpp"
#include "KelpFeature.hpp"
#include "LakesFeature.hpp"
#include "VinesFeature.hpp"
#include "SpringFeature.hpp"
#include "BambooFeature.hpp"
#include "IcePathFeature.hpp"
#include "BlueIceFeature.hpp"
#include "IcebergFeature.hpp"
#include "FossilsFeature.hpp"
#include "SeaGrassFeature.hpp"
#include "DungeonsFeature.hpp"
#include "IceSpikeFeature.hpp"
#include "EndSpikeFeature.hpp"
#include "EndIslandFeature.hpp"
#include "FillLayerFeature.hpp"
#include "BlockBlobFeature.hpp"
#include "BlockPileFeature.hpp"
#include "DecoratedFeature.hpp"
#include "CoralTreeFeature.hpp"
#include "CoralClawFeature.hpp"
#include "SeaPickleFeature.hpp"
#include "EndGatewayFeature.hpp"
#include "HugeFungusFeature.hpp"
#include "BonusChestFeature.hpp"
#include "IceAndSnowFeature.hpp"
#include "DesertWellsFeature.hpp"
#include "RandomPatchFeature.hpp"
#include "WeepingVineFeature.hpp"
#include "ChorusPlantFeature.hpp"
#include "BasaltPillarFeature.hpp"
#include "TwistingVineFeature.hpp"
#include "NoExposedOreFeature.hpp"
#include "ReplaceBlockFeature.hpp"
#include "SingleRandomFeature.hpp"
#include "BasaltColumnFeature.hpp"
#include "CoralMushroomFeature.hpp"
#include "GlowstoneBlobFeature.hpp"
#include "SphereReplaceFeature.hpp"
#include "DefaultFlowersFeature.hpp"
#include "BigRedMushroomFeature.hpp"
#include "BasaltDeltasStructure.hpp"
#include "NetherVegetationFeature.hpp"
#include "BigBrownMushroomFeature.hpp"
#include "BlockWithContextFeature.hpp"
#include "TwoFeatureChoiceFeature.hpp"
#include "VoidStartPlatformFeature.hpp"
#include "MultipleWithChanceRandomFeature.hpp"
#include "NetherackBlobReplacementStructure.hpp"

Registry<Feature> Features::features{};

Feature* Features::NO_OP;
Feature* Features::TREE;
Feature* Features::FLOWER;
Feature* Features::NO_BONEMEAL_FLOWER;
Feature* Features::RANDOM_PATCH;
Feature* Features::BLOCK_PILE;
Feature* Features::SPRING_FEATURE;
Feature* Features::CHORUS_PLANT;
Feature* Features::EMERALD_ORE;
Feature* Features::VOID_START_PLATFORM;
Feature* Features::DESERT_WELL;
Feature* Features::FOSSIL;
Feature* Features::HUGE_RED_MUSHROOM;
Feature* Features::HUGE_BROWN_MUSHROOM;
Feature* Features::ICE_SPIKE;
Feature* Features::GLOWSTONE_BLOB;
Feature* Features::FREEZE_TOP_LAYER;
Feature* Features::VINES;
Feature* Features::MONSTER_ROOM;
Feature* Features::BLUE_ICE;
Feature* Features::ICEBERG;
Feature* Features::FOREST_ROCK;
Feature* Features::DISK;
Feature* Features::ICE_PATCH;
Feature* Features::LAKE;
Feature* Features::ORE;
Feature* Features::END_SPIKE;
Feature* Features::END_ISLAND;
Feature* Features::END_GATEWAY;
Feature* Features::SEAGRASS;
Feature* Features::KELP;
Feature* Features::CORAL_TREE;
Feature* Features::CORAL_MUSHROOM;
Feature* Features::CORAL_CLAW;
Feature* Features::SEA_PICKLE;
Feature* Features::SIMPLE_BLOCK;
Feature* Features::BAMBOO;
Feature* Features::HUGE_FUNGUS;
Feature* Features::NETHER_FOREST_VEGETATION;
Feature* Features::WEEPING_VINES;
Feature* Features::TWISTING_VINES;
Feature* Features::BASALT_COLUMNS;
Feature* Features::DELTA_FEATURE;
Feature* Features::NETHERRACK_REPLACE_BLOBS;
Feature* Features::FILL_LAYER;
Feature* Features::BONUS_CHEST;
Feature* Features::BASALT_PILLAR;
Feature* Features::NO_SURFACE_ORE;
Feature* Features::RANDOM_SELECTOR;
Feature* Features::SIMPLE_RANDOM_SELECTOR;
Feature* Features::RANDOM_BOOLEAN_SELECTOR;
Feature* Features::DECORATED;

void Features::init() {
//    NO_OP = create<NoOpFeature>("no_op");
    TREE = create<TreeFeature>("tree");
    FLOWER = create<DefaultFlowersFeature>("flower");
    NO_BONEMEAL_FLOWER = create<DefaultFlowersFeature>("no_bonemeal_flower");
    RANDOM_PATCH = create<RandomPatchFeature>("random_patch");
    BLOCK_PILE = create<BlockPileFeature>("block_pile");
    SPRING_FEATURE = create<SpringFeature>("spring_feature");
    CHORUS_PLANT = create<ChorusPlantFeature>("chorus_plant");
    EMERALD_ORE = create<ReplaceBlockFeature>("emerald_ore");
    VOID_START_PLATFORM = create<VoidStartPlatformFeature>("void_start_platform");
    DESERT_WELL = create<DesertWellsFeature>("desert_well");
    FOSSIL = create<FossilsFeature>("fossil");
    HUGE_RED_MUSHROOM = create<BigRedMushroomFeature>("huge_red_mushroom");
    HUGE_BROWN_MUSHROOM = create<BigBrownMushroomFeature>("huge_brown_mushroom");
    ICE_SPIKE = create<IceSpikeFeature>("ice_spike");
    GLOWSTONE_BLOB = create<GlowstoneBlobFeature>("glowstone_blob");
    FREEZE_TOP_LAYER = create<IceAndSnowFeature>("freeze_top_layer");
    VINES = create<VinesFeature>("vines");
    MONSTER_ROOM = create<DungeonsFeature>("monster_room");
    BLUE_ICE = create<BlueIceFeature>("blue_ice");
    ICEBERG = create<IcebergFeature>("iceberg");
    FOREST_ROCK = create<BlockBlobFeature>("forest_rock");
    DISK = create<SphereReplaceFeature>("disk");
    ICE_PATCH = create<IcePathFeature>("ice_patch");
    LAKE = create<LakesFeature>("lake");
    ORE = create<OreFeature>("ore");
    END_SPIKE = create<EndSpikeFeature>("end_spike");
    END_ISLAND = create<EndIslandFeature>("end_island");
    END_GATEWAY = create<EndGatewayFeature>("end_gateway");
    SEAGRASS = create<SeaGrassFeature>("seagrass");
    KELP = create<KelpFeature>("kelp");
    CORAL_TREE = create<CoralTreeFeature>("coral_tree");
    CORAL_MUSHROOM = create<CoralMushroomFeature>("coral_mushroom");
    CORAL_CLAW = create<CoralClawFeature>("coral_claw");
    SEA_PICKLE = create<SeaPickleFeature>("sea_pickle");
    SIMPLE_BLOCK = create<BlockWithContextFeature>("simple_block");
    BAMBOO = create<BambooFeature>("bamboo");
    HUGE_FUNGUS = create<HugeFungusFeature>("huge_fungus");
    NETHER_FOREST_VEGETATION = create<NetherVegetationFeature>("nether_forest_vegetation");
    WEEPING_VINES = create<WeepingVineFeature>("weeping_vines");
    TWISTING_VINES = create<TwistingVineFeature>("twisting_vines");
    BASALT_COLUMNS = create<BasaltColumnFeature>("basalt_columns");
    DELTA_FEATURE = create<BasaltDeltasStructure>("delta_feature");
    NETHERRACK_REPLACE_BLOBS = create<NetherackBlobReplacementStructure>("netherrack_replace_blobs");
    FILL_LAYER = create<FillLayerFeature>("fill_layer");
    BONUS_CHEST = create<BonusChestFeature>("bonus_chest");
    BASALT_PILLAR = create<BasaltPillarFeature>("basalt_pillar");
    NO_SURFACE_ORE = create<NoExposedOreFeature>("no_surface_ore");
    RANDOM_SELECTOR = create<MultipleWithChanceRandomFeature>("random_selector");
    SIMPLE_RANDOM_SELECTOR = create<SingleRandomFeature>("simple_random_selector");
    RANDOM_BOOLEAN_SELECTOR = create<TwoFeatureChoiceFeature>("random_boolean_selector");
    DECORATED = create<DecoratedFeature>("decorated");
}
