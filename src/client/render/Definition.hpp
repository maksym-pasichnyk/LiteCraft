#pragma once

#include <map>
#include <string>
#include <vector>
#include <Json.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <tl/optional.hpp>
#include <util/Direction.hpp>
#include <glm/glm.hpp>

enum class FaceIndex {
    Down,
    Up,
    North,
    South,
    West,
    East
};

struct FaceDefinition {
    tl::optional<FaceIndex> cullface;
    int rotation;
    std::string texture;
    tl::optional<int> tintindex;
    tl::optional<glm::vec4> uv;
};

struct RotationDefinition {
    float angle;
    DirectionAxis axis;
    glm::vec3 origin;
    bool rescale;

    void rotate(std::span<glm::vec3> points) const {
        // ix = 1, iy = 2 -> rotate around X axis
        // ix = 2, iy = 0 -> rotate around Y axis
        // ix = 1, iy = 0 -> rotate around Z axis
        const auto [ix, iy] = std::array{
            std::pair{1, 2},
            std::pair{2, 0},
            std::pair{1, 0}
        }[static_cast<size_t>(axis)];

        const auto ox = origin[ix];
        const auto oy = origin[iy];

        const auto s = glm::sin(glm::radians(angle));
        const auto c = glm::cos(glm::radians(angle));

        for (auto &point: points) {
            const auto x = point[ix] - ox;
            const auto y = point[iy] - oy;
            point[ix] = y * s + x * c;
            point[iy] = y * c - x * s;
        }

        if (rescale) {
            const auto scale = glm::sqrt(2.0f);
            for (auto &point: points) {
                point[ix] *= scale;
                point[iy] *= scale;
            }
        }

        for (auto &point: points) {
            point[ix] += ox;
            point[iy] += oy;
        }
    }
};

struct ElementDefinition {
    glm::vec3 from;
    glm::vec3 to;
    tl::optional<RotationDefinition> rotation;
    bool shade;

    std::map<FaceIndex, FaceDefinition> faces;
};

struct RawModelDefinition {
    tl::optional<std::string> parent;
    bool ambientocclusion;
    std::map<std::string, std::string> textures;
    std::vector<ElementDefinition> elements;
};

struct MultipartRule {
    struct Match {
        std::map<std::string, std::string> conditions;
    };
    struct Or {
        std::vector<MultipartRule> rules;
    };
    struct And {
        std::vector<MultipartRule> rules;
    };
    std::variant<Or, And, Match> rule;
};