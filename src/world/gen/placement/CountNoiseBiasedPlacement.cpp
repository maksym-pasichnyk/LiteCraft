#include "CountNoiseBiasedPlacement.hpp"
#include "../../biome/Biome.hpp"

void CountNoiseBiasedPlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const auto& cfg = std::get<TopSolidWithNoiseConfig>(config);
    const double noise = Biome::INFO_NOISE.noiseAt(static_cast<double>(pos.x) / cfg.noiseFactor, static_cast<double>(pos.z) / cfg.noiseFactor, false);
    const int count = static_cast<int>(std::ceil((noise + cfg.noiseOffset) * static_cast<double>(cfg.noiseToCountRatio)));
    for (int i = 0; i < count; i++) {
        fn(pos);
    }
}
