#include "ChunkGenerator.hpp"

#include "feature/ConfiguredFeature.hpp"
#include "feature/ConfiguredFeatures.hpp"
#include "../WorldGenRegion.hpp"
#include "../biome/Biome.hpp"
#include "../biome/provider/BiomeProvider.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"

struct ExampleStructurePiece : StructurePiece {
    ExampleStructurePiece(int32_t pos_x, int32_t pos_z) {
        coordBaseMode = SOUTH;
        boundingBox = BoundingBox::withSize(pos_x - 1, 6, pos_z - 1, 3, 10, 3);
    }

    void place(WorldGenRegion& region, BoundingBox sbb) override {
//        const auto wood = Blocks::WOOD->getDefaultState();
//
//        for (auto y = 0; y < 10; y++) {
//            setBlock(region, sbb, 0, y, 0, Blocks2::iron_bars->getStateWithMeta(2 | 4));
//            setBlock(region, sbb, 0, y, 1, wood);
//            setBlock(region, sbb, 0, y, 2, Blocks2::iron_bars->getStateWithMeta(8 | 4));
//
//            setBlock(region, sbb, 1, y, 0, wood);
//            setBlock(region, sbb, 1, y, 1, wood);
//            setBlock(region, sbb, 1, y, 2, wood);
//
//            setBlock(region, sbb, 2, y, 0, Blocks2::iron_bars->getStateWithMeta(2 | 1));
//            setBlock(region, sbb, 2, y, 1, wood);
//            setBlock(region, sbb, 2, y, 2, Blocks2::iron_bars->getStateWithMeta(8 | 1));
//        }
    }
};

struct ExampleStructureStart : StructureStart {
    void build(int32_t pos_x, int32_t pos_z) override {
        pieces.emplace_back(new ExampleStructurePiece(pos_x + 8, pos_z + 8));
    }
};

void ChunkGenerator::generateStructures(WorldGenRegion &region, Chunk& chunk) {
    if (std::abs(chunk.pos.x) % 2 == std::abs(chunk.pos.z) % 2) {
        auto start = std::make_shared<ExampleStructureStart>();
        start->build(chunk.pos.getStartX(), chunk.pos.getStartZ());
        start->updateBoundingBox();
        chunk.structureStarts.emplace_back(std::move(start));
    }
}

ChunkGenerator::ChunkGenerator(std::unique_ptr<BiomeProvider>&& biomeProvider) : biomeProvider(std::move(biomeProvider)) {}

void ChunkGenerator::getStructureReferences(WorldGenRegion &region, Chunk& chunk) {
    const auto sbb = BoundingBox::fromChunkPos(chunk.pos.x, chunk.pos.z);

    for (auto x = chunk.pos.x - 8; x <= chunk.pos.x + 8; x++) {
        for (auto z = chunk.pos.z - 8; z <= chunk.pos.z + 8; z++) {
            for (auto& start : region.getChunk(x, z)->structureStarts) {
                if (sbb.intersect(start->boundingBox)) {
                    chunk.structureReferences.emplace_back(start);
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

void placeBlock(IBlockWriter auto& blocks, int32_t x, int32_t y, int32_t z, const BlockData& data, const BoundingBox& sbb) {
    if (sbb.contains(x, y, z)) {
        blocks.setData(x, y, z, data);
    }
}

void generateTree(IBlockWriter auto& blocks, int32_t x, int32_t height, int32_t z, Random& rand, const BoundingBox& sbb) {
//    const auto treeHeight = 4 + rand.nextInt(0, 2);
//
//    const BlockData leaves = Blocks::LEAVES->getDefaultState();
//    const BlockData log = Blocks::LOG->getDefaultState();
//
//    for (auto y = treeHeight - 2; y <= treeHeight + 1; y++) {
//        placeBlock(blocks, x - 1, y + height, z - 1, leaves, sbb);
//        placeBlock(blocks, x + 0, y + height, z - 1, leaves, sbb);
//        placeBlock(blocks, x + 1, y + height, z - 1, leaves, sbb);
//
//        placeBlock(blocks, x - 1, y + height, z, leaves, sbb);
//        placeBlock(blocks, x + 0, y + height, z, leaves, sbb);
//        placeBlock(blocks, x + 1, y + height, z, leaves, sbb);
//
//        placeBlock(blocks, x - 1, y + height, z + 1, leaves, sbb);
//        placeBlock(blocks, x + 0, y + height, z + 1, leaves, sbb);
//        placeBlock(blocks, x + 1, y + height, z + 1, leaves, sbb);
//    }
//    for (auto y = height; y < height + treeHeight; y++) {
//        placeBlock(blocks, x, y, z, log, sbb);
//    }
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