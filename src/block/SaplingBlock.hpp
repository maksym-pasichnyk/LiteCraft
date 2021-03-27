#pragma once

#include "Block.hpp"

struct Tree {
    virtual ~Tree() = default;
};
struct OakTree : Tree {};
struct SpruceTree : Tree {};
struct BirchTree : Tree {};
struct JungleTree : Tree {};
struct AcaciaTree : Tree {};
struct DarkOakTree : Tree {};

struct SaplingBlock : Block {
    SaplingBlock(int id, Tree* tree, Properties properties) : Block(id, std::move(properties)) {}
};