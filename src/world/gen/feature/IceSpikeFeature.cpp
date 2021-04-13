#include "IceSpikeFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Block.hpp"
#include "../../../block/Blocks.hpp"

bool IceSpikeFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    while (reader.isAirBlock(pos) && pos.y > 2) {
        pos.y -= 1;
    }

    if (!reader.getData(pos).isIn(Blocks::SNOW_BLOCK)) {
        return false;
    }

    pos.y += random.nextInt(4);

    const int i = random.nextInt(4) + 7;
    const int j = i / 4 + random.nextInt(2);
    if (j > 1 && random.nextInt(60) == 0) {
        pos = pos.up(10 + random.nextInt(30));
    }

    const auto PACKED_ICE = Blocks::PACKED_ICE->getDefaultState();

    for (int k = 0; k < i; ++k) {
        const float f = (1.0F - (float)k / (float)i) * (float)j;
        const int l = std::ceil(f);

        for(int i1 = -l; i1 <= l; ++i1) {
            float f1 = (float)std::abs(i1) - 0.25F;

            for(int j1 = -l; j1 <= l; ++j1) {
                float f2 = (float)std::abs(j1) - 0.25F;
                if ((i1 == 0 && j1 == 0 || !(f1 * f1 + f2 * f2 > f * f)) && (i1 != -l && i1 != l && j1 != -l && j1 != l || !(random.nextFloat() > 0.75F))) {
                    {
                        const auto state = reader.getData(pos + glm::ivec3(i1, k, j1));
                        const auto block = state.getBlock();
                        if (state.isAir() || isDirt(block) || block == Blocks::SNOW_BLOCK || block == Blocks::ICE) {
                            setBlockState(reader, pos + glm::ivec3(i1, k, j1), PACKED_ICE);
                        }
                    }

                    if (k != 0 && l > 1) {
                        const auto state = reader.getData(pos + glm::ivec3(i1, -k, j1));
                        const auto block = state.getBlock();
                        if (state.isAir() || isDirt(block) || block == Blocks::SNOW_BLOCK || block == Blocks::ICE) {
                            setBlockState(reader, pos + glm::ivec3(i1, -k, j1), PACKED_ICE);
                        }
                    }
                }
            }
        }
    }

    const int k1 = std::clamp(j - 1, 0, 1);
    for (int l1 = -k1; l1 <= k1; ++l1) {
        for (int i2 = -k1; i2 <= k1; ++i2) {
            BlockPos blockpos = pos + glm::ivec3(l1, -1, i2);
            int j2 = 50;
            if (std::abs(l1) == 1 && std::abs(i2) == 1) {
                j2 = random.nextInt(5);
            }

            while (blockpos.y > 50) {
                const auto state = reader.getData(blockpos);
                const auto block = state.getBlock();
                if (!state.isAir() &&
                    !isDirt(block) &&
                    block != Blocks::SNOW_BLOCK &&
                    block != Blocks::ICE &&
                    block != Blocks::PACKED_ICE) {
                    break;
                }

                setBlockState(reader, blockpos, PACKED_ICE);
                blockpos.y -= 1;
                --j2;
                if (j2 <= 0) {
                    blockpos.y -= random.nextInt(5) + 1;
                    j2 = random.nextInt(5);
                }
            }
        }
    }

    return true;
}
