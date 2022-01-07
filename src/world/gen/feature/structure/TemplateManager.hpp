#pragma once

#include <map>
#include <memory>
#include <string>
#include <tl/optional.hpp>
#include <ResourceManager.hpp>
#include <util/zlib/istream.hpp>
#include <util/math/BoundingBox.hpp>

struct BlockInfo {
    BlockPos pos;
    BlockData state;
    tl::optional<Nbt::Compound> nbt;
};

struct PlacementSettings {
    BlockPos pivot = BlockPos::from(0, 0, 0);

    Mirror mirror = Mirror::NONE;
    Rotation rotation = Rotation::NONE;
    BoundingBox boundingBox = BoundingBox::newInfinityBoundingBox();

    [[nodiscard]] auto calculateConnectedPosition(BlockPos const& position) const -> BlockPos {
        auto [x, y, z] = position;

        switch (mirror) {
            case Mirror::LEFT_RIGHT:
                z = -z;
                break;
            case Mirror::FRONT_BACK:
                x = -x;
                break;
            default:
                break;
        }

        switch (rotation) {
            case Rotation::COUNTERCLOCKWISE_90:
                return BlockPos::from(pivot.x - pivot.z + z, y, pivot.x + pivot.z - x);
            case Rotation::CLOCKWISE_90:
                return BlockPos::from(pivot.x + pivot.z - z, y, pivot.z - pivot.x + x);
            case Rotation::CLOCKWISE_180:
                return BlockPos::from(pivot.x + pivot.x - x, y, pivot.z + pivot.z - z);
            default:
                return BlockPos::from(x, y, z);
        }
    }
};

struct Template {
    int version;
    glm::ivec3 size;
    std::vector<BlockInfo> blocks;

    [[nodiscard]] auto getBoundingBox(const PlacementSettings& settings, const BlockPos& pos) const -> BoundingBox {
        auto bounds = BoundingBox::from(
            settings.calculateConnectedPosition(BlockPos(0, 0, 0)),
            settings.calculateConnectedPosition(size - glm::ivec3(1))
        );
        bounds.offset(pos.x, pos.y, pos.z);
        return bounds;
    }
};

struct TemplateManager {
    auto get(const std::string& name) -> Template* {
        auto& structure = templates[name];
        if (structure == nullptr) {
            structure = load(name).or_else([] { return std::make_unique<Template>(); }).value();
        }
        return structure.get();
    }

private:
    auto load(const std::string& name) -> tl::optional<std::unique_ptr<Template>> {
        const auto location = ResourceLocation::from(name);

        return Resources::open(fmt::format("data/{}/structures/{}.nbt", location.get_namespace(), location.get_location()))
            .and_then([](auto&& resource) { return Nbt::Read::read(zlib_istream{*resource}); })
            .and_then([this](auto&& nbt) { return readStructure(nbt.root); });
    }

    auto readStructure(Nbt::Compound const& nbt) -> tl::optional<std::unique_ptr<Template>>;

    std::map<std::string, std::unique_ptr<Template>> templates;
};
