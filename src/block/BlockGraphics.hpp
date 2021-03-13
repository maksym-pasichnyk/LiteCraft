#pragma once

#include <map>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

struct TextureAtlasTextureItem;
struct ResourcePackManager;
struct TextureAtlas;

struct BlockGraphics {
    std::string name;
    TextureAtlasTextureItem* topTexture{nullptr};
    TextureAtlasTextureItem* bottomTexture{nullptr};
    TextureAtlasTextureItem* southTexture{nullptr};
    TextureAtlasTextureItem* northTexture{nullptr};
    TextureAtlasTextureItem* eastTexture{nullptr};
    TextureAtlasTextureItem* westTexture{nullptr};

    BlockGraphics(std::string name);

    void setTextures(const nlohmann::json& data);
    void setCarriedTextures(const nlohmann::json& data);
    void setTextureIsotropic(const nlohmann::json& data);

public:
    static TextureAtlas* mTerrainTextureAtlas;
    static std::unordered_map<std::string, BlockGraphics*> mBlockLookupMap;
    static std::vector<std::unique_ptr<BlockGraphics>> mOwnedBlocks;

    static void initBlocks(ResourcePackManager& resources);
    static void registerBlockGraphics(const nlohmann::json& data, const std::string& name);
    static TextureAtlasTextureItem* getTextureItem(const std::string& name);
};