#include "FillLayerFeature.hpp"
#include "world/WorldGenRegion.hpp"

bool FillLayerFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<FillLayerConfig>(config);

    const int ypos = cfg.height;

    for (int dx = 0; dx < 16; ++dx) {
        for (int dz = 0; dz < 16; ++dz) {
            const int xpos = pos.x + dx;
            const int zpos = pos.z + dz;
            if (reader.getData(xpos, ypos, zpos).isAir()) {
                reader.setData(xpos, ypos, zpos, cfg.state/*, 2*/);
            }
        }
    }
    return false;
}