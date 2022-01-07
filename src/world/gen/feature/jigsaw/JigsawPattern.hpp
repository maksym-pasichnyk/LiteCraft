#pragma once

#include <vector>
#include <string>
#include <memory>
#include <random>
#include <util/Random.hpp>
#include <range/v3/view.hpp>

struct JigsawElement;
struct JigsawPattern {
    std::string location;
    std::string fallback;
    std::vector<JigsawElement *> pieces;
    std::vector<std::pair<std::unique_ptr<JigsawElement>, int>> elements;

    auto getJigsawPieces(Random& random) const -> std::vector<JigsawElement*> {
        auto new_pieces = pieces;
        random.shuffle(std::span(new_pieces));
        return new_pieces;
    }
};