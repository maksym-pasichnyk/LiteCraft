#pragma once

#include "IDimTransformer.hpp"
#include "src/world/gen/IExtendedNoiseRandom.hpp"
#include "src/world/gen/area/IAreaFactory.hpp"
#include "src/world/gen/LazyAreaLayerContext.hpp"

template <typename T>
concept IAreaTransformer2 = requires(T self, INoiseRandom& rand, const IArea& area1, const IArea& area2, int x, int z) {
    { self.apply2(rand, area1, area2, x, z)} -> std::same_as<int>;
};

static IAreaFactory make(IAreaTransformer2 auto self, LazyAreaLayerContext&& context, IAreaFactory factory1, IAreaFactory factory2) {
    return [self, context = std::move(context), factory1 = std::move(factory1), factory2 = std::move(factory2)]() mutable {
        return [self, context = std::move(context), area1 = factory1.makeArea(), area2 = factory2.makeArea()] (int x, int z) mutable {
            context.setPosition(x, z);
            return self.apply2(context, area1, area2, x, z);
        };
    };
}

