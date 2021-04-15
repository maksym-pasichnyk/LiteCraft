#include "StructureStart.hpp"

void StructureStart::generate(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos) {
//    synchronized(this.components) {
        if (!components.empty()) {
            const auto& mutableboundingbox = components[0]->bounds;
            const auto pivot = mutableboundingbox.getPivotCenter();
            const auto pos = BlockPos(pivot.x, mutableboundingbox.minY, pivot.z);

            auto it = components.begin();
            while (it != components.end()) {
                auto piece = *it;
                if (piece->getBoundingBox().intersectsWith(bb) && !piece->addComponentParts(region, structureManager, generator, random, bb, chunkPos, pos)) {
                    delete piece;
                    it = components.erase(it);
                } else {
                    it += 1;
                }
            }

            recalculateStructureSize();
        }
//    }
}
