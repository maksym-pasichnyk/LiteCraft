#pragma once

#include "BlockData.hpp"
#include "block/material/BlockMaterial.hpp"
#include "material/DyeColors.hpp"

#include <glm/vec3.hpp>
#include <functional>
#include <utility>
#include <vector>
#include <span>
#include <map>

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
    Fence,
    FenceGate,
    Torch,
    SnowLayer,
    Cactus,
    BambooStem,
    LilyPad,
    Button,
    Anvil
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
struct WorldReader;
struct BlockReader;
struct BlockGraphics;
enum class EntityType;

struct AbstractBlock;

struct BlockBehaviour {
//    using TintTypeImpl = auto(*)(const BlockData&) -> TintType;
//    using RenderTypeImpl = auto(*)(const BlockData& data) -> RenderType;
//    using RenderLayerImpl = auto(*)(const BlockData& data) -> RenderLayer;

    using BlockColorImpl = std::function<MaterialColor(const BlockData& data)>;
    using LightLevelImpl = auto(*)(const BlockData& data) -> int32_t;
    using PositionPredicate = auto(*)(BlockReader& reader, const BlockData& data, const BlockPos& pos) -> bool;
    using ExtendedPositionPredicate = auto(*)(BlockReader& reader, const BlockData& data, const BlockPos& pos, const EntityType& type) -> bool;

    BlockMaterial *material = nullptr;
    BlockColorImpl blockColors;
    bool blocksMovement = true;
    SoundType soundType = SoundType::STONE;
    LightLevelImpl lightLevel = [](const BlockData &data) -> int32_t {
        return 0;
    };
    TintType tintType = TintType::None;
    RenderType renderType = RenderType::Block;
    RenderLayer renderLayer = RenderLayer::Opaque;

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
    PositionPredicate isOpaque = [](BlockReader &reader, const BlockData &data, const BlockPos &pos) -> bool {
        return data.getMaterial()->isOpaque;// && data.hasOpaqueCollisionShape(reader, pos);
    };
    PositionPredicate suffocates = [](BlockReader &reader, const BlockData &data, const BlockPos &pos) -> bool {
        return data.getMaterial()->isBlocksMovement;// && data.hasOpaqueCollisionShape(reader, pos);
    };
    PositionPredicate blocksVision = suffocates;
    PositionPredicate needsPostProcessing = [](BlockReader &reader, const BlockData &data, const BlockPos &pos) -> bool {
        return false;
    };
    PositionPredicate emmissiveRendering = [](BlockReader &reader, const BlockData &data, const BlockPos &pos) -> bool {
        return false;
    };
    bool variableOpacity = false;

    BlockBehaviour &doesNotBlockMovement() {
        blocksMovement = false;
        isSolid = false;
        return *this;
    }

    BlockBehaviour &notSolid() {
        isSolid = false;
        return *this;
    }

    BlockBehaviour &setSlipperiness(float slipperinessIn) {
        slipperiness = slipperinessIn;
        return *this;
    }

    BlockBehaviour &setSpeedFactor(float factor) {
        speedFactor = factor;
        return *this;
    }

    BlockBehaviour &setJumpFactor(float factor) {
        jumpFactor = factor;
        return *this;
    }

    BlockBehaviour &setSound(SoundType soundTypeIn) {
        soundType = soundTypeIn;
        return *this;
    }

    BlockBehaviour &setLightLevel(LightLevelImpl fn) {
        lightLevel = fn;
        return *this;
    }

    BlockBehaviour &setHardnessAndResistance(float hardnessIn, float resistanceIn) {
        hardness = hardnessIn;
        resistance = std::max(0.0F, resistanceIn);
        return *this;
    }

    BlockBehaviour &zeroHardnessAndResistance() {
        return setHardnessAndResistance(0.0F);
    }

    BlockBehaviour &setHardnessAndResistance(float hardnessAndResistance) {
        return setHardnessAndResistance(hardnessAndResistance, hardnessAndResistance);
    }

    BlockBehaviour &setTickRandomly() {
        ticksRandomly = true;
        return *this;
    }

    BlockBehaviour &setVariableOpacity() {
        variableOpacity = true;
        return *this;
    }

    BlockBehaviour &noDrops() {
//        lootTable = LootTables.EMPTY;
        return *this;
    }

