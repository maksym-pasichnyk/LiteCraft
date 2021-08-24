#pragma once

#include <type_traits>

enum class Rotation {
    NONE,
    CLOCKWISE_90,
    CLOCKWISE_180,
    COUNTERCLOCKWISE_90
};

static constexpr auto operator+(Rotation self, Rotation rotation) -> Rotation {
    using base_t = std::underlying_type<Rotation>::type;

    return static_cast<Rotation>((static_cast<base_t>(self) + static_cast<base_t>(rotation)) & 3);
}

static constexpr auto operator-(Rotation self, Rotation rotation) -> Rotation {
    using base_t = std::underlying_type<Rotation>::type;

    return static_cast<Rotation>((static_cast<base_t>(self) - static_cast<base_t>(rotation)) & 3);
}

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