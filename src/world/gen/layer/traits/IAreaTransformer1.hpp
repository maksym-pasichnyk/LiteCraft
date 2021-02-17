#pragma once

#include <utility>

#include "IDimTransformer.hpp"
#include "src/world/gen/IExtendedNoiseRandom.hpp"
#include "src/world/gen/area/IAreaFactory.hpp"
#include "src/world/gen/LazyAreaLayerContext.hpp"

#include <functional>

template <typename T>
concept IAreaTransformer1 = requires(T self, IExtendedNoiseRandom& rand, const IArea& area, int x, int z) {
    { self.apply2(rand, area, x, z)} -> std::same_as<int>;
};

static IAreaFactory make(IAreaTransformer1 auto self, LazyAreaLayerContext&& context, IAreaFactory parent) {
    return [self, context = std::move(context), parent = std::move(parent)]() mutable -> IArea {
        return [self = std::move(self), context = std::move(context), area = parent.makeArea()] (int x, int z) mutable -> int {
            context.setPosition(x, z);
            return self.apply2(context, area, x, z);
        };
    };
}