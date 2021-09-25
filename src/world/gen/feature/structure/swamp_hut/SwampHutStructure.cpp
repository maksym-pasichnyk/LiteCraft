#include "SwampHutStructure.hpp"
#include "SwampHutPiece.hpp"
#include <configs.hpp>

void SwampHutStructure::createComponents(StructurePieces& pieces, ChunkGenerator &generator, TemplateManager &templateManager, int x, int z, Biome &biome, const StructureConfig &config, int64_t seed) {
    auto random = Random::fromLargeFeatureSeed(seed, x, z);
    pieces.emplace(new SwampHutPiece(random, x << 4, z << 4));
}
