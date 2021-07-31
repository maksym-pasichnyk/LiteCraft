#include "ChunkStatus.hpp"
#include "../gen/ChunkGenerator.hpp"
#include "../light/WorldLightManager.hpp"

#include <algorithm>

std::mutex generator_mutex{};

const ChunkStatus ChunkStatus::Empty = create(nullptr, -1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {

});

const ChunkStatus ChunkStatus::StructureStart = create(&ChunkStatus::Empty, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
//    WorldGenRegion region{world, chunks, 0, x, z, seed};
//    generator.generateStructures(region, chunk);
});

const ChunkStatus ChunkStatus::StructureReferences = create(&ChunkStatus::StructureStart, 8, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
//    WorldGenRegion region{world, chunks, 8, x, z, seed};
//    generator.getStructureReferences(region, chunk);
});

//const ChunkStatus ChunkStatus::Biome = create(&ChunkStatus::StructureReferences, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
//    WorldGenRegion region{world, chunks, 0, x, z, seed};
//});
//
//const ChunkStatus ChunkStatus::Noise = create(&ChunkStatus::Biome, 8, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
//    WorldGenRegion region{world, chunks, 0, x, z, seed};
//    if (std::unique_lock _{generator.guard}) {
//        generator.generateTerrain(chunk);
//    }
//});

const ChunkStatus ChunkStatus::Surface = create(&ChunkStatus::StructureReferences, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 0, x, z, seed};

    generator.generateTerrain(chunk);
    generator.generateSurface(region, chunk);
    generator.generateCarvers(region, seed, chunk);
});

//const ChunkStatus ChunkStatus::Carver = create(&ChunkStatus::Surface, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
//    WorldGenRegion region{world, chunks, 0, x, z, seed};
//    generator.generateCarvers(region, seed, chunk, GenerationStage::Carving::AIR);
//});
//
//const ChunkStatus ChunkStatus::LiquidCarver = create(7, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
//    WorldGenRegion region{world, chunks, 0, x, z, seed};
//    generator.generateCarvers(region, seed, chunk, GenerationStage::Carving::LIQUID);
//});

const ChunkStatus ChunkStatus::Features = create(&ChunkStatus::Surface, /*8*/1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 1, x, z, seed};

    generator_mutex.lock();
    generator.generateFeatures(region, chunk);
    generator_mutex.unlock();
});

const ChunkStatus ChunkStatus::Light = create(&ChunkStatus::Features, 1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 1, x, z, seed};
    lightManager.calculate(region, x << 4, z << 4);
});

const ChunkStatus ChunkStatus::Full = create(&ChunkStatus::Light, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk& chunk, std::span<std::weak_ptr<Chunk>> chunks, int64_t seed) {

});

ChunkStatus ChunkStatus::create(ChunkStatus const* parent, int32_t range, Fn generate) noexcept {
    return {
        .ordinal = parent ? parent->ordinal + 1 : 0,
        .range = range,
        .generate = generate
    };
}

ChunkStatus const* ChunkStatus::getById(int32_t ordinal) {
    return ALL[ordinal];
}
