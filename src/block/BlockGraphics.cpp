#include "BlockGraphics.hpp"
#include "../TextureAtlas.hpp"

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