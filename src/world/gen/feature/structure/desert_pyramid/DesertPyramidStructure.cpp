#include "DesertPyramidStructure.hpp"
#include "DesertPyramidStart.hpp"

StructureStart *DesertPyramidStructure::createStart(int x, int z, const BoundingBox &bounds, int refCount, int64_t seed) {
    return new Start(this, x, z, bounds, refCount, seed);
}