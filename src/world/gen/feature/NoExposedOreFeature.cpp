#include "NoExposedOreFeature.hpp"
#include "world/WorldGenRegion.hpp"

bool NoExposedOreFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<OreFeatureConfig>(config);

    const int count = random.nextInt(cfg.size + 1);

    for (int i = 0; i < count; ++i) {
        const int range = std::min(i, 7);
        const int dx = getRandomOffset(random, range);
        const int dy = getRandomOffset(random, range);
        const int dz = getRandomOffset(random, range);
        const auto blockpos = pos.add(dx, dy, dz);

        if (RuleTestUtil::test(cfg.target, reader.getData(blockpos), random) && !isFacingAir(reader, blockpos)) {
            reader.setData(blockpos, cfg.state/*, 2*/);
        }
    }

    return true;
}

int NoExposedOreFeature::getRandomOffset(Random &random, int range) {
    const auto f0 = random.nextFloat();
    const auto f1 = random.nextFloat();
    return static_cast<int>(std::round((f0 - f1) * static_cast<float>(range)));
}

bool NoExposedOreFeature::isFacingAir(WorldGenRegion &reader, const BlockPos& pos) {
    for (auto direction : DirectionUtil::values()) {
        if (reader.getData(pos.offset(direction)).isAir()) {
            return true;
        }
    }
    return false;
}