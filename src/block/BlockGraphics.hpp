#pragma once

#include <map>
#include <string>
#include <Json.hpp>
#include <unordered_map>

struct TextureAtlasTextureItem;
struct ResourceManager;
struct TextureAtlas;

struct BlockGraphics {
    std::string name;
    TextureAtlasTextureItem* topTexture{nullptr};
    TextureAtlasTextureItem* bottomTexture{nullptr};
    TextureAtlasTextureItem* southTexture{nullptr};
    TextureAtlasTextureItem* northTexture{nullptr};
    TextureAtlasTextureItem* eastTexture{nullptr};
    TextureAtlasTextureItem* westTexture{nullptr};

    explicit BlockGraphics(std::string name);

    void setTextures(const Json& data);
    void setCarriedTextures(const Json& data);
    void setTextureIsotropic(const Json& data);

public:
    static BlockGraphics* mMissingTexture;
    static std::unique_ptr<TextureAtlas> mTerrainTextureAtlas;
    static std::vector<std::unique_ptr<BlockGraphics>> mOwnedBlocks;
    static std::unordered_map<std::string, BlockGraphics*> mBlockLookupMap;

    static void init(ResourceManager& resources);
    static void registerBlockGraphics(const Json& data, const std::string& name);
    static auto getTextureItem(const std::string& name) -> TextureAtlasTextureItem*;
};