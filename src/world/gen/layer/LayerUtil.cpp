#include "LayerUtil.hpp"
#include "IslandLayer.hpp"
#include "ZoomLayer.hpp"
#include "AddIslandLayer.hpp"
#include "RemoveTooMuchOceanLayer.hpp"
#include "OceanLayer.hpp"
#include "AddSnowLayer.hpp"
#include "EdgeLayer.hpp"
#include "DeepOceanLayer.hpp"
#include "AddMushroomIslandLayer.hpp"
#include "StartRiverLayer.hpp"
#include "AddBambooForestLayer.hpp"
#include "EdgeBiomeLayer.hpp"
#include "HillsLayer.hpp"
#include "RiverLayer.hpp"
#include "SmoothLayer.hpp"
#include "RareBiomeLayer.hpp"
#include "ShoreLayer.hpp"
#include "MixRiverLayer.hpp"
#include "MixOceansLayer.hpp"
#include "BiomeLayer.hpp"

#include <utility>


IAreaFactory repeat(int64_t seed, IAreaTransformer1 auto layer, IAreaFactory area, int count, const std::function<LazyAreaLayerContext(int64_t)>& contextFactory) {
    auto iareafactory = std::move(area);

    for(int i = 0; i < count; ++i) {
        iareafactory = make(layer, contextFactory(seed + (int64_t) i), std::move(iareafactory));
    }

    return iareafactory;
}

std::unique_ptr<Layer> LayerUtil::createOverworldBiomes(int64_t seed, bool legacyBiomes, int biomeScale, int _4) {
    auto factory = createOverworldBiomes(legacyBiomes, biomeScale, _4, [seed] (int64_t seedModification) {
        return LazyAreaLayerContext(/*25,*/ seed, seedModification);
    });
    return std::make_unique<Layer>(factory.makeArea());
}

IAreaFactory LayerUtil::createOverworldBiomes(bool legacyBiomes, int biomeScale, int repeatCount, const std::function<LazyAreaLayerContext(int64_t)>& contextFactory) {
    auto layer1 = make(IslandLayer{}, contextFactory(1));
    auto layer2 = make(ZoomLayerFuzzy{}, contextFactory(2000), layer1);
    auto layer3 = make(AddIslandLayer{}, contextFactory(1), layer2);
    auto layer4 = make(ZoomLayerNormal{}, contextFactory(2001), layer3);
    auto layer5 = make(AddIslandLayer{}, contextFactory(2), layer4);
    auto layer6 = make(AddIslandLayer{}, contextFactory(50), layer5);
    auto layer7 = make(AddIslandLayer{}, contextFactory(70), layer6);
    auto layer8 = make(RemoveTooMuchOceanLayer{}, contextFactory(2), layer7);
    auto layer9 = make(OceanLayer{}, contextFactory(2));
    auto layer10 = repeat(2001L, ZoomLayerNormal{}, layer9, 6, contextFactory);
    auto layer11 = make(AddSnowLayer{}, contextFactory(2), layer8);
    auto layer12 = make(AddIslandLayer{}, contextFactory(3), layer11);
    auto layer13 = make(EdgeLayer::CoolWarm{}, contextFactory(2), layer12);
    auto layer14 = make(EdgeLayer::HeatIce{}, contextFactory(2), layer13);
    auto layer15 = make(EdgeLayer::Special{}, contextFactory(3), layer14);
    auto layer16 = make(ZoomLayerNormal{}, contextFactory(2002), layer15);
    auto layer17 = make(ZoomLayerNormal{}, contextFactory(2003), layer16);
    auto layer18 = make(AddIslandLayer{}, contextFactory(4), layer17);
    auto layer19 = make(AddMushroomIslandLayer{}, contextFactory(5), layer18);
    auto layer20 = make(DeepOceanLayer{}, contextFactory(4), layer19);
    auto layer21 = repeat(1000L, ZoomLayerNormal{}, layer20, 0, contextFactory);
    auto layer22 = repeat(1000L, ZoomLayerNormal{}, layer21, 0, contextFactory);
    auto layer23 = make(StartRiverLayer{}, contextFactory(100), layer22);
    auto layer24 = make(BiomeLayer{legacyBiomes}, contextFactory(200), layer21);
    auto layer25 = make(AddBambooForestLayer{}, contextFactory(1001), layer24);
    auto layer26 = repeat(1000L, ZoomLayerNormal{}, layer25, 2, contextFactory);
    auto layer27 = make(EdgeBiomeLayer{}, contextFactory(1000), layer26);
    auto layer29 = repeat(1000L, ZoomLayerNormal{}, layer23, 2, contextFactory);
    auto layer30 = make(HillsLayer{}, contextFactory(1000), layer27, layer29);
    auto layer31 = repeat(1000L, ZoomLayerNormal{}, layer23, 2, contextFactory);
    auto layer32 = repeat(1000L, ZoomLayerNormal{}, layer31, repeatCount, contextFactory);
    auto layer33 = make(RiverLayer{}, contextFactory(1), layer32);
    auto layer34 = make(SmoothLayer{}, contextFactory(1000), layer33);
    auto layer35 = make(RareBiomeLayer{}, contextFactory(1001), layer30);

    for (int i = 0; i < biomeScale; ++i) {
        layer35 = make(ZoomLayerNormal{}, contextFactory(1000 + i), layer35);
        if (i == 0) {
            layer35 = make(AddIslandLayer{}, contextFactory(3), layer35);
        }

        if (i == 1 || biomeScale == 1) {
            layer35 = make(ShoreLayer{}, contextFactory(1000), layer35);
        }
    }

    auto layer36 = make(SmoothLayer{}, contextFactory(1000), layer35);
    auto layer37 = make(MixRiverLayer{}, contextFactory(100), layer36, layer34);

    return make(MixOceansLayer{}, contextFactory(100L), layer37, layer10);
}