    BlockBehaviour &setLootFrom(Block* block) {
//        lootTable = block->getLootTable();
        return *this;
    }

    BlockBehaviour &setAir() {
        isAir = true;
        return *this;
    }

    BlockBehaviour &setTintType(TintType v) {
        tintType = v;
        return *this;
    }

    BlockBehaviour &setRenderType(RenderType v) {
        renderType = v;
        return *this;
    }

    BlockBehaviour &setRenderLayer(RenderLayer v) {
        renderLayer = v;
        return *this;
    }

    BlockBehaviour &setAllowsSpawn(ExtendedPositionPredicate fn) {
//        allowsSpawn = std::move(fn);
        return *this;
    }

    BlockBehaviour &setOpaque(PositionPredicate fn) {
        isOpaque = fn;
        return *this;
    }

    BlockBehaviour &setSuffocates(PositionPredicate fn) {
        suffocates = fn;
        return *this;
    }

    BlockBehaviour &setBlocksVision(PositionPredicate fn) {
        blocksVision = fn;
        return *this;
    }

    BlockBehaviour &setNeedsPostProcessing(PositionPredicate fn) {
        needsPostProcessing = fn;
        return *this;
    }

    BlockBehaviour &setEmmisiveRendering(PositionPredicate fn) {
        emmissiveRendering = fn;
        return *this;
    }

    BlockBehaviour &setRequiresTool() {
        requiresTool = true;
        return *this;
    }
};

struct AbstractBlock {
    int id;
    BlockBehaviour behaviour;
    BlockGraphics* graphics{nullptr};

    using PropertyGet = auto(*)(BlockData) -> PropertyValue;
    using PropertySet = auto(*)(BlockData, const PropertyValue &) -> BlockData;

    std::map<Property, std::pair<PropertyGet, PropertySet>> state_properties_binds{};
    std::map<std::string, Property> state_properties_names{};

    explicit AbstractBlock(int id, BlockBehaviour behaviour) : id(id), behaviour(std::move(behaviour)) {}

    auto getMaterial() -> BlockMaterial * {
        return behaviour.material;
    }

    auto getGraphics() -> BlockGraphics& {
        return *graphics;
    }

    auto getMaterialColor() -> MaterialColor {
        return behaviour.material->color;
    }

    auto getLightLevel(const BlockData& data) -> int32_t {
        return behaviour.lightLevel(data);
    }

    auto isOpaque(BlockReader &reader, const BlockData &data, const BlockPos &pos) const -> bool {
        return behaviour.isOpaque(reader, data, pos);
    }

    auto getTintType() const -> TintType {
        return behaviour.tintType;
    }

    auto getRenderType() const -> RenderType {
        return behaviour.renderType;
    }

    auto getRenderLayer() const -> RenderLayer {
        return behaviour.renderLayer;
    }

    virtual auto isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) -> bool {
        return true;
    }

    template <Property property, auto get, auto set>
    void bind() {
        using T = typename TypeFrom<property>::type;

        state_properties_binds.insert_or_assign(property, std::pair<PropertyGet, PropertySet>{
            [](BlockData state) -> PropertyValue {
                return get(state);
            },
            [](BlockData state, const PropertyValue & value) -> BlockData {
                return set(state, std::get<T>(value));
            }
        });
        state_properties_names.insert_or_assign(PropertyUtil::name(property).value(), property);
    }
};

struct BlockBehaviourUtil {
    static auto create(BlockMaterial * material) -> BlockBehaviour {
        return {
            .material = material,
            .blockColors = [material](const BlockData& data) {
                return material->color;
            }
        };
    }

    static auto create(BlockMaterial * material, DyeColors color) -> BlockBehaviour {
        return {
            .material = material,
            .blockColors = [material, color](const BlockData& data) {
                return material->color; //color.getMapColor()
            }
        };
    }

    static auto create(BlockMaterial * material, MaterialColor color) -> BlockBehaviour {
        return {
            .material = material,
            .blockColors = [color](const BlockData& data) {
                return color;
            }
        };
    }

    static auto create(BlockMaterial * material, BlockBehaviour::BlockColorImpl blockColors) -> BlockBehaviour {
        return {
            .material = material,
            .blockColors = std::move(blockColors)
        };
    }

    static auto from(AbstractBlock* block) -> BlockBehaviour {
        return block->behaviour;
    }
};