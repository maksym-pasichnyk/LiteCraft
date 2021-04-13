#include "AbstractSphereReplaceFeature.hpp"
#include "../../WorldGenRegion.hpp"

bool AbstractSphereReplaceFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<SphereReplaceConfig>(config);

    bool flag = false;

    const int radius = cfg.radius.getCount(random);
    for (int x = pos.x - radius; x <= pos.x + radius; ++x) {
        for (int z = pos.z - radius; z <= pos.z + radius; ++z) {
            const int dx = x - pos.x;
            const int dz = z - pos.z;
            if (dx * dx + dz * dz <= radius * radius) {
                for (int y = pos.y - cfg.half_height; y <= pos.y + cfg.half_height; ++y) {
                    const auto block = reader.getData(x, y, z).getBlock();
                    for (const auto target : cfg.targets) {
                        if (target.isIn(block)) {
                            reader.setData(x, y, z, cfg.state/*, 2*/);
                            flag = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    return flag;
}
