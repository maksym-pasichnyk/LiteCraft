#pragma once

#include <span>
#include <array>
#include <glm/vec3.hpp>

enum class Direction {
    DOWN,
    UP,
    NORTH,
    SOUTH,
    WEST,
    EAST
};

enum class DirectionAxis {
    X, Y, Z
};

struct DirectionUtil {
    using Axis = DirectionAxis;

    static constexpr std::array VALUES{
        Direction::DOWN,
        Direction::UP,
        Direction::NORTH,
        Direction::SOUTH,
        Direction::WEST,
        Direction::EAST,
    };

    static constexpr std::array OFFSET {
        glm::ivec3(0, -1, 0),
        glm::ivec3(0, 1, 0),
        glm::ivec3(0, 0, -1),
        glm::ivec3(0, 0, 1),
        glm::ivec3(-1, 0, 0),
        glm::ivec3(1, 0, 0)
    };

    static constexpr std::array OPPOSITE {
        1, 0, 3, 2, 4, 5
    };

    static constexpr std::array AXIS {
        Axis::Y,
        Axis::Y,
        Axis::Z,
        Axis::Z,
        Axis::X,
        Axis::X
    };

    static constexpr std::array ROTATE_Y {
        Direction::DOWN,
        Direction::UP,
        Direction::EAST,
        Direction::WEST,
        Direction::NORTH,
        Direction::SOUTH
    };

    static constexpr std::array ROTATE_YCCW {
        Direction::DOWN,
        Direction::UP,
        Direction::WEST,
        Direction::EAST,
        Direction::SOUTH,
        Direction::NORTH
    };

    struct Plane {
        static constexpr std::array HORIZONTAL{Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
        static constexpr std::array VERTICAL{Direction::UP, Direction::DOWN};
    };

    static constexpr auto values() {
        return std::span(VALUES);
    }

    static constexpr Axis getAxis(Direction direction) {
        return AXIS[static_cast<int>(direction)];
    }

    static constexpr Direction getOpposite(Direction direction) {
        return static_cast<Direction>(OPPOSITE[static_cast<int>(direction)]);
    }

    static constexpr int getXOffset(Direction direction) {
        return OFFSET[static_cast<int>(direction)].x;
    }

    static constexpr int getYOffset(Direction direction) {
        return OFFSET[static_cast<int>(direction)].y;
    }

    static constexpr int getZOffset(Direction direction) {
        return OFFSET[static_cast<int>(direction)].z;
    }

    static constexpr Direction rotateY(Direction direction) {
        return ROTATE_Y[static_cast<int>(direction)];
    }

    static constexpr Direction rotateYCCW(Direction direction) {
        return ROTATE_YCCW[static_cast<int>(direction)];
    }
};