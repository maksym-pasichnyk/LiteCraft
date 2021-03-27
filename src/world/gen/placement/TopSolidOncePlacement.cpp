#include "TopSolidOncePlacement.hpp"
#include "../../WorldGenRegion.hpp"

void TopSolidOncePlacement::forEach(WorldGenRegion &region, Random &random, const PlacementConfig &config, glm::ivec3 pos, const std::function<void(glm::ivec3)> &fn) {
    const int y = region.getHeight(/*Heightmap.Type.OCEAN_FLOOR_WG*/ pos.x, pos.z);
    if (y > 0) {
        fn(glm::ivec3(pos.x, y, pos.z));
    }
}
