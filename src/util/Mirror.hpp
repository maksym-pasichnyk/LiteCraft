#pragma once

#include "Rotation.hpp"

enum class Mirror {
    NONE,
    LEFT_RIGHT,
    FRONT_BACK
};

struct MirrorUtil {
    static constexpr std::array DIRECTION {
        Mirror::NONE,
        Mirror::NONE,
        Mirror::NONE,
        Mirror::LEFT_RIGHT,
        Mirror::LEFT_RIGHT,
        Mirror::NONE
    };

    static constexpr Mirror from(Direction facing) {
        return DIRECTION[static_cast<int>(facing)];
    }

    static constexpr Rotation toRotation(Mirror self, Direction facing) {
        const auto axis = DirectionUtil::getAxis(facing);
        return (self == Mirror::LEFT_RIGHT && axis == DirectionUtil::Axis::Z)
            || (self == Mirror::FRONT_BACK && axis == DirectionUtil::Axis::X)
                ? Rotation::CLOCKWISE_180 : Rotation::NONE;
    }

    static constexpr Direction mirror(Mirror self, Direction facing) {
        const auto axis = DirectionUtil::getAxis(facing);
        return (self == Mirror::LEFT_RIGHT && axis == DirectionUtil::Axis::Z)
            || (self == Mirror::FRONT_BACK && axis == DirectionUtil::Axis::X)
                ? DirectionUtil::getOpposite(facing) : facing;
    }
};