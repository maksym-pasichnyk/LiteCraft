#pragma once

#include "../gen/surface/ConfiguredSurfaceBuilder.hpp"
#include "../gen/carver/ConfiguredCarver.hpp"
#include "../gen/GenerationStage.hpp"

#include <array>
#include <vector>

struct BiomeGenerationSettings {
//    BiomeGenerationSettings() = default;
//    BiomeGenerationSettings(const BiomeGenerationSettings&) = delete;
//    BiomeGenerationSettings& operator=(const BiomeGenerationSettings&) = delete;

    ConfiguredSurfaceBuilder surfaceBuilder;
//    std::map<GenerationStage::Carving, std::vector<ConfiguredCarver>> carvers;
    std::array<std::vector<ConfiguredCarver>, 2> carvers;
//    std::vector<std::vector<ConfiguredFeature>> features;
//    std::vector<StructureFeature> structures;
//    std::vector<ConfiguredFeature> flowerFeatures;

    SurfaceBuilderConfig getSurfaceBuilderConfig() {
        return surfaceBuilder.config;
    }

    struct Builder {
        ConfiguredSurfaceBuilder surfaceBuilder;
        std::array<std::vector<ConfiguredCarver>, 2> carvers;

        Builder& withSurfaceBuilder(const ConfiguredSurfaceBuilder& _surfaceBuilder) {
            surfaceBuilder = _surfaceBuilder;
            return *this;
        }

        Builder& withCarver(GenerationStage::Carving carving, const ConfiguredCarver& carver) {
            carvers.at(static_cast<int>(carving)).emplace_back(carver);
            return *this;
        }

        BiomeGenerationSettings build() {
            return {
                .surfaceBuilder = surfaceBuilder,
                .carvers = std::move(carvers)
            };
        }
    };
};