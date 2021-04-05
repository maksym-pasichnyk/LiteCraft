#include "FoliagePlacer.hpp"
#include "../feature/TreeFeature.hpp"
#include "../../WorldGenRegion.hpp"
#include "../../gen/blockstateprovider/BlockStateProvider.hpp"
#include "../../../util/math/BoundingBox.hpp"
#include "../../../util/math/utility.hpp"

void FoliagePlacer::func_236753_a_(WorldGenRegion &reader, Random &random, const BaseTreeFeatureConfig &config, const glm::ivec3 &p_236753_4_, int p_236753_5_, std::set<glm::ivec3> &set1, int p_236753_7_, bool p_236753_8_, BoundingBox &boundingBox) {
    const int i = p_236753_8_ ? 1 : 0;

    for(int j = -p_236753_5_; j <= p_236753_5_ + i; ++j) {
        for(int k = -p_236753_5_; k <= p_236753_5_ + i; ++k) {
            if (!func_230375_b_(random, j, p_236753_7_, k, p_236753_5_, p_236753_8_)) {
                const auto blockpos = p_236753_4_ + glm::ivec3(j, p_236753_7_, k);
                if (TreeFeature::isReplaceableAt(reader, blockpos)) {
                    reader.setData(blockpos, config.leavesProvider->getBlockState(random, blockpos)/*, 19*/);
                    boundingBox.expandTo(BoundingBox::from(blockpos, blockpos));
                    set1.emplace(blockpos);
                }
            }
        }
    }

}
