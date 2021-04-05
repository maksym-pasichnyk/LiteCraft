#pragma once

#include <vector>

struct ConfiguredFeature;
struct SingleRandomFeatureConfig {
    std::vector<ConfiguredFeature*> features;
};