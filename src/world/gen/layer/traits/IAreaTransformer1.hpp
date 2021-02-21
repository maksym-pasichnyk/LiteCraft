#pragma once

#include <utility>

#include "IDimTransformer.hpp"
#include "../../IExtendedNoiseRandom.hpp"
#include "../../area/IAreaFactory.hpp"
#include "../../LazyAreaLayerContext.hpp"

#include <functional>

template <typename T>
concept IAreaTransformer1 = requires(T self, IExtendedNoiseRandom& rand, const LazyArea& area, int x, int z) {
    { self.apply2(rand, area, x, z)} -> std::same_as<int>;
};

static IAreaFactory<LazyArea> make(IAreaTransformer1 auto self, std::shared_ptr<LazyAreaLayerContext> context, IAreaFactory<LazyArea> parent) {
    return [
        self,
        context = std::move(context),
        parent = std::move(parent)
    ]() mutable -> LazyArea {
        IArea auto area = parent.makeArea();

        return context->makeArea([
            self = std::move(self),
            context = std::move(context),
            area = std::move(area)
        ](int x, int z) mutable -> int {
            context->setPosition(x, z);
            return self.apply2(*context, area, x, z);
        }, area);
    };
}