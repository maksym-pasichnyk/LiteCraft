#include "RawModels.hpp"
#include "Definition.hpp"
#include "FaceInfo.hpp"

#include <array>
#include <Json.hpp>
#include <ResourceManager.hpp>

static auto MISSING_MODEL_MESH = R"({
    "textures": {
        "particle": "missingno",
        "missingno": "missingno"
    },
    "elements": [
        {
            "from": [ 0, 0, 0 ],
            "to": [ 16, 16, 16 ],
            "faces": {
                "down":  { "uv": [ 0, 0, 16, 16 ], "cullface": "down",  "texture": "#missingno" },
                "up":    { "uv": [ 0, 0, 16, 16 ], "cullface": "up",    "texture": "#missingno" },
                "north": { "uv": [ 0, 0, 16, 16 ], "cullface": "north", "texture": "#missingno" },
                "south": { "uv": [ 0, 0, 16, 16 ], "cullface": "south", "texture": "#missingno" },
                "west":  { "uv": [ 0, 0, 16, 16 ], "cullface": "west",  "texture": "#missingno" },
                "east":  { "uv": [ 0, 0, 16, 16 ], "cullface": "east",  "texture": "#missingno" }
            }
        }
    ]
})";

Registry<RawModel> RawModels::models;

struct RawElementRotation {
    glm::vec3 scale;
    glm::vec3 origin;
    glm::quat transform;

    static auto from(const RotationDefinition& definition) -> RawElementRotation {
        const auto axis = [axis = definition.axis] {
            switch (axis) {
                case DirectionAxis::X: return glm::vec3(1, 0, 0);
                case DirectionAxis::Y: return glm::vec3(0, 1, 0);
                case DirectionAxis::Z: return glm::vec3(0, 0, 1);
            }
            return glm::vec3(0);
        }();
        const auto rescale = definition.rescale ? 1.0f / glm::cos(glm::abs(glm::radians(definition.angle))) : 1.0f;
        return {
            .scale = glm::mix(axis, glm::vec3(1.0f), rescale),
            .origin = definition.origin,
            .transform = glm::angleAxis(glm::radians(definition.angle), axis),
        };
    }

    auto rotate(const glm::vec3& pos) const -> glm::vec3 {
        return transform * (pos - origin) * scale + origin;
    }
};

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

        auto shape = std::array<glm::f32, 6>{};
        shape[FaceInfo::Constants::MIN_X] = from.x;
        shape[FaceInfo::Constants::MIN_Y] = from.y;
        shape[FaceInfo::Constants::MIN_Z] = from.z;
        shape[FaceInfo::Constants::MAX_X] = to.x;
        shape[FaceInfo::Constants::MAX_Y] = to.y;
        shape[FaceInfo::Constants::MAX_Z] = to.z;

        const auto rotation = element.rotation.map(RawElementRotation::from);

        for (auto&& [face, v] : element.faces) {
            auto xyz = std::array<glm::vec3, 4>{};
            for (auto i = size_t(0); i < 4; ++i) {
                auto&& info = FaceInfos::get(face).info[i];
                xyz[i] = glm::vec3(
                    shape[info.xFace],
                    shape[info.yFace],
                    shape[info.zFace]
                );
                if (rotation.has_value()) {
                    xyz[i] = rotation->rotate(xyz[i]);
                }
            }
            const auto uvs = [&v = v] {
                switch ((v.rotation / 90) % 4) {
                    default:
                    case 0: return std::array{
                        glm::vec2(v.uv.x, v.uv.y),
                        glm::vec2(v.uv.x, v.uv.w),
                        glm::vec2(v.uv.z, v.uv.w),
                        glm::vec2(v.uv.z, v.uv.y)
                    };
                    case 1: return std::array{
                        glm::vec2(v.uv.x, v.uv.w),
                        glm::vec2(v.uv.z, v.uv.w),
                        glm::vec2(v.uv.z, v.uv.y),
                        glm::vec2(v.uv.x, v.uv.y)
                    };
                    case 2: return std::array{
                        glm::vec2(v.uv.z, v.uv.w),
                        glm::vec2(v.uv.z, v.uv.y),
                        glm::vec2(v.uv.x, v.uv.y),
                        glm::vec2(v.uv.x, v.uv.w)
                    };
                    case 3: return std::array{
                        glm::vec2(v.uv.z, v.uv.y),
                        glm::vec2(v.uv.x, v.uv.y),
                        glm::vec2(v.uv.x, v.uv.w),
                        glm::vec2(v.uv.z, v.uv.w)
                    };
                }
            }();
            const auto vertices = std::array{
                RawVertex{xyz[0] / 16.0f, uvs[0] / 16.0f},
                RawVertex{xyz[1] / 16.0f, uvs[1] / 16.0f},
                RawVertex{xyz[2] / 16.0f, uvs[2] / 16.0f},
                RawVertex{xyz[3] / 16.0f, uvs[3] / 16.0f}
            };
            model->faces.emplace_back(RawFace{
                .texture = v.texture,
                .cullface = v.cullface,
                .vertices = vertices
            });
        }
    }
    return models.add(name, std::move(model));
}