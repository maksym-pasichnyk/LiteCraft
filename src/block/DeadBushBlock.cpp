#include "DeadBushBlock.hpp"
#include "Blocks.hpp"

bool DeadBushBlock::isValidGround(const BlockData &data, WorldReader &reader, const BlockPos &pos) {
    const auto block = data.getBlock();
    return block == Blocks::SAND
           || block == Blocks::RED_SAND
           || block == Blocks::TERRACOTTA
           || block == Blocks::WHITE_TERRACOTTA
           || block == Blocks::ORANGE_TERRACOTTA
           || block == Blocks::MAGENTA_TERRACOTTA
           || block == Blocks::LIGHT_BLUE_TERRACOTTA
           || block == Blocks::YELLOW_TERRACOTTA
           || block == Blocks::LIME_TERRACOTTA
           || block == Blocks::PINK_TERRACOTTA
           || block == Blocks::GRAY_TERRACOTTA
           || block == Blocks::LIGHT_GRAY_TERRACOTTA
           || block == Blocks::CYAN_TERRACOTTA
           || block == Blocks::PURPLE_TERRACOTTA
           || block == Blocks::BLUE_TERRACOTTA
           || block == Blocks::BROWN_TERRACOTTA
           || block == Blocks::GREEN_TERRACOTTA
           || block == Blocks::RED_TERRACOTTA
           || block == Blocks::BLACK_TERRACOTTA
           || block == Blocks::DIRT
           || block == Blocks::COARSE_DIRT
           || block == Blocks::PODZOL;
}
