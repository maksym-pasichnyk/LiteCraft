#pragma once

#include <map>
#include <span>
#include <array>
#include <string>
#include <glm/vec3.hpp>
#include <tl/optional.hpp>

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
    static constexpr auto VALUES = std::array{
        Direction::DOWN,
        Direction::UP,
        Direction::NORTH,
        Direction::SOUTH,
        Direction::WEST,
        Direction::EAST,
    };

    static constexpr auto OFFSET = std::array{
        glm::ivec3(0, -1, 0),
        glm::ivec3(0, 1, 0),
        glm::ivec3(0, 0, -1),
        glm::ivec3(0, 0, 1),
        glm::ivec3(-1, 0, 0),
        glm::ivec3(1, 0, 0)
    };

    static constexpr auto OPPOSITE = std::array{
        1, 0, 3, 2, 5, 4
    };

    static constexpr auto AXIS = std::array {
            DirectionAxis::Y,
            DirectionAxis::Y,
            DirectionAxis::Z,
            DirectionAxis::Z,
            DirectionAxis::X,
            DirectionAxis::X
    };

    static constexpr auto AXIS_DIRECTION = std::array {
        -1,
        1,
        -1,
        1,
        -1,
        1
    };

    static constexpr auto ROTATE_Y = std::array {
        Direction::DOWN,
        Direction::UP,
        Direction::EAST,
        Direction::WEST,
        Direction::NORTH,
        Direction::SOUTH
    };

    static constexpr auto ROTATE_YCCW = std::array{
        Direction::DOWN,
        Direction::UP,
        Direction::WEST,
        Direction::EAST,
        Direction::SOUTH,
        Direction::NORTH
    };

    struct Plane {
        static constexpr auto HORIZONTAL = std::array{
            Direction::NORTH,
            Direction::EAST,
            Direction::SOUTH,
            Direction::WEST
        };
        static constexpr auto VERTICAL = std::array{
            Direction::UP,
            Direction::DOWN
        };
    };

    static constexpr auto values() {
        return std::span(VALUES);
    }

    static constexpr auto getAxis(Direction direction) -> DirectionAxis {
        return AXIS[static_cast<int>(direction)];
    }

    static constexpr auto getOpposite(Direction direction) -> Direction {
        return static_cast<Direction>(OPPOSITE[static_cast<int>(direction)]);
    }

    static constexpr auto getOffset(Direction direction) -> glm::ivec3 {
        return OFFSET[static_cast<int>(direction)];
    }

    static constexpr auto getXOffset(Direction direction) -> int {
        return OFFSET[static_cast<int>(direction)].x;
    }

    static constexpr auto getYOffset(Direction direction) -> int {
        return OFFSET[static_cast<int>(direction)].y;
    }

    static constexpr auto getZOffset(Direction direction) -> int {
        return OFFSET[static_cast<int>(direction)].z;
    }

    static constexpr auto rotateY(Direction direction) -> Direction {
        return ROTATE_Y[static_cast<int>(direction)];
    }

    static constexpr auto rotateYCCW(Direction direction) -> Direction {
        return ROTATE_YCCW[static_cast<int>(direction)];
    }

    static constexpr auto getAxisDirection(Direction direction) -> int {
        return AXIS_DIRECTION[static_cast<int>(direction)];
    }
};
