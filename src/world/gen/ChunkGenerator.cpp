#include "ChunkGenerator.hpp"

#include "feature/ConfiguredFeature.hpp"
#include "../WorldGenRegion.hpp"
#include "../biome/Biome.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"

#include "settings/StructureSeparation.hpp"
#include "feature/structure/Structure.hpp"
#include "feature/structure/StructureStart.hpp"
#include "feature/structure/TemplateManager.hpp"
#include "feature/structure/StructureFeature.hpp"
#include "feature/structure/StructureManager.hpp"


ChunkGenerator::ChunkGenerator(std::unique_ptr<BiomeProvider>&& biomeProvider) : biomeProvider(std::move(biomeProvider)) {}

void ChunkGenerator::generateStructures(WorldGenRegion &region, Chunk& chunk) {
    const auto [xpos, zpos] = chunk.pos;
    auto biome = biomeProvider->getNoiseBiome(xpos << 2, 0, zpos << 2);

    StructureManager structureManager{};
    TemplateManager templateManager{};

    for (auto feature : biome->getGenerationSettings().structures) {
        createStarts(feature, structureManager, chunk, templateManager, region.getSeed(), chunk.pos, *biome);
    }
}

void ChunkGenerator::getStructureReferences(WorldGenRegion &region, Chunk& chunk) {
    const auto sbb = BoundingBox::fromChunkPos(chunk.pos.x, chunk.pos.z);

    for (auto x = chunk.pos.x - 8; x <= chunk.pos.x + 8; x++) {
        for (auto z = chunk.pos.z - 8; z <= chunk.pos.z + 8; z++) {
            for (auto [structure, start] : region.getChunk(x, z)->starts) {
                if (sbb.intersectsWith(start->getBoundingBox())) {
                    chunk.references[structure].emplace(ChunkPos::asLong(x, z));
                }
            }
        }
    }
}

void ChunkGenerator::generateCarvers(WorldGenRegion& region, int64_t seed, Chunk& chunk/*, GenerationStage::Carving carving*/) {
    const auto [xpos, zpos] = chunk.pos;

    const auto getBiome = [&region] (BlockPos pos) {
        return region.getBiome(pos);
    };

    const auto seaLevel = region.getSeaLevel();

    Random random;

    auto biome = biomeProvider->getNoiseBiome(xpos << 2, 0, zpos << 2);

    for (auto carvers : std::span(biome->biomeGenerationSettings.carvers)) {
        for (int32_t xoffset = xpos - 8; xoffset <= xpos + 8; ++xoffset) {
            for (int32_t zoffset = zpos - 8; zoffset <= zpos + 8; ++zoffset) {
//                std::span carvers = biome->biomeGenerationSettings.carvers[static_cast<size_t>(carving)];

                for (size_t i = 0; i < carvers.size(); ++i) {
                    random.setLargeFeatureSeed(seed + static_cast<int64_t>(i), xoffset, zoffset);
                    if (carvers[i]->shouldCarve(random, xoffset, zoffset)) {
                        carvers[i]->carveRegion(chunk, getBiome, random, seaLevel, xoffset, zoffset, xpos, zpos);
                    }
                }
            }
        }
    }
}

void ChunkGenerator::generateFeatures(WorldGenRegion &region, Chunk& chunk) {
    Random random{};

    const auto chunkPos = region.getMainChunkPos();
    const auto xStart = chunkPos.getStartX();
    const auto zStart = chunkPos.getStartZ();
    const auto seed = random.setDecorationSeed(region.getSeed(), xStart, zStart);

    auto biome = biomeProvider->getNoiseBiome((chunkPos.x << 2) + 2, 2, (chunkPos.z << 2) + 2);
    biome->decorate(*this, region, seed, BlockPos(xStart, 0, zStart));
}

Biome *ChunkGenerator::getNoiseBiome(int x, int y, int z) {
    return biomeProvider->getNoiseBiome(x, y, z);
}

void ChunkGenerator::createStarts(StructureFeature *feature, StructureManager &structureManager, Chunk &chunk, TemplateManager &templateManager, int64_t seed, const ChunkPos &chunkPos, Biome &biome) {
    StructureSeparation separation {
        .spacing = 10,
        .separation = 10,
        .salt = 0
    };

    Random random{};
    auto start = feature->structure->generate(*this, *biomeProvider, templateManager, seed, chunkPos, biome, 0, random, separation, feature->config);
    if (start != nullptr) {
        chunk.addStructureStart(feature->structure, start);
    }

//    auto structurestart = structureManager.getStructureStart(SectionPos.from(chunk.getPos(), 0), feature.structure, chunk);
//    const int i = structurestart != nullptr ? structurestart.getRefCount() : 0;
//    StructureSeparationSettings separation = this.settings.getSeparationSettings(feature.structure);
//    if (separation != null) {
//        StructureStart<?> structurestart1 = feature.generate(registries, this, this.biomeProvider, templateManager, seed, chunkPos, biome, i, separation);
//        structureManager.addStructureStart(SectionPos.from(chunk.getPos(), 0), feature.structure, structurestart1, chunk);
//    }
}