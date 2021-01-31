#pragma once

#include "src/world/gen/layer/area/IAreaFactory.hpp"
#include "src/world/gen/IExtendedNoiseRandom.hpp"
#include "src/world/gen/LazyAreaLayerContext.hpp"

#include <memory>
#include <utility>

template <typename T>
concept IAreaTransformer0 = requires(T self, IExtendedNoiseRandom& rand, int x, int z) {
    { self.apply2(rand, x, z)} -> std::same_as<int>;
};

static IAreaFactory make(IAreaTransformer0 auto self, LazyAreaLayerContext&& context) {
    return [self = std::move(self), context = std::move(context)]() mutable {
        return [self = std::move(self), context = std::move(context)] (int x, int z) mutable {
//            std::printf("x: %d, z: %d\n", x, z);

            context.setPosition(x, z);
            return self.apply2(context, x, z);
        };
    };
}