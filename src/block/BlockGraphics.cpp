#include "BlockGraphics.hpp"

#include <Json.hpp>
#include <TextureAtlas.hpp>

BlockGraphics* BlockGraphics::mMissingTexture;
std::unique_ptr<TextureAtlas> BlockGraphics::mTerrainTextureAtlas;
std::vector<std::unique_ptr<BlockGraphics>> BlockGraphics::mOwnedBlocks;
std::unordered_map<std::string, BlockGraphics*> BlockGraphics::mBlockLookupMap;

void BlockGraphics::init(ResourceManager& resources) {
    using namespace std::string_view_literals;

    mTerrainTextureAtlas = std::make_unique<TextureAtlas>();
    mTerrainTextureAtlas->loadMetaFile(resources);
    mTerrainTextureAtlas->loadTexture();

    resources.for_each("blocks.json", [](std::istream& stream) {
        auto blocks = Json::Read::read(stream).value();
        auto format_version = blocks.at("format_version");

        for (auto& [name, data] : blocks.to_object()) {
            if (name == "format_version") {
                continue;
            }
            registerBlockGraphics(data, name);
        }
    });

    mMissingTexture = new BlockGraphics("missing");
    mMissingTexture->setTextures("missing");

    mBlockLookupMap.emplace("missing", mMissingTexture);
    mOwnedBlocks.emplace_back(mMissingTexture);

    mBlockLookupMap.insert_or_assign("void_air", mBlockLookupMap.at("air"));
    mBlockLookupMap.insert_or_assign("cave_air", mBlockLookupMap.at("air"));
    mBlockLookupMap.insert_or_assign("melon", mBlockLookupMap.at("melon_block"));
    mBlockLookupMap.insert_or_assign("jack_o_lantern", mBlockLookupMap.at("lit_pumpkin"));
    mBlockLookupMap.insert_or_assign("lily_pad", mBlockLookupMap.at("waterlily"));
    mBlockLookupMap.insert_or_assign("sugar_cane", mBlockLookupMap.at("reeds"));
    mBlockLookupMap.insert_or_assign("wet_sponge", mBlockLookupMap.at("sponge"));
    mBlockLookupMap.insert_or_assign("red_sand", mBlockLookupMap.at("sand"));
    mBlockLookupMap.insert_or_assign("granite", mBlockLookupMap.at("stone"));
    mBlockLookupMap.insert_or_assign("polished_granite", mBlockLookupMap.at("stone"));
    mBlockLookupMap.insert_or_assign("diorite", mBlockLookupMap.at("stone"));
    mBlockLookupMap.insert_or_assign("polished_diorite", mBlockLookupMap.at("stone"));
    mBlockLookupMap.insert_or_assign("andesite", mBlockLookupMap.at("stone"));
    mBlockLookupMap.insert_or_assign("polished_andesite", mBlockLookupMap.at("stone"));
    mBlockLookupMap.insert_or_assign("grass_block", mBlockLookupMap.at("grass"));
    mBlockLookupMap.insert_or_assign("grass", mBlockLookupMap.at("tallgrass"));
    mBlockLookupMap.insert_or_assign("fern", mBlockLookupMap.at("tallgrass"));
    mBlockLookupMap.insert_or_assign("sunflower", mBlockLookupMap.at("double_plant"));
    mBlockLookupMap.insert_or_assign("lilac", mBlockLookupMap.at("double_plant"));
    mBlockLookupMap.insert_or_assign("rose_bush", mBlockLookupMap.at("double_plant"));
    mBlockLookupMap.insert_or_assign("peony", mBlockLookupMap.at("double_plant"));
    mBlockLookupMap.insert_or_assign("tall_grass", mBlockLookupMap.at("double_plant"));
    mBlockLookupMap.insert_or_assign("large_fern", mBlockLookupMap.at("double_plant"));
    mBlockLookupMap.insert_or_assign("coarse_dirt", mBlockLookupMap.at("dirt"));
    mBlockLookupMap.insert_or_assign("cobweb", mBlockLookupMap.at("web"));
    mBlockLookupMap.insert_or_assign("dead_bush", mBlockLookupMap.at("deadbush"));
    mBlockLookupMap.insert_or_assign("dandelion", mBlockLookupMap.at("yellow_flower"));
    mBlockLookupMap.insert_or_assign("poppy", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("blue_orchid", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("allium", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("azure_bluet", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("red_tulip", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("orange_tulip", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("white_tulip", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("pink_tulip", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("oxeye_daisy", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("cornflower", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("lily_of_the_valley", mBlockLookupMap.at("red_flower"));
    mBlockLookupMap.insert_or_assign("oak_planks", mBlockLookupMap.at("planks"));
    mBlockLookupMap.insert_or_assign("spruce_planks", mBlockLookupMap.at("planks"));
    mBlockLookupMap.insert_or_assign("birch_planks", mBlockLookupMap.at("planks"));
    mBlockLookupMap.insert_or_assign("jungle_planks", mBlockLookupMap.at("planks"));
    mBlockLookupMap.insert_or_assign("acacia_planks", mBlockLookupMap.at("planks"));
    mBlockLookupMap.insert_or_assign("dark_oak_planks", mBlockLookupMap.at("planks"));
    mBlockLookupMap.insert_or_assign("oak_sapling", mBlockLookupMap.at("sapling"));
    mBlockLookupMap.insert_or_assign("spruce_sapling", mBlockLookupMap.at("sapling"));
    mBlockLookupMap.insert_or_assign("birch_sapling", mBlockLookupMap.at("sapling"));
    mBlockLookupMap.insert_or_assign("jungle_sapling", mBlockLookupMap.at("sapling"));
    mBlockLookupMap.insert_or_assign("acacia_sapling", mBlockLookupMap.at("sapling"));
    mBlockLookupMap.insert_or_assign("dark_oak_sapling", mBlockLookupMap.at("sapling"));
    mBlockLookupMap.insert_or_assign("oak_log", mBlockLookupMap.at("log"));
    mBlockLookupMap.insert_or_assign("spruce_log", mBlockLookupMap.at("log"));
    mBlockLookupMap.insert_or_assign("birch_log", mBlockLookupMap.at("log"));
    mBlockLookupMap.insert_or_assign("jungle_log", mBlockLookupMap.at("log"));
    mBlockLookupMap.insert_or_assign("acacia_log", mBlockLookupMap.at("log"));
    mBlockLookupMap.insert_or_assign("dark_oak_log", mBlockLookupMap.at("log"));
    mBlockLookupMap.insert_or_assign("oak_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("spruce_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("birch_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("jungle_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("acacia_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("dark_oak_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("stripped_oak_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("stripped_spruce_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("stripped_birch_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("stripped_jungle_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("stripped_acacia_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("stripped_dark_oak_wood", mBlockLookupMap.at("wood"));
    mBlockLookupMap.insert_or_assign("oak_leaves", mBlockLookupMap.at("leaves"));
    mBlockLookupMap.insert_or_assign("spruce_leaves", mBlockLookupMap.at("leaves"));
    mBlockLookupMap.insert_or_assign("birch_leaves", mBlockLookupMap.at("leaves"));
    mBlockLookupMap.insert_or_assign("jungle_leaves", mBlockLookupMap.at("leaves"));
    mBlockLookupMap.insert_or_assign("acacia_leaves", mBlockLookupMap.at("leaves"));
    mBlockLookupMap.insert_or_assign("dark_oak_leaves", mBlockLookupMap.at("leaves"));
    mBlockLookupMap.insert_or_assign("white_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("orange_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("magenta_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("light_blue_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("yellow_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("lime_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("pink_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("gray_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("light_gray_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("cyan_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("purple_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("blue_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("brown_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("green_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("red_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("black_bed", mBlockLookupMap.at("bed"));
    mBlockLookupMap.insert_or_assign("white_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("orange_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("magenta_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("light_blue_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("yellow_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("lime_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("pink_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("gray_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("light_gray_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("cyan_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("purple_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("blue_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("brown_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("green_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("red_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("black_wool", mBlockLookupMap.at("wool"));
    mBlockLookupMap.insert_or_assign("white_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("orange_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("magenta_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("light_blue_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("yellow_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("lime_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("pink_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("gray_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("light_gray_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("cyan_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("purple_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("blue_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("brown_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("green_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("red_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("black_carpet", mBlockLookupMap.at("carpet"));
    mBlockLookupMap.insert_or_assign("terracotta", mBlockLookupMap.at("hardened_clay"));
    mBlockLookupMap.insert_or_assign("white_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("orange_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("magenta_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("light_blue_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("yellow_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("lime_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("pink_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("gray_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("light_gray_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("cyan_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("purple_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("blue_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("brown_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("green_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("red_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("black_terracotta", mBlockLookupMap.at("stained_hardened_clay"));
    mBlockLookupMap.insert_or_assign("white_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("orange_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("magenta_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("light_blue_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("yellow_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("lime_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("pink_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("gray_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("light_gray_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("cyan_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("purple_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("blue_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("brown_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("green_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("red_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("black_stained_glass_pane", mBlockLookupMap.at("stained_glass_pane"));
    mBlockLookupMap.insert_or_assign("white_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("orange_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("magenta_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("light_blue_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("yellow_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("lime_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("pink_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("gray_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("light_gray_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("cyan_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("purple_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("blue_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("brown_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("green_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("red_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("black_shulker_box", mBlockLookupMap.at("shulker_box"));
    mBlockLookupMap.insert_or_assign("shulker_box", mBlockLookupMap.at("undyed_shulker_box"));
    mBlockLookupMap.insert_or_assign("white_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("orange_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("magenta_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("light_blue_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("yellow_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("lime_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("pink_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("gray_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("light_gray_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("cyan_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("purple_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("blue_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("brown_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("green_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("red_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("black_concrete", mBlockLookupMap.at("concrete"));
    mBlockLookupMap.insert_or_assign("white_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("orange_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("magenta_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("light_blue_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("yellow_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("lime_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("pink_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("gray_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("light_gray_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("cyan_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("purple_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("blue_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("brown_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("green_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("red_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("black_concrete_powder", mBlockLookupMap.at("concretePowder"));
    mBlockLookupMap.insert_or_assign("white_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("orange_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("magenta_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("light_blue_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("yellow_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("lime_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("pink_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("gray_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("light_gray_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("cyan_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("purple_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("blue_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("brown_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("green_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("red_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("black_banner", mBlockLookupMap.at("standing_banner"));
    mBlockLookupMap.insert_or_assign("white_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("orange_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("magenta_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("light_blue_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("yellow_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("lime_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("pink_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("gray_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("light_gray_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("cyan_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("purple_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("blue_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("brown_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("green_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("red_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("black_wall_banner", mBlockLookupMap.at("wall_banner"));
    mBlockLookupMap.insert_or_assign("white_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("orange_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("magenta_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("light_blue_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("yellow_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("lime_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("pink_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("gray_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("light_gray_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("cyan_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("purple_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("blue_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("brown_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("green_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("red_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("black_stained_glass", mBlockLookupMap.at("stained_glass"));
    mBlockLookupMap.insert_or_assign("potted_oak_sapling", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_spruce_sapling", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_birch_sapling", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_jungle_sapling", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_acacia_sapling", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_dark_oak_sapling", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_fern", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_dandelion", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_poppy", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_blue_orchid", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_allium", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_azure_bluet", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_red_tulip", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_orange_tulip", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_white_tulip", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_pink_tulip", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_oxeye_daisy", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_cornflower", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_lily_of_the_valley", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_wither_rose", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_red_mushroom", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_brown_mushroom", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_dead_bush", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_cactus", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_bamboo", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_crimson_fungus", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_warped_fungus", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_crimson_roots", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("potted_warped_roots", mBlockLookupMap.at("flower_pot"));
    mBlockLookupMap.insert_or_assign("oak_button", mBlockLookupMap.at("wooden_button"));
    mBlockLookupMap.insert_or_assign("oak_fence", mBlockLookupMap.at("fence"));
    mBlockLookupMap.insert_or_assign("spruce_fence", mBlockLookupMap.at("fence"));
    mBlockLookupMap.insert_or_assign("birch_fence", mBlockLookupMap.at("fence"));
    mBlockLookupMap.insert_or_assign("jungle_fence", mBlockLookupMap.at("fence"));
    mBlockLookupMap.insert_or_assign("acacia_fence", mBlockLookupMap.at("fence"));
    mBlockLookupMap.insert_or_assign("dark_oak_fence", mBlockLookupMap.at("fence"));
    mBlockLookupMap.insert_or_assign("oak_sign", mBlockLookupMap.at("standing_sign"));
    mBlockLookupMap.insert_or_assign("spruce_sign", mBlockLookupMap.at("spruce_standing_sign"));
    mBlockLookupMap.insert_or_assign("birch_sign", mBlockLookupMap.at("birch_standing_sign"));
    mBlockLookupMap.insert_or_assign("acacia_sign", mBlockLookupMap.at("acacia_standing_sign"));
    mBlockLookupMap.insert_or_assign("jungle_sign", mBlockLookupMap.at("jungle_standing_sign"));
    mBlockLookupMap.insert_or_assign("dark_oak_sign", mBlockLookupMap.at("darkoak_standing_sign"));
    mBlockLookupMap.insert_or_assign("oak_wall_sign", mBlockLookupMap.at("wall_sign"));
    mBlockLookupMap.insert_or_assign("dark_oak_wall_sign", mBlockLookupMap.at("darkoak_wall_sign"));
    mBlockLookupMap.insert_or_assign("crimson_sign", mBlockLookupMap.at("crimson_standing_sign"));
    mBlockLookupMap.insert_or_assign("warped_sign", mBlockLookupMap.at("warped_standing_sign"));
    mBlockLookupMap.insert_or_assign("note_block", mBlockLookupMap.at("noteblock"));
    mBlockLookupMap.insert_or_assign("powered_rail", mBlockLookupMap.at("activator_rail"));
    mBlockLookupMap.insert_or_assign("tall_seagrass", mBlockLookupMap.at("seagrass"));
    mBlockLookupMap.insert_or_assign("wall_torch", mBlockLookupMap.at("torch"));
    mBlockLookupMap.insert_or_assign("oak_door", mBlockLookupMap.at("wooden_door"));
    mBlockLookupMap.insert_or_assign("chipped_anvil", mBlockLookupMap.at("anvil"));
    mBlockLookupMap.insert_or_assign("damaged_anvil", mBlockLookupMap.at("anvil"));
    mBlockLookupMap.insert_or_assign("bricks", mBlockLookupMap.at("brick_block"));
    mBlockLookupMap.insert_or_assign("spawner", mBlockLookupMap.at("mob_spawner"));
    mBlockLookupMap.insert_or_assign("weeping_vines_plant", mBlockLookupMap.at("weeping_vines"));
    mBlockLookupMap.insert_or_assign("twisting_vines_plant", mBlockLookupMap.at("twisting_vines"));
    mBlockLookupMap.insert_or_assign("oak_pressure_plate", mBlockLookupMap.at("wooden_pressure_plate"));
    mBlockLookupMap.insert_or_assign("redstone_wall_torch", mBlockLookupMap.at("redstone_torch"));
    mBlockLookupMap.insert_or_assign("soul_wall_torch", mBlockLookupMap.at("soul_torch"));
    mBlockLookupMap.insert_or_assign("oak_trapdoor", mBlockLookupMap.at("trapdoor"));

    mBlockLookupMap.insert_or_assign("dead_tube_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("dead_brain_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("dead_bubble_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("dead_fire_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("dead_horn_coral_block", mBlockLookupMap.at("coral_block"));

    mBlockLookupMap.insert_or_assign("tube_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("brain_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("bubble_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("fire_coral_block", mBlockLookupMap.at("coral_block"));
    mBlockLookupMap.insert_or_assign("horn_coral_block", mBlockLookupMap.at("coral_block"));

    mBlockLookupMap.insert_or_assign("dead_tube_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("dead_brain_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("dead_bubble_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("dead_fire_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("dead_horn_coral", mBlockLookupMap.at("coral"));

    mBlockLookupMap.insert_or_assign("tube_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("brain_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("bubble_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("fire_coral", mBlockLookupMap.at("coral"));
    mBlockLookupMap.insert_or_assign("horn_coral", mBlockLookupMap.at("coral"));

    mBlockLookupMap.insert_or_assign("dead_tube_coral_fan", mBlockLookupMap.at("coral_fan_dead"));
    mBlockLookupMap.insert_or_assign("dead_brain_coral_fan", mBlockLookupMap.at("coral_fan_dead"));
    mBlockLookupMap.insert_or_assign("dead_bubble_coral_fan", mBlockLookupMap.at("coral_fan_dead"));
    mBlockLookupMap.insert_or_assign("dead_fire_coral_fan", mBlockLookupMap.at("coral_fan_dead"));
    mBlockLookupMap.insert_or_assign("dead_horn_coral_fan", mBlockLookupMap.at("coral_fan_dead"));

    mBlockLookupMap.insert_or_assign("tube_coral_fan", mBlockLookupMap.at("coral_fan"));
    mBlockLookupMap.insert_or_assign("brain_coral_fan", mBlockLookupMap.at("coral_fan"));
    mBlockLookupMap.insert_or_assign("bubble_coral_fan", mBlockLookupMap.at("coral_fan"));
    mBlockLookupMap.insert_or_assign("fire_coral_fan", mBlockLookupMap.at("coral_fan"));
    mBlockLookupMap.insert_or_assign("horn_coral_fan", mBlockLookupMap.at("coral_fan"));

    mBlockLookupMap.insert_or_assign("dead_tube_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang"));
    mBlockLookupMap.insert_or_assign("dead_brain_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang"));
    mBlockLookupMap.insert_or_assign("dead_bubble_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang2"));
    mBlockLookupMap.insert_or_assign("dead_fire_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang2"));
    mBlockLookupMap.insert_or_assign("dead_horn_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang3"));

    mBlockLookupMap.insert_or_assign("tube_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang"));
    mBlockLookupMap.insert_or_assign("brain_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang"));
    mBlockLookupMap.insert_or_assign("bubble_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang2"));
    mBlockLookupMap.insert_or_assign("fire_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang2"));
    mBlockLookupMap.insert_or_assign("horn_coral_wall_fan", mBlockLookupMap.at("coral_fan_hang3"));

    mBlockLookupMap.insert_or_assign("prismarine_slab", mBlockLookupMap.at("stone_slab2"));
    mBlockLookupMap.insert_or_assign("prismarine_brick_slab", mBlockLookupMap.at("stone_slab2"));
    mBlockLookupMap.insert_or_assign("dark_prismarine_slab", mBlockLookupMap.at("stone_slab2"));
    mBlockLookupMap.insert_or_assign("oak_slab", mBlockLookupMap.at("wooden_slab"));
    mBlockLookupMap.insert_or_assign("spruce_slab", mBlockLookupMap.at("wooden_slab"));
    mBlockLookupMap.insert_or_assign("birch_slab", mBlockLookupMap.at("wooden_slab"));
    mBlockLookupMap.insert_or_assign("jungle_slab", mBlockLookupMap.at("wooden_slab"));
    mBlockLookupMap.insert_or_assign("acacia_slab", mBlockLookupMap.at("wooden_slab"));
    mBlockLookupMap.insert_or_assign("dark_oak_slab", mBlockLookupMap.at("wooden_slab"));
    mBlockLookupMap.insert_or_assign("smooth_stone_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("sandstone_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("cut_sandstone_slab", mBlockLookupMap.at("stone_slab4"));
    mBlockLookupMap.insert_or_assign("petrified_oak_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("cobblestone_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("brick_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("stone_brick_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("nether_brick_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("quartz_slab", mBlockLookupMap.at("stone_slab"));
    mBlockLookupMap.insert_or_assign("red_sandstone_slab", mBlockLookupMap.at("stone_slab2"));
    mBlockLookupMap.insert_or_assign("cut_red_sandstone_slab", mBlockLookupMap.at("stone_slab4"));
    mBlockLookupMap.insert_or_assign("purpur_slab", mBlockLookupMap.at("stone_slab2"));
    mBlockLookupMap.insert_or_assign("polished_granite_slab", mBlockLookupMap.at("stone_slab3"));
    mBlockLookupMap.insert_or_assign("smooth_red_sandstone_slab", mBlockLookupMap.at("stone_slab3"));
    mBlockLookupMap.insert_or_assign("mossy_stone_brick_slab", mBlockLookupMap.at("stone_slab4"));
    mBlockLookupMap.insert_or_assign("polished_diorite_slab", mBlockLookupMap.at("stone_slab3"));
    mBlockLookupMap.insert_or_assign("mossy_cobblestone_slab", mBlockLookupMap.at("stone_slab2"));

    mBlockLookupMap.insert_or_assign("end_stone_brick_slab", mBlockLookupMap.at("stone_slab3"));
    mBlockLookupMap.insert_or_assign("smooth_sandstone_slab", mBlockLookupMap.at("stone_slab2"));
    mBlockLookupMap.insert_or_assign("smooth_quartz_slab", mBlockLookupMap.at("stone_slab4"));
    mBlockLookupMap.insert_or_assign("granite_slab", mBlockLookupMap.at("stone_slab3"));
    mBlockLookupMap.insert_or_assign("andesite_slab", mBlockLookupMap.at("stone_slab3"));
    mBlockLookupMap.insert_or_assign("red_nether_brick_slab", mBlockLookupMap.at("stone_slab2"));
    mBlockLookupMap.insert_or_assign("polished_andesite_slab", mBlockLookupMap.at("stone_slab3"));
    mBlockLookupMap.insert_or_assign("diorite_slab", mBlockLookupMap.at("stone_slab3"));

    mBlockLookupMap.insert_or_assign("infested_stone", mBlockLookupMap.at("monster_egg"));
    mBlockLookupMap.insert_or_assign("infested_cobblestone", mBlockLookupMap.at("monster_egg"));
    mBlockLookupMap.insert_or_assign("infested_stone_bricks", mBlockLookupMap.at("monster_egg"));
    mBlockLookupMap.insert_or_assign("infested_mossy_stone_bricks", mBlockLookupMap.at("monster_egg"));
    mBlockLookupMap.insert_or_assign("infested_cracked_stone_bricks", mBlockLookupMap.at("monster_egg"));
    mBlockLookupMap.insert_or_assign("infested_chiseled_stone_bricks", mBlockLookupMap.at("monster_egg"));

    mBlockLookupMap.insert_or_assign("mossy_cobblestone_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("brick_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("prismarine_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("red_sandstone_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("mossy_stone_brick_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("granite_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("stone_brick_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("nether_brick_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("andesite_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("red_nether_brick_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("sandstone_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("end_stone_brick_wall", mBlockLookupMap.at("cobblestone_wall"));
    mBlockLookupMap.insert_or_assign("diorite_wall", mBlockLookupMap.at("cobblestone_wall"));

    mBlockLookupMap.insert_or_assign("chiseled_sandstone", mBlockLookupMap.at("sandstone"));
    mBlockLookupMap.insert_or_assign("cut_sandstone", mBlockLookupMap.at("sandstone"));
    mBlockLookupMap.insert_or_assign("chiseled_red_sandstone", mBlockLookupMap.at("red_sandstone"));
    mBlockLookupMap.insert_or_assign("cut_red_sandstone", mBlockLookupMap.at("red_sandstone"));
    mBlockLookupMap.insert_or_assign("smooth_sandstone", mBlockLookupMap.at("sandstone"));
    mBlockLookupMap.insert_or_assign("smooth_red_sandstone", mBlockLookupMap.at("red_sandstone"));

    mBlockLookupMap.insert_or_assign("zombie_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("player_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("creeper_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("dragon_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("zombie_wall_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("player_wall_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("creeper_wall_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("dragon_wall_head", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("skeleton_skull", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("wither_skeleton_skull", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("skeleton_wall_skull", mBlockLookupMap.at("skull"));
    mBlockLookupMap.insert_or_assign("wither_skeleton_wall_skull", mBlockLookupMap.at("skull"));

    mBlockLookupMap.insert_or_assign("stone_bricks", mBlockLookupMap.at("stonebrick"));
    mBlockLookupMap.insert_or_assign("mossy_stone_bricks", mBlockLookupMap.at("stonebrick"));
    mBlockLookupMap.insert_or_assign("cracked_stone_bricks", mBlockLookupMap.at("stonebrick"));
    mBlockLookupMap.insert_or_assign("chiseled_stone_bricks", mBlockLookupMap.at("stonebrick"));
    mBlockLookupMap.insert_or_assign("nether_bricks", mBlockLookupMap.at("nether_brick"));
    mBlockLookupMap.insert_or_assign("prismarine_bricks", mBlockLookupMap.at("prismarine"));
    mBlockLookupMap.insert_or_assign("end_stone_bricks", mBlockLookupMap.at("end_bricks"));
    mBlockLookupMap.insert_or_assign("red_nether_bricks", mBlockLookupMap.at("red_nether_brick"));
    mBlockLookupMap.insert_or_assign("dark_prismarine", mBlockLookupMap.at("prismarine"));

    mBlockLookupMap.insert_or_assign("piston_head", mBlockLookupMap.at("pistonArmCollision"));
    mBlockLookupMap.insert_or_assign("moving_piston", mBlockLookupMap.at("movingBlock"));
    mBlockLookupMap.insert_or_assign("cobblestone_stairs", mBlockLookupMap.at("stone_stairs"));
    mBlockLookupMap.insert_or_assign("snow_block", mBlockLookupMap.at("snow"));
    mBlockLookupMap.insert_or_assign("nether_portal", mBlockLookupMap.at("portal"));
    mBlockLookupMap.insert_or_assign("repeater", mBlockLookupMap.at("powered_repeater"));
    mBlockLookupMap.insert_or_assign("mushroom_stem", mBlockLookupMap.at("brown_mushroom_block"));
    mBlockLookupMap.insert_or_assign("attached_pumpkin_stem", mBlockLookupMap.at("pumpkin_stem"));
    mBlockLookupMap.insert_or_assign("attached_melon_stem", mBlockLookupMap.at("melon_stem"));
    mBlockLookupMap.insert_or_assign("oak_fence_gate", mBlockLookupMap.at("fence_gate"));
    mBlockLookupMap.insert_or_assign("tripwire", mBlockLookupMap.at("tripWire"));
    mBlockLookupMap.insert_or_assign("comparator", mBlockLookupMap.at("powered_comparator"));
    mBlockLookupMap.insert_or_assign("nether_quartz_ore", mBlockLookupMap.at("quartz_ore"));
    mBlockLookupMap.insert_or_assign("chiseled_quartz_block", mBlockLookupMap.at("quartz_block"));
    mBlockLookupMap.insert_or_assign("quartz_pillar", mBlockLookupMap.at("quartz_block"));
    mBlockLookupMap.insert_or_assign("slime_block", mBlockLookupMap.at("slime"));
    mBlockLookupMap.insert_or_assign("prismarine_brick_stairs", mBlockLookupMap.at("prismarine_bricks_stairs"));
    mBlockLookupMap.insert_or_assign("sea_lantern", mBlockLookupMap.at("seaLantern"));
    mBlockLookupMap.insert_or_assign("smooth_quartz", mBlockLookupMap.at("quartz_block"));
    mBlockLookupMap.insert_or_assign("purpur_pillar", mBlockLookupMap.at("purpur_block"));
    mBlockLookupMap.insert_or_assign("beetroots", mBlockLookupMap.at("beetroot"));
    mBlockLookupMap.insert_or_assign("magma_block", mBlockLookupMap.at("magma"));
    mBlockLookupMap.insert_or_assign("light_gray_glazed_terracotta", mBlockLookupMap.at("silver_glazed_terracotta"));
    mBlockLookupMap.insert_or_assign("kelp_plant", mBlockLookupMap.at("kelp"));
    mBlockLookupMap.insert_or_assign("end_stone_brick_stairs", mBlockLookupMap.at("end_brick_stairs"));

}

void BlockGraphics::registerBlockGraphics(const Json& data, const std::string& name) {
    auto graphics = std::make_unique<BlockGraphics>(name);

//    if (auto isotropic = data.find("isotropic"); isotropic != data.end()) {
//        graphics->setTextureIsotropic(isotropic.value());
//    }

    if (data.contains("textures")) {
        graphics->setTextures(data.at("textures"));
    }

//    if (auto carried_textures = data.find("carried_textures"); carried_textures != data.end()) {
//        graphics->setCarriedTextures(carried_textures.value());
//    }

//    if (auto sound = data.find("sound"); sound != data.end()) {
//    }

//    if (auto brightness_gamma = data.find("brightness_gamma"); brightness_gamma != data.end()) {
//    }

    mBlockLookupMap.emplace(name, graphics.get());
    mOwnedBlocks.emplace_back(std::move(graphics));
}

auto BlockGraphics::getTextureItem(const std::string& name) -> TextureAtlasTextureItem* {
    return mTerrainTextureAtlas->getTextureItem(name);
}

BlockGraphics::BlockGraphics(std::string name) : name(std::move(name)) {}

void BlockGraphics::setTextures(const Json &data) {
    if (data.is_object()) {
        topTexture = getTextureItem(data.at("up").to_string());
        bottomTexture = getTextureItem(data.at("down").to_string());

        if (data.contains("side")) {
            auto texture = getTextureItem(data.at("side").to_string());

            southTexture = texture;
            northTexture = texture;
            eastTexture = texture;
            westTexture = texture;
        } else {
            southTexture = getTextureItem(data.at("south").to_string());
            northTexture = getTextureItem(data.at("north").to_string());
            eastTexture = getTextureItem(data.at("east").to_string());
            westTexture = getTextureItem(data.at("west").to_string());
        }
    } else {
        auto texture = getTextureItem(data.to_string());

        topTexture = texture;
        bottomTexture = texture;
        southTexture = texture;
        northTexture = texture;
        eastTexture = texture;
        westTexture = texture;
    }
}

void BlockGraphics::setCarriedTextures(const Json &data) {

}

void BlockGraphics::setTextureIsotropic(const Json &data) {
}