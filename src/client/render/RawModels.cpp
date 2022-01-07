#include "RawModels.hpp"
#include "Definition.hpp"

#include <Json.hpp>
#include <glm/glm.hpp>
#include <ResourceManager.hpp>

Registry<RawModel> RawModels::models;

auto RawModels::get(const std::string& name) -> RawModel* {
    if (auto cache = models.get(name)) {
        return *cache;
    }

    const auto location = ResourceLocation::from(name);

    auto o = Resources::open(fmt::format("assets/{}/models/{}.json", location.get_namespace(), location.get_location()))
         .and_then([](auto&& resource) { return Json::Read::read(*resource); })
         .and_then(Json::Into<RawModelDefinition>::into)
         .value();

    auto model = std::make_unique<RawModel>();
    model->parent = o.parent.map(get).value_or(nullptr);
    model->textures = o.textures;

    for (auto&& element : o.elements) {
        const auto from = element.from;
        const auto to = element.to;

        auto points = std::array {
            glm::vec3(from.x, from.y, from.z),
            glm::vec3(from.x,   to.y, from.z),
            glm::vec3(  to.x,   to.y, from.z),
            glm::vec3(  to.x, from.y, from.z),

            glm::vec3(  to.x, from.y, to.z),
            glm::vec3(  to.x,   to.y, to.z),
            glm::vec3(from.x,   to.y, to.z),
            glm::vec3(from.x, from.y, to.z),
        };
        element.rotation.map([&points](auto&& self) {
            self.rotate(points);
        });

        const auto vertices = std::array{
            std::array{points[3], points[4], points[7], points[0]},
            std::array{points[5], points[2], points[1], points[6]},
            std::array{points[0], points[1], points[2], points[3]},
            std::array{points[4], points[5], points[6], points[7]},
            std::array{points[7], points[6], points[1], points[0]},
            std::array{points[3], points[2], points[5], points[4]},
        };

        for (auto&& [face, v] : element.faces) {
            const auto uv = v.uv.map_or_else([](auto uv) { return uv; }, [&, face = face] {
                switch (face) {
                    case FaceIndex::South: case FaceIndex::North:
                        return glm::vec4(from[0], from[1], to[0], to[1]);
                    case FaceIndex::East: case FaceIndex::West:
                        return glm::vec4(from[2], from[1], to[2], to[1]);
                    case FaceIndex::Up: case FaceIndex::Down:
                        return glm::vec4(from[0], from[2], to[0], to[2]);
                }
            });

            const auto xyz = std::array{
                vertices[size_t(face)][0] / 16.0f,
                vertices[size_t(face)][1] / 16.0f,
                vertices[size_t(face)][2] / 16.0f,
                vertices[size_t(face)][3] / 16.0f
            };
            auto uvs = std::array {
                glm::vec2(uv.x, uv.w),
                glm::vec2(uv.x, uv.y),
                glm::vec2(uv.z, uv.y),
                glm::vec2(uv.z, uv.w),
            };
//            for (int i = 0; i < v.rotation; i += 90) {
//                uvs = std::array {
//                    glm::vec2(uvs[3].x, uvs[3].y),
//                    glm::vec2(uvs[0].x, uvs[0].y),
//                    glm::vec2(uvs[1].x, uvs[1].y),
//                    glm::vec2(uvs[2].x, uvs[2].y)
//                };
//            }

            model->faces.emplace_back(RawFace{
                .texture = v.texture,
                .vertices = std::array{
                    RawVertex{xyz[0], uvs[0] / 16.0f},
                    RawVertex{xyz[1], uvs[1] / 16.0f},
                    RawVertex{xyz[2], uvs[2] / 16.0f},
                    RawVertex{xyz[3], uvs[3] / 16.0f}
                }
            });
        }
    }
    return models.add(name, std::move(model));
}