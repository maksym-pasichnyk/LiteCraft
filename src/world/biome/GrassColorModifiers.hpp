#pragma once

struct GrassColorModifiers {
    static auto none(double x, double z, int color) -> int;
    static auto dark_forest(double x, double z, int color) -> int;
    static auto swamp(double x, double z, int color) -> int;
};
