#include "EndGatewayFeature.hpp"
#include <block/Block.hpp>
#include <block/Blocks.hpp>
#include <world/WorldGenRegion.hpp>

bool EndGatewayFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto &cfg = std::get<EndGatewayConfig>(config);

    for (const auto blockpos : BlockPos::getAllInBox(pos.sub(1, 2, 1), pos.add(1, 2, 1))) {
        const auto [flag0, flag1, flag2] = glm::equal(blockpos, pos);
        const auto flag3 = std::abs(blockpos.y - pos.y) == 2;
        if (flag0 && flag1 && flag2) {
            setBlockState(reader, blockpos, Blocks::END_GATEWAY->getDefaultState());
            if (auto exit = cfg.exit; exit.has_value()) {
//                TileEntity tileentity = reader.getTileEntity(blockpos);
//                if (tileentity instanceof EndGatewayTileEntity) {
//                    EndGatewayTileEntity endgatewaytileentity = (EndGatewayTileEntity) tileentity;
//                    endgatewaytileentity.setExitPortal(*exit, cfg.func_214701_c());
//                    tileentity.markDirty();
//                }
            }
        } else if (flag1) {
            setBlockState(reader, blockpos, Blocks::AIR->getDefaultState());
        } else if (flag3 && flag0 && flag2) {
            setBlockState(reader, blockpos, Blocks::BEDROCK->getDefaultState());
        } else if ((flag0 || flag2) && !flag3) {
            setBlockState(reader, blockpos, Blocks::BEDROCK->getDefaultState());
        } else {
            setBlockState(reader, blockpos, Blocks::AIR->getDefaultState());
        }
    }

    return true;
}