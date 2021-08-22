#pragma once

#include "AbstractTrunkPlacer.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

struct FancyTrunkPlacer : AbstractTrunkPlacer {
    struct Foliage {
        FoliagePlacer::Foliage foliage;
        int y;

        Foliage(const BlockPos& pos, int y)
            : foliage(pos, 0, false), y(y) {
        }
    };

    static bool func_236885_a_(int p_236885_1_, int p_236885_2_) {
        return static_cast<double>(p_236885_2_) >= static_cast<double>(p_236885_1_) * 0.2;
    }

    static int lMaxNorm(const BlockPos& pos) {
        return glm::max(std::abs(pos.x), std::max(std::abs(pos.y), std::abs(pos.z)));
    }

    using AbstractTrunkPlacer::AbstractTrunkPlacer;

    float func_236890_b_(int p_236890_1_, int p_236890_2_) {
        if (static_cast<float>(p_236890_2_) < static_cast<float>(p_236890_1_) * 0.3F) {
            return -1.0F;
        }
        const float f = static_cast<float>(p_236890_1_) / 2.0F;
        const float f1 = f - static_cast<float>(p_236890_2_);
        float f2 = std::sqrt(f * f - f1 * f1);
        if (f1 == 0.0F) {
            f2 = f;
        } else if (std::abs(f1) >= f) {
            return 0.0F;
        }

        return f2 * 0.5F;
    }

    void func_236886_a_(WorldGenRegion &reader, Random& random, int p_236886_3_, const BlockPos& pos, const std::list<Foliage>& foliages, std::set<BlockPos>& set1, BoundingBox& boundingBox, const BaseTreeFeatureConfig &config) {
        for (const auto& [foliage, y] : foliages) {
            const auto blockpos = BlockPos::from(pos.x, y, pos.z);
            if ((blockpos != foliage.position) && func_236885_a_(p_236886_3_, y - pos.y)) {
                placeTrunk(reader, random, blockpos, foliage.position, true, set1, boundingBox, config);
            }
        }
    }

    std::list<FoliagePlacer::Foliage> getFoliages(WorldGenRegion &reader, Random &random, int height, const BlockPos &pos, std::set<BlockPos> &set1, BoundingBox &boundingBox, const BaseTreeFeatureConfig &config) override;
    bool placeTrunk(WorldGenRegion &reader, Random& random, const BlockPos& pos1, const BlockPos& pos2, bool needPlace, std::set<BlockPos>& set1, BoundingBox& boundingBox, const BaseTreeFeatureConfig& config);
};