#include "ChunkStatus.hpp"
#include "../gen/ChunkGenerator.hpp"
#include "../light/WorldLightManager.hpp"

#include <algorithm>

const ChunkStatus ChunkStatus::Empty = create(0, -1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {

});

const ChunkStatus ChunkStatus::StructureStart = create(1, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 0, x, z, seed};
    generator.generateStructures(region, *chunk);
});

const ChunkStatus ChunkStatus::StructureReferences = create(2, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
//    WorldGenRegion region{chunks, 0, x, z, seed};
//    generator.getStructureReferences(region, *chunk);
});

const ChunkStatus ChunkStatus::Biome = create(3, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
});

const ChunkStatus ChunkStatus::Noise = create(4, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    generator.generateTerrain(*chunk);
});

const ChunkStatus ChunkStatus::Surface = create(5, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    std::ranges::for_each(chunks, &Chunk::updateHeightmaps);

    WorldGenRegion region{world, chunks, 0, x, z, seed};
    generator.generateSurface(region, *chunk);
});

const ChunkStatus ChunkStatus::Carver = create(6, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 0, x, z, seed};
    generator.generateCarvers(region, seed, *chunk, GenerationStage::Carving::AIR);
});

const ChunkStatus ChunkStatus::LiquidCarver = create(7, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 0, x, z, seed};
    generator.generateCarvers(region, seed, *chunk, GenerationStage::Carving::LIQUID);
});

const ChunkStatus ChunkStatus::Features = create(8, 1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 1, x, z, seed};
    generator.generateFeatures(region, *chunk);
});

const ChunkStatus ChunkStatus::Light = create(9, 1, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{world, chunks, 1, x, z, seed};
    lightManager.calculate(region, x << 4, z << 4);
});

const ChunkStatus ChunkStatus::Full = create(10, 0, [](ServerWorld* world, WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {

});

ChunkStatus ChunkStatus::create(int32_t ordinal, int32_t range, Fn generate) noexcept {
    return {
        .ordinal = ordinal,
        .range = range,
        .generate = generate
    };
}

ChunkStatus const* ChunkStatus::getById(int32_t ordinal) {
    return ALL.at(ordinal);
}
