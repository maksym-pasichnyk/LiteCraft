#include "Structure.hpp"
#include "StructureStart.hpp"

#include "../../../../util/math/Math.hpp"

StructureStart* Structure::generate(ChunkGenerator &generator, BiomeProvider &provider, TemplateManager &templateManager, int64_t seed, const ChunkPos &pos, Biome &biome, int refCount, Random &random, const StructureSeparation& settings, const StructureConfig &config) {
    const auto chunkpos = getChunkPosForStructure(settings, seed, random, pos.x, pos.z);
    if (pos == chunkpos && canGenerate(generator, provider, seed, random, pos.x, pos.z, biome, chunkpos, config)) {
        auto start = createStart(pos.x, pos.z, BoundingBox::getNewBoundingBox(), refCount, seed);
        start->createComponents(/*dynamicRegistries,*/ generator, templateManager, pos.x, pos.z, biome, config);
        if (start->isValid()) {
            return start;
        }
    }
    return nullptr;/*StructureStart.DUMMY*/;
}

ChunkPos Structure::getChunkPosForStructure(const StructureSeparation &settings, int64_t seed, Random &random, int x, int z) {
    const auto [spacing, separation, salt] = settings;
    const int ix = Math::floorDiv(x, spacing);
    const int iz = Math::floorDiv(z, spacing);
    random.setLargeFeatureSeedWithSalt(seed, ix, iz, salt);
    int i1;
    int j1;
    if (func_230365_b_()) {
        i1 = random.nextInt(spacing - separation);
        j1 = random.nextInt(spacing - separation);
    } else {
        i1 = (random.nextInt(spacing - separation) + random.nextInt(spacing - separation)) / 2;
        j1 = (random.nextInt(spacing - separation) + random.nextInt(spacing - separation)) / 2;
    }
    return ChunkPos::from(ix * spacing + i1, iz * spacing + j1);
}
