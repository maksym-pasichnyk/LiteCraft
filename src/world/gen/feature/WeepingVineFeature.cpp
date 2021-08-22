#include "WeepingVineFeature.hpp"
#include <world/WorldGenRegion.hpp>
#include <block/Blocks.hpp>
#include <block/AbstractTopPlantBlock.hpp>

bool WeepingVineFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    if (reader.isAirBlock(pos)) {
        const auto state = reader.getData(pos.up());
        if (!state.is(Blocks::NETHERRACK) && !state.is(Blocks::NETHER_WART_BLOCK)) {
            return false;
        }
        generateWartBlocks(reader, random, pos);
        generateVines(reader, random, pos);
        return true;
    }
    return false;
}

void WeepingVineFeature::generateWartBlocks(WorldGenRegion &reader, Random& random, const BlockPos& start) {
    const auto NETHER_WART_BLOCK = Blocks::NETHER_WART_BLOCK->getDefaultState();

    reader.setData(start, NETHER_WART_BLOCK/*, 2*/);

    for (int i = 0; i < 200; ++i) {
        const auto x0 = random.nextInt(6);
        const auto x1 = random.nextInt(6);
        const auto y0 = random.nextInt(2);
        const auto y1 = random.nextInt(5);
        const auto z0 = random.nextInt(6);
        const auto z1 = random.nextInt(6);
        const auto pos = start.add(x0 - x1, y0 - y1, z0 - z1);

        if (reader.isAirBlock(pos)) {
            int count_of_blocks = 0;

            for (const auto direction : DirectionUtil::values()) {
                const auto state = reader.getData(pos.offset(direction));
                if (state.is(Blocks::NETHERRACK) || state.is(Blocks::NETHER_WART_BLOCK)) {
                    ++count_of_blocks;
                }

                if (count_of_blocks > 1) {
                    break;
                }
            }

            if (count_of_blocks == 1) {
                reader.setData(pos, NETHER_WART_BLOCK/*, 2*/);
            }
        }
    }
}

void WeepingVineFeature::generateVines(WorldGenRegion &reader, Random& random, const BlockPos& start) {
    for (int i = 0; i < 100; ++i) {
        const auto x0 = random.nextInt(8);
        const auto x1 = random.nextInt(8);
        const auto y0 = random.nextInt(2);
        const auto y1 = random.nextInt(7);
        const auto z0 = random.nextInt(8);
        const auto z1 = random.nextInt(8);
        const auto pos = start.add(x0 - x1, y0 - y1, z0 - z1);

        if (reader.isAirBlock(pos)) {
            const auto state = reader.getData(pos.up());
            if (state.is(Blocks::NETHERRACK) || state.is(Blocks::NETHER_WART_BLOCK)) {
                int height = random.nextInt(1, 8);
                if (random.nextInt(6) == 0) {
                    height *= 2;
                }

                if (random.nextInt(5) == 0) {
                    height = 1;
                }

                placeVines(reader, random, pos, height, 17, 25);
            }
        }
    }
}

void WeepingVineFeature::placeVines(WorldGenRegion &reader, Random &random, const BlockPos &start, int height, int min_age, int max_age) {
    auto pos = start;

    const auto WEEPING_VINES = Blocks::WEEPING_VINES->getDefaultState();
    const auto WEEPING_VINES_PLANT = Blocks::WEEPING_VINES_PLANT->getDefaultState();

    for (int i = 0; i <= height; ++i) {
        if (reader.isAirBlock(pos)) {
            if (i == height || !reader.isAirBlock(pos.down())) {
                const auto age = random.nextInt(min_age, max_age);
                reader.setData(pos, WEEPING_VINES.set<AbstractTopPlantBlock::AGE>(age)/*, 2*/);
                break;
            }

            reader.setData(pos, WEEPING_VINES_PLANT/*, 2*/);
        }
        pos = pos.down();
    }
}
