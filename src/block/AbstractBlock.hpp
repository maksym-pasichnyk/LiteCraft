#pragma once

#include "material/Material.hpp"
#include "material/DyeColors.hpp"

#include <glm/vec3.hpp>
#include <functional>
#include <utility>
#include <span>

enum class TintType {
    None,
    Grass,
    Foliage
};

enum class RenderType {
    Air,
    Liquid,
    Block,
    Leaves,
    Cross,
    Pane,
    Torch,
    SnowLayer,
    Cactus,
};

enum class RenderLayer {
    Opaque,
    Cutout,
    Transparent
};

enum class SoundType {
    WOOD,
    GROUND,
    PLANT,
    LILY_PADS,
    STONE,
    METAL,
    GLASS,
    CLOTH,
    SAND,
    SNOW,
    LADDER,
    ANVIL,
    SLIME,
    HONEY,
    WET_GRASS,
    CORAL,
    BAMBOO,
    BAMBOO_SAPLING,
    SCAFFOLDING,
    SWEET_BERRY_BUSH,
    CROP,
    STEM,
    VINE,
    NETHER_WART,
    LANTERN,
    HYPHAE,
    NYLIUM,
    FUNGUS,
    ROOT,
    SHROOMLIGHT,
    NETHER_VINE,
    NETHER_VINE_LOWER_PITCH,
    SOUL_SAND,
    SOUL_SOIL,
    BASALT,
    WART,
    NETHERRACK,
    NETHER_BRICK,
    NETHER_SPROUT,
    NETHER_ORE,
    BONE,
    NETHERITE,
    ANCIENT_DEBRIS,
    LODESTONE,
    CHAIN,
    NETHER_GOLD,
    GILDED_BLACKSTONE
};

struct Block;
struct BlockData;
struct EntityType;
struct WorldReader;
struct BlockReader;
struct BlockGraphics;
enum class BlockStateProperties;

struct AbstractBlock {
    using IBlockColor = std::function<MaterialColor(const BlockData& data)>;
    using ILightLevel = std::function<int32_t(const BlockData& data)>;
    using IPositionPredicate = std::function<bool(BlockReader& reader, const BlockData& data, const glm::ivec3& pos)>;
    using IExtendedPositionPredicate = std::function<bool(BlockReader& reader, const BlockData& data, const glm::ivec3& pos, const EntityType& type)>;

    struct Properties {
        Material *material = nullptr;
        IBlockColor blockColors;
        bool blocksMovement = true;
        SoundType soundType = SoundType::STONE;
        ILightLevel lightLevel = [](const BlockData &data) -> int32_t {
            return 0;
        };
        float resistance = 0.0f;
        float hardness = 0.0f;
        bool requiresTool = false;
        bool ticksRandomly = false;
        float slipperiness = 0.6F;
        float speedFactor = 1.0F;
        float jumpFactor = 1.0F;
        /*ResourceLocation lootTable;*/
        bool isSolid = true;
        bool isAir = false;
        IPositionPredicate isOpaque = [](BlockReader &reader, const BlockData &data, const glm::ivec3 &pos) -> bool {
            return false;
        };
        IPositionPredicate suffocates = [](BlockReader &reader, const BlockData &data, const glm::ivec3 &pos) -> bool {
            return false;
        };
        IPositionPredicate blocksVision = suffocates;
        IPositionPredicate needsPostProcessing = [](BlockReader &reader, const BlockData &data, const glm::ivec3 &pos) -> bool {
            return false;
        };
        IPositionPredicate emmissiveRendering = [](BlockReader &reader, const BlockData &data, const glm::ivec3 &pos) -> bool {
            return false;
        };
        bool variableOpacity = false;

        static Properties create(Material* material) {
            return {
                .material = material,
                .blockColors = [material](const BlockData& data) {
                    return material->color;
                }
            };
        }
//
        static Properties create(Material* material, DyeColors color) {
            return {
                .material = material,
                .blockColors = [material, color](const BlockData& data) {
                    return material->color; //color.getMapColor()
                }
            };
        }

        static Properties create(Material* material, MaterialColor color) {
            return {
                .material = material,
                .blockColors = [color](const BlockData& data) {
                    return color;
                }
            };
        }

