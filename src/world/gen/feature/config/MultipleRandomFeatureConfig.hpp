#pragma once

#include "../ConfiguredRandomFeatureList.hpp"

struct ConfiguredFeature;
struct MultipleRandomFeatureConfig {
    std::vector<ConfiguredRandomFeatureList> features;
    ConfiguredFeature* defaultFeature;
};