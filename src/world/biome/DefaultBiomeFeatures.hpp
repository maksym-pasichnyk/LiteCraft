#pragma once

#include "MobSpawnInfo.hpp"
#include "BiomeGenerationSettings.hpp"
#include "../gen/carver/ConfiguredCarvers.hpp"
#include "../gen/feature/ConfiguredFeatures.hpp"
#include "../gen/feature/structure/StructureFeatures.hpp"

struct DefaultBiomeFeatures {
    static void withBadlandsStructures(BiomeGenerationSettings::Builder& builder) {
        builder.withStructure(StructureFeatures::MINESHAFT_BADLANDS);
//        builder.withStructure(StructureFeatures::STRONGHOLD);
    }

    static void withStrongholdAndMineshaft(BiomeGenerationSettings::Builder& builder) {
        builder.withStructure(StructureFeatures::MINESHAFT);
//        builder.withStructure(StructureFeatures::STRONGHOLD);
    }

    static void withOceanStructures(BiomeGenerationSettings::Builder& builder) {
        builder.withStructure(StructureFeatures::MINESHAFT);
//        builder.withStructure(StructureFeatures::SHIPWRECK);
    }

    static void withCavesAndCanyons(BiomeGenerationSettings::Builder& builder) {
        builder.withCarver(GenerationStage::Carving::AIR, ConfiguredCarvers::CAVE);
        builder.withCarver(GenerationStage::Carving::AIR, ConfiguredCarvers::CANYON);
    }

    static void withOceanCavesAndCanyons(BiomeGenerationSettings::Builder& builder) {
        builder.withCarver(GenerationStage::Carving::AIR, ConfiguredCarvers::OCEAN_CAVE);
        builder.withCarver(GenerationStage::Carving::AIR, ConfiguredCarvers::CANYON);
//        builder.withCarver(GenerationStage::Carving::LIQUID, ConfiguredCarvers::UNDERWATER_CANYON);
//        builder.withCarver(GenerationStage::Carving::LIQUID, ConfiguredCarvers::UNDERWATER_CAVE);
    }

    static void withLavaAndWaterLakes(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::LAKES, ConfiguredFeatures::LAKE_WATER);
        builder.withFeature(GenerationStage::Decoration::LAKES, ConfiguredFeatures::LAKE_LAVA);
    }

    static void withLavaLakes(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::LAKES, ConfiguredFeatures::LAKE_LAVA);
    }

    static void withMonsterRoom(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_STRUCTURES, ConfiguredFeatures::MONSTER_ROOM);
    }

    static void withCommonOverworldBlocks(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_DIRT);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_GRAVEL);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_GRANITE);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_DIORITE);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_ANDESITE);
    }

    static void withOverworldOres(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_COAL);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_IRON);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_GOLD);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_REDSTONE);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_DIAMOND);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_LAPIS);
    }

    static void withExtraGoldOre(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_GOLD_EXTRA);
    }

    static void withEmeraldOre(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::ORE_EMERALD);
    }

    static void withInfestedStone(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::ORE_INFESTED);
    }

    static void withDisks(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::DISK_SAND);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::DISK_CLAY);
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::DISK_GRAVEL);
    }

    static void withClayDisks(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_ORES, ConfiguredFeatures::DISK_CLAY);
    }

    static void withForestRocks(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::LOCAL_MODIFICATIONS, ConfiguredFeatures::FOREST_ROCK);
    }

    static void withLargeFern(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_LARGE_FERN);
    }

    static void withChanceBerries(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_BERRY_DECORATED);
    }

    static void withSparseBerries(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_BERRY_SPARSE);
    }

    static void withLightBambooVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BAMBOO_LIGHT);
    }

    static void withBambooVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BAMBOO);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BAMBOO_VEGETATION);
    }

    static void withTaigaVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TAIGA_VEGETATION);
    }

    static void withTreesInWater(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_WATER);
    }

    static void withBirchTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_BIRCH);
    }

    static void withForestBirchTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BIRCH_OTHER);
    }

    static void withTallBirches(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BIRCH_TALL);
    }

    static void withSavannaTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_SAVANNA);
    }

    static void withShatteredSavannaTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_SHATTERED_SAVANNA);
    }

    static void withMountainTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_MOUNTAIN);
    }

    static void withMountainEdgeTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_MOUNTAIN_EDGE);
    }

    static void withJungleTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_JUNGLE);
    }

    static void withJungleEdgeTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_JUNGLE_EDGE);
    }

    static void withBadlandsOakTrees(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::OAK_BADLANDS);
    }

    static void withSnowySpruces(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::SPRUCE_SNOWY);
    }

    static void withJungleGrass(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_JUNGLE);
    }

    static void withTallGrass(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_TALL_GRASS);
    }

    static void withNormalGrassPatch(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_NORMAL);
    }

    static void withSavannaGrass(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_SAVANNA);
    }

    static void withBadlandsGrassAndBush(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_BADLANDS);