        static Properties create(Material* material, IBlockColor blockColors) {
            return {
                .material = material,
                .blockColors = std::move(blockColors)
            };
        }

        static Properties from(AbstractBlock* block) {
            return block->properties;
        }

        Properties &doesNotBlockMovement() {
            blocksMovement = false;
            isSolid = false;
            return *this;
        }

        Properties &notSolid() {
            isSolid = false;
            return *this;
        }

        Properties &setSlipperiness(float slipperinessIn) {
            slipperiness = slipperinessIn;
            return *this;
        }

        Properties &setSpeedFactor(float factor) {
            speedFactor = factor;
            return *this;
        }

        Properties &setJumpFactor(float factor) {
            jumpFactor = factor;
            return *this;
        }

        Properties &setSound(SoundType soundTypeIn) {
            soundType = soundTypeIn;
            return *this;
        }

        Properties &setLightLevel(ILightLevel stateLightFunction) {
            lightLevel = std::move(stateLightFunction);
            return *this;
        }

        Properties &setHardnessAndResistance(float hardnessIn, float resistanceIn) {
            hardness = hardnessIn;
            resistance = std::max(0.0F, resistanceIn);
            return *this;
        }

        Properties &zeroHardnessAndResistance() {
            return setHardnessAndResistance(0.0F);
        }

        Properties &setHardnessAndResistance(float hardnessAndResistance) {
            return setHardnessAndResistance(hardnessAndResistance, hardnessAndResistance);
        }

        Properties &setTickRandomly() {
            ticksRandomly = true;
            return *this;
        }

        Properties &setVariableOpacity() {
            variableOpacity = true;
            return *this;
        }

        Properties &noDrops() {
//            lootTable = LootTables.EMPTY;
            return *this;
        }

        Properties &setLootFrom(Block* block) {
//            lootTable = block->getLootTable();
            return *this;
        }

        Properties &setAir() {
            isAir = true;
            return *this;
        }

        Properties &setAllowsSpawn(IExtendedPositionPredicate allowsSpawn) {
            allowsSpawn = std::move(allowsSpawn);
            return *this;
        }

        Properties &setOpaque(IPositionPredicate opaquePredicate) {
            isOpaque = std::move(opaquePredicate);
            return *this;
        }

        Properties &setSuffocates(IPositionPredicate suffocatesPredicate) {
            suffocates = std::move(suffocatesPredicate);
            return *this;
        }

        Properties &setBlocksVision(IPositionPredicate blocksVisionPredicate) {
            blocksVision = std::move(blocksVisionPredicate);
            return *this;
        }

        Properties &setNeedsPostProcessing(IPositionPredicate postProcessingPredicate) {
            needsPostProcessing = std::move(postProcessingPredicate);
            return *this;
        }

        Properties &setEmmisiveRendering(IPositionPredicate emmisiveRenderPredicate) {
            emmissiveRendering = std::move(emmisiveRenderPredicate);
            return *this;
        }

        Properties &setRequiresTool() {
            requiresTool = true;
            return *this;
        }
    };

    int id;
    Properties properties;
    std::vector<BlockStateProperties> blockStateProperties;
    BlockGraphics* graphics{nullptr};

    explicit AbstractBlock(int id, Properties properties) : id(id), properties(std::move(properties)) {}

    Material* getMaterial() {
        return properties.material;
    }

    BlockGraphics& getGraphics() {
        return *graphics;
    }

    MaterialColor getMaterialColor() {
        return properties.material->color;
    }

    int32_t getLightLevel(const BlockData& data) {
        return properties.lightLevel(data);
    }

    std::span<BlockStateProperties> getBlockStateProperties() {
        return blockStateProperties;
    }

    virtual TintType getTintType() const {
        return TintType::None;
    }

    virtual RenderType getRenderType() const {
        return RenderType::Block;
    }

    virtual RenderLayer getRenderLayer() const {
        return RenderLayer::Opaque;
    }

    virtual bool isValidPosition(const BlockData& data, WorldReader &reader, const glm::ivec3 &pos) {
        return true;
    }
};