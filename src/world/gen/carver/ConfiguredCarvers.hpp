#pragma once

#include "ConfiguredCarver.hpp"

#include <util/Registry.hpp>
#include <world/gen/feature/config/ProbabilityConfig.hpp>

struct WorldCarver;
struct ConfiguredCarvers {
    static Registry<ConfiguredCarver> carvers;

    static auto configure(std::string name, WorldCarver* carver, ProbabilityConfig config) -> ConfiguredCarver* {
        return carvers.add(std::move(name), std::make_unique<ConfiguredCarver>(ConfiguredCarver{
           .carver = carver,
           .config = config
        }));
    }

    static void init();
};