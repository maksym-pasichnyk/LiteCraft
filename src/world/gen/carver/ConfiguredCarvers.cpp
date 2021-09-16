#include "ConfiguredCarvers.hpp"
#include "ConfiguredCarver.hpp"
#include "Carvers.hpp"

#include <fstream>
#include <configs.hpp>

Registry<ConfiguredCarver> ConfiguredCarvers::carvers;

ConfiguredCarver* ConfiguredCarvers::CAVE;
ConfiguredCarver* ConfiguredCarvers::CANYON;
ConfiguredCarver* ConfiguredCarvers::OCEAN_CAVE;
ConfiguredCarver* ConfiguredCarvers::NETHER_CAVE;

static auto configure(std::string name, WorldCarver* carver, ProbabilityConfig config) -> ConfiguredCarver* {
    return ConfiguredCarvers::carvers.add(std::move(name), std::make_unique<ConfiguredCarver>(ConfiguredCarver{
        .carver = carver,
        .config = config
    }));
}

void ConfiguredCarvers::init() {
    CAVE = configure("cave", Carvers::CAVE, { .probability = 0.14285715F });
    CANYON = configure("canyon", Carvers::CANYON, { .probability = 0.02F });
    OCEAN_CAVE = configure("ocean_cave", Carvers::CAVE, { .probability = 0.06666667F });
    NETHER_CAVE = configure("nether_cave", Carvers::NETHER_CAVE, { .probability = 0.2F });

    for (const auto& [name, carver] : carvers.objects) {
        std::ofstream out{fmt::format("definitions/configured_carvers/{}.json", name), std::ios::binary};
        out << Json{
            {"type", carver->carver},
            {"config", carver->config}
        };
    }
}
