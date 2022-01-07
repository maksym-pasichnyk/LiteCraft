#include "Definition.hpp"

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <state/Property.hpp>
#include <block/BlockStates.hpp>

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
auto Json::Into<RawModelDefinition>::into(const Json& o) -> Result {
    return RawModelDefinition{
        .parent = o.find("parent"),
        .ambientocclusion = o.value_or("ambientocclusion", false),
        .textures = o.value_or("textures", std::map<std::string, std::string>{}),
        .elements = o.value_or("elements", std::vector<ElementDefinition>{})
    };
}

template<>
auto Json::Into<MultipartRule>::into(Self const& self) -> Result {
    if (auto o = self.find("OR")) {
        return MultipartRule{ .rule = MultipartRule::Or{ .rules = *o } };
    }
    if (auto o = self.find("AND")) {
        return MultipartRule{ .rule = MultipartRule::And{ .rules = *o } };
    }
    return MultipartRule{.rule = MultipartRule::Match { .conditions = self }};
}

template<>
auto Json::Into<Model>::into(const Json& o) -> Result {
    const auto location = o.at("model").as_string().value();
    const auto x = o.value_or("x", 0);
    const auto y = o.value_or("y", 0);
    const auto z = o.value_or("z", 0);

    auto model = Model{};
    const auto raw = RawModels::get(location);

    for (auto&& face : raw->get_faces()) {
        auto vertices = face.vertices;

        const auto rot = [&](int ix, int iy, float angle) {
            const auto origin = glm::vec3(0.5f);
            const auto ox = origin[ix];
            const auto oy = origin[iy];

            const auto s = glm::sin(angle);
            const auto c = glm::cos(angle);

            for (auto& vertex : vertices) {
                const auto x = vertex.pos[ix] - ox;
                const auto y = vertex.pos[iy] - oy;
                vertex.pos[ix] = (y * s + x * c) + ox;
                vertex.pos[iy] = (y * c - x * s) + oy;
            }
        };

        if (x != 0) {
            rot(1, 2, glm::radians(glm::f32(x)));
        }
        if (y != 0) {
            rot(2, 0, glm::radians(glm::f32(y)));
        }
        if (z != 0) {
            rot(1, 0, glm::radians(glm::f32(z)));
        }

        auto texture = raw->get_texture(face.texture);
        if (texture) {
            TextureManager::instance().load_texture(*texture);
        } else {
            spdlog::error("missing texture {} for model {}", face.texture, location);
        }
        model.quads.emplace_back(ModelFace{
            .layer = RenderLayer::Cutout,
            .texture = texture.value_or("missing_texture"),
            .vertices = vertices
        });
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