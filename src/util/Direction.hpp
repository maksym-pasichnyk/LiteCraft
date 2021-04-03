#pragma once

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
    static constexpr std::array OFFSET {
        glm::ivec3(0, -1, 0),
        glm::ivec3(0, 1, 0),
        glm::ivec3(0, 0, -1),
        glm::ivec3(0, 0, 1),
        glm::ivec3(-1, 0, 0),
        glm::ivec3(1, 0, 0)
    };

    struct Plane {
        static constexpr std::array HORIZONTAL{Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
        static constexpr std::array VERTICAL{Direction::UP, Direction::DOWN};
    };
    
    static constexpr glm::ivec3 offset(const glm::ivec3& pos, Direction direction) {
        return pos + OFFSET[static_cast<int>(direction)];
    }
};