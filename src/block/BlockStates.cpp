#include "BlockStates.hpp"
#include "Blocks.hpp"
#include "Block.hpp"

#include <TextureAtlas.hpp>
#include <ResourceManager.hpp>
#include <client/render/RawModels.hpp>
#include <client/render/Definition.hpp>

DynamicRegistry<Block*, BlockState> BlockStates::states;

static auto parseRule(Block* block, const std::string& str) -> tl::optional<Variant::Rule> {
    const auto i = str.find('=');
    if (!block->properties.contains(str.substr(0, i))) {
        return tl::nullopt;
    }
    const auto prop = block->properties.at(str.substr(0, i));
    auto value = PropertyUtil::parse(prop, str.substr(i + 1));
    if (!value.has_value()) {
        return tl::nullopt;
    }
    return Variant::Rule{ prop, *value };
}

static auto parseRules(Block* block, const std::string& props) -> tl::optional<std::vector<Variant::Rule>> {
    std::vector<Variant::Rule> rules;
    if (!props.empty()) {
        auto pos = size_t(0);
        auto start = size_t(0);
        while ((pos = props.find(',', start)) != std::string::npos) {
            auto rule = parseRule(block, props.substr(start, pos - start));
            if (!rule.has_value()) {
                return tl::nullopt;
            }
            rules.emplace_back(*rule);
            start = pos + 1;
        }

        auto rule = parseRule(block, props.substr(start, pos));
        if (!rule.has_value()) {
            return tl::nullopt;
        }
        rules.emplace_back(*rule);
    }
    return rules;
}

static auto modelFromVariant(const VariantDefinition& definition) -> Model {
    auto model = Model{};

    const auto raw = RawModels::get(definition.model);

    auto& resources = *ResourceManager::mGlobalResourcePack;
    auto& textures = TextureManager::instance();

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

        if (definition.x != 0) {
            rot(2, 1, glm::radians(glm::f32(definition.x)));
        }
        if (definition.y != 0) {
            rot(0, 2, glm::radians(glm::f32(definition.y)));
        }
        if (definition.z != 0) {
            rot(1, 0, glm::radians(glm::f32(definition.z)));
        }

        auto texture = raw->get_texture(face.texture);
        if (texture) {
            textures.load_texture(resources, *texture);
        } else {
            spdlog::error("missing texture {} for model {}", face.texture, definition.model);
        }

        model.quads.emplace_back(RawFace{
            .texture = texture.value_or("missing_texture"),
            .vertices = vertices
        });
    }
    return model;
}

void BlockStates::init() {
    auto& resources = *ResourceManager::mGlobalResourcePack;
    auto& textures = TextureManager::instance();

    for (auto&& [name, block] : Blocks::blocks.objects) {
        auto o = ResourceManager::mGlobalResourcePack->open(fmt::format("assets/minecraft/blockstates/{}.json", name))
             .and_then([](auto&& resource) { return Json::Read::read(*resource.io); })
             .map([](const Json& o) { return o.into<BlockStateDefinition>(); })
             .value();

        auto state = std::make_unique<BlockState>();
        for (auto&& multipart : o.multiparts) {
            state->multipart.emplace_back(Variant{
                .parts = ranges::to_vector(ranges::views::transform(multipart.apply, modelFromVariant)),
//                .rules = std::move(*rules)
            });
        }

        for (auto&& [props, variant] : o.variants) {
            auto rules = parseRules(block, props);
            if (!rules.has_value()) {
                continue;
            }
            state->variants.emplace_back(Variant{
                .parts = ranges::to_vector(ranges::views::transform(variant, modelFromVariant)),
                .rules = std::move(*rules)
            });
        }
        states.add(block, std::move(state));
    }
    textures.build();
    textures.upload();
}