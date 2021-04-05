#pragma once

struct ConfiguredFeature;
struct TwoFeatureChoiceConfig {
    ConfiguredFeature* feature_true;
    ConfiguredFeature* feature_false;
};