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

struct Directions {
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

    struct Plane {
        static constexpr std::array HORIZONTAL{Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
        static constexpr std::array VERTICAL{Direction::UP, Direction::DOWN};
    };

    static constexpr auto values() {
        return std::span(VALUES);
    }
    
    static constexpr glm::ivec3 offset(const glm::ivec3& pos, Direction direction) {
        return pos + OFFSET[static_cast<int>(direction)];
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
};