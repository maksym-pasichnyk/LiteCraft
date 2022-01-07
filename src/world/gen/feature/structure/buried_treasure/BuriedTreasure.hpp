#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct BuriedTreasure {
    static auto create() -> std::unique_ptr<Structure> {
        return std::make_unique<Structure>(Structure{
            .configFromJson = [](const Json& o) -> tl::optional<StructureConfig> {
                return o.into<ProbabilityConfig>();
            },
            .generatePieces = createComponents
        });
    }
    static void createComponents(StructurePieces& pieces, StructureGenerateContext& context, const StructureConfig& config) {}
};