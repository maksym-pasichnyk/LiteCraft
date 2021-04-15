#include "VinesFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/VineBlock.hpp"
#include "../../../util/Direction.hpp"

bool VinesFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto VINE = Blocks::VINE->getDefaultState();
    for (int y = 64; y < 256; ++y) {
        const auto x = pos.x + random.nextInt(4) - random.nextInt(4);
        const auto z = pos.z + random.nextInt(4) - random.nextInt(4);

        const BlockPos blockpos{x, y, z};
        if (reader.isAirBlock(blockpos)) {
            for(Direction direction : DirectionUtil::values()) {
                if (direction != Direction::DOWN && VineBlock::canAttachTo(reader, blockpos, direction)) {
                    const auto state = VINE;//.with(VineBlock.getPropertyFor(direction), true);
                    reader.setData(blockpos, state/*, 2*/);
                    break;
                }
            }
        }
    }

    return true;
}
