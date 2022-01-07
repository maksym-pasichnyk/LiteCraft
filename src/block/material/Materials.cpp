#include "Materials.hpp"

#include <array>
#include <string>
#include <fstream>
#include <Json.hpp>
#include <spdlog/fmt/fmt.h>

BlockMaterial * Materials::AIR;
BlockMaterial * Materials::STRUCTURE_VOID;
BlockMaterial * Materials::PORTAL;
BlockMaterial * Materials::CARPET;
BlockMaterial * Materials::PLANTS;
BlockMaterial * Materials::OCEAN_PLANT;
BlockMaterial * Materials::TALL_PLANTS;
BlockMaterial * Materials::NETHER_PLANTS;
BlockMaterial * Materials::SEA_GRASS;
BlockMaterial * Materials::WATER;
BlockMaterial * Materials::BUBBLE_COLUMN;
BlockMaterial * Materials::LAVA;
BlockMaterial * Materials::SNOW;
BlockMaterial * Materials::FIRE;
BlockMaterial * Materials::MISCELLANEOUS;
BlockMaterial * Materials::WEB;
BlockMaterial * Materials::REDSTONE_LIGHT;
BlockMaterial * Materials::CLAY;
BlockMaterial * Materials::EARTH;
BlockMaterial * Materials::ORGANIC;
BlockMaterial * Materials::PACKED_ICE;
BlockMaterial * Materials::SAND;
BlockMaterial * Materials::SPONGE;
BlockMaterial * Materials::SHULKER;
BlockMaterial * Materials::WOOD;
BlockMaterial * Materials::NETHER_WOOD;
BlockMaterial * Materials::BAMBOO_SAPLING;
BlockMaterial * Materials::BAMBOO;
BlockMaterial * Materials::WOOL;
BlockMaterial * Materials::TNT;
BlockMaterial * Materials::LEAVES;
BlockMaterial * Materials::GLASS;
BlockMaterial * Materials::ICE;
BlockMaterial * Materials::CACTUS;
BlockMaterial * Materials::ROCK;
BlockMaterial * Materials::IRON;
BlockMaterial * Materials::SNOW_BLOCK;
BlockMaterial * Materials::ANVIL;
BlockMaterial * Materials::BARRIER;
BlockMaterial * Materials::PISTON;
BlockMaterial * Materials::CORAL;
BlockMaterial * Materials::GOURD;
BlockMaterial * Materials::DRAGON_EGG;
BlockMaterial * Materials::CAKE;

template<>
auto Json::From<PushReaction>::from(const Value &value) -> Self {
    switch (value) {
        case PushReaction::NORMAL: return "normal";
        case PushReaction::DESTROY: return "destroy";
        case PushReaction::BLOCK: return "block";
        case PushReaction::IGNORE: return "ignore";
        case PushReaction::PUSH_ONLY: return "push_only";
    }
    return {};
}

