#include "BlockGraphics.hpp"
#include "../TextureAtlas.hpp"

TextureAtlas* BlockGraphics::mTerrainTextureAtlas;
std::unordered_map<std::string, BlockGraphics*> BlockGraphics::mBlockLookupMap;
std::vector<std::unique_ptr<BlockGraphics>> BlockGraphics::mOwnedBlocks;

void BlockGraphics::initBlocks(ResourcePackManager& resources) {
    using namespace std::string_view_literals;

    // todo: merge
    resources.loadAllVersionsOf("blocks.json", [](std::span<const char> bytes) {
        auto blocks = nlohmann::json::parse(bytes, nullptr, true, true);
        auto format_version = blocks.erase("format_version");

        for (auto& [name, data] : blocks.items()) {
            registerBlockGraphics(data, name);
        }
    });
}

void BlockGraphics::registerBlockGraphics(const nlohmann::json& data, const std::string& name) {
    auto graphics = std::make_unique<BlockGraphics>(name);

    auto isotropic = data.find("isotropic");
    if (isotropic != data.end()) {
        graphics->setTextureIsotropic(isotropic.value());
    }

    auto textures = data.find("textures");
    if (textures != data.end()) {
        graphics->setTextures(textures.value());
    }

    auto carried_textures = data.find("carried_textures");
    if (carried_textures != data.end()) {
        graphics->setCarriedTextures(carried_textures.value());
    }

    auto sound = data.find("sound");
    if (sound != data.end()) {
    }

    auto brightness_gamma = data.find("brightness_gamma");
    if (brightness_gamma != data.end()) {
    }

    mBlockLookupMap.emplace(name, graphics.get());
    mOwnedBlocks.emplace_back(std::move(graphics));
}

TextureAtlasTextureItem* BlockGraphics::getTextureItem(const std::string& name) {
    return mTerrainTextureAtlas->getTextureItem(name);
}

BlockGraphics::BlockGraphics(std::string name) : name(std::move(name)) {

}

void BlockGraphics::setTextures(const nlohmann::json &data) {
    if (data.is_object()) {
        topTexture = getTextureItem(data["up"].get<std::string>());
        bottomTexture = getTextureItem(data["down"].get<std::string>());

        if (auto side = data.find("side"); side != data.end()) {
            auto texture = getTextureItem(side->get<std::string>());

            southTexture = texture;
            northTexture = texture;
            eastTexture = texture;
            westTexture = texture;
        } else {
            southTexture = getTextureItem(data["south"].get<std::string>());
            northTexture = getTextureItem(data["north"].get<std::string>());
            eastTexture = getTextureItem(data["east"].get<std::string>());
            westTexture = getTextureItem(data["west"].get<std::string>());
        }
    } else {
        auto texture = getTextureItem(data.get<std::string>());

        topTexture = texture;
        bottomTexture = texture;
        southTexture = texture;
        northTexture = texture;
        eastTexture = texture;
        westTexture = texture;
    }
}

void BlockGraphics::setCarriedTextures(const nlohmann::json &data) {

}

void BlockGraphics::setTextureIsotropic(const nlohmann::json &data) {
}