#pragma once

#include <vector>
#include <string>
#include <memory>

struct JigsawPiece;
struct JigsawPattern {
    std::string location;
    std::string fallback;
    std::vector<JigsawPiece *> pool;
    std::vector<std::pair<std::unique_ptr<JigsawPiece>, int>> elements;
};