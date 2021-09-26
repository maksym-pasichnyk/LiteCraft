#include "ServerWorld.hpp"
#include <CraftServer.hpp>

#include "biome/provider/SingleBiomeProvider.hpp"
#include "biome/provider/OverworldBiomeProvider.hpp"
#include "gen/NoiseChunkGenerator.hpp"
#include "ChunkManager.hpp"

#include "gen/feature/structure/TemplateManager.hpp"


//NoiseSettings settings{
//    .sampling{
//        .xz_scale = 1,
//        .y_scale = 3,
//        .xz_factor = 80,
//        .y_factor = 60
//    },
//    .topSlide{
//        .target = 120,
//        .size = 3,
//        .offset = 0
//    },
//    .bottomSlide{
//        .target = 320,
//        .size = 4,
//        .offset = -1
//    },
//    .height = 128,
//    .sizeVertical = 2,
//    .sizeHorizontal = 1,
//    .destinyFactor = 1.0,
//    .densityOffset = 0.019921875,
//    .randomDensityOffset = false
//};

ServerWorld::ServerWorld(CraftServer *server, int viewDistance) : server(server), viewDistance(viewDistance) {
    DimensionSettings dimensionSettings {
        .noise{
            .sampling{
                .xz_scale = 0.9999999814507745,
                .y_scale = 0.9999999814507745,
                .xz_factor = 80,
                .y_factor = 160
            },
            .topSlide{
                .target = -10,
                .size = 3,
                .offset = 0
            },
            .bottomSlide{
                .target = -30,
                .size = 0,
                .offset = 0
            },
            .height = 256,
            .sizeVertical = 2,
            .sizeHorizontal = 1,
            .destinyFactor = 1.0,
            .densityOffset = -0.46875,
            .randomDensityOffset = true,
            .islandNoiseOverride = false,
            .amplified = false
        },
        .layer = Blocks::STONE->getDefaultState(),
        .fluid = Blocks::WATER->getDefaultState(),
        .bedrockRoofPosition = -1,
        .bedrockFloorPosition = 0,
        .seaLevel = 63,
        .disableMobGeneration = false
    };

    templates = std::make_unique<TemplateManager>(server->resources);
    generator = std::make_unique<NoiseChunkGenerator>(seed, dimensionSettings, std::make_unique<OverworldBiomeProvider>(seed, false, false));
//        generator = std::make_unique<NoiseChunkGenerator>(seed, std::make_unique<SingleBiomeProvider>(Biomes::SWAMP));
    manager = std::make_unique<ChunkManager>(this, generator.get(), templates.get());
}

Biome *ServerWorld::getNoiseBiomeRaw(int x, int y, int z) {
    return generator->biomeProvider->getNoiseBiome(x, y, z);
}
