#include "OceanRuinStart.hpp"
#include "OceanRuinPiece.hpp"

void OceanRuinStructure::Start::createComponents(ChunkGenerator &generator, TemplateManager &templateManager, int chunkx, int chunkz, Biome &biome, const StructureConfig &config, int64_t seed) {
    auto random = Random::fromLargeFeatureSeed(seed, chunkx, chunkz);
    recalculateStructureSize();
}
