#pragma once

#include "../gen/surface/ConfiguredSurfaceBuilder.hpp"
#include "../gen/carver/ConfiguredCarver.hpp"

#include <array>
#include <vector>

struct BiomeGenerationSettings {
    ConfiguredSurfaceBuilder surfaceBuilder;
//    std::map<GenerationStage::Carving, std::vector<ConfiguredCarver>> carvers;
    std::array<std::vector<ConfiguredCarver>, 2> carvers;
//    std::vector<std::vector<ConfiguredFeature>> features;
//    std::vector<StructureFeature> structures;
//    std::vector<ConfiguredFeature> flowerFeatures;

    struct Builder {
        ConfiguredSurfaceBuilder surfaceBuilder;

        Builder& withSurfaceBuilder(ConfiguredSurfaceBuilder& _surfaceBuilder) {
            surfaceBuilder = _surfaceBuilder;
            return *this;
        }

        BiomeGenerationSettings build() {
            return {
                .surfaceBuilder = surfaceBuilder
            };
        }
    };
};