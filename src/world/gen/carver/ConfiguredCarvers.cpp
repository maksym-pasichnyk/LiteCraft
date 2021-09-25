#include "ConfiguredCarvers.hpp"
#include "Carvers.hpp"

#include <fstream>
#include <filesystem>
#include <configs.hpp>

Registry<ConfiguredCarver> ConfiguredCarvers::carvers;

void ConfiguredCarvers::init() {
    for (auto&& entry : std::filesystem::directory_iterator{"definitions/configured_carvers"}) {
        if (!entry.is_regular_file()) {
            continue;
        }

        auto o = Json::Read::read(std::ifstream{entry.path(), std::ios::binary}).value();
        auto carver = Carvers::carvers.get(o.at("type").to_string()).value();
        auto config = static_cast<ProbabilityConfig>(o.at("config"));

        configure(entry.path().stem().string(), carver, config);
    }

//    for (const auto& [name, carver] : carvers.objects) {
//        std::ofstream out{fmt::format("definitions/configured_carvers/{}.json", name), std::ios::binary};
//        out << Json{
//            {"type", carver->carver},
//            {"config", carver->config}
//        };
//    }
}
