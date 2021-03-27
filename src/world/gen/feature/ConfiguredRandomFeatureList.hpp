#pragma once

struct ConfiguredFeature;
struct ConfiguredRandomFeatureList {
    ConfiguredFeature* feature;
    /*[[range(0.0F, 1.0F)]]*/ float chance;
};