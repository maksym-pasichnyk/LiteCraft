#include "BonusChestFeature.hpp"
#include <range/v3/view.hpp>
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <util/math/ChunkPos.hpp>
#include <world/WorldGenRegion.hpp>

bool BonusChestFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    const auto chunkpos = ChunkPos::from(pos);
    
    const auto CHEST = Blocks::CHEST->getDefaultState();
    const auto TORCH = Blocks::TORCH->getDefaultState();

    for (auto x : ranges::views::iota(chunkpos.getStartX(), chunkpos.getEndX())) { // todo: shuffle
        for (auto z : ranges::views::iota(chunkpos.getStartZ(), chunkpos.getEndZ())) { // todo: shuffle
            const auto blockpos = reader.getHeight(HeightmapType::MOTION_BLOCKING_NO_LEAVES, BlockPos::from(x, 0, z));
            if (reader.isAirBlock(blockpos) /*|| reader.getData(blockpos).getCollisionShape(reader, blockpos).isEmpty()*/) {
                reader.setData(blockpos, CHEST/*, 2*/);
//                LockableLootTileEntity.setLootTable(reader, rand, blockpos, LootTables.CHESTS_SPAWN_BONUS_CHEST);

                for (const auto direction : DirectionUtil::Plane::HORIZONTAL) {
                    const auto blockpos1 = blockpos.offset(direction);
                    if (TORCH.isValidPosition(reader, blockpos1)) {
                        reader.setData(blockpos1, TORCH/*, 2*/);
                    }
                }
                return true;
            }
        }
    }
    return false;
}