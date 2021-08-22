#include "VinesFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/VineBlock.hpp"
#include "../../../util/Direction.hpp"

bool VinesFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto VINE = Blocks::VINE->getDefaultState();
    for (int y = 64; y < 256; ++y) {
        const auto x0 = random.nextInt(4);
        const auto x1 = random.nextInt(4);
        const auto z0 = random.nextInt(4);
        const auto z1 = random.nextInt(4);

        const auto blockpos = BlockPos::from(pos.x + x0 - x1, y, pos.z + z0 - z1);
        if (reader.isAirBlock(blockpos)) {
            for (const auto direction : DirectionUtil::values()) {
                if (direction != Direction::DOWN && VineBlock::canAttachTo(reader, blockpos, direction)) {
                    const auto state = VINE.set(VineBlock::getPropertyFor(direction), true);
                    reader.setData(blockpos, state /*, 2*/);
                    break;
                }
            }
        }
    }

    return true;
}