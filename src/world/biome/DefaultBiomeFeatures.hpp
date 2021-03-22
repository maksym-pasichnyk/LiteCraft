#pragma once

#include "BiomeGenerationSettings.hpp"

struct DefaultBiomeFeatures {
    static void withBadlandsStructures(BiomeGenerationSettings::Builder& builder) {
//        builder.withStructure(StructureFeatures::MINESHAFT_BADLANDS);
//        builder.withStructure(StructureFeatures::STRONGHOLD);
    }

    static void withStrongholdAndMineshaft(BiomeGenerationSettings::Builder& builder) {
//        builder.withStructure(StructureFeatures::MINESHAFT);
//        builder.withStructure(StructureFeatures::STRONGHOLD);
    }

    static void withOceanStructures(BiomeGenerationSettings::Builder& builder) {
//        builder.withStructure(StructureFeatures::MINESHAFT);
//        builder.withStructure(StructureFeatures::SHIPWRECK);
    }

    static void withCavesAndCanyons(BiomeGenerationSettings::Builder& builder) {
//        builder.withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.CAVE);
//        builder.withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.CANYON);
    }

    static void withOceanCavesAndCanyons(BiomeGenerationSettings::Builder& builder) {
//        builder.withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.OCEAN_CAVE);
//        builder.withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.CANYON);
//        builder.withCarver(GenerationStage::Carving.LIQUID, ConfiguredCarvers.UNDERWATER_CANYON);
//        builder.withCarver(GenerationStage::Carving.LIQUID, ConfiguredCarvers.UNDERWATER_CAVE);
    }

