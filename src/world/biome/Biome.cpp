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
//        auto features = biomeGenerationSettings.features;

    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            const int xpos = pos.x + x;
            const int zpos = pos.z + z;
            const int ypos = region.getHeight(/*Heightmap::Type::MOTION_BLOCKING,*/ xpos, zpos);
            const glm::ivec3 selfpos{xpos, ypos, zpos};
            const glm::ivec3 downpos{xpos, ypos - 1, zpos};
            auto biome = region.getBiome(selfpos);
            if (biome->doesWaterFreeze(region, downpos, false)) {
                region.setData(downpos, Blocks::ICE->getDefaultState()/*, 2*/);
            }

            if (biome->doesSnowGenerate(region, selfpos)) {
                region.setData(selfpos, Blocks::SNOW->getDefaultState()/*, 2*/);
                const auto data = region.getData(downpos);
                if (data.hasProperty(SnowyDirtBlock::SNOWY)) {
//                    region.setData(downpos, data.with(SnowyDirtBlock::SNOWY, true)/*, 2*/);
                }
            }
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
