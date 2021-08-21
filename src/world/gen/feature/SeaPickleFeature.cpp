#include "SeaPickleFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool SeaPickleFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    const auto &cfg = std::get<FeatureSpreadConfig>(config);

    int i = 0;
    const auto count = cfg.spread.get(random);
    for (int k = 0; k < count; ++k) {
        const auto x0 = random.nextInt(8);
        const auto x1 = random.nextInt(8);
        const auto z0 = random.nextInt(8);
        const auto z1 = random.nextInt(8);
        const auto blockpos = reader.getHeight(HeightmapType::OCEAN_FLOOR, pos.add(x0 - x1, 0, z0 - z1));
        const auto state = Blocks::SEA_PICKLE->getDefaultState();
//                            .with(SeaPickleBlock::PICKLES, random.nextInt(4) + 1);
        if (reader.getData(blockpos).is(Blocks::WATER) && state.isValidPosition(reader, blockpos)) {
            reader.setData(blockpos, state/*, 2*/);
            ++i;
        }
    }
    return i > 0;
}