#pragma once

#include "block/BlockData.hpp"

#include <variant>

struct BlockMatchRuleTest {
    Block* block;

    bool test(BlockData state, Random& random) const {
        return state.isIn(block);
    }
};
struct RandomBlockMatchRuleTest {
    Block* block;
    float probability;

    bool test(BlockData state, Random& random) const {
        return state.isIn(block) && random.nextFloat() < probability;
    }
};

struct BlockStateMatchRuleTest {
    BlockData block_state;

    bool test(BlockData state, Random& random) const {
        return block_state == state;
    }
};

struct RandomBlockStateMatchRuleTest {
    BlockData block_state;
    float probability;

    bool test(BlockData state, Random& random) const {
        return block_state == state && random.nextFloat() < probability;
    }
};

struct TagMatchRuleTest {
    BlockTag tag;

    bool test(BlockData state, Random& random) const {
        return state.isIn(tag);
    }
};

struct AlwaysTrueRuleTest {
    bool test(BlockData state, Random& random) const {
        return true;
    }
};

using RuleTest = std::variant<
    AlwaysTrueRuleTest,
    BlockMatchRuleTest,
    BlockStateMatchRuleTest,
    RandomBlockMatchRuleTest,
    RandomBlockStateMatchRuleTest,
    TagMatchRuleTest
>;

struct RuleTestUtil {
    static bool test(const RuleTest& rule, BlockData state, Random& random) {
        return std::visit([state, &random]<typename T>(const T& rule) { return rule.test(state, random); }, rule);
    }
};

struct OreFeatureConfig {
    RuleTest target;
    BlockData state;
    int size;
};