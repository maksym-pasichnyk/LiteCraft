#include "CoralFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <tags/BlockTags.hpp>
#include <world/WorldGenRegion.hpp>

bool CoralFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
//    const auto i = random.nextInt(static_cast<size_t>(BlockTags::CORAL_BLOCKS.items.size()));
//    const auto state = (*std::next(BlockTags::CORAL_BLOCKS.items.begin(), i))->getDefaultState();
//    return generate(reader, random, pos, state);
    return false;
}

bool CoralFeature::generateCorals(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state) {
    const auto blockpos = pos.up();
    const auto blockstate = reader.getData(pos);
    if ((blockstate.is(Blocks::WATER) || blockstate.in(BlockTags::CORALS)) && reader.getData(blockpos).is(Blocks::WATER)) {
        reader.setData(pos, state/*, 3*/);
        if (random.nextFloat() < 0.25F) {
//            reader.setData(blockpos, BlockTags::CORALS.getRandomElement(random).getDefaultState(), 2);
        } else if (random.nextFloat() < 0.05F) {
            const auto age = random.nextInt(4) + 1;
            reader.setData(blockpos, Blocks::SEA_PICKLE->getDefaultState()/*.with<SeaPickleBlock.PICKLES>(age)*//*, 2*/);
        }

        for (const auto direction : DirectionUtil::Plane::HORIZONTAL) {
            if (random.nextFloat() < 0.2F) {
                const auto blockpos1 = pos.offset(direction);
                if (reader.getData(blockpos1).is(Blocks::WATER)) {
//                    const auto state = BlockTags::WALL_CORALS.getRandomElement(random).getDefaultState().with<DeadCoralWallFanBlock.FACING>(direction);
//                    reader.setData(blockpos1, state, 2);
                }
            }
        }

        return true;
    }
    return false;
}