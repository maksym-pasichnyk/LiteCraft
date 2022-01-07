#pragma once

#include <array>
#include <util/Rotation.hpp>

enum class Mirror {
    NONE,
    LEFT_RIGHT,
    FRONT_BACK
};

struct MirrorUtil {
    static constexpr auto DIRECTION = std::array {
        Mirror::NONE,
        Mirror::NONE,
        Mirror::NONE,
        Mirror::LEFT_RIGHT,
        Mirror::LEFT_RIGHT,
        Mirror::NONE
    };

    static constexpr auto from(Direction facing) -> Mirror {
        return DIRECTION[static_cast<int>(facing)];
    }

    static constexpr auto toRotation(Mirror self, Direction facing) -> Rotation {
        const auto axis = DirectionUtil::getAxis(facing);
        return (self == Mirror::LEFT_RIGHT && axis == DirectionAxis::Z)
            || (self == Mirror::FRONT_BACK && axis == DirectionAxis::X)
                ? Rotation::CLOCKWISE_180
                : Rotation::NONE;
    }

    static constexpr auto mirror(Mirror self, Direction facing) -> Direction {
        const auto axis = DirectionUtil::getAxis(facing);
        return (self == Mirror::LEFT_RIGHT && axis == DirectionAxis::Z)
            || (self == Mirror::FRONT_BACK && axis == DirectionAxis::X)
                ? DirectionUtil::getOpposite(facing)
                : facing;
    }
};