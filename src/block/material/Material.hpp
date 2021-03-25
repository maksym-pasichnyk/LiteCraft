#pragma once

#include "PushReaction.hpp"
#include "MaterialColors.hpp"

struct Material {
    MaterialColor color = MaterialColors::AIR;
    PushReaction pushReaction = PushReaction::NORMAL;
    bool isBlocksMovement = true;
    bool isReplaceable = false;
    bool isFlammable = false;
    bool isLiquid = false;
    bool isOpaque = true;
    bool isSolid = true;

    struct Builder {
        MaterialColor color;
        PushReaction pushReaction = PushReaction::NORMAL;
        bool isBlocksMovement = true;
        bool isReplaceable = false;
        bool isFlammable = false;
        bool isLiquid = false;
        bool isOpaque = true;
        bool isSolid = true;

        constexpr Builder(MaterialColor color) : color(color) {}

        constexpr Builder& liquid() {
            isLiquid = true;
            return *this;
        }

        constexpr Builder& notSolid() {
            isSolid = false;
            return *this;
        }

        constexpr Builder& doesNotBlockMovement() {
            isBlocksMovement = false;
            return *this;
        }

        constexpr Builder& notOpaque() {
            isOpaque = false;
            return *this;
        }

        constexpr Builder& flammable() {
            isFlammable = true;
            return *this;
        }

        constexpr Builder& replaceable() {
            isReplaceable = true;
            return *this;
        }

        constexpr Builder& pushDestroys() {
            pushReaction = PushReaction::DESTROY;
            return *this;
        }

        constexpr Builder& pushBlocks() {
            pushReaction = PushReaction::BLOCK;
            return *this;
        }

        /*constexpr*/ Material* build() {
            return new Material {
                .color = color,
                .pushReaction = pushReaction,
                .isBlocksMovement = isBlocksMovement,
                .isReplaceable = isReplaceable,
                .isFlammable = isFlammable,
                .isLiquid = isLiquid,
                .isOpaque = isOpaque,
                .isSolid = isSolid
            };
        }
    };
};