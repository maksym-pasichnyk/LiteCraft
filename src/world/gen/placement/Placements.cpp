#include "Placements.hpp"
#include "Passthrough.hpp"
#include "ChancePlacement.hpp"
#include "CountPlacement.hpp"
#include "CountNoisePlacement.hpp"
#include "CountNoiseBiasedPlacement.hpp"
#include "CountExtraPlacement.hpp"
#include "SquarePlacement.hpp"
#include "HeightmapPlacement.hpp"
#include "HeightmapSpreadDoublePlacement.hpp"
#include "TopSolidOncePlacement.hpp"
#include "HeightmapWorldSurfacePlacement.hpp"
#include "RangePlacement.hpp"
#include "RangeBiasedPlacement.hpp"
#include "RangeVeryBiasedPlacement.hpp"
#include "DepthAveragePlacement.hpp"
#include "Spread32AbovePlacement.hpp"
#include "CaveEdgePlacement.hpp"
#include "FirePlacement.hpp"
#include "NetherMagmaPlacement.hpp"
#include "Height4To32Placement.hpp"
#include "LakeLavaPlacement.hpp"
#include "LakeWaterPlacement.hpp"
#include "GlowstonePlacement.hpp"
#include "EndGatewayPlacement.hpp"
#include "DarkOakTreePlacement.hpp"
#include "IcebergPlacement.hpp"
#include "EndIslandPlacement.hpp"
#include "DecoratedPlacement.hpp"
#include "CountMultilayerPlacement.hpp"

Registry<Placement> Placements::placements{};
Placement* Placements::NOPE;
Placement* Placements::CHANCE;
Placement* Placements::COUNT;
Placement* Placements::COUNT_NOISE;
Placement* Placements::COUNT_NOISE_BIASED;
Placement* Placements::COUNT_EXTRA;
Placement* Placements::SQUARE;
Placement* Placements::HEIGHTMAP;
Placement* Placements::HEIGHTMAP_SPREAD_DOUBLE;
Placement* Placements::TOP_SOLID_HEIGHTMAP;
Placement* Placements::HEIGHTMAP_WORLD_SURFACE;
Placement* Placements::RANGE;
Placement* Placements::RANGE_BIASED;
Placement* Placements::RANGE_VERY_BIASED;
Placement* Placements::DEPTH_AVERAGE;
Placement* Placements::SPREAD_32_ABOVE;
Placement* Placements::CARVING_MASK;
Placement* Placements::FIRE;
Placement* Placements::MAGMA;
Placement* Placements::EMERALD_ORE;
Placement* Placements::LAVA_LAKE;
Placement* Placements::WATER_LAKE;
Placement* Placements::GLOWSTONE;
Placement* Placements::END_GATEWAY;
Placement* Placements::DARK_OAK_TREE;
Placement* Placements::ICEBERG;
Placement* Placements::END_ISLAND;
Placement* Placements::DECORATED;
Placement* Placements::COUNT_MULTILAYER;

template<typename T, typename... Args>
static T* createPlacement(std::string name, Args&&... args) {
    return dynamic_cast<T*>(Placements::placements.add(std::move(name), std::make_unique<T>(std::forward<Args>(args)...)));
}

void Placements::registerPlacements() {
    NOPE = createPlacement<Passthrough>("nope");
    CHANCE = createPlacement<ChancePlacement>("chance");
    COUNT = createPlacement<CountPlacement>("count");
    COUNT_NOISE = createPlacement<CountNoisePlacement>("count_noise");
    COUNT_NOISE_BIASED = createPlacement<CountNoiseBiasedPlacement>("count_noise_biased");
    COUNT_EXTRA = createPlacement<CountExtraPlacement>("count_extra");
    SQUARE = createPlacement<SquarePlacement>("square");
    HEIGHTMAP = createPlacement<HeightmapPlacement>("heightmap");
    HEIGHTMAP_SPREAD_DOUBLE = createPlacement<HeightmapSpreadDoublePlacement>("heightmap_spread_double");
    TOP_SOLID_HEIGHTMAP = createPlacement<TopSolidOncePlacement>("top_solid_heightmap");
    HEIGHTMAP_WORLD_SURFACE = createPlacement<HeightmapWorldSurfacePlacement>("heightmap_world_surface");
    RANGE = createPlacement<RangePlacement>("range");
    RANGE_BIASED = createPlacement<RangeBiasedPlacement>("range_biased");
    RANGE_VERY_BIASED = createPlacement<RangeVeryBiasedPlacement>("range_very_biased");
    DEPTH_AVERAGE = createPlacement<DepthAveragePlacement>("depth_average");
    SPREAD_32_ABOVE = createPlacement<Spread32AbovePlacement>("spread_32_above");
    CARVING_MASK = createPlacement<CaveEdgePlacement>("carving_mask");
    FIRE = createPlacement<FirePlacement>("fire");
    MAGMA = createPlacement<NetherMagmaPlacement>("magma");
    EMERALD_ORE = createPlacement<Height4To32Placement>("emerald_ore");
    LAVA_LAKE = createPlacement<LakeLavaPlacement>("lava_lake");
    WATER_LAKE = createPlacement<LakeWaterPlacement>("water_lake");
    GLOWSTONE = createPlacement<GlowstonePlacement>("glowstone");
    END_GATEWAY = createPlacement<EndGatewayPlacement>("end_gateway");
    DARK_OAK_TREE = createPlacement<DarkOakTreePlacement>("dark_oak_tree");
    ICEBERG = createPlacement<IcebergPlacement>("iceberg");
    END_ISLAND = createPlacement<EndIslandPlacement>("end_island");
    DECORATED = createPlacement<DecoratedPlacement>("decorated");
    COUNT_MULTILAYER = createPlacement<CountMultilayerPlacement>("count_multilayer");
}
