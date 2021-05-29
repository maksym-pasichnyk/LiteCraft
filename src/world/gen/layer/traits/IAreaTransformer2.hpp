#pragma once

#include "IDimTransformer.hpp"
#include "../../IExtendedNoiseRandom.hpp"
#include "../../area/IAreaFactory.hpp"
#include "../../LazyAreaLayerContext.hpp"

template <typename T>
concept IAreaTransformer2 = requires(T self, INoiseRandom& rand, const LazyArea& area1, const LazyArea& area2, int x, int z) {
    { self.get(rand, area1, area2, x, z)} -> std::same_as<int>;
};

static IAreaFactory<LazyArea> make(IAreaTransformer2 auto self, std::shared_ptr<LazyAreaLayerContext> context, IAreaFactory<LazyArea> factory1, IAreaFactory<LazyArea> factory2) {
    return [
        self,
        context = std::move(context),
        factory1 = std::move(factory1),
        factory2 = std::move(factory2)
    ]() mutable {
        IArea auto area1 = factory1.makeArea();
        IArea auto area2 = factory2.makeArea();

        return context->makeArea([
            self,
            context = std::move(context),
            area1 = std::move(area1),
            area2 = std::move(area2)
        ] (int x, int z) mutable {
            context->setPosition(x, z);
            return self.get(*context, area1, area2, x, z);
        }, area1, area2);
    };
}

