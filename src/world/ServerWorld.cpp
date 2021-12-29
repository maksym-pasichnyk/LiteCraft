#include "ServerWorld.hpp"
#include <CraftServer.hpp>

#include <memory>
#include <world/biome/Biomes.hpp>
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

struct DebugChunkGenerator : public ChunkGenerator {
    std::vector<BlockData> states;
    std::unique_ptr<Biome> biome;
    glm::ivec2 grid{};

    DebugChunkGenerator() : ChunkGenerator(std::make_unique<SingleBiomeProvider>(createBiome())) {
        for (auto&& [name, block] : Blocks::blocks.objects) {
            for (auto state : block->validStates) {
                states.emplace_back(state);
            }
        }

        spdlog::info("States: {}", states.size());

        grid.x = std::ceil(std::sqrt(states.size()));
        grid.y = (states.size() - 1) / grid.x;
    }

    void generateTerrain(Chunk &chunk) override {
    }

    void generateSurface(WorldGenRegion &region, Chunk& chunk) override {
        for (int x = 0; x < 16; ++x) {
            for (int z = 0; z < 16; ++z) {
                const auto pos = chunk.coords.getBlockPos(x, 0, z);

                const auto state = getBlockStateFor(pos.x, pos.z);
                if (state.has_value()) {
                    region.setData(pos, *state);
                }
            }
        }
    }

    auto createBiome() -> Biome* {
        biome = std::make_unique<Biome>(Biome {
            .climate = BiomeClimate{},
            .biomeGenerationSettings = BiomeGenerationSettings{},
            .mobSpawnInfo = MobSpawnInfo{},
            .depth = 0.0f,
            .scale = 0.0f,
            .category = BiomeCategory::NONE,
            .effects = BiomeAmbience{}
        });
        return biome.get();
    }

    auto getBlockStateFor(int x, int z) -> tl::optional<BlockData> {
        if (x > 0 && z > 0 && x % 2 != 0 && z % 2 != 0) {
            x = x / 2;
            z = z / 2;
            if (x <= grid.x && z <= grid.y) {
                const auto i = std::abs(x * grid.x + z);
                if (i < states.size()) {
                    return states[i];
                }
            }
        }

        return tl::nullopt;
    }
};

ServerWorld::ServerWorld(CraftServer *server, int viewDistance) : server(server), viewDistance(viewDistance) {
    auto dimensionSettings = DimensionSettings{
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
//    generator = std::make_unique<NoiseChunkGenerator>(seed, dimensionSettings, std::make_unique<OverworldBiomeProvider>(seed, false, false));
    generator = std::make_unique<DebugChunkGenerator>();
//        generator = std::make_unique<NoiseChunkGenerator>(seed, std::make_unique<SingleBiomeProvider>(Biomes::SWAMP));
    manager = std::make_unique<ChunkManager>(this, generator.get(), templates.get());
}

Biome *ServerWorld::getNoiseBiomeRaw(int x, int y, int z) {
    return generator->biomeProvider->getNoiseBiome(x, y, z);
}
