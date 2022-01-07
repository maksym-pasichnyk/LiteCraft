#include "PillagerOutpost.hpp"
#include <world/gen/feature/jigsaw/Jigsaw.hpp>

auto PillagerOutpost::create() -> std::unique_ptr<Structure> {
    return std::make_unique<Structure>(Structure{
        .configFromJson = [](const Json& o) -> tl::optional<StructureConfig> {
            return o.into<JigsawConfig>();
        },
        .canGenerate = canGenerate,
        .generatePieces = Jigsaw::createComponents
    });
}

auto PillagerOutpost::canGenerate(ChunkGenerator& generator, BiomeProvider& biomes, int64_t seed, Random& random, int x, int z, Biome& biome, const ChunkPos& pos, const StructureConfig& config) -> bool {
    return true;
}