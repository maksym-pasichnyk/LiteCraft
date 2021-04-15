#pragma once

#include <type_traits>

#include "Direction.hpp"

enum class Rotation {
    NONE,
    CLOCKWISE_90,
    CLOCKWISE_180,
    COUNTERCLOCKWISE_90
};

static constexpr Rotation operator+(Rotation self, Rotation rotation) {
    using base_t = std::underlying_type<Rotation>::type;

    return static_cast<Rotation>((static_cast<base_t>(self) + static_cast<base_t>(rotation)) & 3);
}

static constexpr Rotation operator-(Rotation self, Rotation rotation) {
    using base_t = std::underlying_type<Rotation>::type;

    return static_cast<Rotation>((static_cast<base_t>(self) - static_cast<base_t>(rotation)) & 3);
}

struct RotationUtil {
    static constexpr std::array DIRECTION {
        Rotation::NONE,
        Rotation::NONE,
        Rotation::NONE,
        Rotation::NONE,
        Rotation::CLOCKWISE_90,
        Rotation::CLOCKWISE_90
    };

    static constexpr Rotation from(Direction facing) {
        return DIRECTION[static_cast<int>(facing)];
    }

    static constexpr Rotation add(Rotation self, Rotation rotation) {
        return self + rotation;
        switch(rotation) {
            case Rotation::CLOCKWISE_180:
                switch(self) {
                    case Rotation::NONE:
                        return Rotation::CLOCKWISE_180;
                    case Rotation::CLOCKWISE_90:
                        return Rotation::COUNTERCLOCKWISE_90;
                    case Rotation::CLOCKWISE_180:
                        return Rotation::NONE;
                    case Rotation::COUNTERCLOCKWISE_90:
                        return Rotation::CLOCKWISE_90;
                }
            case Rotation::COUNTERCLOCKWISE_90:
                switch(self) {
                    case Rotation::NONE:
                        return Rotation::COUNTERCLOCKWISE_90;
                    case Rotation::CLOCKWISE_90:
                        return Rotation::NONE;
                    case Rotation::CLOCKWISE_180:
                        return Rotation::CLOCKWISE_90;
                    case Rotation::COUNTERCLOCKWISE_90:
                        return Rotation::CLOCKWISE_180;
                }
            case Rotation::CLOCKWISE_90:
                switch(self) {
                    case Rotation::NONE:
                        return Rotation::CLOCKWISE_90;
                    case Rotation::CLOCKWISE_90:
                        return Rotation::CLOCKWISE_180;
                    case Rotation::CLOCKWISE_180:
                        return Rotation::COUNTERCLOCKWISE_90;
                    case Rotation::COUNTERCLOCKWISE_90:
                        return Rotation::NONE;
                }
            default:
                return self;
        }
    }

    static constexpr Direction rotate(Rotation self, Direction facing) {
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

//static_assert([] {
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            if (RotationUtil::add(static_cast<Rotation>(i), static_cast<Rotation>(j)) != (static_cast<Rotation>(i) + static_cast<Rotation>(j))) {
//                return false;
//            }
//        }
//    }
//    return true;
//}());