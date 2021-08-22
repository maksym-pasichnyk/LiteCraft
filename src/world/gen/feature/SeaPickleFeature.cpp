#include "SeaPickleFeature.hpp"
#include <block/Blocks.hpp>
#include <block/SeaPickleBlock.hpp>
#include <world/WorldGenRegion.hpp>

bool SeaPickleFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    const auto &cfg = std::get<FeatureSpreadConfig>(config);

    const auto SEA_PICKLE = Blocks::SEA_PICKLE->getDefaultState();

    auto count_of_blocks = 0;
    const auto count = cfg.spread.get(random);
    for (int k = 0; k < count; ++k) {
        const auto x0 = random.nextInt(8);
        const auto x1 = random.nextInt(8);
        const auto z0 = random.nextInt(8);
        const auto z1 = random.nextInt(8);
        const auto blockpos = reader.getHeight(HeightmapType::OCEAN_FLOOR, pos.add(x0 - x1, 0, z0 - z1));
        const auto state = SEA_PICKLE.set<SeaPickleBlock::PICKLES>(random.nextInt(4) + 1);
        if (reader.getData(blockpos).is(Blocks::WATER) && state.isValidPosition(reader, blockpos)) {
            reader.setData(blockpos, state/*, 2*/);
            ++count_of_blocks;
        }
    }
    return count_of_blocks > 0;
}