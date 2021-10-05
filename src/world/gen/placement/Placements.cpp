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

void Placements::init() {
    NOPE = create<Passthrough>("nope");
    CHANCE = create<ChancePlacement>("chance");
    COUNT = create<CountPlacement>("count");
    COUNT_NOISE = create<CountNoisePlacement>("count_noise");
    COUNT_NOISE_BIASED = create<CountNoiseBiasedPlacement>("count_noise_biased");
    COUNT_EXTRA = create<CountExtraPlacement>("count_extra");
    SQUARE = create<SquarePlacement>("square");
    HEIGHTMAP = create<HeightmapPlacement>("heightmap");
    HEIGHTMAP_SPREAD_DOUBLE = create<HeightmapSpreadDoublePlacement>("heightmap_spread_double");
    TOP_SOLID_HEIGHTMAP = create<TopSolidOncePlacement>("top_solid_heightmap");
    HEIGHTMAP_WORLD_SURFACE = create<HeightmapWorldSurfacePlacement>("heightmap_world_surface");
    RANGE = create<RangePlacement>("range");
    RANGE_BIASED = create<RangeBiasedPlacement>("range_biased");
    RANGE_VERY_BIASED = create<RangeVeryBiasedPlacement>("range_very_biased");
    DEPTH_AVERAGE = create<DepthAveragePlacement>("depth_average");
    SPREAD_32_ABOVE = create<Spread32AbovePlacement>("spread_32_above");
    CARVING_MASK = create<CaveEdgePlacement>("carving_mask");
    FIRE = create<FirePlacement>("fire");
    MAGMA = create<NetherMagmaPlacement>("magma");
    EMERALD_ORE = create<Height4To32Placement>("emerald_ore");
    LAVA_LAKE = create<LakeLavaPlacement>("lava_lake");
    WATER_LAKE = create<LakeWaterPlacement>("water_lake");
    GLOWSTONE = create<GlowstonePlacement>("glowstone");
    END_GATEWAY = create<EndGatewayPlacement>("end_gateway");
    DARK_OAK_TREE = create<DarkOakTreePlacement>("dark_oak_tree");
    ICEBERG = create<IcebergPlacement>("iceberg");
    END_ISLAND = create<EndIslandPlacement>("end_island");
    DECORATED = create<DecoratedPlacement>("decorated");
    COUNT_MULTILAYER = create<CountMultilayerPlacement>("count_multilayer");
}
