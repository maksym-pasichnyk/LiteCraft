#include "Stronghold.hpp"
#include "StrongholdPieces.hpp"

auto Stronghold::create() -> std::unique_ptr<Structure> {
    return std::make_unique<Structure>(Structure{
        .canGenerate = canGenerate,
        .generatePieces = createComponents
    });
}

bool Stronghold::canGenerate(ChunkGenerator &generator, BiomeProvider &biomes, int64_t seed, Random &random, int x, int z, Biome &biome, const ChunkPos &pos, const StructureConfig &config) {
    random.setLargeFeatureSeed(seed, x, z);
    return random.nextDouble() < 0.25f;
}

void Stronghold::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {

}
