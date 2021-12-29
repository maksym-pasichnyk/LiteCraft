#pragma once

#include <TextureAtlas.hpp>
#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <map>
#include <string>
#include <tl/optional.hpp>
#include <util/Registry.hpp>
#include <vector>

struct RawVertex {
    glm::vec3 pos;
    glm::vec2 uv;
};

struct RawFace {
    std::string texture;
    std::array<RawVertex, 4> vertices;
};

struct RawModel {
    RawModel* parent;
    std::vector<RawFace> faces;
    std::map<std::string, std::string> textures;

    [[nodiscard]] auto get_faces() const -> std::span<const RawFace> {
        return faces.empty() && parent ? parent->get_faces() : std::span(faces);
    }

    [[nodiscard]] auto get_texture(const std::string& name) const -> tl::optional<std::string> {
        auto texture = name;
        while (texture.starts_with('#')) {
            auto ref = get_texture_lookup(texture.substr(1));
            if (!ref) {
                return tl::nullopt;
            }
            texture = *ref;
        }
        return texture;
    }

    [[nodiscard]] auto get_texture_lookup(const std::string& name) const -> tl::optional<const std::string&> {
        for (auto model = this; model != nullptr; model = model->parent) {
            if (auto it = model->textures.find(name); it != model->textures.end()) {
                return it->second;
            }
        }
        return tl::nullopt;
    }
};

struct Model {
    std::vector<RawFace> quads;
};

struct RawModels {
    static Registry<RawModel> models;

    static auto get(const std::string& name) -> RawModel*;
};