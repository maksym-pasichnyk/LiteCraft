#include "Models.hpp"
#include "ModelFormat.hpp"

#include <iostream>
#include <Json.hpp>
#include <spdlog/spdlog.h>
#include <range/v3/all.hpp>
#include <ResourceManager.hpp>

using namespace std::string_literals;
using namespace std::string_view_literals;

template <>
struct Json::Into<glm::vec3> {
    static auto into(const Json& obj) -> std::optional<glm::vec3> {
        auto&& o = obj.to_array();
        return glm::vec3{
            static_cast<float>(o[0].to_f64()),
            static_cast<float>(o[1].to_f64()),
            static_cast<float>(o[2].to_f64())
        };
    }
};

template <>
struct Json::Into<glm::vec2> {
    static auto into(const Json& obj) -> std::optional<glm::vec2> {
        auto&& o = obj.to_array();
        return glm::vec2{
            static_cast<float>(o[0].to_f64()),
            static_cast<float>(o[1].to_f64())
        };
    }
};

Registry<ModelFormat> Models::models;

void Models::parse(const Json& obj) {
    auto&& geometries = obj.to_object();
    auto&& format_version = geometries.at("format_version").to_string();

    if (format_version == "1.8.0"sv || format_version == "1.10.0"sv) {
        for (auto&& [name, geometry] : geometries) {
            if (!name.starts_with("geometry.")) { continue; }

            auto model_format = std::make_unique<ModelFormat>();
            auto delim = name.find_first_of(':');
            if (delim != std::string::npos) {
                model_format->name = name.substr(0, delim);
                model_format->parent = name.substr(delim + 1);
            } else {
                model_format->name = name.substr(0);
            }
            if (geometry.contains("bones")) {
                model_format->bones = geometry.at("bones").to_array() | ranges::views::transform([](auto&& bone) {
                    auto&& bone_name = bone.at("name").to_string();
                    return std::pair{bone_name, std::make_unique<ModelBoneFormat>(ModelBoneFormat{
                        .name = bone_name,
                        .pivot = bone.value_or("pivot", glm::vec3{}),
                        .never_render = bone.value_or("neverRender", false),
                        .mirror = bone.value_or("mirror", false),
                        .reset = bone.value_or("reset", false),
                        .cubes = bone.contains("cubes")
                             ? bone.at("cubes").to_array() | ranges::views::transform([](auto&& cube) {
                                   return ModelCubeFormat{
                                       .origin = cube.at("origin"),
                                       .size = cube.at("size"),
                                       .tex = cube.value_or("uv", glm::vec2{16, 16})
                                   };
                               }) | ranges::to_vector
                             : std::vector<ModelCubeFormat>{}
                    })};
                }) | ranges::to<std::map<std::string, std::unique_ptr<ModelBoneFormat>>>();
            }

            models.add(model_format->name, std::move(model_format));
        }
    } else if (format_version == "1.12.0"sv || format_version == "1.16.0"sv) {
        for (auto&& geometry : geometries.at("minecraft:geometry").to_array()) {
            auto&& description = geometry.at("description");

            auto model_format = std::make_unique<ModelFormat>();

            model_format->name = description.at("identifier").to_string();
            model_format->visible_bounds_width = description.value_or("visible_bounds_width", 0);
            model_format->visible_bounds_height = description.value_or("visible_bounds_height", 0);
            model_format->texture_width = description.value_or("texture_width", 64);
            model_format->texture_height = description.value_or("texture_height", 64);

            if (geometry.contains("bones")) {
                model_format->bones = geometry.at("bones").to_array() | ranges::views::transform([](auto&& bone) {
                    auto&& bone_name = bone.at("name").to_string();
                    return std::pair{bone_name, std::make_unique<ModelBoneFormat>(ModelBoneFormat{
                        .name = bone_name,
                        .pivot = bone.value_or("pivot", glm::vec3{}),
                        .never_render = bone.value_or("neverRender", false),
                        .mirror = bone.value_or("mirror", false),
                        .reset = bone.value_or("reset", false),
                        .cubes = bone.contains("cubes")
                            ? bone.at("cubes").to_array() | ranges::views::transform([](auto&& cube) {
                                return ModelCubeFormat{
                                    .origin = cube.at("origin"),
                                    .rotation = cube.value_or("rotation", glm::vec3{}),
                                    .size = cube.at("size"),
                                    .tex = cube.contains("uv")
                                        ? cube.at("uv").is_array()
                                            ? ModelTexFormat{static_cast<glm::vec2>(cube.at("uv"))}
                                            : ModelTexFormat{cube.at("uv").to_object() | ranges::views::transform([](auto&& element) {
                                                return std::pair{element.first, ModelFaceFormat{
                                                    .uv = element.second.at("uv")
                                                }};
                                            }) | ranges::to<std::unordered_map<std::string, ModelFaceFormat>>()}
                                        : ModelTexFormat{glm::vec2{16, 16}}
                                };
                            }) | ranges::to_vector
                            : std::vector<ModelCubeFormat>{}
                    })};
                }) | ranges::to<std::map<std::string, std::unique_ptr<ModelBoneFormat>>>();
            }

            models.add(model_format->name, std::move(model_format));
        }
    } else {
        std::cerr << fmt::format("Unknown model format: {}", format_version) << std::endl;
    }
}

void Models::init(ResourceManager& resources) {
    resources.enumerate("models", [](std::istream& stream) {
        parse(Json::Read::read(stream).value());
    });
}