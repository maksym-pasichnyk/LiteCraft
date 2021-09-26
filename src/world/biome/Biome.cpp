#include "Biome.hpp"
#include "../WorldGenRegion.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"
#include "../../block/Blocks.hpp"
#include "../../block/SnowyDirtBlock.hpp"
#include "../../block/material/Materials.hpp"
#include "../gen/feature/structure/Structure.hpp"
#include "../gen/feature/structure/Structures.hpp"
#include "../gen/feature/structure/StructureStart.hpp"
#include "../gen/feature/structure/TemplateManager.hpp"

#include <range/v3/view.hpp>
#include <world/chunk/ChunkStatus.hpp>

const PerlinNoiseGenerator Biome::TEMPERATURE_NOISE = PerlinNoiseGenerator(Random::from(1234), ranges::views::single(0));
const PerlinNoiseGenerator Biome::FROZEN_TEMPERATURE_NOISE = PerlinNoiseGenerator(Random::from(3456), ranges::views::iota(-2, 0 + 1));
const PerlinNoiseGenerator Biome::INFO_NOISE = PerlinNoiseGenerator(Random::from(2345), ranges::views::single(0));

void Biome::decorate(ChunkGenerator &generator, WorldGenRegion &region, TemplateManager& templates, int64_t seed, const BlockPos& pos) {
    const auto chunk_pos = ChunkPos::from(pos);

    auto main_chunk = region.getChunk(chunk_pos.x, chunk_pos.z);
    const auto bb = BoundingBox::fromChunkPos(chunk_pos.x, chunk_pos.z);

    Random random{};
    for (int stage = 0; stage < 10; stage++) {
        int k = 0;

        for (auto structure : Structures::stages[stage]) {
            if (auto it = main_chunk->references.find(structure); it != main_chunk->references.end()) {
                for (auto ref_pos : it->second | ranges::views::transform([](int64_t i) { return ChunkPos::from(i); })) {
                    auto chunk = region.getChunk(ref_pos.x, ref_pos.z);
                    if (auto start = chunk->starts.find(structure); start != chunk->starts.end()) {
                        random.setFeatureSeed(seed, k, stage);
                        start->second->generate(region, templates, generator, random, bb, chunk_pos);
                    }
                }
            }
        }

        for (auto feature : biomeGenerationSettings.features[stage]) {
            random.setFeatureSeed(seed, k, stage);
            feature->generate(region, generator, random, pos);
            ++k;
        }
    }
}

bool Biome::doesSnowGenerate(WorldReader &world, const BlockPos &pos) {
    if (getTemperature(pos) >= 0.15F) {
        return false;
    }
    if (pos.y >= 0 && pos.y < 256 && world.getBlockLight(pos) < 10) {
        const auto data = world.getData(pos);
        return data.isAir() && Blocks::SNOW->getDefaultState().isValidPosition(world, pos);
    }

    return false;
}
bool Biome::doesWaterFreeze(WorldReader &world, const BlockPos &pos, bool mustBeAtEdge) {
    if (getTemperature(pos) >= 0.15F) {
        return false;
    }
    if (pos.y >= 0 && pos.y < 256 && world.getBlockLight(/*LightType::BLOCK,*/ pos) < 10) {
        const auto data = world.getData(pos);
        if (data.getBlock()->getMaterial() == Materials::WATER) {
            if (!mustBeAtEdge) {
                return true;
            }
            bool flag = world.hasWater(pos.west()) &&
                        world.hasWater(pos.east()) &&
                        world.hasWater(pos.north()) &&
                        world.hasWater(pos.south());
            return !flag;
        }
//        FluidState fluidstate = worldIn.getFluidState(pos);
//        if (fluidstate.getFluid() == Fluids.WATER && blockstate.getBlock() instanceof FlowingFluidBlock) {
//            if (!mustBeAtEdge) {
//                return true;
//            }
//
//        }
    }

    return false;
}
