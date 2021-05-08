#pragma once

#include "../gen/surface/ConfiguredSurfaceBuilder.hpp"
#include "../gen/feature/ConfiguredFeature.hpp"
#include "../gen/carver/ConfiguredCarver.hpp"
#include "../gen/GenerationStage.hpp"

#include <vector>
#include <array>
#include <span>

struct StructureFeature;
struct ConfiguredFeature;
struct BiomeGenerationSettings {
//    BiomeGenerationSettings() = default;
//    BiomeGenerationSettings(const BiomeGenerationSettings&) = delete;
//    BiomeGenerationSettings& operator=(const BiomeGenerationSettings&) = delete;

    ConfiguredSurfaceBuilder* surfaceBuilder;
    std::array<std::vector<ConfiguredCarver>, 2> carvers;
    std::array<std::vector<ConfiguredFeature*>, 10> features;
    std::vector<StructureFeature*> structures;
//    std::vector<ConfiguredFeature> flowerFeatures;

    SurfaceBuilderConfig getSurfaceBuilderConfig() {
        return surfaceBuilder->config;
    }

//    std::span<ConfiguredFeature*> getFeatures(GenerationStage::Decoration decoration) {
//        return features[static_cast<int>(decoration)];
//    }

    struct Builder {
        ConfiguredSurfaceBuilder* surfaceBuilder;
        std::array<std::vector<ConfiguredCarver>, 2> carvers;
        std::array<std::vector<ConfiguredFeature*>, 10> features;
        std::vector<StructureFeature*> structures;

        Builder& withSurfaceBuilder(ConfiguredSurfaceBuilder* builder) {
            surfaceBuilder = builder;
            return *this;
        }

        Builder& withCarver(GenerationStage::Carving carving, const ConfiguredCarver& carver) {
            carvers.at(static_cast<int>(carving)).emplace_back(carver);
            return *this;
        }

        Builder& withFeature(GenerationStage::Decoration decoration, ConfiguredFeature* feature) {
            features.at(static_cast<int>(decoration)).emplace_back(feature);
            return *this;
        }

        Builder& withStructure(StructureFeature* structure) {
            structures.emplace_back(structure);
            return *this;
        }

        BiomeGenerationSettings build() {
            return {
                .surfaceBuilder = surfaceBuilder,
                .carvers = std::move(carvers),
                .features = std::move(features),
                .structures = std::move(structures)
            };
        }
    };
};