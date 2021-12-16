#include "RandomPatchFeature.hpp"
#include "../../../block/material/Materials.hpp"
#include "../../WorldGenRegion.hpp"
#include "../blockplacer/BlockPlacer.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "block/material/BlockMaterial.hpp"

static bool hasWater(WorldReader& reader, const BlockPos& pos) {
    return reader.getData(pos).getMaterial() == Materials::WATER;
}

static bool hasNearByWater(WorldReader& reader, const BlockPos& pos) {
    return hasWater(reader, pos.west()) ||
           hasWater(reader, pos.east()) ||
           hasWater(reader, pos.north()) ||
           hasWater(reader, pos.south());
}

bool RandomPatchFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BlockClusterFeatureConfig>(config);
    const auto blockstate = cfg.stateProvider->getBlockState(random, pos);
    const auto projected = cfg.project ? reader.getHeight(HeightmapType::WORLD_SURFACE_WG, pos) : pos;

    int i = 0;
    for (int j = 0; j < cfg.tries; ++j) {
        const auto x0 = random.nextInt(cfg.xspread + 1);
        const auto x1 = random.nextInt(cfg.xspread + 1);
        const auto y0 = random.nextInt(cfg.yspread + 1);
        const auto y1 = random.nextInt(cfg.yspread + 1);
        const auto z0 = random.nextInt(cfg.zspread + 1);
        const auto z1 = random.nextInt(cfg.zspread + 1);
        const auto nearbypos = projected.add(x0 - x1, y0 - y1,  z0 - z1);
        const auto underPos = nearbypos.down();
        const auto underBlock = reader.getData(underPos);
        if (reader.isAirBlock(nearbypos) || cfg.can_replace && reader.getData(nearbypos).getMaterial()->isReplaceable) {
            if (!blockstate.isValidPosition(reader, nearbypos)) {
                continue;
            }
            if (!cfg.whitelist.empty() && !cfg.whitelist.contains(underBlock.getBlock())) {
                continue;
            }
            if (cfg.blacklist.contains(underBlock)) {
                continue;
            }
            if (cfg.requiresWater && !hasNearByWater(reader, underPos)) {
                continue;
            }
            cfg.blockPlacer->place(reader, nearbypos, blockstate, random);
            ++i;
        }
    }

    return i > 0;
}
