#include "VillageStructure.hpp"
#include "VillageStart.hpp"

StructureStart *VillageStructure::createStart(int x, int z, const BoundingBox &bounds, int refCount, int64_t seed) {
    return new Start(this, x, z, bounds, refCount, seed);
}