    static void withLavaAndWaterLakes(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::LAKES, Features::LAKE_WATER);
//        builder.withFeature(GenerationStage::Decoration::LAKES, Features::LAKE_LAVA);
    }

    static void withLavaLakes(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::LAKES, Features::LAKE_LAVA);
    }

    static void withMonsterRoom(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_STRUCTURES, Features::MONSTER_ROOM);
    }

    static void withCommonOverworldBlocks(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_DIRT);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_GRAVEL);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_GRANITE);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_DIORITE);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_ANDESITE);
    }

    static void withOverworldOres(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_COAL);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_IRON);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_GOLD);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_REDSTONE);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_DIAMOND);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_LAPIS);
    }

    static void withExtraGoldOre(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_GOLD_EXTRA);
    }

    static void withEmeraldOre(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::ORE_EMERALD);
    }

    static void withInfestedStone(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_INFESTED);
    }

    static void withDisks(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::DISK_SAND);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::DISK_CLAY);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::DISK_GRAVEL);
    }

    static void withClayDisks(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, Features::DISK_CLAY);
    }

    static void withForestRocks(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::LOCAL_MODIFICATIONS, Features::FOREST_ROCK);
    }

    static void withLargeFern(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_LARGE_FERN);
    }

    static void withChanceBerries(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_BERRY_DECORATED);
    }

    static void withSparseBerries(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_BERRY_SPARSE);
    }

    static void withLightBambooVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BAMBOO_LIGHT);
    }

    static void withBambooVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BAMBOO);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BAMBOO_VEGETATION);
    }

    static void withTaigaVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TAIGA_VEGETATION);
    }

    static void withTreesInWater(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_WATER);
    }

    static void withBirchTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_BIRCH);
    }

    static void withForestBirchTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BIRCH_OTHER);
    }

    static void withTallBirches(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BIRCH_TALL);
    }

    static void withSavannaTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_SAVANNA);
    }

    static void withShatteredSavannaTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_SHATTERED_SAVANNA);
    }

    static void withMountainTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_MOUNTAIN);
    }

    static void withMountainEdgeTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_MOUNTAIN_EDGE);
    }

    static void withJungleTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_JUNGLE);
    }

    static void withJungleEdgeTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TREES_JUNGLE_EDGE);
    }

    static void withBadlandsOakTrees(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::OAK_BADLANDS);
    }

    static void withSnowySpruces(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRUCE_SNOWY);
    }

    static void withJungleGrass(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_JUNGLE);
    }

    static void withTallGrass(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_TALL_GRASS);
    }

    static void withNormalGrassPatch(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_NORMAL);
    }

    static void withSavannaGrass(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_SAVANNA);
    }

    static void withBadlandsGrassAndBush(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_BADLANDS);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_DEAD_BUSH_BADLANDS);
    }

    static void withAllForestFlowerGeneration(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FOREST_FLOWER_VEGETATION);
    }

    static void withForestGrass(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_FOREST);
    }

    static void withSwampVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SWAMP_TREE);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FLOWER_SWAMP);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_NORMAL);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_DEAD_BUSH);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_WATERLILLY);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BROWN_MUSHROOM_SWAMP);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::RED_MUSHROOM_SWAMP);
    }

    static void withMushroomBiomeVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::MUSHROOM_FIELD_VEGETATION);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BROWN_MUSHROOM_TAIGA);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::RED_MUSHROOM_TAIGA);
    }

    static void withPlainGrassVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PLAIN_VEGETATION);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FLOWER_PLAIN_DECORATED);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_PLAIN);
    }

    static void withDesertDeadBushes(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_DEAD_BUSH_2);
    }

    static void withGiantTaigaGrassVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_TAIGA);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_DEAD_BUSH);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BROWN_MUSHROOM_GIANT);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::RED_MUSHROOM_GIANT);
    }

    static void withDefaultFlowers(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FLOWER_DEFAULT);
    }

    static void withWarmFlowers(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FLOWER_WARM);
    }

    static void withBadlandsGrass(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_BADLANDS);
    }

    static void withTaigaGrassVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_GRASS_TAIGA_2);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BROWN_MUSHROOM_TAIGA);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::RED_MUSHROOM_TAIGA);
    }

    static void withNoiseTallGrass(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_TALL_GRASS_2);
    }

    static void withNormalMushroomGeneration(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::BROWN_MUSHROOM_NORMAL);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::RED_MUSHROOM_NORMAL);
    }

    static void withSugarCaneAndPumpkins(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_SUGAR_CANE);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_PUMPKIN);
    }

    static void withBadlandsVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_SUGAR_CANE_BADLANDS);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_PUMPKIN);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_CACTUS_DECORATED);
    }

    static void withMelonPatchesAndVines(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_MELON);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::VINES);
    }

    static void withDesertVegetation(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_SUGAR_CANE_DESERT);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_PUMPKIN);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_CACTUS_DESERT);
    }

    static void withSwampSugarcaneAndPumpkin(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_SUGAR_CANE_SWAMP);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_PUMPKIN);
    }

    static void withDesertWells(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::DESERT_WELL);
    }

    static void withFossils(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_STRUCTURES, Features::FOSSIL);
    }

    static void withColdKelp(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::KELP_COLD);
    }

    static void withSimpleSeagrass(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SEAGRASS_SIMPLE);
    }

    static void withWarmKelp(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::KELP_WARM);
    }

    static void withLavaAndWaterSprings(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRING_WATER);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRING_LAVA);
    }

    static void withIcebergs(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::LOCAL_MODIFICATIONS, Features::ICEBERG_PACKED);
//        builder.withFeature(GenerationStage::Decoration::LOCAL_MODIFICATIONS, Features::ICEBERG_BLUE);
    }

    static void withBlueIce(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::BLUE_ICE);
    }

    static void withFrozenTopLayer(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::TOP_LAYER_MODIFICATION, Features::FREEZE_TOP_LAYER);
    }

    static void withCommonNetherBlocks(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_GRAVEL_NETHER);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_BLACKSTONE);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_GOLD_NETHER);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_QUARTZ_NETHER);
//        withDebrisOre(builder);
    }

    static void withDebrisOre(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_DEBRIS_LARGE);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_DEBRIS_SMALL);
    }

//    static void withPassiveMobs(MobSpawnInfo::Builder& builder) {
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::SHEEP, 12, 4, 4));
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::PIG, 10, 4, 4));
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::CHICKEN, 10, 4, 4));
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::COW, 8, 4, 4));
//    }