//        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_DEAD_BUSH_BADLANDS);
    }

    static void withAllForestFlowerGeneration(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::FOREST_FLOWER_VEGETATION);
    }

    static void withForestGrass(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_FOREST);
    }

    static void withSwampVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::SWAMP_TREE);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::FLOWER_SWAMP);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_NORMAL);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_DEAD_BUSH);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_WATERLILLY);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BROWN_MUSHROOM_SWAMP);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::RED_MUSHROOM_SWAMP);
    }

    static void withMushroomBiomeVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::MUSHROOM_FIELD_VEGETATION);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BROWN_MUSHROOM_TAIGA);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::RED_MUSHROOM_TAIGA);
    }

    static void withPlainGrassVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PLAIN_VEGETATION);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::FLOWER_PLAIN_DECORATED);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_PLAIN);
    }

    static void withDesertDeadBushes(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_DEAD_BUSH_2);
    }

    static void withGiantTaigaGrassVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_TAIGA);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_DEAD_BUSH);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BROWN_MUSHROOM_GIANT);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::RED_MUSHROOM_GIANT);
    }

    static void withDefaultFlowers(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::FLOWER_DEFAULT);
    }

    static void withWarmFlowers(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::FLOWER_WARM);
    }

    static void withBadlandsGrass(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_BADLANDS);
    }

    static void withTaigaGrassVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_GRASS_TAIGA_2);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BROWN_MUSHROOM_TAIGA);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::RED_MUSHROOM_TAIGA);
    }

    static void withNoiseTallGrass(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_TALL_GRASS_2);
    }

    static void withNormalMushroomGeneration(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::BROWN_MUSHROOM_NORMAL);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::RED_MUSHROOM_NORMAL);
    }

    static void withSugarCaneAndPumpkins(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_SUGAR_CANE);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_PUMPKIN);
    }

    static void withBadlandsVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_SUGAR_CANE_BADLANDS);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_PUMPKIN);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_CACTUS_DECORATED);
    }

    static void withMelonPatchesAndVines(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_MELON);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::VINES);
    }

    static void withDesertVegetation(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_SUGAR_CANE_DESERT);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_PUMPKIN);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_CACTUS_DESERT);
    }

    static void withSwampSugarcaneAndPumpkin(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_SUGAR_CANE_SWAMP);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_PUMPKIN);
    }

    static void withDesertWells(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, ConfiguredFeatures::DESERT_WELL);
    }

    static void withFossils(BiomeGenerationSettings::Builder& builder) {
//        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_STRUCTURES, ConfiguredFeatures::FOSSIL);
    }

    static void withColdKelp(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::KELP_COLD);
    }

    static void withSimpleSeagrass(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::SEAGRASS_SIMPLE);
    }

    static void withWarmKelp(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::KELP_WARM);
    }

    static void withLavaAndWaterSprings(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::SPRING_WATER);
        builder.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::SPRING_LAVA);
    }

    static void withIcebergs(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::LOCAL_MODIFICATIONS, ConfiguredFeatures::ICEBERG_PACKED);
        builder.withFeature(GenerationStage::Decoration::LOCAL_MODIFICATIONS, ConfiguredFeatures::ICEBERG_BLUE);
    }

    static void withBlueIce(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, ConfiguredFeatures::BLUE_ICE);
    }

    static void withFrozenTopLayer(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::TOP_LAYER_MODIFICATION, ConfiguredFeatures::FREEZE_TOP_LAYER);
    }

    static void withCommonNetherBlocks(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::ORE_GRAVEL_NETHER);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::ORE_BLACKSTONE);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::ORE_GOLD_NETHER);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::ORE_QUARTZ_NETHER);
        withDebrisOre(builder);
    }

    static void withDebrisOre(BiomeGenerationSettings::Builder& builder) {
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::ORE_DEBRIS_LARGE);
        builder.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::ORE_DEBRIS_SMALL);
    }

    static void withPassiveMobs(MobSpawnInfo& builder) {
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::SHEEP, 12, 4, 4});
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::PIG, 10, 4, 4});
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::CHICKEN, 10, 4, 4});
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::COW, 8, 4, 4});
    }

    static void withBats(MobSpawnInfo& builder) {
        builder.spawners.emplace(EntityClassification::AMBIENT, MobSpawnInfo::Spawners{EntityType::BAT, 10, 8, 8});
    }

    static void withBatsAndHostiles(MobSpawnInfo& builder) {
        withBats(builder);
        withHostileMobs(builder, 95, 5, 100);
    }

    static void withOceanMobs(MobSpawnInfo& builder, int squidWeight, int squidMaxCount, int codWeight) {
        builder.spawners.emplace(EntityClassification::WATER_CREATURE, MobSpawnInfo::Spawners{EntityType::SQUID, squidWeight, 1, squidMaxCount});
        builder.spawners.emplace(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners{EntityType::COD, codWeight, 3, 6});
        withBatsAndHostiles(builder);
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::DROWNED, 5, 1, 1});
    }

    static void withWarmOceanMobs(MobSpawnInfo& builder, int squidWeight, int squidMinCount) {
        builder.spawners.emplace(EntityClassification::WATER_CREATURE, MobSpawnInfo::Spawners{EntityType::SQUID, squidWeight, squidMinCount, 4});
        builder.spawners.emplace(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners{EntityType::TROPICAL_FISH, 25, 8, 8});
        builder.spawners.emplace(EntityClassification::WATER_CREATURE, MobSpawnInfo::Spawners{EntityType::DOLPHIN, 2, 1, 2});
        withBatsAndHostiles(builder);
    }

    static void withSpawnsWithHorseAndDonkey(MobSpawnInfo& builder) {
        withPassiveMobs(builder);
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::HORSE, 5, 2, 6});
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::DONKEY, 1, 1, 3});
        withBatsAndHostiles(builder);
    }

    static void withSnowyBiomeMobs(MobSpawnInfo& builder) {
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::RABBIT, 10, 2, 3});
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::POLAR_BEAR, 1, 1, 2});
        withBats(builder);
        withHostileMobs(builder, 95, 5, 20);
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::STRAY, 80, 4, 4});
    }

    static void withDesertMobs(MobSpawnInfo& builder) {
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::RABBIT, 4, 2, 3});
        withBats(builder);
        withHostileMobs(builder, 19, 1, 100);
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::HUSK, 80, 4, 4});
    }

    static void withHostileMobs(MobSpawnInfo& builder, int zombieWeight, int zombieVillagerWeight, int skeletonWeight) {
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::SPIDER, 100, 4, 4});
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::ZOMBIE, zombieWeight, 4, 4});
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::ZOMBIE_VILLAGER, zombieVillagerWeight, 1, 1});
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::SKELETON, skeletonWeight, 4, 4});
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::CREEPER, 100, 4, 4});
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::SLIME, 100, 4, 4});
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::ENDERMAN, 10, 1, 4});
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::WITCH, 5, 1, 1});
    }

    static void withMooshroomsAndBats(MobSpawnInfo& builder) {
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::MOOSHROOM, 8, 4, 8});
        withBats(builder);
    }

    static void withSpawnsWithExtraChickens(MobSpawnInfo& builder) {
        withPassiveMobs(builder);
        builder.spawners.emplace(EntityClassification::CREATURE, MobSpawnInfo::Spawners{EntityType::CHICKEN, 10, 4, 4});
        withBatsAndHostiles(builder);
    }

    static void withEndermen(MobSpawnInfo& builder) {
        builder.spawners.emplace(EntityClassification::MONSTER, MobSpawnInfo::Spawners{EntityType::ENDERMAN, 10, 4, 4});
    }
};