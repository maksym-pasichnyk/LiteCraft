#pragma once

#include "../../area/IAreaFactory.hpp"
#include "../../IExtendedNoiseRandom.hpp"
#include "../../LazyAreaLayerContext.hpp"

#include <memory>
#include <utility>

template <typename T>
concept IAreaTransformer0 = requires(T self, IExtendedNoiseRandom& rand, int x, int z) {
    { self.get(rand, x, z)} -> std::same_as<int>;
};

static IAreaFactory<LazyArea> make(IAreaTransformer0 auto self, std::shared_ptr<LazyAreaLayerContext> context) {
    return [
        self = std::move(self),
        context = std::move(context)
    ]() mutable {
        return context->makeArea([
            self = std::move(self),
            context = std::move(context)
        ] (int x, int z) mutable {
            context->setPosition(x, z);
            return self.get(*context, x, z);
        });
    };
}