#pragma once

#include <vector>
#include <string>

struct JigsawPiece;
struct JigsawPattern {
    std::string location;
    std::string fallback;
    std::vector<JigsawPiece *> pool;
    std::vector<std::pair<JigsawPiece *, int>> elements;
};