#include "BasaltPillarFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool BasaltPillarFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    if (!reader.isAirBlock(pos) || reader.isAirBlock(pos.up())) {
        return false;
    }

    auto lowest = pos;
    auto flag0 = true;
    auto flag1 = true;
    auto flag2 = true;
    auto flag3 = true;

    while (reader.isAirBlock(lowest)) {
    	if (lowest.y <= 0) {
            return true;
        }

        reader.setData(lowest, Blocks::BASALT->getDefaultState()/*, 2*/);
        flag0 = flag0 && placeBasaltRandom10(reader, random, lowest.north());
        flag1 = flag1 && placeBasaltRandom10(reader, random, lowest.south());
        flag2 = flag2 && placeBasaltRandom10(reader, random, lowest.west());
        flag3 = flag3 && placeBasaltRandom10(reader, random, lowest.east());
        lowest = lowest.down();
    }

    placeBasalt(reader, random, lowest.up().north());
    placeBasalt(reader, random, lowest.up().south());
    placeBasalt(reader, random, lowest.up().west());
    placeBasalt(reader, random, lowest.up().east());

    for (int dx = -3; dx < 4; ++dx) {
        for (int dz = -3; dz < 4; ++dz) {
            const auto sq = std::abs(dx) * std::abs(dz);
            if (random.nextInt(10) < 10 - sq) {
                auto air_pos = lowest.add(dx, 0, dz);
                for (int i = 0; i < 3 && reader.isAirBlock(air_pos.down()); ++i) {
                	air_pos = air_pos.down();
                }
                if (!reader.isAirBlock(air_pos.down())) {
                    reader.setData(air_pos, Blocks::BASALT->getDefaultState()/*, 2*/);
                }
            }
        }
    }

    return true;
}

void BasaltPillarFeature::placeBasalt(WorldGenRegion &reader, Random &random, const BlockPos &pos) {
	if (random.nextBoolean()) {
		reader.setData(pos, Blocks::BASALT->getDefaultState()/*, 2*/);
	}
}

bool BasaltPillarFeature::placeBasaltRandom10(WorldGenRegion &reader, Random &random, const BlockPos &pos) {
	if (random.nextInt(10) != 0) {
		reader.setData(pos, Blocks::BASALT->getDefaultState()/*, 2*/);
		return true;
	}
	return false;
}
