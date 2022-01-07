#include "Village.hpp"
#include <world/gen/feature/jigsaw/Jigsaw.hpp>

auto Village::create() -> std::unique_ptr<Structure> {
    return std::make_unique<Structure>(Structure{
        .configFromJson = [](const Json& o) -> tl::optional<StructureConfig> {
            return o.into<JigsawConfig>();
        },
        .generatePieces = Jigsaw::createComponents
    });
}