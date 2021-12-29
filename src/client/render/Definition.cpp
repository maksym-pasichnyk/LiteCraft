#include "Definition.hpp"

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <state/Property.hpp>

template <>
auto Json::Into<FaceIndex>::into(const Json& o) -> Result {
    auto&& s = o.as_string().value();
    if (s == "south") {
        return FaceIndex::South;
    }
    if (s == "north") {
        return FaceIndex::North;
    }
    if (s == "east") {
        return FaceIndex::East;
    }
    if (s == "west") {
        return FaceIndex::West;
    }
    if (s == "up") {
        return FaceIndex::Up;
    }
    if (s == "down") {
        return FaceIndex::Down;
    }
    return tl::nullopt;
}

template <>
auto Json::Into<glm::vec2>::into(const Json& obj) -> Result {
    return obj.as_array().map([](auto&& o) {
        return glm::vec2{
            static_cast<glm::f32>(o.at(0)),
            static_cast<glm::f32>(o.at(1))
        };
    });
}

template <>
auto Json::Into<glm::vec3>::into(const Json& obj) -> Result {
    return obj.as_array().map([](auto&& o) {
        return glm::vec3{
            static_cast<glm::f32>(o.at(0)),
            static_cast<glm::f32>(o.at(1)),
            static_cast<glm::f32>(o.at(2))
        };
    });
}

template <>
auto Json::Into<glm::vec4>::into(const Json& obj) -> Result {
    return obj.as_array().map([](auto&& o) {
        return glm::vec4{
            static_cast<glm::f32>(o.at(0)),
            static_cast<glm::f32>(o.at(1)),
            static_cast<glm::f32>(o.at(2)),
            static_cast<glm::f32>(o.at(3))
        };
    });
}

template<>
auto Json::Into<FaceDefinition>::into(const Json &o) -> Result {
    return FaceDefinition{
//        .cullface = o.find("cullface").map([](const Json& o) {
//            return o.into<FaceIndex>();
//        }),
        .rotation = o.value_or("rotation", 0),
        .texture = o.at("texture"),
        .tintindex = o.value_or("tintindex", -1),
        .uv = o.find("uv")
    };
}

template<>
auto Json::Into<RotationDefinition>::into(const Json &o) -> Result {
    return RotationDefinition{
        .angle = o.at("angle"),
        .axis = o.at("axis"),
        .origin = o.at("origin"),
        .rescale = o.value_or("rescale", false)
    };
}

template<>
auto Json::Into<ElementDefinition>::into(const Json &o) -> Result {
    return ElementDefinition{
        .from = o.at("from"),
        .to = o.at("to"),
        .rotation = o.find("rotation"),
        .shade = o.value_or("shade", false),
        .faces = o.value_or("faces", std::map<FaceIndex, FaceDefinition>{})
    };
}

template<>
auto Json::Into<ModelDefinition>::into(const Json& o) -> Result {
    return ModelDefinition{
        .parent = o.find("parent"),
        .ambientocclusion = o.value_or("ambientocclusion", false),
        .textures = o.value_or("textures", std::map<std::string, std::string>{}),
        .elements = o.value_or("elements", std::vector<ElementDefinition>{})
    };
}

template<>
auto Json::Into<VariantDefinition>::into(const Json& o) -> Result {
    return VariantDefinition{
        .model = o.at("model"),
        .x = o.value_or("x", 0),
        .y = o.value_or("y", 0),
        .z = o.value_or("z", 0)
    };
}

static auto splitString(const std::string& str, char delim) -> std::vector<std::string> {
    auto out = std::vector<std::string>{};

    auto pos = size_t(0);
    auto start = size_t(0);
    while ((pos = str.find(delim, start)) != std::string::npos) {
        out.emplace_back(str.substr(start, pos - start));
        start = pos + 1;
    }
    out.emplace_back(str.substr(start, pos));
    return out;
}

static auto rulesFromJson(const Json& o) -> std::vector<MultipartRuleDefinition> {
    auto rules = std::vector<MultipartRuleDefinition>{};

    for (auto&& [name, val] : o.as_object().value()) {
        if (name == "OR") {
            auto or_rules = std::vector<std::vector<MultipartRuleDefinition>>{};
            for (auto&& sub : val.as_array().value()) {
                or_rules.emplace_back(rulesFromJson(sub));
            }
            rules.emplace_back(std::move(or_rules));
        } else {
            rules.emplace_back(std::pair{name, splitString(val.as_string().value(), '|')});
        }
    }
    return rules;
}

template<>
auto Json::Into<MultipartDefinition>::into(const Json& o) -> Result {
    return MultipartDefinition{
        .rules = o.find("when").map_or(rulesFromJson, std::vector<MultipartRuleDefinition>{}),
        .apply = o.at("apply")
    };
}

template<>
auto Json::Into<BlockStateDefinition>::into(const Json& o) -> Result {
    return BlockStateDefinition{
        .multiparts = o.value_or("multipart", std::vector<MultipartDefinition>{}),
        .variants = o.value_or("variants", std::map<std::string, std::vector<VariantDefinition>>{})
    };
}