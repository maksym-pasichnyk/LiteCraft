#pragma once

enum class OceanRuinType {
    WARM,
    COLD
};

struct OceanRuinConfig {
    OceanRuinType type;
    float largeProbability;
    float clusterProbability;
};