//    static void withBats(MobSpawnInfo::Builder& builder) {
//        builder.withSpawner(EntityClassification::AMBIENT, new MobSpawnInfo::Spawners(EntityType::BAT, 10, 8, 8));
//    }

//    static void withBatsAndHostiles(MobSpawnInfo::Builder& builder) {
//        withBats(builder);
//        withHostileMobs(builder, 95, 5, 100);
//    }

//    static void withOceanMobs(MobSpawnInfo::Builder& builder, int squidWeight, int squidMaxCount, int codWeight) {
//        builder.withSpawner(EntityClassification::WATER_CREATURE, new MobSpawnInfo::Spawners(EntityType::SQUID, squidWeight, 1, squidMaxCount));
//        builder.withSpawner(EntityClassification::WATER_AMBIENT, new MobSpawnInfo::Spawners(EntityType::COD, codWeight, 3, 6));
//        withBatsAndHostiles(builder);
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::DROWNED, 5, 1, 1));
//    }

//    static void withWarmOceanMobs(MobSpawnInfo::Builder& builder, int squidWeight, int squidMinCount) {
//        builder.withSpawner(EntityClassification::WATER_CREATURE, new MobSpawnInfo::Spawners(EntityType::SQUID, squidWeight, squidMinCount, 4));
//        builder.withSpawner(EntityClassification::WATER_AMBIENT, new MobSpawnInfo::Spawners(EntityType::TROPICAL_FISH, 25, 8, 8));
//        builder.withSpawner(EntityClassification::WATER_CREATURE, new MobSpawnInfo::Spawners(EntityType::DOLPHIN, 2, 1, 2));
//        withBatsAndHostiles(builder);
//    }

//    static void withSpawnsWithHorseAndDonkey(MobSpawnInfo::Builder& builder) {
//        withPassiveMobs(builder);
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::HORSE, 5, 2, 6));
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::DONKEY, 1, 1, 3));
//        withBatsAndHostiles(builder);
//    }

//    static void withSnowyBiomeMobs(MobSpawnInfo::Builder& builder) {
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::RABBIT, 10, 2, 3));
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::POLAR_BEAR, 1, 1, 2));
//        withBats(builder);
//        withHostileMobs(builder, 95, 5, 20);
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::STRAY, 80, 4, 4));
//    }

//    static void withDesertMobs(MobSpawnInfo::Builder& builder) {
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::RABBIT, 4, 2, 3));
//        withBats(builder);
//        withHostileMobs(builder, 19, 1, 100);
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::HUSK, 80, 4, 4));
//    }

//    static void withHostileMobs(MobSpawnInfo::Builder& builder, int zombieWeight, int zombieVillagerWeight, int skeletonWeight) {
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::SPIDER, 100, 4, 4));
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::ZOMBIE, zombieWeight, 4, 4));
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::ZOMBIE_VILLAGER, zombieVillagerWeight, 1, 1));
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::SKELETON, skeletonWeight, 4, 4));
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::CREEPER, 100, 4, 4));
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::SLIME, 100, 4, 4));
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::ENDERMAN, 10, 1, 4));
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::WITCH, 5, 1, 1));
//    }

//    static void withMooshroomsAndBats(MobSpawnInfo::Builder& builder) {
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::MOOSHROOM, 8, 4, 8));
//        withBats(builder);
//    }

//    static void withSpawnsWithExtraChickens(MobSpawnInfo::Builder& builder) {
//        withPassiveMobs(builder);
//        builder.withSpawner(EntityClassification::CREATURE, new MobSpawnInfo::Spawners(EntityType::CHICKEN, 10, 4, 4));
//        withBatsAndHostiles(builder);
//    }

//    static void withEndermen(MobSpawnInfo::Builder& builder) {
//        builder.withSpawner(EntityClassification::MONSTER, new MobSpawnInfo::Spawners(EntityType::ENDERMAN, 10, 4, 4));
//    }
};