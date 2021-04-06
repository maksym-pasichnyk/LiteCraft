#pragma once

#include "DefaultBiomeFeatures.hpp"
#include "TemperatureModifiers.hpp"
#include "Biome.hpp"

#include "../gen/surface/ConfiguredSurfaceBuilders.hpp"

struct BiomeMaker {
    static int getSkyColorWithTemperatureModifier(float temperature) {
//        const float v = std::clamp(temperature / 3.0F, -1.0F, 1.0F);
        return 0;//MathHelper.hsvToRGB(0.62222224F - v * 0.05F, 0.5F + v * 0.1F, 1.0F);
    }

    static Biome* makeGiantTaigaBiome(float depth, float scale, float temperature, bool isSpruceVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        mobSpawnInfo.withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::WOLF, 8, 4, 4));
//        mobSpawnInfo.withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::RABBIT, 4, 2, 3));
//        mobSpawnInfo.withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::FOX, 8, 2, 4));
//        if (isSpruceVariant) {
//            DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
//        } else {
//            DefaultBiomeFeatures::withBats(mobSpawnInfo);
//            DefaultBiomeFeatures::withHostileMobs(mobSpawnInfo, 100, 25, 100);
//        }

        auto generation = BiomeGenerationSettings::Builder{}
                .withSurfaceBuilder(ConfiguredSurfaceBuilders::GIANT_TREE_TAIGA);
        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withForestRocks(generation);
        DefaultBiomeFeatures::withLargeFern(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        if (isSpruceVariant) {
            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_GIANT_SPRUCE);
        } else {
            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::TREES_GIANT);
        }
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withGiantTaigaGrassVegetation(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withSparseBerries(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = temperature,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.8F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::TAIGA,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(temperature),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeBirchForestBiome(float depth, float scale, bool isTallVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::GRASS);
        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withAllForestFlowerGeneration(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        if (isTallVariant) {
            DefaultBiomeFeatures::withTallBirches(generation);
        } else {
            DefaultBiomeFeatures::withBirchTrees(generation);
        }

        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withForestGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.6F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.6F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::FOREST,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.6F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeJungleBiome() {
        return makeGenericJungleBiome(0.1F, 0.2F, 40, 2, 3);
    }

    static Biome* makeJungleEdgeBiome() {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withSpawnsWithExtraChickens(mobSpawnInfo);
        return makeTropicalBiome(0.1F, 0.2F, 0.8F, false, true, false/*, mobSpawnInfo*/);
    }

    static Biome* makeModifiedJungleEdgeBiome() {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withSpawnsWithExtraChickens(mobSpawnInfo);
        return makeTropicalBiome(0.2F, 0.4F, 0.8F, false, true, true/*, mobSpawnInfo*/);
    }

    static Biome* makeModifiedJungleBiome() {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withSpawnsWithExtraChickens(mobSpawnInfo);
//        mobSpawnInfo.withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::PARROT, 10, 1, 1))
//        .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::OCELOT, 2, 1, 1));
        return makeTropicalBiome(0.2F, 0.4F, 0.9F, false, false, true/*, mobSpawnInfo*/);
    }

    static Biome* makeJungleHillsBiome() {
        return makeGenericJungleBiome(0.45F, 0.3F, 10, 1, 1);
    }

    static Biome* makeBambooJungleBiome() {
        return makeGenericBambooBiome(0.1F, 0.2F, 40, 2);
    }

    static Biome* makeBambooJungleHillsBiome() {
        return makeGenericBambooBiome(0.45F, 0.3F, 10, 1);
    }

    static Biome* makeGenericJungleBiome(float depth, float scale, int parrotWeight, int parrotMaxCount, int ocelotMaxCount) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withSpawnsWithExtraChickens(mobSpawnInfo);
//        mobSpawnInfo
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::PARROT, parrotWeight, 1, parrotMaxCount))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::OCELOT, 2, 1, ocelotMaxCount))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::PANDA, 1, 1, 2));
//        mobSpawnInfo.isValidSpawnBiomeForPlayer();
        return makeTropicalBiome(depth, scale, 0.9F, false, false, false/*, mobSpawnInfo*/);
    }



    static Biome* makeGenericBambooBiome(float depth, float scale, int parrotWeight, int parrotMaxCount) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withSpawnsWithExtraChickens(mobSpawnInfo);
