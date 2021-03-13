#include "ChunkStatus.hpp"
#include "../gen/ChunkGenerator.hpp"
#include "../light/WorldLightManager.hpp"
#include "../../WorldGenRegion.hpp"

constexpr std::array ALL {
    &ChunkStatus::Empty,
    &ChunkStatus::StructureStart,
    &ChunkStatus::StructureReferences,
    &ChunkStatus::Noise,
    &ChunkStatus::Surface,
    &ChunkStatus::Features,
    &ChunkStatus::Light,
    &ChunkStatus::Full
};

const ChunkStatus ChunkStatus::Empty = create(0, -1, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {

});

const ChunkStatus ChunkStatus::StructureStart = create(1, 0, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{chunks, 0, x, z, seed};
    generator.generateStructures(region, *chunk);
});

const ChunkStatus ChunkStatus::StructureReferences = create(2, 0, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
//    WorldGenRegion region{chunks, 0, x, z, seed};
//    generator.getStructureReferences(region, *chunk);
});

const ChunkStatus ChunkStatus::Noise = create(3, 0, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    generator.generateTerrain(*chunk);
});

const ChunkStatus ChunkStatus::Surface = create(4, 0, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{chunks, 0, x, z, seed};
    generator.generateSurface(region, *chunk);
});

const ChunkStatus ChunkStatus::Features = create(5, 0, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{chunks, 0, x, z, seed};
    generator.generateFeatures(region, *chunk);
});

const ChunkStatus ChunkStatus::Light = create(6, 1, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {
    WorldGenRegion region{chunks, 1, x, z, seed};
    lightManager.calculate(region, x << 4, z << 4);
});

const ChunkStatus ChunkStatus::Full = create(7, 0, [](WorldLightManager& lightManager, ChunkGenerator& generator, int32_t x, int32_t z, Chunk* chunk, std::span<Chunk*> chunks, int64_t seed) {

});

ChunkStatus ChunkStatus::create(int id, int range, Fn generate) noexcept {
    return {
        .range = range,
        .generate = generate
    };
}

ChunkStatus const* ChunkStatus::getById(int id) {
    return ALL[id];
}
