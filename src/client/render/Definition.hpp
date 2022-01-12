#pragma once

#include <map>
#include <string>
#include <vector>
#include <Json.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <tl/optional.hpp>
#include <util/Direction.hpp>

struct FaceDefinition {
    int rotation;
    std::string texture;
    tl::optional<int> tintindex;
    tl::optional<glm::vec4> uv;
    tl::optional<Direction> cullface;
};

struct RotationDefinition {
    float angle;
    DirectionAxis axis;
    glm::vec3 origin;
    bool rescale;
};

struct ElementDefinition {
    glm::vec3 from;
    glm::vec3 to;
    tl::optional<RotationDefinition> rotation;
    bool shade;

    std::map<Direction, FaceDefinition> faces;
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