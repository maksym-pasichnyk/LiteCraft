#pragma once

#include <array>
#include <util/Direction.hpp>

struct FaceInfo {
    struct Constants {
        static constexpr auto MIN_X = static_cast<size_t>(Direction::WEST);
        static constexpr auto MIN_Y = static_cast<size_t>(Direction::DOWN);
        static constexpr auto MIN_Z = static_cast<size_t>(Direction::NORTH);
        static constexpr auto MAX_X = static_cast<size_t>(Direction::EAST);
        static constexpr auto MAX_Y = static_cast<size_t>(Direction::UP);
        static constexpr auto MAX_Z = static_cast<size_t>(Direction::SOUTH);
    };
    struct VertexInfo {
        int xFace;
        int yFace;
        int zFace;
    };

    std::array<VertexInfo, 4> info;
};

struct FaceInfos {
    using Constants = FaceInfo::Constants;
    using VertexInfo = FaceInfo::VertexInfo;

    static constexpr auto DOWN = FaceInfo{
            VertexInfo{Constants::MIN_X, Constants::MIN_Y, Constants::MAX_Z},
            VertexInfo{Constants::MIN_X, Constants::MIN_Y, Constants::MIN_Z},
            VertexInfo{Constants::MAX_X, Constants::MIN_Y, Constants::MIN_Z},
            VertexInfo{Constants::MAX_X, Constants::MIN_Y, Constants::MAX_Z}
    };
    static constexpr auto UP = FaceInfo{
            VertexInfo{Constants::MIN_X, Constants::MAX_Y, Constants::MIN_Z},
            VertexInfo{Constants::MIN_X, Constants::MAX_Y, Constants::MAX_Z},
            VertexInfo{Constants::MAX_X, Constants::MAX_Y, Constants::MAX_Z},
            VertexInfo{Constants::MAX_X, Constants::MAX_Y, Constants::MIN_Z}
    };
    static constexpr auto NORTH = FaceInfo{
            VertexInfo{Constants::MAX_X, Constants::MAX_Y, Constants::MIN_Z},
            VertexInfo{Constants::MAX_X, Constants::MIN_Y, Constants::MIN_Z},
            VertexInfo{Constants::MIN_X, Constants::MIN_Y, Constants::MIN_Z},
            VertexInfo{Constants::MIN_X, Constants::MAX_Y, Constants::MIN_Z}
    };
    static constexpr auto SOUTH = FaceInfo{
            VertexInfo{Constants::MIN_X, Constants::MAX_Y, Constants::MAX_Z},
            VertexInfo{Constants::MIN_X, Constants::MIN_Y, Constants::MAX_Z},
            VertexInfo{Constants::MAX_X, Constants::MIN_Y, Constants::MAX_Z},
            VertexInfo{Constants::MAX_X, Constants::MAX_Y, Constants::MAX_Z}
    };
    static constexpr auto WEST = FaceInfo{
            VertexInfo{Constants::MIN_X, Constants::MAX_Y, Constants::MIN_Z},
            VertexInfo{Constants::MIN_X, Constants::MIN_Y, Constants::MIN_Z},
            VertexInfo{Constants::MIN_X, Constants::MIN_Y, Constants::MAX_Z},
            VertexInfo{Constants::MIN_X, Constants::MAX_Y, Constants::MAX_Z}
    };
    static constexpr auto EAST = FaceInfo{
            VertexInfo{Constants::MAX_X, Constants::MAX_Y, Constants::MAX_Z},
            VertexInfo{Constants::MAX_X, Constants::MIN_Y, Constants::MAX_Z},
            VertexInfo{Constants::MAX_X, Constants::MIN_Y, Constants::MIN_Z},
            VertexInfo{Constants::MAX_X, Constants::MAX_Y, Constants::MIN_Z}
    };

    static constexpr auto FACING = [] {
        auto self = std::array<FaceInfo, 6>{};
        self[Constants::MIN_Y] = DOWN;
        self[Constants::MAX_Y] = UP;
        self[Constants::MIN_Z] = NORTH;
        self[Constants::MAX_Z] = SOUTH;
        self[Constants::MIN_X] = WEST;
        self[Constants::MAX_X] = EAST;
        return self;
    }();

    static auto get(Direction facing) -> const FaceInfo& {
        return FACING[static_cast<size_t>(facing)];
    }
};