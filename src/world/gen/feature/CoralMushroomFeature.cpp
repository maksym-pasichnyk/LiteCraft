#include "CoralMushroomFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool CoralMushroomFeature::generate(WorldGenRegion& reader, Random& random, const BlockPos& pos, BlockData state) {
    const auto max_y = random.nextInt(3) + 3;
    const auto max_x = random.nextInt(3) + 3;
    const auto max_z = random.nextInt(3) + 3;
    const auto height = random.nextInt(3) + 1;

    for (int dx = 0; dx <= max_x; ++dx) {
        for (int dy = 0; dy <= max_y; ++dy) {
            for (int dz = 0; dz <= max_z; ++dz) {
                if ((dx == 0 || dx == max_x) && (dy == 0 || dy == max_y)) {
                    continue;
                }
                if ((dz == 0 || dz == max_z) && (dy == 0 || dy == max_y)) {
                    continue;
                }
                if ((dx == 0 || dx == max_x) && (dz == 0 || dz == max_z)) {
                    continue;
                }
                if (dx != 0 && dx != max_x && dy != 0 && dy != max_y && dz != 0 && dz != max_z) {
                    continue;
                }
                if (random.nextFloat() < 0.1F) {
                    continue;
                }
                generateCorals(reader, random, pos.add(dx, dy, dz).down(height), state);
            }
        }
    }

    return true;
}