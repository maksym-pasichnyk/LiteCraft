#pragma once

struct GenerationStage {
    enum class Carving {
        AIR,
        LIQUID
    };

    enum class Decoration {
        RAW_GENERATION,
        LAKES,
        LOCAL_MODIFICATIONS,
        UNDERGROUND_STRUCTURES,
        SURFACE_STRUCTURES,
        STRONGHOLDS,
        UNDERGROUND_ORES,
        UNDERGROUND_DECORATION,
        VEGETAL_DECORATION,
        TOP_LAYER_MODIFICATION
    };
};