#include "OceanRuinStructure.hpp"
#include "OceanRuinStart.hpp"

StructureStart *OceanRuinStructure::createStart(int x, int z, const BoundingBox &bounds, int refCount, int64_t seed) {
    return new Start(this, x, z, bounds, refCount, seed);
}