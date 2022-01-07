#include "ServerWorld.hpp"
#include "ChunkManager.hpp"
#include "world/gen/feature/structure/Structure.hpp"
#include "world/gen/feature/structure/StructureStart.hpp"
#include "world/gen/feature/structure/StructurePieces.hpp"
#include "world/gen/feature/structure/StructureGenerateContext.hpp"

#include <CraftServer.hpp>

#include <world/biome/Biomes.hpp>
#include <world/biome/provider/SingleBiomeProvider.hpp>
#include <world/biome/provider/OverworldBiomeProvider.hpp>

#include <world/gen/NoiseChunkGenerator.hpp>
#include <world/gen/feature/structure/TemplateManager.hpp>
#include <world/gen/feature/structure/StructureFeatures.hpp>

#include <memory>
#include <fstream>
#include <Json.hpp>

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


//static auto jsonFromProperties(std::map<std::string, Property> const& props) -> Json {
//    auto out = Json::Object{};
//    for (auto&& [k, v] : props) {
//        out[k] = ranges::to_vector(PropertyUtil::values(v) | ranges::views::transform([](const auto& item) {
//            return PropertyUtil::string(item).value();
//        }));
//    }
//    return out;
//}
//template <>
//auto Json::From<BlockBehaviour>::from(const Value& value) -> Self {
//    return {
//        {"blocks_movement", value.blocksMovement},
//        {"sound", value.soundType},
//        {"resistance", value.resistance},
//        {"hardness", value.hardness},
//        {"requires_tool", value.requiresTool},
//        {"ticks_randomly", value.ticksRandomly},
//        {"slipperiness", value.slipperiness},
//        {"speed_factor", value.speedFactor},
//        {"jump_factor", value.jumpFactor},
//        {"is_solid", value.isSolid},
//        {"is_air", value.isAir},
//        {"variable_opacity", value.isAir},
//    };
//}

auto TemplateManager::readStructure(Nbt::Compound const& nbt) -> tl::optional<std::unique_ptr<Template>> {
    try {
        const auto AIR = Blocks::AIR->getDefaultState();

        auto palette = std::vector<BlockData>{};
        for (auto&& item : nbt.at("palette").get<Nbt::List>()) {
            palette.emplace_back([&nbt = item.get<Nbt::Compound>()] {
                const auto location = ResourceLocation::from(nbt.at("Name").get<Nbt::String>());
                const auto block = Blocks::blocks.get(location.get_location()).value();
                auto state = block->getDefaultState();

                if (nbt.contains("Properties")) {
                    auto&& properties = nbt.at("Properties").get<Nbt::Compound>();

                    for (auto&& [k, v] : properties) {
                        if (!block->properties.contains(k)) {
//                            spdlog::info("Missing property: {}", k);
                            continue;
                        }
                        const auto property = block->properties.at(k);
                        state = state.set(property, PropertyUtil::parse(property, v).value());
                    }
                }
                return state;
            }());
        }

        auto tmpl = std::make_unique<Template>();
        tmpl->size = [&nbt = nbt.at("size").get<Nbt::List>()] {
            return glm::ivec3{
                nbt.at(0).get<Nbt::Int>(),
                nbt.at(1).get<Nbt::Int>(),
                nbt.at(2).get<Nbt::Int>()
            };
        }();

        for (auto&& item : nbt.at("blocks").get<Nbt::List>()) {
            tmpl->blocks.emplace_back([&, &nbt = item.get<Nbt::Compound>()] {
                return BlockInfo{
                    .pos = [&nbt = nbt.at("pos").get<Nbt::List>()] {
                        return glm::ivec3{
                            nbt.at(0).get<Nbt::Int>(),
                            nbt.at(1).get<Nbt::Int>(),
                            nbt.at(2).get<Nbt::Int>()
                        };
                    }(),
                    .state = palette[nbt.at("state").get<Nbt::Int>()],
                    .nbt = nbt.contains("nbt") ? tl::optional(nbt.at("nbt").get<Nbt::Compound>()) : tl::nullopt
                };
            }());
        }
        return tmpl;
    } catch (const std::exception& e) {
        spdlog::error("TemplateManager::readStructure: {}", e.what());
    }
    return tl::nullopt;
}

struct DebugChunkGenerator : public ChunkGenerator {
    std::vector<BlockData> states;
    std::unique_ptr<Biome> biome;
    glm::ivec2 grid{};

    DebugChunkGenerator() : ChunkGenerator(std::make_unique<SingleBiomeProvider>(createBiome())) {
//        for (auto&& [name, block] : Blocks::blocks.objects) {
//            auto&& props = block->properties;
//
//            auto state = block->getDefaultState();
//
//            std::ofstream file{fmt::format("blocks/{}.json", name), std::ios::binary};
//            Json::Dump::dump(file, Json{
//                {"properties", jsonFromProperties(block->properties)},
//                {"default", [&] {
//                    auto out = Json::Object{};
//                    for (auto&& [k, v]: props) {
//                        out[k] = PropertyUtil::string(state.get(v)).value();
//                    }
//                    return out;
//                }()}
//                // {"behaviour", block->behaviour}
//            });
//        }
        for (auto&& [name, block] : Blocks::blocks.objects) {
            for (auto state : block->validStates) {
                states.emplace_back(state);
            }
        }

        spdlog::info("States: {}", states.size());

        grid.x = std::ceil(std::sqrt(states.size()));
        grid.y = (states.size() - 1) / grid.x;
    }

    void generateStructures(WorldGenRegion& region, Chunk& chunk, TemplateManager& templates) override {
        if (chunk.coords == ChunkPos::from(0, 0)) {
            auto feature = StructureFeatures::registry.get("village_plains").value();

            auto pieces = StructurePieces{};
            auto context = StructureGenerateContext {
                *this,
                templates,
                chunk.coords,
                *biome,
                region.getSeed()
            };
            feature->structure->generatePieces(pieces, context, feature->config);

            spdlog::info("pieces: {}", pieces.components.size());

            if (!pieces.empty()) {
                auto bounds = pieces.getBoundingBox().value();
                auto start = new StructureStart(
                    std::move(pieces.components),
                    feature->structure,
                    context.pos.x,
                    context.pos.z,
                    bounds,
                    1,
                    context.seed
                );
                chunk.addStructureStart(feature->structure, start);
            }
        }
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
//        if (x > 0 && z > 0 && x % 2 != 0 && z % 2 != 0) {
//            x = x / 2;
//            z = z / 2;
//            if (x <= grid.x && z <= grid.y) {
//                const auto i = std::abs(x * grid.x + z);
//                if (i < states.size()) {
//                    return states[i];
//                }
//            }
//        }
        return tl::nullopt;
    }
};

ServerWorld::ServerWorld(CraftServer *server, int viewDistance) : server(server), viewDistance(viewDistance) {
    std::default_random_engine engine{};
    engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    seed = engine();

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

    templates = std::make_unique<TemplateManager>();
//    generator = std::make_unique<NoiseChunkGenerator>(seed, dimensionSettings, std::make_unique<OverworldBiomeProvider>(seed, false, false));
    generator = std::make_unique<DebugChunkGenerator>();
//        generator = std::make_unique<NoiseChunkGenerator>(seed, std::make_unique<SingleBiomeProvider>(Biomes::SWAMP));
    manager = std::make_unique<ChunkManager>(this, generator.get(), templates.get());
}

Biome *ServerWorld::getNoiseBiomeRaw(int x, int y, int z) {
    return generator->biomeProvider->getNoiseBiome(x, y, z);
}
