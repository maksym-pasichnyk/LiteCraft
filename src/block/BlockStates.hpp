#pragma once

#include <util/Registry.hpp>
#include <state/Property.hpp>
#include <block/BlockData.hpp>
#include <client/render/RawModels.hpp>

struct Variant {
    struct Rule {
        Property property;
        PropertyValue value;

        [[nodiscard]] auto check(BlockData state) const -> bool {
            return state.has(property) && (state.get(property) == value);
        }
    };

    std::vector<Model> parts;
    std::vector<Rule> rules;

    [[nodiscard]] auto check(BlockData state) const -> bool {
        return ranges::all_of(rules, [state](auto& test) {
            return test.check(state);
        });
    }

    [[nodiscard]] auto get_model() const -> const Model& {
        return parts.at(0);
    }
};

struct BlockState {
    std::vector<Variant> multipart;
    std::vector<Variant> variants;

    [[nodiscard]] auto get_variant(BlockData state) const -> const Variant* {
        for (auto& variant : multipart) {
            if (variant.check(state)) {
                return &variant;
            }
        }
        for (auto& variant : variants) {
            if (variant.check(state)) {
                return &variant;
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