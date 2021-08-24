#pragma once

#include "DirectionUtil.hpp"
#include <util/Rotation.hpp>

struct RotationUtil {
    static constexpr auto DIRECTION = std::array {
        Rotation::NONE,
        Rotation::NONE,
        Rotation::NONE,
        Rotation::NONE,
        Rotation::CLOCKWISE_90,
        Rotation::CLOCKWISE_90
    };

    static constexpr auto from(Direction facing) -> Rotation {
        return DIRECTION[static_cast<int>(facing)];
    }

    static constexpr auto add(Rotation self, Rotation rotation) -> Rotation {
        return self + rotation;
    }

    static constexpr auto rotate(Rotation self, Direction facing) -> Direction {
        if (DirectionUtil::getAxis(facing) == DirectionUtil::Axis::Y) {
            return facing;
        }

        switch (self) {
            case Rotation::CLOCKWISE_90:
                return DirectionUtil::rotateY(facing);
            case Rotation::CLOCKWISE_180:
                return DirectionUtil::getOpposite(facing);
            case Rotation::COUNTERCLOCKWISE_90:
                return DirectionUtil::rotateYCCW(facing);
            default:
                return facing;
        }
    }
};
