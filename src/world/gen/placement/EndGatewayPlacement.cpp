#include "EndGatewayPlacement.hpp"
#include "../../WorldGenRegion.hpp"

void EndGatewayPlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) {
    if (random.nextInt(700) == 0) {
        const int x = random.nextInt(16) + pos.x;
        const int z = random.nextInt(16) + pos.z;
        const int height = region.getHeight(HeightmapType::MOTION_BLOCKING, x, z);
        if (height > 0) {
            const int y = height + 3 + random.nextInt(7);
            fn(glm::ivec3 (x, y, z));
        }
    }
}