//        mobSpawnInfo
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::PARROT, parrotWeight, 1, parrotMaxCount))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::PANDA, 80, 1, 2))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::OCELOT, 2, 1, 1));
        return makeTropicalBiome(depth, scale, 0.9F, true, false, false/*, mobSpawnInfo*/);
    }

    static Biome* makeTropicalBiome(float depth, float scale, float downfall, bool hasOnlyBambooVegetation, bool isEdgeBiome, bool isModified/*, MobSpawnInfo::Builder mobSpawnBuilder*/) {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::GRASS);
        if (!isEdgeBiome && !isModified) {
//            generation.withStructure(StructureFeatures::JUNGLE_PYRAMID);
        }

        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL_JUNGLE);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        if (hasOnlyBambooVegetation) {
            DefaultBiomeFeatures::withBambooVegetation(generation);
        } else {
            if (!isEdgeBiome && !isModified) {
                DefaultBiomeFeatures::withLightBambooVegetation(generation);
            }

            if (isEdgeBiome) {
                DefaultBiomeFeatures::withJungleEdgeTrees(generation);
            } else {
                DefaultBiomeFeatures::withJungleTrees(generation);
            }
        }

        DefaultBiomeFeatures::withWarmFlowers(generation);
        DefaultBiomeFeatures::withJungleGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withMelonPatchesAndVines(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.95F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = downfall
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::JUNGLE,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.95F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeMountainBiome(float depth, float scale, ConfiguredSurfaceBuilder surfaceBuilder, bool isEdgeBiome) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        mobSpawnInfo.withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::LLAMA, 5, 4, 6));
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(surfaceBuilder);
        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL_MOUNTAIN);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        if (isEdgeBiome) {
            DefaultBiomeFeatures::withMountainEdgeTrees(generation);
        } else {
            DefaultBiomeFeatures::withMountainTrees(generation);
        }

        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withBadlandsGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withEmeraldOre(generation);
        DefaultBiomeFeatures::withInfestedStone(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.2F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.3F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::EXTREME_HILLS,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.2F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeDesertBiome(float depth, float scale, bool hasVillageAndOutpost, bool hasDesertPyramid, bool hasFossils) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withDesertMobs(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::DESERT);
        if (hasVillageAndOutpost) {
//            generation.withStructure(StructureFeatures::VILLAGE_DESERT);
//            generation.withStructure(StructureFeatures::PILLAGER_OUTPOST);
        }

        if (hasDesertPyramid) {
//            generation.withStructure(StructureFeatures::DESERT_PYRAMID);
        }

        if (hasFossils) {
            DefaultBiomeFeatures::withFossils(generation);
        }

        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL_DESERT);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withBadlandsGrass(generation);
        DefaultBiomeFeatures::withDesertDeadBushes(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withDesertVegetation(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withDesertWells(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 2.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::DESERT,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(2.0F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makePlainsBiome(bool isSunflowerVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withSpawnsWithHorseAndDonkey(mobSpawnInfo);
        if (!isSunflowerVariant) {
//            mobSpawnInfo.isValidSpawnBiomeForPlayer();
        }

        BiomeGenerationSettings::Builder
        generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::GRASS);
        if (!isSunflowerVariant) {
//            generation
//                .withStructure(StructureFeatures::VILLAGE_PLAINS)
//                .withStructure(StructureFeatures::PILLAGER_OUTPOST);
        }

        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withNoiseTallGrass(generation);
        if (isSunflowerVariant) {
//            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::PATCH_SUNFLOWER);
        }

        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withPlainGrassVegetation(generation);
        if (isSunflowerVariant) {
            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_SUGAR_CANE);
        }

        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        if (isSunflowerVariant) {
            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, ConfiguredFeatures::PATCH_PUMPKIN);
        } else {
            DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        }

        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.8F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.4F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.125F,
            .scale = 0.05F,
            .category = BiomeCategory::PLAINS,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.8F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }
    static Biome* makeEndBiome(BiomeGenerationSettings::Builder generationSettingsBuilder) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withEndermen(mobSpawnInfo);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 0.5F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.5F
            },
            .biomeGenerationSettings = generationSettingsBuilder.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.1F,
            .scale = 0.2F,
            .category = BiomeCategory::THEEND,
            .effects{
                .fogColor = 10518688,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = 0,
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeEndBarrensBiome() {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::END);
        return makeEndBiome(generation);
    }

    static Biome* makeTheEndBiome() {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::END);
//            .withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::END_SPIKE);
        return makeEndBiome(generation);
    }

    static Biome* makeEndMidlandsBiome() {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::END);
//            .withStructure(StructureFeatures::END_CITY);
        return makeEndBiome(generation);
    }

    static Biome* makeEndHighlandsBiome() {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::END);
//            .withStructure(StructureFeatures::END_CITY)
//            .withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::END_GATEWAY)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::CHORUS_PLANT);
        return makeEndBiome(generation);
    }

    static Biome* makeSmallEndIslandsBiome() {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::END);
//            .withFeature(GenerationStage::Decoration::RAW_GENERATION, Features::END_ISLAND_DECORATED);
        return makeEndBiome(generation);
    }

    static Biome* makeMushroomBiome(float depth, float scale) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withMooshroomsAndBats(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::MYCELIUM);
        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withMushroomBiomeVegetation(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.9F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 1.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::MUSHROOM,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.9F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }



    static Biome* makeGenericSavannaBiome(float depth, float scale, float temperature, bool isHighland, bool isShatteredSavanna/*, MobSpawnInfo::Builder mobSpawnBuilder*/) {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(isShatteredSavanna ? ConfiguredSurfaceBuilders::SHATTERED_SAVANNA : ConfiguredSurfaceBuilders::GRASS);
        if (!isHighland && !isShatteredSavanna) {
//            generation
//                .withStructure(StructureFeatures::VILLAGE_SAVANNA)
//                .withStructure(StructureFeatures::PILLAGER_OUTPOST);
        }

        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation
//            .withStructure(isHighland ? StructureFeatures::RUINED_PORTAL_MOUNTAIN : StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        if (!isShatteredSavanna) {
            DefaultBiomeFeatures::withTallGrass(generation);
        }

        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        if (isShatteredSavanna) {
            DefaultBiomeFeatures::withShatteredSavannaTrees(generation);
            DefaultBiomeFeatures::withDefaultFlowers(generation);
            DefaultBiomeFeatures::withNormalGrassPatch(generation);
        } else {
            DefaultBiomeFeatures::withSavannaTrees(generation);
            DefaultBiomeFeatures::withWarmFlowers(generation);
            DefaultBiomeFeatures::withSavannaGrass(generation);
        }

        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = temperature,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::SAVANNA,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(temperature),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeSavannaBiome(float depth, float scale, float temperature, bool isHighland, bool isShatteredSavanna) {
//        MobSpawnInfo::Builder mobSpawnInfo = getSpawnsWithHorseAndDonkey();
        return makeGenericSavannaBiome(depth, scale, temperature, isHighland, isShatteredSavanna/*, mobSpawnInfo*/);
    }

