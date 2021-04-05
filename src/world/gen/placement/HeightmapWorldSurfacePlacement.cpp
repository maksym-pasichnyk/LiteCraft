#include "HeightmapWorldSurfacePlacement.hpp"
#include "../../WorldGenRegion.hpp"

void HeightmapWorldSurfacePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) {
    const int y = region.getHeight(HeightmapType::WORLD_SURFACE_WG, pos.x, pos.z);
    if (y > 0) {
        fn(glm::ivec3(pos.x, y, pos.z));
    }
}
