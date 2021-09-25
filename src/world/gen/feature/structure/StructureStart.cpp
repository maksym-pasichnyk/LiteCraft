#include "StructureStart.hpp"
#include "Structure.hpp"

void StructureStart::generate(WorldGenRegion &region, StructureManager &structureManager, ChunkGenerator &generator, Random &random, const BoundingBox &bb, const ChunkPos &chunkPos) {
    if (components.empty()) {
        return;
    }

    const auto& cbb = components[0]->bounds;
    const auto pivot = cbb.getPivotCenter();
    const auto pos = BlockPos(pivot.x, cbb.minY, pivot.z);

    for (auto piece : components) {
        if (!piece->getBoundingBox().intersectsWith(bb)) {
            continue;
        }
        piece->addComponentParts(region, structureManager, generator, random, bb, chunkPos, pos);
    }
}