#include "MineshaftStructure.hpp"
#include "MineshaftRoom.hpp"
#include <configs.hpp>

bool MineshaftStructure::canGenerate(ChunkGenerator &generator, BiomeProvider &biomes, int64_t seed, Random &random, int x, int z, Biome &biome, const ChunkPos &pos, const StructureConfig &config) {
    random.setLargeFeatureSeed(seed, x, z);
    return random.nextDouble() < std::get<MineshaftConfig>(config).probability;
}

void MineshaftStructure::createComponents(StructurePieces& pieces, ChunkGenerator &generator, TemplateManager &templateManager, int x, int z, Biome &biome, const StructureConfig &config, int64_t seed) {
    const auto& cfg = std::get<MineshaftConfig>(config);
    
    Random random{};
    random.setLargeFeatureSeed(seed, x, z);

    auto room = new MineshaftPieces::Room(0, random, (x << 4) + 2, (z << 4) + 2, cfg.type);
    pieces.emplace(room);
    room->buildComponent(room, pieces.components, random);
    if (cfg.type == MineshaftType::MESA) {
        const auto bounds = pieces.getBoundingBox().value();
        const auto y = /*generator.getSeaLevel()*/63 - bounds.maxY + bounds.getYSize() / 2 + 5;
        pieces.moveVertically(y);
    } else {
        pieces.markAvailableHeight(/*generator.getSeaLevel()*/63, 0/*minY*/, random, 10);
    }
}
