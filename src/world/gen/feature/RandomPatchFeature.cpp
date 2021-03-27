#include "RandomPatchFeature.hpp"
#include "../blockplacer/BlockPlacer.hpp"
#include "../blockstateprovider/BlockStateProvider.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/material/Material.hpp"
#include "../../../block/material/Materials.hpp"

static bool hasWater(WorldReader& reader, const glm::ivec3& pos) {
    return reader.getData(pos).getMaterial() == Materials::WATER;
}

static bool hasNearByWater(WorldReader& reader, const glm::ivec3& pos) {
    return hasWater(reader, pos - glm::ivec3(1, 0, 0)) ||
           hasWater(reader, pos + glm::ivec3(1, 0, 0)) ||
           hasWater(reader, pos - glm::ivec3(0, 0, 1)) ||
           hasWater(reader, pos + glm::ivec3(0, 0, 1));
}

bool RandomPatchFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, glm::ivec3 pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BlockClusterFeatureConfig>(config);
    const auto blockstate = cfg.stateProvider->getBlockState(random, pos);
    const auto projected = cfg.project ? reader.getHeight(/*Heightmap.Type.WORLD_SURFACE_WG,*/ pos) : pos;

    int i = 0;

    for (int j = 0; j < cfg.tries; ++j) {
        const auto nearbypos = projected + glm::ivec3(
                random.nextInt(cfg.xspread + 1) - random.nextInt(cfg.xspread + 1),
                random.nextInt(cfg.yspread + 1) - random.nextInt(cfg.yspread + 1),
                random.nextInt(cfg.zspread + 1) - random.nextInt(cfg.zspread + 1)
        );
        const auto underPos = nearbypos - glm::ivec3(0, 1, 0);
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
//            cfg.blockPlacer->place(reader, nearbypos, blockstate, random);
            reader.setData(nearbypos, blockstate);
            ++i;
        }
    }

    return i > 0;
}
