#include "GrassColorModifiers.hpp"
#include "Biome.hpp"

auto GrassColorModifiers::none(double x, double z, int color) -> int {
    return color;
}

auto GrassColorModifiers::dark_forest(double x, double z, int color) -> int {
    return ((color & 16711422) + 2634762) >> 1;
}

auto GrassColorModifiers::swamp(double x, double z, int color) -> int {
    const auto noise = Biome::INFO_NOISE.noiseAt(x * 0.0225, z * 0.0225, false);
    return noise < -0.1 ? 5011004 : 6975545;
}