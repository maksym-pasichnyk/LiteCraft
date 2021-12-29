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
};

struct ElementDefinition {
    glm::vec3 from;
    glm::vec3 to;
    tl::optional<RotationDefinition> rotation;
    bool shade;

    std::map<FaceIndex, FaceDefinition> faces;
};

struct ModelDefinition {
    tl::optional<std::string> parent;
    bool ambientocclusion;
    std::map<std::string, std::string> textures;
    std::vector<ElementDefinition> elements;
};

struct VariantDefinition {
    std::string model;
    int x = 0;
    int y = 0;
    int z = 0;
};

struct MultipartRuleDefinition : std::variant<std::pair<std::string, std::vector<std::string>>, std::vector<std::vector<MultipartRuleDefinition>>> {
    using variant::variant;
};

struct MultipartDefinition {
    std::vector<MultipartRuleDefinition> rules;
    std::vector<VariantDefinition> apply;
};

struct BlockStateDefinition {
    std::vector<MultipartDefinition> multiparts;
    std::map<std::string, std::vector<VariantDefinition>> variants;
};