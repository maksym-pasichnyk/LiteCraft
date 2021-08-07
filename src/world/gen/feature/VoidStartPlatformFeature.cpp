#include "VoidStartPlatformFeature.hpp"
#include <world/WorldGenRegion.hpp>
#include <block/Blocks.hpp>
#include <block/Block.hpp>

static int distance(int x0, int z0, int x1, int z1) {
    return std::max(std::abs(x0 - x1), std::abs(z0 - z1));
}

bool VoidStartPlatformFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto chunkpos = ChunkPos::from(pos);
    if (distance(chunkpos.x, chunkpos.z, VOID_SPAWN_CHUNK_POS.x, VOID_SPAWN_CHUNK_POS.z) > 1) {
        return true;
    }

    const auto STONE = Blocks::STONE->getDefaultState();
    const auto COBBLESTONE = Blocks::COBBLESTONE->getDefaultState();

    for (int z = chunkpos.getStartX(); z <= chunkpos.getEndZ(); ++z) {
        for (int x = chunkpos.getStartX(); x <= chunkpos.getEndX(); ++x) {
            if (distance(VOID_SPAWN_POS.x, VOID_SPAWN_POS.z, x, z) <= 16) {
                const auto blockpos = BlockPos::from(x, VOID_SPAWN_POS.y, z);
                reader.setData(blockpos, blockpos == VOID_SPAWN_POS ? COBBLESTONE : STONE/*, 2*/);
            }
        }
    }

    return true;
}
