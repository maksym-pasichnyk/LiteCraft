#include "CountNoisePlacement.hpp"
#include "../../biome/Biome.hpp"

void CountNoisePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, BlockPos pos, const std::function<void(BlockPos)> &fn) {
    const auto& cfg = std::get<NoiseDependantConfig>(config);
    const double noise = Biome::INFO_NOISE.noiseAt(static_cast<double>(pos.x) / 200.0, static_cast<double>(pos.z) / 200.0, false);
    const int count = noise < cfg.noiseLevel ? cfg.belowNoise : cfg.aboveNoise;

    for (int i = 0; i < count; i++) {
        fn(pos);
    }
}
