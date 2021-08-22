#define _USE_MATH_DEFINES

#include "EndSpikeFeature.hpp"
#include <block/Blocks.hpp>
#include <block/PaneBlock.hpp>
#include <world/WorldGenRegion.hpp>
#include <cmath>

static auto createSpikes(WorldGenRegion &reader) -> std::vector<EndSpike> {
    auto random = Random::from(reader.getSeed());
    const auto seed = random.nextLong() & 0xFFFF;

    std::array ints{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//    Collections.shuffle(list, Random::from(seed));
    std::vector<EndSpike> spikes{};

    for (int i = 0; i < 10; ++i) {
        const auto centerX = static_cast<int>(std::floor(42.0 * std::cos(2.0 * (-M_PI + (M_PI / 10) * static_cast<double>(i)))));
        const auto centerZ = static_cast<int>(std::floor(42.0 * std::sin(2.0 * (-M_PI + (M_PI / 10) * static_cast<double>(i)))));
        const auto dz = ints[i];
        const auto radius = 2 + dz / 3;
        const auto height = 76 + dz * 3;
        const auto guarded = dz == 1 || dz == 2;

        spikes.emplace_back(EndSpike{centerX, centerZ, radius, height, guarded});
    }

    return spikes;
}

bool EndSpikeFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto &cfg = std::get<EndSpikeFeatureConfig>(config);

    if (cfg.spikes.empty()) {
        for (const auto& spike : createSpikes(reader)) {
            if (spike.doesStartInChunk(pos)) {
                placeSpike(reader, random, cfg, spike);
            }
        }
    } else {
        for (const auto& spike : cfg.spikes) {
            if (spike.doesStartInChunk(pos)) {
                placeSpike(reader, random, cfg, spike);
            }
        }
    }

    return true;
}

void EndSpikeFeature::placeSpike(WorldGenRegion &reader, Random &random, const EndSpikeFeatureConfig &config, const EndSpike &spike) {
    const auto radius = spike.radius;
    const auto min_pos = BlockPos::from(spike.centerX, 0, spike.centerZ);
    const auto max_pos = BlockPos::from(spike.centerX, spike.height, spike.centerZ);

    for (const auto pos : BlockPos::getAllInBox(min_pos.sub(radius, 0, radius), max_pos.add(radius, 10, radius))) {
        if (pos.y < spike.height && pos.distanceSq(glm::dvec3(min_pos.up(pos.y)), false) <= static_cast<double>(radius * radius + 1)) {
            setBlockState(reader, pos, Blocks::OBSIDIAN->getDefaultState());
        } else if (pos.y > 65) {
            setBlockState(reader, pos, Blocks::AIR->getDefaultState());
        }
    }

    if (spike.guarded) {
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dz = -2; dz <= 2; ++dz) {
                for (int dy = 0; dy <= 3; ++dy) {
                    const auto flag0 = std::abs(dx) == 2;
                    const auto flag1 = std::abs(dz) == 2;
                    const auto flag2 = dy == 3;
                    
                    if (flag0 || flag1 || flag2) {
                        const auto flag3 = dx == -2 || dx == 2 || flag2;
                        const auto flag4 = dz == -2 || dz == 2 || flag2;
                        const auto state = Blocks::IRON_BARS->getDefaultState()
                                                .set<PaneBlock::NORTH>(flag3 && dz != -2)
                                                .set<PaneBlock::SOUTH>(flag3 && dz != 2)
                                                .set<PaneBlock::WEST>(flag4 && dx != -2)
                                                .set<PaneBlock::EAST>(flag4 && dx != 2);
                                           
                        setBlockState(reader, max_pos.add(dx, dy, dz), state);
                    }
                }
            }
        }
    }

//    EnderCrystalEntity endercrystalentity = EntityType.END_CRYSTAL.create(reader.getWorld());
//    endercrystalentity.setBeamTarget(config.getCrystalBeamTarget());
//    endercrystalentity.setInvulnerable(config.isCrystalInvulnerable());
//    endercrystalentity.setLocationAndAngles((double) spike.centerX + 0.5D, (double) (spike.getHeight() + 1), (double) spike.centerZ + 0.5D, random.nextFloat() * 360.0F, 0.0F);
//    reader.addEntity(endercrystalentity);
    setBlockState(reader, max_pos, Blocks::BEDROCK->getDefaultState());
}