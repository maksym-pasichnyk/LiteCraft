#include "SeaGrassFeature.hpp"
#include <block/Blocks.hpp>
#include <block/TallSeaGrassBlock.hpp>
#include <world/WorldGenRegion.hpp>

bool SeaGrassFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    const auto& cfg = std::get<ProbabilityConfig>(config);
    
    const auto x0 = random.nextInt(8);
    const auto x1 = random.nextInt(8);
    const auto z0 = random.nextInt(8);
    const auto z1 = random.nextInt(8);

    auto flag = false;
    const auto ocen_top = reader.getHeight(HeightmapType::OCEAN_FLOOR, pos.add(x0 - x1, 0, z0 - z1));
    if (reader.getData(ocen_top).is(Blocks::WATER)) {
        const auto is_tall = random.nextDouble() < static_cast<double>(cfg.probability);
        const auto state = is_tall
                            ? Blocks::TALL_SEAGRASS->getDefaultState()
                            : Blocks::SEAGRASS->getDefaultState();
        if (state.isValidPosition(reader, ocen_top)) {
            if (is_tall) {
                const auto up_pos = ocen_top.up();
                if (reader.getData(up_pos).is(Blocks::WATER)) {
                    reader.setData(ocen_top, state/*, 2*/);
                    reader.setData(up_pos, state.set<TallSeaGrassBlock::HALF>(DoubleBlockHalf::UPPER)/*, 2*/);
                }
            } else {
                reader.setData(ocen_top, state/*, 2*/);
            }
            flag = true;
        }
    }

    return flag;
}