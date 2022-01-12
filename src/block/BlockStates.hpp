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

    auto join(const Model& model) const -> Model {
        auto out = *this;
        for (auto&& quad : model.quads) {
            out.quads.emplace_back(quad);
        }
        return out;
    }
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

    auto check(BlockData state) const -> bool {
        return when.map_or([state](const MultipartRule& rule) -> bool {
            return eval(rule, state);
        }, true);
    }

    static auto eval(const MultipartRule& rule, BlockData state) -> bool {
        return match(rule.rule,
            [state](const MultipartRule::Or& rule) {
                return cpp_iter(rule.rules).any([state](auto&& rule) {
                    return eval(rule, state);
                });
            },
            [state](const MultipartRule::And& rule) {
                return cpp_iter(rule.rules).all([state](auto&& rule) {
                    return eval(rule, state);
                });
            },
            [state](const MultipartRule::Match& rule) {
                for (auto&& [k, v] : rule.conditions) {
                    const auto prop = PropertyUtil::string(state.get(k)).value();
                    const auto flag = cpp_iter(v)
                        .split('|')
                        .map(ranges::to<std::string>())
                        .any([&prop](auto&& s) {
                            return s == prop;
                        });
                    if (!flag) {
                        return false;
                    }
                }
                return true;
            }
        );
    }
};

static thread_local auto MULTIPART_CACHE = std::map<BlockData, Model>{};

struct BlockState {
    std::vector<Variant> variants;
    std::vector<Multipart> multiparts;

    [[nodiscard]] auto get_model(BlockData state) const -> const Model * {
        if (auto it = MULTIPART_CACHE.find(state); it != MULTIPART_CACHE.end()) {
            return &it->second;
        }
        MULTIPART_CACHE.emplace(state, [this, state] {
            if (multiparts.empty()) {
                for (auto& variant : variants) {
                    if (variant.rule.check(state)) {
                        return variant.models.at(0);
                    }
                }
            }
            auto model = tl::optional<Model>{};
            for (auto& multipart : multiparts) {
                if (!multipart.check(state)) {
                    continue;
                }
                model = model ? model->join(multipart.apply.at(0)) : multipart.apply.at(0);
            }
            return model.value_or(Model{});
        }());
        return &MULTIPART_CACHE.at(state);
    }
};

struct BlockStates {
    static DynamicRegistry<Block*, BlockState> states;

    static void init();

    static auto get(Block* const& block) -> BlockState* {
        return states.get(block).value_or(nullptr);
    }
};