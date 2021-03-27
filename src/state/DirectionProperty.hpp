#pragma once

#include "EnumProperty.hpp"

enum class EnumFacing {
    DOWN,
    UP,
    NORTH,
    SOUTH,
    WEST,
    EAST
};

struct DirectionProperty : EnumProperty<EnumFacing> {

};