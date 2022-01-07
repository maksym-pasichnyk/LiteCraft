#pragma once

#include <util/Registry.hpp>
#include <state/Property.hpp>
#include <block/BlockData.hpp>
#include <client/render/RawModels.hpp>
#include <client/render/Definition.hpp>
#include "AbstractBlock.hpp"

struct ModelFace {
    RenderLayer layer;
    std::string texture;
    std::array<RawVertex, 4> vertices;
};

struct Model {
    std::vector<ModelFace> quads;
};
struct VariantRule {
    std::vector<std::pair<std::string, std::string>> properties;

    auto check(BlockData state) const -> bool {
        return cpp_iter(properties).all([state](auto& rule) {
            return PropertyUtil::string(state.get(rule.first)).value() == rule.second;
        });
    }

    static auto from(const std::string& str) -> VariantRule {
        return VariantRule{
            .properties = cpp_iter(str)
                .split(',')
                .map(ranges::to<std::string>())
                .map([](auto&& s) {
                    const auto pos = s.find('=');
                    return std::pair{ s.substr(0, pos), s.substr(pos + 1), };
                })
                .collect()
        };
    }
};

struct Variant {
    VariantRule rule;
    std::vector<Model> models;
};

struct Multipart {
    std::vector<Model> apply;
    tl::optional<MultipartRule> when;
};

struct BlockState {
    std::vector<Variant> variants;
    std::vector<Multipart> multiparts;

    [[nodiscard]] auto get_model(BlockData state) const -> const Model * {
        for (auto& multipart : multiparts) {
            return &multipart.apply.at(0);
        }
        for (auto& variant : variants) {
            if (variant.rule.check(state)) {
                return &variant.models.at(0);
            }
        }
        return nullptr;
    }
};

struct BlockStates {
    static DynamicRegistry<Block*, BlockState> states;

    static void init();

    static auto get(Block* const& block) -> BlockState* {
        return states.get(block).value_or(nullptr);
    }
};