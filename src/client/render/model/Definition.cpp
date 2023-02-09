#include "Definition.hpp"

#include <state/Property.hpp>
#include <block/BlockStates.hpp>

template <typename T> struct FromString {
    using Self = std::string;
    using Result = tl::optional<T>;

    static auto from(const Self& s) -> Result;
};

template <typename T> struct IntoString {
    using Value = T;
    using Result = tl::optional<std::string>;

    static auto into(const T& s) -> Result;
};

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
    const auto from = o.at("from").into<glm::vec3>();
    const auto to = o.at("to").into<glm::vec3>();

    return ElementDefinition{
        .from = from,
        .to = to,
        .rotation = o.find("rotation"),
        .shade = o.value_or("shade", false),
        .faces = o.find("faces")
            .and_then([](auto&& o) { return o.as_object(); })
            .map([&](auto&& o) {
                auto out = std::map<Direction, FaceDefinition>{};
                for (auto&& [k, v] : o) {
                    const auto face = FromString<Direction>::from(k).value();
                    out.emplace(face, FaceDefinition{
                        .rotation = v.value_or("rotation", 0),
                        .texture = v.at("texture"),
                        .tintindex = v.value_or("tintindex", -1),
                        .uv = v.find("uv")
                            .map_or_else([](auto&& o) { return o.template into<glm::vec4>(); }, [&] {
                                switch (face) {
                                    case Direction::DOWN:
                                        return glm::vec4(from.x, 16.0f - to.z, to.x, 16.0f - from.z);
                                    case Direction::UP:
                                        return glm::vec4(from.x, from.z, to.x, to.z);
                                    case Direction::NORTH:
                                        return glm::vec4(16.0f - to.x, 16.0f - to.y, 16.0f - from.x, 16.0f - from.y);
                                    case Direction::SOUTH:
                                        return glm::vec4(from.x, 16.0f - to.y, to.x, 16.0f - from.y);
                                    case Direction::WEST:
                                        return glm::vec4(from.z, 16.0f - to.y, to.z, 16.0f - from.y);
                                    case Direction::EAST:
                                        return glm::vec4(16.0f - to.z, 16.0f - to.y, 16.0f - from.z, 16.0f - from.y);
                                }
                                return glm::vec4(16.0f - to.x, 16.0f - to.y, 16.0f - from.x, 16.0f - from.y);
                            }),
                        .cullface = v.find("cullface").and_then(Json::Into<Direction>::into),
                    });
                }
                return out;
            })
            .value_or(std::map<Direction, FaceDefinition>{})
    };
}

template<>
auto Json::Into<RawModelDefinition>::into(const Json& o) -> Result {
    return RawModelDefinition{
        .parent = o.find("parent").and_then([](auto&& o) { return o.as_string(); }),
        .ambientocclusion = o.value_or("ambientocclusion", false),
        .textures = o.value_or("textures", std::map<std::string, std::string>{}),
        .elements = o.value_or("elements", std::vector<ElementDefinition>{})
    };
}

template<>
auto Json::Into<MultipartRule>::into(Self const& self) -> Result {
    if (auto o = self.find("OR")) {
        return MultipartRule{ .rule = MultipartRule::Or{ .rules = o->into<std::vector<MultipartRule>>() } };
    }
    if (auto o = self.find("AND")) {
        return MultipartRule{ .rule = MultipartRule::And{ .rules = o->into<std::vector<MultipartRule>>() } };
    }
    return MultipartRule{.rule = MultipartRule::Match { .conditions = self.into<std::map<std::string, std::string>>() }};
}

struct ModelRotation {
    glm::quat transform;

    static auto from(glm::i32 x, glm::i32 y) -> ModelRotation {
        const auto a = glm::angleAxis(-glm::radians(glm::f32(y)), glm::vec3(0, 1, 0));
        const auto b = glm::angleAxis(-glm::radians(glm::f32(x)), glm::vec3(1, 0, 0));
        return { .transform = a * b };
    }

    auto rotate(const glm::vec3& p) const -> glm::vec3 {
        return transform * p;
    }

    auto rotate(Direction direction) const -> Direction {
        const auto norm = transform * glm::vec3(DirectionUtil::getOffset(direction));
        auto dist = std::numeric_limits<glm::f32>::min();
        auto out = Direction::NORTH;
        for (auto dir : DirectionUtil::VALUES) {
            const auto v = glm::dot(norm, glm::vec3(DirectionUtil::getOffset(dir)));
            if (v > dist) {
                dist = v;
                out = dir;
            }
        }
        return out;
    }
};

template<>
auto Json::Into<Model>::into(const Json& o) -> Result {
    const auto location = o.at("model").as_string().value();
    const auto rotation = ModelRotation::from(
        o.value_or("x", 0),
        o.value_or("y", 0)
    );

    auto model = Model{};
    const auto raw = RawModels::get(location);

    for (auto&& face : raw->get_faces()) {
        auto vertices = face.vertices;
        for (auto& vertex : vertices) {
            vertex.pos = rotation.rotate(vertex.pos - 0.5f) + 0.5f;
        }
        const auto texture = raw->get_texture(face.texture);
        if (texture) {
            TextureManager::instance().load_texture(*texture);
        } else {
            spdlog::error("missing texture {} for model {}", face.texture, location);
        }
        const auto cullface = face.cullface.map([rotation](Direction direction) {
            return rotation.rotate(direction);
        });

        if (cullface.has_value()) {
            model.faces[*cullface].emplace_back(ModelFace{
                .texture = texture.value_or("missing_texture"),
                .vertices = vertices
            });
        } else {
            model.quads.emplace_back(ModelFace{
                .texture = texture.value_or("missing_texture"),
                .vertices = vertices
            });
        }
    }
    return model;
}
template<>
auto Json::Into<Multipart>::into(const Json& o) -> Result {
    return Multipart{
        .apply = o.at("apply"),
        .when = o.find("when").and_then(Json::Into<MultipartRule>::into),
    };
}

template<>
auto Json::Into<BlockState>::into(const Json& o) -> Result {
    return BlockState{
        .variants = o.find("variants")
            .and_then([] (auto&& o) { return o.as_object(); })
            .map_or([](auto&& o) {
                auto out = std::vector<Variant>{};
                for (auto&& [k, v] : o) {
                    out.emplace_back(Variant{
                        .rule = VariantRule::from(k),
                        .models = v
                    });
                }
                return out;
            }, std::vector<Variant>{}),
        .multiparts = o.value_or("multipart", std::vector<Multipart>{})
    };
}