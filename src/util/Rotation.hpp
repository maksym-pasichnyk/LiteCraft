#pragma once

#include <util/Direction.hpp>
#include <state/JigsawOrientation.hpp>

enum class Rotation {
    NONE,
    CLOCKWISE_90,
    CLOCKWISE_180,
    COUNTERCLOCKWISE_90
};

struct RotationUtil {
    static constexpr auto VALUES = std::array {
        Rotation::NONE,
        Rotation::CLOCKWISE_90,
        Rotation::CLOCKWISE_180,
        Rotation::COUNTERCLOCKWISE_90
    };

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
        using base = std::underlying_type_t<Rotation>;
        return Rotation(base(self) + base(rotation));
    }

    static constexpr auto getTopFacing(JigsawOrientation orientation) -> Direction {
        return JigsawOrientations::getTopFacing(orientation);
    }

    static constexpr auto getFrontFacing(JigsawOrientation orientation) -> Direction {
        return JigsawOrientations::getFrontFacing(orientation);
    }

    static constexpr auto rotate(Rotation self, Direction facing) -> Direction {
        if (DirectionUtil::getAxis(facing) == DirectionAxis::Y) {
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

    static constexpr auto rotate(Rotation self, JigsawOrientation orientation) -> JigsawOrientation {
        return JigsawOrientations::from(
            rotate(self, getFrontFacing(orientation)),
            rotate(self, getTopFacing(orientation))
        ).value();
    }
};