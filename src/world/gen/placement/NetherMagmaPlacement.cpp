#include "NetherMagmaPlacement.hpp"
#include "../../WorldGenRegion.hpp"

void NetherMagmaPlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) {
    const int seaLevel = 63;
    const int y = seaLevel - 5 + random.nextInt(10);
    fn(glm::ivec3(pos.x, y, pos.z));
}
