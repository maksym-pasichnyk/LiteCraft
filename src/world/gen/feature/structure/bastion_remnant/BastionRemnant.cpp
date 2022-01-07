#include "BastionRemnant.hpp"
#include <world/gen/feature/jigsaw/Jigsaw.hpp>

auto BastionRemnant::create() -> std::unique_ptr<Structure> {
    return std::make_unique<Structure>(Structure{
        .configFromJson = [](const Json& o) -> tl::optional<StructureConfig> {
            return o.into<JigsawConfig>();
        },
        .generatePieces = Jigsaw::createComponents
    });
}

auto BastionRemnant::canGenerate(ChunkGenerator &generator, BiomeProvider &biomes, int64_t seed, Random &random, int x, int z, Biome &biome, const ChunkPos &pos, const StructureConfig &config) -> bool {
    random.setLargeFeatureSeed(seed, x, z);
    return random.nextInt(5) >= 2;
}