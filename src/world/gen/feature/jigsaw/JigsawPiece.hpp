#pragma once

#include "JigsawProjection.hpp"

#include <functional>
#include <json/json.hpp>

struct ConfiguredFeature;
struct StructureProcessorList;

struct JigsawPiece {
    using Factory = std::function<auto(JigsawProjection) -> JigsawPiece*>;

    JigsawProjection projection;

    explicit JigsawPiece(JigsawProjection projection) : projection(projection) {}
    virtual ~JigsawPiece() = default;

    virtual auto to_json() -> Json = 0;
    virtual auto getGroundLevelDelta() -> int {
        return 1;
    }

    static auto list(std::vector<Factory> factories) -> Factory;
    static auto single(std::string name) -> Factory;
    static auto single(std::string name, StructureProcessorList* processor) -> Factory;
    static auto feature(ConfiguredFeature* feature) -> Factory;
    static auto legacy(std::string name) -> Factory;
    static auto legacy(std::string name, StructureProcessorList* processor) -> Factory;
    static auto empty() -> Factory;
};
