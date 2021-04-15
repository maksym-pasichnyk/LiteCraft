#include "ChunkGenerator.hpp"

#include "feature/ConfiguredFeature.hpp"
#include "../WorldGenRegion.hpp"
#include "../biome/Biome.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"

#include "settings/StructureSeparation.hpp"
#include "feature/structure/Structure.hpp"
#include "feature/structure/StructureFeature.hpp"

struct StructureManager {

};

struct TemplateManager {

};

//struct ExampleStructurePiece : StructurePiece {
//    ExampleStructurePiece(int32_t pos_x, int32_t pos_z) {
//        coordBaseMode = SOUTH;
//        boundingBox = BoundingBox::withSize(pos_x - 1, 6, pos_z - 1, 3, 10, 3);
//    }
//
//    void place(WorldGenRegion& region, BoundingBox sbb) override {
////        const auto wood = Blocks::WOOD->getDefaultState();
////
////        for (auto y = 0; y < 10; y++) {
////            setBlock(region, sbb, 0, y, 0, Blocks2::iron_bars->getStateWithMeta(2 | 4));
////            setBlock(region, sbb, 0, y, 1, wood);
////            setBlock(region, sbb, 0, y, 2, Blocks2::iron_bars->getStateWithMeta(8 | 4));
////
////            setBlock(region, sbb, 1, y, 0, wood);
////            setBlock(region, sbb, 1, y, 1, wood);
////            setBlock(region, sbb, 1, y, 2, wood);
////
////            setBlock(region, sbb, 2, y, 0, Blocks2::iron_bars->getStateWithMeta(2 | 1));
////            setBlock(region, sbb, 2, y, 1, wood);
////            setBlock(region, sbb, 2, y, 2, Blocks2::iron_bars->getStateWithMeta(8 | 1));
////        }
//    }
//};

//struct ExampleStructureStart : StructureStart {
//    void build(int32_t pos_x, int32_t pos_z) override {
//        pieces.emplace_back(new ExampleStructurePiece(pos_x + 8, pos_z + 8));
//    }
//};

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
//    const auto sbb = BoundingBox::fromChunkPos(chunk.pos.x, chunk.pos.z);

//    for (auto x = chunk.pos.x - 8; x <= chunk.pos.x + 8; x++) {
//        for (auto z = chunk.pos.z - 8; z <= chunk.pos.z + 8; z++) {
//            for (auto& start : region.getChunk(x, z)->structureStarts) {
//                if (sbb.intersectsWith(start->boundingBox)) {
//                    chunk.structureReferences.emplace_back(start);
//                }
//            }
//        }
//    }
}

void ChunkGenerator::generateCarvers(WorldGenRegion& region, int64_t seed, Chunk& chunk/*, GenerationStage::Carving carving*/) {
    const auto [xpos, zpos] = chunk.pos;

    const auto getBiome = [&region] (BlockPos pos) {
        return region.getBiome(pos);
    };

    Random random;

    auto biome = biomeProvider->getNoiseBiome(xpos << 2, 0, zpos << 2);

    for (auto carvers : std::span(biome->biomeGenerationSettings.carvers)) {
        for (int32_t xoffset = xpos - 8; xoffset <= xpos + 8; ++xoffset) {
            for (int32_t zoffset = zpos - 8; zoffset <= zpos + 8; ++zoffset) {
//                std::span carvers = biome->biomeGenerationSettings.carvers[static_cast<size_t>(carving)];

                for (size_t i = 0; i < carvers.size(); ++i) {
                    random.setLargeFeatureSeed(seed + static_cast<int64_t>(i), xoffset, zoffset);
                    if (carvers[i].shouldCarve(random, xoffset, zoffset)) {
                        carvers[i].carveRegion(chunk, getBiome, random, /*seaLevel*/63, xoffset, zoffset, xpos, zpos/*, carvingMask*/);
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
    biome->decorate(*this, region, seed, random, BlockPos(xStart, 0, zStart));
}

void ChunkGenerator::createStarts(StructureFeature *feature, StructureManager &structureManager, Chunk &chunk, TemplateManager &templateManager, int64_t seed, const ChunkPos &chunkPos, Biome &biome) {
    StructureSeparation separation {
        .spacing = 10,
        .separation = 10,
        .salt = 0
    };

    Random random{};
    auto start = feature->structure->generate(*this, *biomeProvider, templateManager, seed, chunkPos, biome, 0, random, separation, feature->config);
    chunk.addStructureStart(feature->structure, start);


//    auto structurestart = structureManager.getStructureStart(SectionPos.from(chunk.getPos(), 0), feature.structure, chunk);
//    const int i = structurestart != nullptr ? structurestart.getRefCount() : 0;
//    StructureSeparationSettings separation = this.settings.getSeparationSettings(feature.structure);
//    if (separation != null) {
//        StructureStart<?> structurestart1 = feature.generate(registries, this, this.biomeProvider, templateManager, seed, chunkPos, biome, i, separation);
//        structureManager.addStructureStart(SectionPos.from(chunk.getPos(), 0), feature.structure, structurestart1, chunk);
//    }
}
