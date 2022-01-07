#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct EndCity {
    static auto create() -> std::unique_ptr<Structure> {
        return std::make_unique<Structure>(Structure{
            .generatePieces = createComponents
        });
    }

    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};