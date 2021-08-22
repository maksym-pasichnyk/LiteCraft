#include "AcaciaFoliagePlacer.hpp"

int AcaciaFoliagePlacer::getHeight(Random &random, int heightIn, const BaseTreeFeatureConfig& config) {
    return 0;
}

bool AcaciaFoliagePlacer::func_230373_a_(Random &random, int p_230373_2_, int p_230373_3_, int p_230373_4_, int radius, bool p_230373_6_) {
    if (p_230373_3_ == 0) {
        return (p_230373_2_ > 1 || p_230373_4_ > 1) && p_230373_2_ != 0 && p_230373_4_ != 0;
    } else {
        return p_230373_2_ == radius && p_230373_4_ == radius && radius > 0;
    };
}

void AcaciaFoliagePlacer::func_230372_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, int p_230372_4_, const FoliagePlacer::Foliage &foliage, int p_230372_6_, int p_230372_7_, std::set<BlockPos> &set1, int p_230372_9_, BoundingBox &boundingBox) {
    const bool flag = foliage.persistence;
    const auto blockpos = foliage.position.up(p_230372_9_);
    placeLeaves(reader, random, config, blockpos, p_230372_7_ + foliage.distance, set1, -1 - p_230372_6_, flag, boundingBox);
    placeLeaves(reader, random, config, blockpos, p_230372_7_ - 1, set1, -p_230372_6_, flag, boundingBox);
    placeLeaves(reader, random, config, blockpos, p_230372_7_ + foliage.distance - 1, set1, 0, flag, boundingBox);
}
