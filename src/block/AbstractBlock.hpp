#pragma once

#include "BlockData.hpp"
#include "BlockRenderShape.hpp"
#include "material/DyeColors.hpp"
#include "block/material/BlockMaterial.hpp"

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
    RenderType renderType = RenderType::Opaque;
    BlockRenderShape renderShape = BlockRenderShape::MODEL;

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

    BlockBehaviour &setTintType(TintType type) {
        tintType = type;
        return *this;
    }

    BlockBehaviour &setRenderShape(BlockRenderShape shape) {
        renderShape = shape;
        return *this;
    }

    BlockBehaviour &setRenderType(RenderType type) {
        renderType = type;
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
//    BlockGraphics* graphics{nullptr};

    using PropertyGet = auto(*)(BlockData) -> PropertyValue;
    using PropertySet = auto(*)(BlockData, const PropertyValue &) -> BlockData;

    std::map<std::string, Property> properties{};
    std::map<Property, std::pair<PropertyGet, PropertySet>> binds{};

    explicit AbstractBlock(int id, BlockBehaviour behaviour) : id(id), behaviour(std::move(behaviour)) {}

    auto getMaterial() -> BlockMaterial * {
        return behaviour.material;
    }

//    auto getGraphics() -> BlockGraphics& {
//        return *graphics;
//    }

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

    auto getRenderShape() const -> BlockRenderShape {
        return behaviour.renderShape;
    }

    auto getRenderType() const -> RenderType {
        return behaviour.renderType;
    }

    virtual auto isValidPosition(const BlockData& data, WorldReader &reader, const BlockPos &pos) -> bool {
        return true;
    }

    template <Property property, auto get, auto set>
    void bind() {
        using T = typename TypeFrom<property>::type;

        binds.insert_or_assign(property, std::pair<PropertyGet, PropertySet>{
            [](BlockData state) -> PropertyValue { return get(state); },
            [](BlockData state, const PropertyValue & value) -> BlockData {
                return set(state, std::get<T>(value));
            }
        });
        properties.insert_or_assign(PropertyUtil::name(property), property);
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