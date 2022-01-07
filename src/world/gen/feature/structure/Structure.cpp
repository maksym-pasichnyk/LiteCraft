#include "Structure.hpp"
#include "PieceGenerator.hpp"
#include "StructureStart.hpp"

#include <util/math/Math.hpp>

auto Structure::generate(ChunkGenerator &generator, BiomeProvider &provider, TemplateManager &templateManager, int64_t seed, const ChunkPos &pos, Biome &biome, int refCount, Random &random, const StructureSeparation& settings, const StructureConfig &config) -> StructureStart* {
    const auto chunkpos = getChunkPosForStructure(settings, seed, random, pos.x, pos.z);
    if (pos == chunkpos && canGenerate(generator, provider, seed, random, pos.x, pos.z, biome, chunkpos, config)) {
        auto pieces = StructurePieces{};

        auto context = StructureGenerateContext {
            generator,
            templateManager,
            ChunkPos::from(pos.x, pos.z),
            biome,
            seed
        };
        generatePieces(pieces, context, config);

        if (pieces.empty()) {
            return nullptr;
        }

        auto bounds = pieces.getBoundingBox().value();
        return new StructureStart(std::move(pieces.components), this, pos.x, pos.z, bounds, refCount, seed);
    }
    return nullptr;/*StructureStart.DUMMY*/;
}

auto Structure::getChunkPosForStructure(const StructureSeparation &settings, int64_t seed, Random &random, int x, int z) -> ChunkPos {
    const auto [spacing, separation, salt] = settings;
    const int ix = Math::floorDiv(x, spacing);
    const int iz = Math::floorDiv(z, spacing);
    random.setLargeFeatureSeedWithSalt(seed, ix, iz, salt);
    int i1;
    int j1;
    if (hasSimpleSeparation()) {
        i1 = random.nextInt(spacing - separation);
        j1 = random.nextInt(spacing - separation);
    } else {
        const int g0 = random.nextInt(spacing - separation);
        const int g1 = random.nextInt(spacing - separation);
        i1 = (g0 + g1) / 2;

        const int g2 = random.nextInt(spacing - separation);
        const int g3 = random.nextInt(spacing - separation);
        j1 = (g2 + g3) / 2;
    }
    return ChunkPos::from(ix * spacing + i1, iz * spacing + j1);
}
