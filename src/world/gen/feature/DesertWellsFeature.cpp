#include "DesertWellsFeature.hpp"

#include <world/WorldGenRegion.hpp>
#include <block/States.hpp>
#include <block/Blocks.hpp>
#include <block/Block.hpp>

bool DesertWellsFeature::generate(WorldGenRegion& reader, ChunkGenerator& generator, Random& random, BlockPos pos, const FeatureConfig& config) {
    pos = pos.up();
    while (reader.isAirBlock(pos) && pos.y > 2) {
        pos = pos.down();
    }

    if (!reader.getData(pos).in(BlockTags::SAND)) {
        return false;
    }

    for (int dx = -2; dx <= 2; ++dx) {
        for (int dz = -2; dz <= 2; ++dz) {
            if (reader.isAirBlock(pos.add(dx, -1, dz)) && reader.isAirBlock(pos.add(dx, -2, dz))) {
                return false;
            }
        }
    }

    for (int dy = -1; dy <= 0; ++dy) {
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dz = -2; dz <= 2; ++dz) {
                reader.setData(pos.add(dx, dy, dz), States::SANDSTONE /*, 2*/);
            }
        }
    }

    reader.setData(pos, States::WATER/*, 2*/);

    for (Direction direction : DirectionUtil::Plane::HORIZONTAL) {
        reader.setData(pos.offset(direction), States::WATER/*, 2*/);
    }

    for (int dx = -2; dx <= 2; ++dx) {
        for (int dz = -2; dz <= 2; ++dz) {
            if (dx == -2 || dx == 2 || dz == -2 || dz == 2) {
                reader.setData(pos.add(dx, 1, dz), States::SANDSTONE /*, 2*/);
            }
        }
    }

    reader.setData(pos.add(2, 1, 0), States::SANDSTONE_SLAB /*, 2*/);
    reader.setData(pos.add(-2, 1, 0), States::SANDSTONE_SLAB /*, 2*/);
    reader.setData(pos.add(0, 1, 2), States::SANDSTONE_SLAB /*, 2*/);
    reader.setData(pos.add(0, 1, -2), States::SANDSTONE_SLAB /*, 2*/);

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dz = -1; dz <= 1; ++dz) {
            reader.setData(pos.add(dx, 4, dz), dx == 0 && dz == 0 ? States::SANDSTONE : States::SANDSTONE_SLAB /*, 2*/);
        }
    }

    for (int dy = 1; dy <= 3; ++dy) {
        reader.setData(pos.add(-1, dy, -1), States::SANDSTONE /*, 2*/);
        reader.setData(pos.add(-1, dy, 1), States::SANDSTONE /*, 2*/);
        reader.setData(pos.add(1, dy, -1), States::SANDSTONE /*, 2*/);
        reader.setData(pos.add(1, dy, 1), States::SANDSTONE /*, 2*/);
    }

    return true;
}