//    static MobSpawnInfo::Builder getSpawnsWithHorseAndDonkey() {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        mobSpawnInfo
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::HORSE, 1, 2, 6))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::DONKEY, 1, 1, 1));
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
//        return mobSpawnInfo;
//    }

    static Biome* makeSavannaPlateauBiome() {
//        MobSpawnInfo::Builder mobSpawnInfo = getSpawnsWithHorseAndDonkey();
//        mobSpawnInfo.withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::LLAMA, 8, 4, 4));
        return makeGenericSavannaBiome(1.5F, 0.025F, 1.0F, true, false/*, mobSpawnInfo*/);
    }

    static Biome* makeGenericBadlandsBiome(ConfiguredSurfaceBuilder surfaceBuilder, float depth, float scale, bool isHighland, bool hasOakTrees) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(surfaceBuilder);
        DefaultBiomeFeatures::withBadlandsStructures(generation);
//        generation.withStructure(isHighland ? StructureFeatures::RUINED_PORTAL_MOUNTAIN : StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withExtraGoldOre(generation);
        DefaultBiomeFeatures::withDisks(generation);
        if (hasOakTrees) {
            DefaultBiomeFeatures::withBadlandsOakTrees(generation);
        }

        DefaultBiomeFeatures::withBadlandsGrassAndBush(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withBadlandsVegetation(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 2.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::MESA,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(2.0F),
                .foliageColor = 10387789,
                .grassColor = 9470285,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeBadlandsBiome(float depth, float scale, bool isHighland) {
        return makeGenericBadlandsBiome(ConfiguredSurfaceBuilders::BADLANDS, depth, scale, isHighland, false);
    }

    static Biome* makeWoodedBadlandsPlateauBiome(float depth, float scale) {
        return makeGenericBadlandsBiome(ConfiguredSurfaceBuilders::WOODED_BADLANDS, depth, scale, true, true);
    }

    static Biome* makeErodedBadlandsBiome() {
        return makeGenericBadlandsBiome(ConfiguredSurfaceBuilders::ERODED_BADLANDS, 0.1F, 0.2F, true, false);
    }

    static Biome* makeOceanBiome(/*MobSpawnInfo::Builder mobSpawnBuilder,*/ int waterColor, int waterFogColor, bool isDeepVariant, BiomeGenerationSettings::Builder generationSettingsBuilder) {
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.5F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.5F
            },
            .biomeGenerationSettings = generationSettingsBuilder.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = isDeepVariant ? -1.8F : -1.0F,
            .scale = 0.1F,
            .category = BiomeCategory::OCEAN,
            .effects{
                .fogColor = 12638463,
                .waterColor = waterColor,
                .waterFogColor = waterFogColor,
                .skyColor = getSkyColorWithTemperatureModifier(0.5F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

 static BiomeGenerationSettings::Builder getOceanGenerationSettingsBuilder(ConfiguredSurfaceBuilder surfaceBuilder, bool hasOceanMonument, bool isWarmOcean, bool isDeepVariant) {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(surfaceBuilder);
//        StructureFeature structurefeature = isWarmOcean
//                ? StructureFeatures::OCEAN_RUIN_WARM
//                : StructureFeatures::OCEAN_RUIN_COLD;
        if (isDeepVariant) {
            if (hasOceanMonument) {
//                generation.withStructure(StructureFeatures::MONUMENT);
            }

            DefaultBiomeFeatures::withOceanStructures(generation);
//            generation.withStructure(structurefeature);
        } else {
//            generation.withStructure(structurefeature);
            if (hasOceanMonument) {
//                generation.withStructure(StructureFeatures::MONUMENT);
            }

            DefaultBiomeFeatures::withOceanStructures(generation);
        }

//        generation.withStructure(StructureFeatures::RUINED_PORTAL_OCEAN);
        DefaultBiomeFeatures::withOceanCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withTreesInWater(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withBadlandsGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        return generation;
    }

    static Biome* makeColdOceanBiome(bool isDeepVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withOceanMobs(mobSpawnInfo, 3, 4, 15);
//        mobSpawnInfo.withSpawner(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners(EntityType::SALMON, 15, 1, 5));
        bool flag = !isDeepVariant;
        auto generation = getOceanGenerationSettingsBuilder(ConfiguredSurfaceBuilders::GRASS, isDeepVariant, false, flag);
//        generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, isDeepVariant ? Features::SEAGRASS_DEEP_COLD : Features::SEAGRASS_COLD);
        DefaultBiomeFeatures::withSimpleSeagrass(generation);
        DefaultBiomeFeatures::withColdKelp(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return makeOceanBiome(/*mobSpawnInfo,*/ 4020182, 329011, isDeepVariant, generation);
    }

    static Biome* makeOceanBiome(bool isDeepVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withOceanMobs(mobSpawnInfo, 1, 4, 10);
//        mobSpawnInfo.withSpawner(EntityClassification::WATER_CREATURE, MobSpawnInfo::Spawners(EntityType::DOLPHIN, 1, 1, 2));
        auto generation = getOceanGenerationSettingsBuilder(ConfiguredSurfaceBuilders::GRASS, isDeepVariant, false, true);
//        generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, isDeepVariant ? Features::SEAGRASS_DEEP : Features::SEAGRASS_NORMAL);
        DefaultBiomeFeatures::withSimpleSeagrass(generation);
        DefaultBiomeFeatures::withColdKelp(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return makeOceanBiome(/*mobSpawnInfo,*/ 4159204, 329011, isDeepVariant, generation);
    }

    static Biome* makeLukewarmOceanBiome(bool isDeepVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        if (isDeepVariant) {
//            DefaultBiomeFeatures::withOceanMobs(mobSpawnInfo, 8, 4, 8);
//        } else {
//            DefaultBiomeFeatures::withOceanMobs(mobSpawnInfo, 10, 2, 15);
//        }

//        mobSpawnInfo
//            .withSpawner(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners(EntityType::PUFFERFISH, 5, 1, 3))
//            .withSpawner(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners(EntityType::TROPICAL_FISH, 25, 8, 8))
//            .withSpawner(EntityClassification::WATER_CREATURE, MobSpawnInfo::Spawners(EntityType::DOLPHIN, 2, 1, 2));
        auto generation = getOceanGenerationSettingsBuilder(ConfiguredSurfaceBuilders::OCEAN_SAND, isDeepVariant, true, false);
//        generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, isDeepVariant ? Features::SEAGRASS_DEEP_WARM : Features::SEAGRASS_WARM);
        if (isDeepVariant) {
            DefaultBiomeFeatures::withSimpleSeagrass(generation);
        }

        DefaultBiomeFeatures::withWarmKelp(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return makeOceanBiome(/*mobSpawnInfo,*/ 4566514, 267827, isDeepVariant, generation);
    }

    static Biome* makeWarmOceanBiome() {
//        MobSpawnInfo::Builder mobSpawnInfo = MobSpawnInfo::Builder{}
//            .withSpawner(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners(EntityType::PUFFERFISH, 15, 1, 3));
//        DefaultBiomeFeatures::withWarmOceanMobs(mobSpawnInfo, 10, 4);
        auto generation = getOceanGenerationSettingsBuilder(ConfiguredSurfaceBuilders::FULL_SAND, false, true, false);
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::WARM_OCEAN_VEGETATION)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SEAGRASS_WARM)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SEA_PICKLE);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return makeOceanBiome(/*mobSpawnInfo,*/ 4445678, 270131, false, generation);
    }

    static Biome* makeDeepWarmOceanBiome() {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withWarmOceanMobs(mobSpawnInfo, 5, 1);
//        mobSpawnInfo.withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::DROWNED, 5, 1, 1));
        BiomeGenerationSettings::Builder
        generation = getOceanGenerationSettingsBuilder(ConfiguredSurfaceBuilders::FULL_SAND, true, true, false);
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SEAGRASS_DEEP_WARM);
        DefaultBiomeFeatures::withSimpleSeagrass(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return makeOceanBiome(/*mobSpawnInfo,*/ 4445678, 270131, true, generation);
    }

    static Biome* makeFrozenOceanBiome(bool isDeepVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo = MobSpawnInfo::Builder{}
//                .withSpawner(EntityClassification::WATER_CREATURE, MobSpawnInfo::Spawners(EntityType::SQUID, 1, 1, 4))
//                .withSpawner(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners(EntityType::SALMON, 15, 1, 5))
//                .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::POLAR_BEAR, 1, 1, 2));
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
//        mobSpawnInfo.withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::DROWNED, 5, 1, 1));
        const float temperature = isDeepVariant ? 0.5F : 0.0F;
        BiomeGenerationSettings::Builder
        generation = BiomeGenerationSettings::Builder{}
                .withSurfaceBuilder(ConfiguredSurfaceBuilders::FROZEN_OCEAN);
//        generation.withStructure(StructureFeatures::OCEAN_RUIN_COLD);
        if (isDeepVariant) {
//            generation.withStructure(StructureFeatures::MONUMENT);
        }

        DefaultBiomeFeatures::withOceanStructures(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL_OCEAN);
        DefaultBiomeFeatures::withOceanCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withIcebergs(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withBlueIce(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withTreesInWater(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withBadlandsGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);

        return new Biome {
            .climate{
                .precipitation = isDeepVariant ? RainType::RAIN : RainType::SNOW,
                .temperature = temperature,
                .temperatureModifier = TemperatureModifiers::frozen,
                .downfall = 0.5F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = isDeepVariant ? -1.8F : -1.0F,
            .scale = 0.1F,
            .category = BiomeCategory::OCEAN,
            .effects{
                .fogColor = 12638463,
                .waterColor = 3750089,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(temperature),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }



    static Biome* makeGenericForestBiome(float depth, float scale, bool isFlowerForestVariant/*, MobSpawnInfo::Builder mobSpawnBuilder*/) {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::GRASS);
        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        if (isFlowerForestVariant) {
//            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FOREST_FLOWER_VEGETATION_COMMON);
        } else {
            DefaultBiomeFeatures::withAllForestFlowerGeneration(generation);
        }

        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        if (isFlowerForestVariant) {
//            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FOREST_FLOWER_TREES);
//            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::FLOWER_FOREST);
            DefaultBiomeFeatures::withBadlandsGrass(generation);
        } else {
            DefaultBiomeFeatures::withForestBirchTrees(generation);
            DefaultBiomeFeatures::withDefaultFlowers(generation);
            DefaultBiomeFeatures::withForestGrass(generation);
        }

        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.7F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.8F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::FOREST,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.7F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

//    static MobSpawnInfo::Builder getStandardMobSpawnBuilder() {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
//        return mobSpawnInfo;
//    }

    static Biome* makeForestBiome(float depth, float scale) {
//        MobSpawnInfo::Builder mobSpawnInfo = getStandardMobSpawnBuilder()
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::WOLF, 5, 4, 4))
//            .isValidSpawnBiomeForPlayer();
        return makeGenericForestBiome(depth, scale, false/*, mobSpawnInfo*/);
    }

    static Biome* makeFlowerForestBiome() {
//        MobSpawnInfo::Builder mobSpawnInfo = getStandardMobSpawnBuilder()
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::RABBIT, 4, 2, 3));
        return makeGenericForestBiome(0.1F, 0.4F, true/*, mobSpawnInfo*/);
    }

    static Biome* makeTaigaBiome(float depth, float scale, bool isSnowyVariant, bool isMountainVariant, bool hasVillageAndOutpost, bool hasIgloos) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        mobSpawnInfo
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::WOLF, 8, 4, 4))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::RABBIT, 4, 2, 3))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::FOX, 8, 2, 4));
        if (!isSnowyVariant && !isMountainVariant) {
//            mobSpawnInfo.isValidSpawnBiomeForPlayer();
        }

//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
        float temperature = isSnowyVariant ? -0.5F : 0.25F;
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::GRASS);
        if (hasVillageAndOutpost) {
//            generation.withStructure(StructureFeatures::VILLAGE_TAIGA);
//            generation.withStructure(StructureFeatures::PILLAGER_OUTPOST);
        }

        if (hasIgloos) {
//            generation.withStructure(StructureFeatures::IGLOO);
        }

        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(isMountainVariant ? StructureFeatures::RUINED_PORTAL_MOUNTAIN : StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withLargeFern(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withTaigaVegetation(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withTaigaGrassVegetation(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        if (isSnowyVariant) {
            DefaultBiomeFeatures::withChanceBerries(generation);
        } else {
            DefaultBiomeFeatures::withSparseBerries(generation);
        }

        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = isSnowyVariant ? RainType::SNOW : RainType::RAIN,
                .temperature = temperature,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = isSnowyVariant ? 0.4F : 0.8F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::TAIGA,
            .effects{
                .fogColor = 12638463,
                .waterColor = isSnowyVariant ? 4020182 : 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(temperature),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeDarkForestBiome(float depth, float scale, bool isHillsVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::GRASS);
//        generation.withStructure(StructureFeatures::MANSION);
        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
//        generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, isHillsVariant ? Features::DARK_FOREST_VEGETATION_RED : Features::DARK_FOREST_VEGETATION_BROWN);
        DefaultBiomeFeatures::withAllForestFlowerGeneration(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withForestGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.7F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.8F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::FOREST,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.7F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = BiomeAmbience::GrassColorModifier::DARK_FOREST,
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeGenericSwampBiome(float depth, float scale, bool isHillsVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        DefaultBiomeFeatures::withPassiveMobs(mobSpawnInfo);
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
//        mobSpawnInfo.withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::SLIME, 1, 1, 1));
        BiomeGenerationSettings::Builder
        generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::SWAMP);
        if (!isHillsVariant) {
//            generation.withStructure(StructureFeatures::SWAMP_HUT);
        }

//        generation.withStructure(StructureFeatures::MINESHAFT);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL_SWAMP);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        if (!isHillsVariant) {
            DefaultBiomeFeatures::withFossils(generation);
        }

        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withClayDisks(generation);
        DefaultBiomeFeatures::withSwampVegetation(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSwampSugarcaneAndPumpkin(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        if (isHillsVariant) {
            DefaultBiomeFeatures::withFossils(generation);
        } else {
//            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SEAGRASS_SWAMP);
        }

        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::RAIN,
                .temperature = 0.8F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.9F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::SWAMP,
            .effects{
                .fogColor = 12638463,
                .waterColor = 6388580,
                .waterFogColor = 2302743,
                .skyColor = getSkyColorWithTemperatureModifier(0.8F),
                .foliageColor = 6975545,
                .grassColor = std::nullopt,
//                .grassColorModifier = BiomeAmbience::GrassColorModifier::SWAMP,
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeSnowyBiome(float depth, float scale, bool isIceSpikesBiome, bool isMountainVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo = MobSpawnInfo::Builder{}
//            .withCreatureSpawnProbability(0.07F);
//        DefaultBiomeFeatures::withSnowyBiomeMobs(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(isIceSpikesBiome ? ConfiguredSurfaceBuilders::ICE_SPIKES : ConfiguredSurfaceBuilders::GRASS);
        if (!isIceSpikesBiome && !isMountainVariant) {
//            generation
//                .withStructure(StructureFeatures::VILLAGE_SNOWY)
//                .withStructure(StructureFeatures::IGLOO);
        }

        DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
        if (!isIceSpikesBiome && !isMountainVariant) {
//            generation.withStructure(StructureFeatures::PILLAGER_OUTPOST);
        }

//        generation.withStructure(isMountainVariant ? StructureFeatures::RUINED_PORTAL_MOUNTAIN : StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        if (isIceSpikesBiome) {
//            generation.withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::ICE_SPIKE);
//            generation.withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::ICE_PATCH);
        }

        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withSnowySpruces(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withBadlandsGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::SNOW,
                .temperature = 0.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.5F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::ICY,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.0F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeRiverBiome(float depth, float scale, float temperature, int waterColor, bool isSnowy) {
//        MobSpawnInfo::Builder mobSpawnInfo = MobSpawnInfo::Builder{}
//            .withSpawner(EntityClassification::WATER_CREATURE, MobSpawnInfo::Spawners(EntityType::SQUID, 2, 1, 4))
//            .withSpawner(EntityClassification::WATER_AMBIENT, MobSpawnInfo::Spawners(EntityType::SALMON, 5, 1, 5));
//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
//        mobSpawnInfo.withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::DROWNED, isSnowy ? 1 : 100, 1, 1));
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::GRASS);
//        generation.withStructure(StructureFeatures::MINESHAFT);
//        generation.withStructure(StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withTreesInWater(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withBadlandsGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        if (!isSnowy) {
//            generation.withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SEAGRASS_RIVER);
        }

        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = isSnowy ? RainType::SNOW : RainType::RAIN,
                .temperature = temperature,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.5F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = BiomeCategory::RIVER,
            .effects{
                .fogColor = 12638463,
                .waterColor = waterColor,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(temperature),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeBeachBiome(float depth, float scale, float temperature, float downfall, int waterColor, bool isColdBiome, bool isStoneVariant) {
//        MobSpawnInfo::Builder mobSpawnInfo{};
//        if (!isStoneVariant && !isColdBiome) {
//            mobSpawnInfo.withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::TURTLE, 5, 2, 5));
//        }

//        DefaultBiomeFeatures::withBatsAndHostiles(mobSpawnInfo);
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(isStoneVariant ? ConfiguredSurfaceBuilders::STONE : ConfiguredSurfaceBuilders::DESERT);
        if (isStoneVariant) {
            DefaultBiomeFeatures::withStrongholdAndMineshaft(generation);
        } else {
//            generation.withStructure(StructureFeatures::MINESHAFT);
//            generation.withStructure(StructureFeatures::BURIED_TREASURE);
//            generation.withStructure(StructureFeatures::SHIPWRECK_BEACHED);
        }

//        generation.withStructure(isStoneVariant ? StructureFeatures::RUINED_PORTAL_MOUNTAIN : StructureFeatures::RUINED_PORTAL);
        DefaultBiomeFeatures::withCavesAndCanyons(generation);
        DefaultBiomeFeatures::withLavaAndWaterLakes(generation);
        DefaultBiomeFeatures::withMonsterRoom(generation);
        DefaultBiomeFeatures::withCommonOverworldBlocks(generation);
        DefaultBiomeFeatures::withOverworldOres(generation);
        DefaultBiomeFeatures::withDisks(generation);
        DefaultBiomeFeatures::withDefaultFlowers(generation);
        DefaultBiomeFeatures::withBadlandsGrass(generation);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        DefaultBiomeFeatures::withSugarCaneAndPumpkins(generation);
        DefaultBiomeFeatures::withLavaAndWaterSprings(generation);
        DefaultBiomeFeatures::withFrozenTopLayer(generation);
        return new Biome {
            .climate{
                .precipitation = isColdBiome ? RainType::SNOW : RainType::RAIN,
                .temperature = temperature,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = downfall
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = depth,
            .scale = scale,
            .category = isStoneVariant ? BiomeCategory::NONE : BiomeCategory::BEACH,
            .effects{
                .fogColor = 12638463,
                .waterColor = waterColor,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(temperature),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
            }
        };
    }

    static Biome* makeVoidBiome() {
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::NOPE);
//        generation.withFeature(GenerationStage::Decoration::TOP_LAYER_MODIFICATION, Features::VOID_START_PLATFORM);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 0.5F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.5F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.1F,
            .scale = 0.2F,
            .category = BiomeCategory::NONE,
            .effects{
                .fogColor = 12638463,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(0.5F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = std::nullopt,
//                .moodSound = MoodSoundAmbience::DEFAULT_CAVE,
//                .additionsSound = std::nullopt,
//                .music = std::nullopt
                }
        };
    }

    static Biome* makeNetherWastesBiome() {
//        MobSpawnInfo mobspawninfo = MobSpawnInfo::Builder{}
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::GHAST, 50, 4, 4))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::ZOMBIFIED_PIGLIN, 100, 4, 4))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::MAGMA_CUBE, 2, 4, 4))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::ENDERMAN, 1, 4, 4))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::PIGLIN, 15, 4, 4))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::STRIDER, 60, 1, 2))
//            .copy();
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::NETHER);
//            .withStructure(StructureFeatures::RUINED_PORTAL_NETHER)
//            .withStructure(StructureFeatures::FORTRESS)
//            .withStructure(StructureFeatures::BASTION_REMNANT)
//            .withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.NETHER_CAVE)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRING_LAVA);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        generation
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_OPEN)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::PATCH_FIRE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::PATCH_SOUL_FIRE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE_EXTRA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::BROWN_MUSHROOM_NETHER)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::RED_MUSHROOM_NETHER);
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_MAGMA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_CLOSED);
        DefaultBiomeFeatures::withCommonNetherBlocks(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 2.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.1F,
            .scale = 0.2F,
            .category = BiomeCategory::NETHER,
            .effects{
                .fogColor = 3344392,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(2.0F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = std::nullopt,
//                .ambientSound = SoundEvents::AMBIENT_NETHER_WASTES_LOOP,
//                .moodSound = MoodSoundAmbience(SoundEvents::AMBIENT_NETHER_WASTES_MOOD, 6000, 8, 2.0),
//                .additionsSound = SoundAdditionsAmbience(SoundEvents::AMBIENT_NETHER_WASTES_ADDITIONS, 0.0111),
//                .music = BackgroundMusicTracks::getDefaultBackgroundMusicSelector(SoundEvents::MUSIC_NETHER_NETHER_WASTES)
            }
        };
    }

    static Biome* makeSoulSandValleyBiome() {
//        MobSpawnInfo mobspawninfo = MobSpawnInfo::Builder{}
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::SKELETON, 20, 5, 5))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::GHAST, 50, 4, 4))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::ENDERMAN, 1, 4, 4))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::STRIDER, 60, 1, 2))
//            .withSpawnCost(EntityType::SKELETON, 0.7, 0.15)
//            .withSpawnCost(EntityType::GHAST, 0.7, 0.15)
//            .withSpawnCost(EntityType::ENDERMAN, 0.7, 0.15)
//            .withSpawnCost(EntityType::STRIDER, 0.7, 0.15)
//            .copy();
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::SOUL_SAND_VALLEY);
//            .withStructure(StructureFeatures::FORTRESS)
//            .withStructure(StructureFeatures::NETHER_FOSSIL)
//            .withStructure(StructureFeatures::RUINED_PORTAL_NETHER)
//            .withStructure(StructureFeatures::BASTION_REMNANT)
//            .withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.NETHER_CAVE)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRING_LAVA)
//            .withFeature(GenerationStage::Decoration::LOCAL_MODIFICATIONS, Features::BASALT_PILLAR)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_OPEN)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE_EXTRA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::PATCH_CRIMSON_ROOTS)
        generation.withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::PATCH_FIRE);
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::PATCH_SOUL_FIRE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_MAGMA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_CLOSED)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_SOUL_SAND);
        DefaultBiomeFeatures::withCommonNetherBlocks(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 2.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.1F,
            .scale = 0.2F,
            .category = BiomeCategory::NETHER,
            .effects{
                .fogColor = 1787717,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(2.0F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = ParticleEffectAmbience(ParticleTypes::ASH, 0.00625F),
//                .ambientSound = SoundEvents::AMBIENT_SOUL_SAND_VALLEY_LOOP,
//                .moodSound = MoodSoundAmbience(SoundEvents::AMBIENT_SOUL_SAND_VALLEY_MOOD, 6000, 8, 2.0),
//                .additionsSound = SoundAdditionsAmbience(SoundEvents::AMBIENT_SOUL_SAND_VALLEY_ADDITIONS, 0.0111),
//                .music = BackgroundMusicTracks::getDefaultBackgroundMusicSelector(SoundEvents::MUSIC_NETHER_SOUL_SAND_VALLEY)
                }
        };
    }

    static Biome* makeBasaltDeltasBiome() {
//        MobSpawnInfo mobspawninfo = MobSpawnInfo::Builder{}
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::GHAST, 40, 1, 1))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::MAGMA_CUBE, 100, 2, 5))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::STRIDER, 60, 1, 2))
//            .copy();
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::BASALT_DELTAS)
//            .withStructure(StructureFeatures::RUINED_PORTAL_NETHER)
//            .withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.NETHER_CAVE)
//            .withStructure(StructureFeatures::FORTRESS)
//            .withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::DELTA)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRING_LAVA_DOUBLE)
//            .withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::SMALL_BASALT_COLUMNS)
//            .withFeature(GenerationStage::Decoration::SURFACE_STRUCTURES, Features::LARGE_BASALT_COLUMNS)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::BASALT_BLOBS)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::BLACKSTONE_BLOBS)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_DELTA)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::PATCH_FIRE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::PATCH_SOUL_FIRE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE_EXTRA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::BROWN_MUSHROOM_NETHER)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::RED_MUSHROOM_NETHER);
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_MAGMA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_CLOSED_DOUBLE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_GOLD_DELTAS)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_QUARTZ_DELTAS);
        DefaultBiomeFeatures::withDebrisOre(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 2.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.1F,
            .scale = 0.2F,
            .category = BiomeCategory::NETHER,
            .effects{
                .fogColor = 6840176,
                .waterColor = 4159204,
                .waterFogColor = 4341314,
                .skyColor = getSkyColorWithTemperatureModifier(2.0F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = ParticleEffectAmbience(ParticleTypes::WHITE_ASH, 0.118093334F),
//                .ambientSound = SoundEvents::AMBIENT_BASALT_DELTAS_LOOP,
//                .moodSound = MoodSoundAmbience(SoundEvents::AMBIENT_BASALT_DELTAS_MOOD, 6000, 8, 2.0),
//                .additionsSound = SoundAdditionsAmbience(SoundEvents::AMBIENT_BASALT_DELTAS_ADDITIONS, 0.0111),
//                .music = BackgroundMusicTracks::getDefaultBackgroundMusicSelector(SoundEvents::MUSIC_NETHER_BASALT_DELTAS)
                }
        };
    }

    static Biome* makeCrimsonForestBiome() {
//        MobSpawnInfo mobspawninfo = MobSpawnInfo::Builder{}
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::ZOMBIFIED_PIGLIN, 1, 2, 4))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::HOGLIN, 9, 3, 4))
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::PIGLIN, 5, 3, 4))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::STRIDER, 60, 1, 2))
//            .copy();
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::CRIMSON_FOREST);
//            .withStructure(StructureFeatures::RUINED_PORTAL_NETHER)
//            .withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.NETHER_CAVE)
//            .withStructure(StructureFeatures::FORTRESS)
//            .withStructure(StructureFeatures::BASTION_REMNANT)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRING_LAVA);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        generation
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_OPEN)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::PATCH_FIRE);
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE_EXTRA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_MAGMA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_CLOSED)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::WEEPING_VINES)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::CRIMSON_FUNGI)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::CRIMSON_FOREST_VEGETATION);
        DefaultBiomeFeatures::withCommonNetherBlocks(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 2.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.1F,
            .scale = 0.2F,
            .category = BiomeCategory::NETHER,
            .effects{
                .fogColor = 3343107,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(2.0F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = ParticleEffectAmbience(ParticleTypes::CRIMSON_SPORE, 0.025F),
//                .ambientSound = SoundEvents::AMBIENT_CRIMSON_FOREST_LOOP,
//                .moodSound = MoodSoundAmbience(SoundEvents::AMBIENT_CRIMSON_FOREST_MOOD, 6000, 8, 2.0),
//                .additionsSound = SoundAdditionsAmbience(SoundEvents::AMBIENT_CRIMSON_FOREST_ADDITIONS, 0.0111),
//                .music = BackgroundMusicTracks::getDefaultBackgroundMusicSelector(SoundEvents::MUSIC_NETHER_CRIMSON_FOREST)
            }
        };
    }

    static Biome* makeWarpedForestBiome() {
//        MobSpawnInfo mobspawninfo = MobSpawnInfo::Builder{}
//            .withSpawner(EntityClassification::MONSTER, MobSpawnInfo::Spawners(EntityType::ENDERMAN, 1, 4, 4))
//            .withSpawner(EntityClassification::CREATURE, MobSpawnInfo::Spawners(EntityType::STRIDER, 60, 1, 2))
//            .withSpawnCost(EntityType::ENDERMAN, 1.0, 0.12)
//            .copy();
        auto generation = BiomeGenerationSettings::Builder{}
            .withSurfaceBuilder(ConfiguredSurfaceBuilders::WARPED_FOREST);
//            .withStructure(StructureFeatures::FORTRESS)
//            .withStructure(StructureFeatures::BASTION_REMNANT)
//            .withStructure(StructureFeatures::RUINED_PORTAL_NETHER)
//            .withCarver(GenerationStage::Carving.AIR, ConfiguredCarvers.NETHER_CAVE)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::SPRING_LAVA);
        DefaultBiomeFeatures::withNormalMushroomGeneration(generation);
        generation
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_OPEN)
            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, ConfiguredFeatures::PATCH_FIRE);
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::PATCH_SOUL_FIRE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE_EXTRA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::GLOWSTONE)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::ORE_MAGMA)
//            .withFeature(GenerationStage::Decoration::UNDERGROUND_DECORATION, Features::SPRING_CLOSED)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::WARPED_FUNGI)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::WARPED_FOREST_VEGETATION)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::NETHER_SPROUTS)
//            .withFeature(GenerationStage::Decoration::VEGETAL_DECORATION, Features::TWISTING_VINES);
        DefaultBiomeFeatures::withCommonNetherBlocks(generation);
        return new Biome {
            .climate{
                .precipitation = RainType::NONE,
                .temperature = 2.0F,
                .temperatureModifier = TemperatureModifiers::none,
                .downfall = 0.0F
            },
            .biomeGenerationSettings = generation.build(),
//            .mobSpawnInfo = mobSpawnInfo.copy(),
            .depth = 0.1F,
            .scale = 0.2F,
            .category = BiomeCategory::NETHER,
            .effects{
                .fogColor = 1705242,
                .waterColor = 4159204,
                .waterFogColor = 329011,
                .skyColor = getSkyColorWithTemperatureModifier(2.0F),
                .foliageColor = std::nullopt,
                .grassColor = std::nullopt,
//                .grassColorModifier = {},
//                .particle = ParticleEffectAmbience(ParticleTypes::WARPED_SPORE, 0.01428F),
//                .ambientSound = SoundEvents::AMBIENT_WARPED_FOREST_LOOP,
//                .moodSound = MoodSoundAmbience(SoundEvents::AMBIENT_WARPED_FOREST_MOOD, 6000, 8, 2.0),
//                .additionsSound = SoundAdditionsAmbience(SoundEvents::AMBIENT_WARPED_FOREST_ADDITIONS, 0.0111),
//                .music = BackgroundMusicTracks::getDefaultBackgroundMusicSelector(SoundEvents::MUSIC_NETHER_WARPED_FOREST)
            }
        };
    }
};