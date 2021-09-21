#include "ChunkStatus.hpp"
#include "../gen/ChunkGenerator.hpp"
#include "../light/WorldLightManager.hpp"

#include <algorithm>

std::mutex generator_mutex{};

Registry<ChunkStatus> ChunkStatus::all;

ChunkStatus* ChunkStatus::Empty;
ChunkStatus* ChunkStatus::StructureStart;
ChunkStatus* ChunkStatus::StructureReferences;
ChunkStatus* ChunkStatus::Biome;
ChunkStatus* ChunkStatus::Noise;
ChunkStatus* ChunkStatus::Surface;
ChunkStatus* ChunkStatus::Carvers;
ChunkStatus* ChunkStatus::Features;
ChunkStatus* ChunkStatus::Light;
ChunkStatus* ChunkStatus::Full;

static auto create(std::string name, ChunkStatus* parent, int32_t range, ChunkStatus::Fn on_generate, ChunkStatus::Fn on_load = nullptr) -> ChunkStatus* {
    const auto ordinal = parent ? parent->ordinal + 1 : 0;
    return ChunkStatus::all.add(ordinal, std::move(name), std::make_unique<ChunkStatus>(ChunkStatus{
        .ordinal = ordinal,
        .range = range,
        .on_generate = on_generate,
        .on_load = on_load
    }));
}

void ChunkStatus::init() {
    Empty = create("empty", nullptr, -1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {});
    StructureStart = create("structure_starts", Empty, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
//        WorldGenRegion region{world, chunks, radius, x, z, seed};
//        generator.generateStructures(region, chunk);
    });
    StructureReferences = create("structure_references", StructureStart, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
//        WorldGenRegion region{world, chunks, radius, x, z, seed};
//        generator.getStructureReferences(region, chunk);
    });
    Biome = create("biome", StructureReferences, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
        WorldGenRegion region{world, chunks, radius, x, z, seed};
    });
    Noise = create("noise", Biome, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
        WorldGenRegion region{world, chunks, radius, x, z, seed};
        generator.generateTerrain(chunk);
    });
    Surface = create("surface", Noise, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
        WorldGenRegion region{world, chunks, radius, x, z, seed};
        generator.generateSurface(region, chunk);
        generator.generateCarvers(region, seed, chunk);
    });
    Carvers = create("carvers", Surface, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
        WorldGenRegion region{world, chunks, radius, x, z, seed};
        generator.generateCarvers(region, seed, chunk);
//        generator.generateCarvers(region, seed, chunk, GenerationStage::Carving::AIR);
//        generator.generateCarvers(region, seed, chunk, GenerationStage::Carving::LIQUID);
    });
    Features = create("features", Carvers, 8, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
        WorldGenRegion region{world, chunks, radius, x, z, seed};

        generator_mutex.lock();
        generator.generateFeatures(region, chunk);
        generator_mutex.unlock();
    });
    Light = create("light", Features, 1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {
        WorldGenRegion region{world, chunks, radius, x, z, seed};
        lightManager.calculate(region, x << 4, z << 4);
    });
    Full = create("full", Light, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::shared_ptr<Chunk>> chunks, int64_t seed, int radius) {});
}
