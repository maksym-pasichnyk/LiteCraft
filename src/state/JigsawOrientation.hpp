#pragma once

#include <array>
#include <tl/optional.hpp>
#include <util/Direction.hpp>

enum class JigsawOrientation {
    DOWN_EAST, //("down_east", Direction.DOWN, Direction.EAST),
    DOWN_NORTH, //("down_north", Direction.DOWN, Direction.NORTH),
    DOWN_SOUTH, //("down_south", Direction.DOWN, Direction.SOUTH),
    DOWN_WEST, //("down_west", Direction.DOWN, Direction.WEST),
    UP_EAST, //("up_east", Direction.UP, Direction.EAST),
    UP_NORTH, //("up_north", Direction.UP, Direction.NORTH),
    UP_SOUTH, //("up_south", Direction.UP, Direction.SOUTH),
    UP_WEST, //("up_west", Direction.UP, Direction.WEST),
    WEST_UP, //("west_up", Direction.WEST, Direction.UP),
    EAST_UP, //("east_up", Direction.EAST, Direction.UP),
    NORTH_UP, //("north_up", Direction.NORTH, Direction.UP),
    SOUTH_UP, //("south_up", Direction.SOUTH, Direction.UP);
};

struct JigsawOrientations {
    static constexpr auto ORIENTATIONS = std::array {
        std::pair{JigsawOrientation::DOWN_EAST, std::pair{Direction::DOWN, Direction::EAST}},
        std::pair{JigsawOrientation::DOWN_NORTH, std::pair{Direction::DOWN, Direction::NORTH}},
        std::pair{JigsawOrientation::DOWN_SOUTH, std::pair{Direction::DOWN, Direction::SOUTH}},
        std::pair{JigsawOrientation::DOWN_WEST, std::pair{Direction::DOWN, Direction::WEST}},
        std::pair{JigsawOrientation::UP_EAST, std::pair{Direction::UP, Direction::EAST}},
        std::pair{JigsawOrientation::UP_NORTH, std::pair{Direction::UP, Direction::NORTH}},
        std::pair{JigsawOrientation::UP_SOUTH, std::pair{Direction::UP, Direction::SOUTH}},
        std::pair{JigsawOrientation::UP_WEST, std::pair{Direction::UP, Direction::WEST}},
        std::pair{JigsawOrientation::WEST_UP, std::pair{Direction::WEST, Direction::UP}},
        std::pair{JigsawOrientation::EAST_UP, std::pair{Direction::EAST, Direction::UP}},
        std::pair{JigsawOrientation::NORTH_UP, std::pair{Direction::NORTH, Direction::UP}},
        std::pair{JigsawOrientation::SOUTH_UP, std::pair{Direction::SOUTH, Direction::UP}},
    };

    static constexpr auto getTopFacing(JigsawOrientation orientation) -> Direction {
        return ORIENTATIONS.at(static_cast<size_t>(orientation)).second.second;
    }

    static constexpr auto getFrontFacing(JigsawOrientation orientation) -> Direction {
        return ORIENTATIONS.at(static_cast<size_t>(orientation)).second.first;
    }

    static constexpr auto from(Direction front, Direction top) -> tl::optional<JigsawOrientation> {
        for (auto&& [orientation, front_and_top] : ORIENTATIONS) {
            if (front_and_top.first == front && front_and_top.second == top) {
                return orientation;
            }
        }
        return tl::nullopt;
    }
};