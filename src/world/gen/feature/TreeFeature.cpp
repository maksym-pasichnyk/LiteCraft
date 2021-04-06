#include "TreeFeature.hpp"
#include "FeatureSizeType.hpp"
#include "../trunkplacer/AbstractTrunkPlacer.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../../block/Blocks.hpp"
#include "../../../block/material/Materials.hpp"
#include "../../../util/math/BoundingBox.hpp"

bool TreeFeature::isVineAt(WorldReader &reader, const BlockPos &pos) {
    return reader.getData(pos).isIn(Blocks::VINE);
}

bool TreeFeature::isWaterAt(WorldReader &reader, const BlockPos &pos) {
    return reader.getData(pos).isIn(Blocks::WATER);
}

bool TreeFeature::isTallPlantAt(WorldReader &reader, const BlockPos &pos) {
    return reader.getData(pos).getMaterial() == Materials::TALL_PLANTS;
}

bool TreeFeature::isAirOrLeavesAt(WorldReader &reader, const BlockPos &pos) {
    const auto state = reader.getData(pos);
    return state.isAir() || state.isIn(BlockTags::LEAVES);
}

bool TreeFeature::isReplaceableAt(WorldReader& reader, const BlockPos& pos) {
    return isAirOrLeavesAt(reader, pos) || isTallPlantAt(reader, pos) || isWaterAt(reader, pos);
}

bool TreeFeature::isDirtOrFarmlandAt(WorldReader& reader, const BlockPos& pos) {
    auto block = reader.getData(pos).getBlock();
    return isDirt(block) || block == Blocks::FARMLAND;
}

bool TreeFeature::isReplaceableOrLogAt(WorldReader& reader, const BlockPos& pos) {
    return isReplaceableAt(reader, pos) || reader.getData(pos).isIn(BlockTags::LOGS);
}

void TreeFeature::placeBlockState(WorldWriter &writer, const BlockPos &pos, BlockData state) {
    writer.setData(pos, state/*, 19*/);
}

bool TreeFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<BaseTreeFeatureConfig>(config);
    std::set<BlockPos> set{};
    std::set<BlockPos> set1{};
    std::set<BlockPos> set2{};
    auto mutableboundingbox = BoundingBox::getNewBoundingBox();
    const bool flag = place(reader, random, pos, set, set1, mutableboundingbox, cfg);
    if (mutableboundingbox.minX <= mutableboundingbox.maxX && flag && !set.empty()) {
        if (!cfg.decorators.empty()) {
            std::list<BlockPos> list{set.begin(), set.end()};
            std::list<BlockPos> list1{set1.begin(), set1.end()};
//            list.sort(Comparator.comparingInt(Vector3i::getY));
//            list1.sort(Comparator.comparingInt(Vector3i::getY));
//            cfg.decorators.forEach((decorator) -> decorator.decorate(reader, random, list, list1, set2, mutableboundingbox));
        }

//        VoxelShapePart voxelshapepart = this.func_236403_a_(reader, mutableboundingbox, set, set2);
//        Template.updatePostPlacement(reader, 3, voxelshapepart, mutableboundingbox.minX, mutableboundingbox.minY, mutableboundingbox.minZ);
        return true;
    }
    return false;
}

bool TreeFeature::place(WorldGenRegion &reader, Random &random, const BlockPos &pos, std::set<BlockPos> &set1, std::set<BlockPos> &set2, BoundingBox &boundingBoxIn, const BaseTreeFeatureConfig &config) {
    const int trunkHeight = config.trunkPlacer->getRandomHeight(random);
    const int j = config.foliagePlacer->getHeight(random, trunkHeight, config);
    const int k = trunkHeight - j;
    const int l = config.foliagePlacer->getRadius(random, k);
    BlockPos blockpos = pos;
    if (!config.forcePlacement) {
        const int i1 = reader.getHeight(HeightmapType::OCEAN_FLOOR, pos).y;
        const int j1 = reader.getHeight(HeightmapType::WORLD_SURFACE, pos).y;
        if (j1 - i1 > config.maxWaterDepth) {
            return false;
        }

        int k1;
        if (config.heightmap == HeightmapType::OCEAN_FLOOR) {
            k1 = i1;
        } else if (config.heightmap == HeightmapType::WORLD_SURFACE) {
            k1 = j1;
        } else {
            k1 = reader.getHeight(config.heightmap, pos).y;
        }

        blockpos.y = k1;
    }

    if (blockpos.y >= 1 && blockpos.y + trunkHeight + 1 <= 256) {
        if (!isDirtOrFarmlandAt(reader, blockpos.down())) {
            return false;
        }
        const auto min_clipped_height = config.minimumSize.min_clipped_height();
        const int l1 = func_241521_a_(reader, trunkHeight, blockpos, config);
        if (l1 >= trunkHeight || min_clipped_height.has_value() && l1 >= *min_clipped_height) {
            for (const auto& p_236407_8_ : config.trunkPlacer->getFoliages(reader, random, l1, blockpos, set1, boundingBoxIn, config)) {
                config.foliagePlacer->func_236752_a_(reader, random, config, l1, p_236407_8_, j, l, set2, boundingBoxIn);
            }
            return true;
        }
    }
    return false;
}

int TreeFeature::func_241521_a_(WorldGenRegion &reader, int p_241521_2_, const BlockPos &pos, const BaseTreeFeatureConfig &config) {
    for (int i = 0; i <= p_241521_2_ + 1; ++i) {
        const int j = config.minimumSize.func_230369_a_(p_241521_2_, i);

        for (int k = -j; k <= j; ++k) {
            for (int l = -j; l <= j; ++l) {
                const auto blockpos = pos + BlockPos(k, i, l);
                if (!isReplaceableOrLogAt(reader, blockpos) || !config.ignoreVines && isVineAt(reader, blockpos)) {
                    return i - 2;
                }
            }
        }
    }

    return p_241521_2_;
}