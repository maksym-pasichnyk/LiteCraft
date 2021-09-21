#pragma once

#include "ConfiguredSurfaceBuilder.hpp"

#include <util/Registry.hpp>
#include <memory>
#include <map>

struct ConfiguredSurfaceBuilders {
    static Registry<ConfiguredSurfaceBuilder> builders;

    static auto configure(std::string name, SurfaceBuilder* builder, const SurfaceBuilderConfig& config) -> ConfiguredSurfaceBuilder* {
        return builders.add(std::move(name), std::make_unique<ConfiguredSurfaceBuilder>(ConfiguredSurfaceBuilder{
            .builder = builder,
            .config = config
        }));
    }

    static void init();
};