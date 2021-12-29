#include "TwistingVineFeature.hpp"
#include <world/WorldGenRegion.hpp>
#include <block/Blocks.hpp>
#include <block/AbstractTopPlantBlock.hpp>

bool TwistingVineFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    return tryGenerateVines(reader, random, pos, 8, 4, 8);
}

bool TwistingVineFeature::canGenerateVines(WorldGenRegion &reader, const BlockPos &pos) {
    if (reader.isAirBlock(pos)) {
        const auto state = reader.getData(pos.down());
        return state.is(Blocks::NETHERRACK) || state.is(Blocks::WARPED_NYLIUM) || state.is(Blocks::WARPED_WART_BLOCK);
    }
    return false;
}

bool TwistingVineFeature::tryGenerateVines(WorldGenRegion &reader, Random &random, const BlockPos &pos, int xz_range, int y_range, int max_height) {
    if (canGenerateVines(reader, pos)) {
        generateVines(reader, random, pos, xz_range, y_range, max_height);
        return true;
    }
    return false;
}

void TwistingVineFeature::generateVines(WorldGenRegion &reader, Random &random, const BlockPos &pos, int xz_range, int y_range, int max_height) {
    for (int i = 0; i < xz_range * xz_range; ++i) {
        const auto dx = random.nextInt(-xz_range, xz_range);
        const auto dy = random.nextInt(-y_range, y_range);
        const auto dz = random.nextInt(-xz_range, xz_range);

        const auto start = getLowestPosition(reader, pos.add(dx, dy, dz));
        if (start.has_value() && canGenerateVines(reader, *start)) {
            int height = random.nextInt(1, max_height);
            if (random.nextInt(6) == 0) {
                height *= 2;
            }

            if (random.nextInt(5) == 0) {
                height = 1;
            }

            placeVines(reader, random, *start, height, 17, 25);
        }
    }
}

auto TwistingVineFeature::getLowestPosition(WorldGenRegion &reader, const BlockPos& pos) -> tl::optional<BlockPos> {
    for (auto ret = pos.down(); ret.y >= 0; ret = ret.down()) {
        if (!reader.isAirBlock(ret)) {
            return ret.up();
        }
    }
    return tl::nullopt;
}

void TwistingVineFeature::placeVines(WorldGenRegion &reader, Random& random, const BlockPos &start, int height, int min_age, int max_age) {
    auto pos = start;
    
    const auto TWISTING_VINES = Blocks::TWISTING_VINES->getDefaultState();
    const auto TWISTING_VINES_PLANT = Blocks::TWISTING_VINES_PLANT->getDefaultState();

    for (int i = 1; i <= height; ++i) {
        if (reader.isAirBlock(pos)) {
            if (i == height || !reader.isAirBlock(pos.up())) {
                const auto age = random.nextInt(min_age, max_age);

                reader.setData(pos, TWISTING_VINES.set<AbstractTopPlantBlock::AGE>(age)/*, 2*/);
                break;
            }

            reader.setData(pos, TWISTING_VINES_PLANT/*, 2*/);
        }

        pos = pos.up();
    }
}