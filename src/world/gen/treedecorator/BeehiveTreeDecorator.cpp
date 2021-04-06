#include "BeehiveTreeDecorator.hpp"
#include "../../../util/Random.hpp"

void BeehiveTreeDecorator::decorate(WorldGenRegion &reader, Random &random, std::vector<BlockPos> &positions1, std::vector<BlockPos> &positions2, std::set<BlockPos> &positions3, BoundingBox &boundingBox) {
    if (random.nextFloat() >= probability) {
        return;
    }
//    Direction direction = BeehiveBlock.getGenerationDirection(random);
//    int i = !positions2.isEmpty() ? Math.max(positions2.get(0).getY() - 1, positions1.get(0).getY()) : Math.min(positions1.get(0).getY() + 1 + random.nextInt(3), positions1.get(positions1.size() - 1).getY());
//    List<BlockPos> list = positions1.stream().filter((pos) -> pos.getY() == i).collect(Collectors.toList());
//    if (!list.isEmpty()) {
//        BlockPos blockpos = list.get(random.nextInt(list.size()));
//        BlockPos blockpos1 = blockpos.offset(direction);
//        if (Feature.isAirAt(reader, blockpos1) && Feature.isAirAt(reader, blockpos1.offset(Direction.SOUTH))) {
//            BlockState blockstate = Blocks.BEE_NEST.getDefaultState().with(BeehiveBlock.FACING, Direction.SOUTH);
//            this.placeBlock(reader, blockpos1, blockstate, positions3, boundingBox);
//            TileEntity tileentity = reader.getTileEntity(blockpos1);
//            if (tileentity instanceof BeehiveTileEntity) {
//                BeehiveTileEntity beehivetileentity = (BeehiveTileEntity)tileentity;
//                int j = 2 + random.nextInt(2);
//
//                for(int k = 0; k < j; ++k) {
//                    BeeEntity beeentity = new BeeEntity(EntityType.BEE, reader.getWorld());
//                    beehivetileentity.tryEnterHive(beeentity, false, random.nextInt(599));
//                }
//            }
//
//        }
//    }
}
