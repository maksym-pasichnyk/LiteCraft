#include "SpringFeature.hpp"
#include "world/WorldGenRegion.hpp"

bool SpringFeature::generate(WorldGenRegion &reader, ChunkGenerator &generator, Random &random, BlockPos pos, const FeatureConfig &config) {
    const auto& cfg = std::get<LiquidsConfig>(config);
    
    if (!cfg.acceptedBlocks.contains(reader.getData(pos.up()).getBlock())) {
        return false;
    }
    if (cfg.needsBlockBelow && !cfg.acceptedBlocks.contains(reader.getData(pos.down()).getBlock())) {
        return false;
    }
    const auto state = reader.getData(pos);
    if (!state.isAir() && !cfg.acceptedBlocks.contains(state.getBlock())) {
        return false;
    }

    int rockAmount = 0;
    rockAmount += cfg.acceptedBlocks.contains(reader.getData(pos.west()).getBlock()) ? 1 : 0;
    rockAmount += cfg.acceptedBlocks.contains(reader.getData(pos.east()).getBlock()) ? 1 : 0;
    rockAmount += cfg.acceptedBlocks.contains(reader.getData(pos.north()).getBlock()) ? 1 : 0;
    rockAmount += cfg.acceptedBlocks.contains(reader.getData(pos.south()).getBlock()) ? 1 : 0;
    rockAmount += cfg.acceptedBlocks.contains(reader.getData(pos.down()).getBlock()) ? 1 : 0;

    int holeAmount = 0;
    holeAmount += reader.isAirBlock(pos.west()) ? 1 : 0;
    holeAmount += reader.isAirBlock(pos.east()) ? 1 : 0;
    holeAmount += reader.isAirBlock(pos.north()) ? 1 : 0;
    holeAmount += reader.isAirBlock(pos.south()) ? 1 : 0;
    holeAmount += reader.isAirBlock(pos.down()) ? 1 : 0;

    if (rockAmount == cfg.rockAmount && holeAmount == cfg.holeAmount) {
        reader.setData(pos, cfg.state/*, 2*/);
//        reader.getPendingFluidTicks().scheduleTick(pos, cfg.state.getFluid(), 0);
        return true;
    }

    return false;
}
