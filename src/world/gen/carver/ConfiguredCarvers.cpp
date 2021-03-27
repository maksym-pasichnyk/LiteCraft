#include "ConfiguredCarvers.hpp"
#include "ConfiguredCarver.hpp"
#include "Carvers.hpp"

ConfiguredCarver ConfiguredCarvers::CAVE;
ConfiguredCarver ConfiguredCarvers::CANYON;
ConfiguredCarver ConfiguredCarvers::OCEAN_CAVE;
ConfiguredCarver ConfiguredCarvers::NETHER_CAVE;

void ConfiguredCarvers::configureCarvers() {
    CAVE = {
        .carver = Carvers::CAVE,
        .config {
            .probability = 0.14285715F
        }
    };
    CANYON = {
        .carver = Carvers::CANYON,
        .config {
            .probability = 0.02F
        }
    };
    OCEAN_CAVE = {
        .carver = Carvers::CAVE,
        .config {
            .probability = 0.06666667F
        }
    };
    NETHER_CAVE = {
        .carver = Carvers::CAVE,
        .config {
            .probability = 0.2F
        }
    };
}