void Materials::init() {
    AIR = BlockMaterial::Builder(MaterialColors::AIR).doesNotBlockMovement().notOpaque().notSolid().replaceable().build();
    STRUCTURE_VOID = BlockMaterial::Builder(MaterialColors::AIR).doesNotBlockMovement().notOpaque().notSolid().replaceable().build();
    PORTAL = BlockMaterial::Builder(MaterialColors::AIR).doesNotBlockMovement().notOpaque().notSolid().pushBlocks().build();
    CARPET = BlockMaterial::Builder(MaterialColors::WOOL).doesNotBlockMovement().notOpaque().notSolid().flammable().build();
    PLANTS = BlockMaterial::Builder(MaterialColors::FOLIAGE).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().build();
    OCEAN_PLANT = BlockMaterial::Builder(MaterialColors::WATER).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().build();
    TALL_PLANTS = BlockMaterial::Builder(MaterialColors::FOLIAGE).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().flammable().build();
    NETHER_PLANTS = BlockMaterial::Builder(MaterialColors::FOLIAGE).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().build();
    SEA_GRASS = BlockMaterial::Builder(MaterialColors::WATER).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().build();
    WATER = BlockMaterial::Builder(MaterialColors::WATER).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().liquid().build();
    BUBBLE_COLUMN = BlockMaterial::Builder(MaterialColors::WATER).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().liquid().build();
    LAVA = BlockMaterial::Builder(MaterialColors::TNT).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().liquid().build();
    SNOW = BlockMaterial::Builder(MaterialColors::SNOW).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().build();
    FIRE = BlockMaterial::Builder(MaterialColors::AIR).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().replaceable().build();
    MISCELLANEOUS = BlockMaterial::Builder(MaterialColors::AIR).doesNotBlockMovement().notOpaque().notSolid().pushDestroys().build();
    WEB = BlockMaterial::Builder(MaterialColors::WOOL).doesNotBlockMovement().notOpaque().pushDestroys().build();
    REDSTONE_LIGHT = BlockMaterial::Builder(MaterialColors::AIR).build();
    CLAY = BlockMaterial::Builder(MaterialColors::CLAY).build();
    EARTH = BlockMaterial::Builder(MaterialColors::DIRT).build();
    ORGANIC = BlockMaterial::Builder(MaterialColors::GRASS).build();
    PACKED_ICE = BlockMaterial::Builder(MaterialColors::ICE).build();
    SAND = BlockMaterial::Builder(MaterialColors::SAND).build();
    SPONGE = BlockMaterial::Builder(MaterialColors::YELLOW).build();
    SHULKER = BlockMaterial::Builder(MaterialColors::PURPLE).build();
    WOOD = BlockMaterial::Builder(MaterialColors::WOOD).flammable().build();
    NETHER_WOOD = BlockMaterial::Builder(MaterialColors::WOOD).build();
    BAMBOO_SAPLING = BlockMaterial::Builder(MaterialColors::WOOD).flammable().pushDestroys().doesNotBlockMovement().build();
    BAMBOO = BlockMaterial::Builder(MaterialColors::WOOD).flammable().pushDestroys().build();
    WOOL = BlockMaterial::Builder(MaterialColors::WOOL).flammable().build();
    TNT = BlockMaterial::Builder(MaterialColors::TNT).flammable().notOpaque().build();
    LEAVES = BlockMaterial::Builder(MaterialColors::FOLIAGE).flammable().notOpaque().pushDestroys().build();
    GLASS = BlockMaterial::Builder(MaterialColors::AIR).notOpaque().build();
    ICE = BlockMaterial::Builder(MaterialColors::ICE).notOpaque().build();
    CACTUS = BlockMaterial::Builder(MaterialColors::FOLIAGE).notOpaque().pushDestroys().build();
    ROCK = BlockMaterial::Builder(MaterialColors::STONE).build();
    IRON = BlockMaterial::Builder(MaterialColors::IRON).build();
    SNOW_BLOCK = BlockMaterial::Builder(MaterialColors::SNOW).build();
    ANVIL = BlockMaterial::Builder(MaterialColors::IRON).pushBlocks().build();
    BARRIER = BlockMaterial::Builder(MaterialColors::AIR).pushBlocks().build();
    PISTON = BlockMaterial::Builder(MaterialColors::STONE).pushBlocks().build();
    CORAL = BlockMaterial::Builder(MaterialColors::FOLIAGE).pushDestroys().build();
    GOURD = BlockMaterial::Builder(MaterialColors::FOLIAGE).pushDestroys().build();
    DRAGON_EGG = BlockMaterial::Builder(MaterialColors::FOLIAGE).pushDestroys().build();
    CAKE = BlockMaterial::Builder(MaterialColors::AIR).pushDestroys().build();

    using namespace std::string_literals;

    const auto materials = std::array {
        std::pair{"air"s, AIR},
        std::pair{"structure_void"s, STRUCTURE_VOID},
        std::pair{"portal"s, PORTAL},
        std::pair{"carpet"s, CARPET},
        std::pair{"plants"s, PLANTS},
        std::pair{"ocean_plant"s, OCEAN_PLANT},
        std::pair{"tall_plants"s, TALL_PLANTS},
        std::pair{"nether_plants"s, NETHER_PLANTS},
        std::pair{"sea_grass"s, SEA_GRASS},
        std::pair{"water"s, WATER},
        std::pair{"bubble_column"s, BUBBLE_COLUMN},
        std::pair{"lava"s, LAVA},
        std::pair{"snow"s, SNOW},
        std::pair{"fire"s, FIRE},
        std::pair{"miscellaneous"s, MISCELLANEOUS},
        std::pair{"web"s, WEB},
        std::pair{"redstone_light"s, REDSTONE_LIGHT},
        std::pair{"clay"s, CLAY},
        std::pair{"earth"s, EARTH},
        std::pair{"organic"s, ORGANIC},
        std::pair{"packed_ice"s, PACKED_ICE},
        std::pair{"sand"s, SAND},
        std::pair{"sponge"s, SPONGE},
        std::pair{"shulker"s, SHULKER},
        std::pair{"wood"s, WOOD},
        std::pair{"nether_wood"s, NETHER_WOOD},
        std::pair{"bamboo_sapling"s, BAMBOO_SAPLING},
        std::pair{"bamboo"s, BAMBOO},
        std::pair{"wool"s, WOOL},
        std::pair{"tnt"s, TNT},
        std::pair{"leaves"s, LEAVES},
        std::pair{"glass"s, GLASS},
        std::pair{"ice"s, ICE},
        std::pair{"cactus"s, CACTUS},
        std::pair{"rock"s, ROCK},
        std::pair{"iron"s, IRON},
        std::pair{"snow_block"s, SNOW_BLOCK},
        std::pair{"anvil"s, ANVIL},
        std::pair{"barrier"s, BARRIER},
        std::pair{"piston"s, PISTON},
        std::pair{"coral"s, CORAL},
        std::pair{"gourd"s, GOURD},
        std::pair{"dragon_egg"s, DRAGON_EGG},
        std::pair{"cake"s, CAKE}
    };
}
