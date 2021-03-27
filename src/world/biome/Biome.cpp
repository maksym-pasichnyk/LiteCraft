#include "Biome.hpp"
#include "../WorldGenRegion.hpp"
#include "../chunk/Chunk.hpp"
#include "../../block/Block.hpp"
#include "../../block/Blocks.hpp"
#include "../../block/SnowyDirtBlock.hpp"
#include "../../block/material/Materials.hpp"

#include <ranges>

const PerlinNoiseGenerator Biome::TEMPERATURE_NOISE = PerlinNoiseGenerator(Random::from(1234), std::views::single(0));
const PerlinNoiseGenerator Biome::FROZEN_TEMPERATURE_NOISE = PerlinNoiseGenerator(Random::from(3456), std::views::iota(-2, 0 + 1));
const PerlinNoiseGenerator Biome::INFO_NOISE = PerlinNoiseGenerator(Random::from(2345), std::views::single(0));

void Biome::decorate(ChunkGenerator &generator, WorldGenRegion &region, int64_t seed, Random &rand, glm::ivec3 pos) {
    for (int i = 0; i < 10; i++) {
        int k = 0;

        for (auto feature : biomeGenerationSettings.features[i]) {
            rand.setFeatureSeed(seed, k, i);
            feature->generate(region, generator, rand, pos);
            ++k;
        }
    }
}

bool Biome::doesSnowGenerate(WorldReader &world, const glm::ivec3 &pos) {
    if (getTemperature(pos) >= 0.15F) {
        return false;
    }
    if (pos.y >= 0 && pos.y < 256 && world.getBlockLight(/*LightType::BLOCK,*/ pos) < 10) {
        const auto data = world.getData(pos);
        return data.isAir() && Blocks::SNOW->getDefaultState().isValidPosition(world, pos);
    }

    return false;
}
bool Biome::doesWaterFreeze(WorldReader &world, const glm::ivec3 &pos, bool mustBeAtEdge) {
    if (getTemperature(pos) >= 0.15F) {
        return false;
    }
    if (pos.y >= 0 && pos.y < 256 && world.getBlockLight(/*LightType::BLOCK,*/ pos) < 10) {
        const auto data = world.getData(pos);
        if (data.getBlock()->getMaterial() == Materials::WATER) {
            if (!mustBeAtEdge) {
                return true;
            }
            bool flag = world.hasWater(pos - glm::ivec3(1, 0, 0)) &&
                        world.hasWater(pos + glm::ivec3(1, 0, 0)) &&
                        world.hasWater(pos - glm::ivec3(0, 0, 1)) &&
                        world.hasWater(pos + glm::ivec3(0, 0, 1));
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
