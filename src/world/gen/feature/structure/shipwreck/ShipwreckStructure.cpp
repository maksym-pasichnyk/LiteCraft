#include "ShipwreckStructure.hpp"
#include "ShipwreckPiece.hpp"

static auto STRUCTURE_LOCATION_BEACHED = std::vector<std::string>{
    "shipwreck/with_mast",
    "shipwreck/sideways_full",
    "shipwreck/sideways_fronthalf",
    "shipwreck/sideways_backhalf",
    "shipwreck/rightsideup_full",
    "shipwreck/rightsideup_fronthalf",
    "shipwreck/rightsideup_backhalf",
    "shipwreck/with_mast_degraded",
    "shipwreck/rightsideup_full_degraded",
    "shipwreck/rightsideup_fronthalf_degraded",
    "shipwreck/rightsideup_backhalf_degraded"
};

static auto STRUCTURE_LOCATION_OCEAN = std::vector<std::string>{
    "shipwreck/with_mast",
    "shipwreck/upsidedown_full",
    "shipwreck/upsidedown_fronthalf",
    "shipwreck/upsidedown_backhalf",
    "shipwreck/sideways_full",
    "shipwreck/sideways_fronthalf",
    "shipwreck/sideways_backhalf",
    "shipwreck/rightsideup_full",
    "shipwreck/rightsideup_fronthalf",
    "shipwreck/rightsideup_backhalf",
    "shipwreck/with_mast_degraded",
    "shipwreck/upsidedown_full_degraded",
    "shipwreck/upsidedown_fronthalf_degraded",
    "shipwreck/upsidedown_backhalf_degraded",
    "shipwreck/sideways_full_degraded",
    "shipwreck/sideways_fronthalf_degraded",
    "shipwreck/sideways_backhalf_degraded",
    "shipwreck/rightsideup_full_degraded",
    "shipwreck/rightsideup_fronthalf_degraded",
    "shipwreck/rightsideup_backhalf_degraded"
};

void ShipwreckStructure::createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {
    auto&& cfg = std::get<ShipwreckConfig>(config);

    auto random = Random::fromLargeFeatureSeed(context.seed, context.pos.x, context.pos.z);
    const auto rotation = random.nextElement(std::span(RotationUtil::DIRECTION));
    const auto position = BlockPos::from(context.pos.getStartX(), 90, context.pos.getStartZ());
    auto location = random.nextElement(cfg.isBeached ? std::span(STRUCTURE_LOCATION_BEACHED) : std::span(STRUCTURE_LOCATION_OCEAN));
    pieces.emplace(new ShipwreckPiece(context.templateManager, std::move(location), position, rotation, cfg.isBeached));
}
