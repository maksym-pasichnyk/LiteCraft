#include "StrongholdStructure.hpp"
#include "StrongholdPieces.hpp"

bool StrongholdStructure::canGenerate(ChunkGenerator &generator, BiomeProvider &biomes, int64_t seed, Random &random, int x, int z, Biome &biome, const ChunkPos &pos, const StructureConfig &config) {
//    random.setLargeFeatureSeed(seed, x, z);
//    return random.nextDouble() < std::get<StrongholdConfig>(config).probability;
    return false;
}

//void StrongholdStructure::createComponents(ChunkGenerator &generator, TemplateManager &templateManager, int chunkx, int chunkz, Biome &biome, const StructureConfig &config, int64_t seed) {
//    const auto& cfg = std::get<StrongholdConfig>(config);
//
//    auto room = new StrongholdPieces::Room(0, rand, (chunkx << 4) + 2, (chunkz << 4) + 2, cfg.type);
//    components.emplace_back(room);
//    room->buildComponent(room, components, rand);
//    recalculateStructureSize();
//    if (cfg.type == StrongholdType::MESA) {
//        const int y = /*generator.getSeaLevel()*/63 - bounds.maxY + bounds.getYSize() / 2 + 5;
//        bounds.offset(0, y, 0);
//
//        for (auto piece : components) {
//            piece->offset(0, y, 0);
//        }
//    } else {
//        markAvailableHeight(/*generator.getSeaLevel()*/63, rand, 10);
//    }
//}

void StrongholdStructure::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {

}
