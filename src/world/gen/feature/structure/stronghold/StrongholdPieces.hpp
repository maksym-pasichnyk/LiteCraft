//#pragma once
//
//#include <world/gen/feature/structure/StructurePiece.hpp>
//
//struct StrongholdPieces {
//    struct Piece;
//    struct Straight;
//    struct Crossing;
//    struct RoomCrossing;
//    struct Stairs;
//    struct Stairs2;
//    struct StairsStraight;
//    struct Corridor;
//    struct ChestCorridor;
//    struct Turn;
//    struct LeftTurn;
//    struct RightTurn;
//    struct Prison;
//    struct PortalRoom;
//    struct Library;
//
//    struct Factory {
//        auto(*createPiece)(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//
//        template <typename T>
//        static constexpr auto from() noexcept -> Factory {
//            return Factory{
//                .createPiece = [](std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
//                    return T::createPiece(pieces, random, x, y, z, facing, componentIndex);
//                }
//            };
//        }
//    };
//
//    struct PieceWeight {
//        size_t id = -1;
//        Factory factory{};
//        int pieceWeight = 0;
//        int instancesLimit = 0;
//        int instancesSpawned = 0;
//        tl::optional<int> optLimit = tl::nullopt;
//
//        auto canSpawnMoreStructures() const -> bool {
//            return instancesLimit == 0 || instancesSpawned < instancesLimit;
//        }
//        auto canSpawnMoreStructuresOfType(int type) const -> bool {
//            return (instancesLimit == 0 || instancesSpawned < instancesLimit) && (!optLimit.has_value() || *optLimit > type);
//        }
//    };
//
//    static int totalWeight;
//    static std::vector<PieceWeight> structurePieceList;
//    static tl::optional<Factory> strongComponentType;
//
//    static void prepareStructurePieces();
//    static auto canAddStructurePieces() -> bool;
//    static auto findAndCreatePieceFactory(const Factory& factory, std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//    static auto generatePieceFromSmallDoor(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//    static auto generateAndAddPiece(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> StructurePiece*;
//};
//
//struct StrongholdPieces::Piece : StructurePiece {
//    enum class Door {
//        OPENING,
//        WOOD_DOOR,
//        GRATES,
//        IRON_DOOR
//    };
//
//    Door entryDoor = Door::OPENING;
//
//    Piece(int piecedex) : StructurePiece(piecedex) {}
//
//    void placeDoor(WorldGenRegion& region, Random& random, const BoundingBox& bb, Door door, int x, int y, int z);
//
//    auto getNextComponentNormal(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int x, int y) -> StructurePiece*;
//    auto getNextComponentX(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int y, int z) -> StructurePiece*;
//    auto getNextComponentZ(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int y, int z) -> StructurePiece*;
//
//    static auto getRandomDoor(Random& random) -> Door {
//        switch (random.nextInt(5)) {
//            case 0:
//            case 1:
//            default:
//                return Door::OPENING;
//            case 2:
//                return Door::WOOD_DOOR;
//            case 3:
//                return Door::GRATES;
//            case 4:
//                return Door::IRON_DOOR;
//        }
//    }
//
//    static auto canStrongholdGoDeeper(const BoundingBox& bb) -> bool {
//        return /*bb != null &&*/ bb.minY > 10;
//    }
//};
//
//struct StrongholdPieces::Straight : Piece {
//    bool expandsX = false;
//    bool expandsZ = false;
//
//    Straight(int piecedex, Random& random, const BoundingBox& bb, Direction facing) : Piece(piecedex) {
//        setCoordBaseMode(facing);
//        entryDoor = getRandomDoor(random);
//        bounds = bb;
//        expandsX = random.nextInt(2) == 0;
//        expandsZ = random.nextInt(2) == 0;
//    }
//
//    void buildComponent(StructurePiece* piece, std::vector<StructurePiece*>& pieces, Random& random);
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::Crossing : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::RoomCrossing : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::Stairs : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::Stairs2 : Piece {
//    tl::optional<PieceWeight> lastPlaced = tl::nullopt;
//    std::vector<StructurePiece*> pendingChildren{};
//
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::StairsStraight : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::Corridor : Piece {
//    int steps = 0;
//
//    Corridor(int componentIndex, const BoundingBox& bb, Direction facing) : Piece(componentIndex) {
//        setCoordBaseMode(facing);
//        bounds = bb;
//        steps = facing != Direction::NORTH && facing != Direction::SOUTH ? bb.getXSize() : bb.getZSize();
//    }
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override;
//
//    static auto findPieceBox(std::span<StructurePiece*> pieces, Random& random, int x, int y, int z, Direction facing) -> tl::optional<BoundingBox> {
//        auto bounds = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 4, facing);
//        auto piece = StructurePiece::findIntersecting(pieces, bounds);
//        if (piece != nullptr && piece->getBoundingBox().minY == bounds.minY) {
//            for (int i = 3; i >= 1; --i) {
//                bounds = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, i - 1, facing);
//                if (!piece->getBoundingBox().intersectsWith(bounds)) {
//                    return BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, i, facing);
//                }
//            }
//        }
//        return tl::nullopt;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::ChestCorridor : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::Turn : Piece {
//    using Piece::Piece;
//
//};
//
//struct StrongholdPieces::LeftTurn : Turn {
//    using Turn::Turn;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::RightTurn : Turn {
//    using Turn::Turn;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::Prison : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::PortalRoom : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
//
//struct StrongholdPieces::Library : Piece {
//    using Piece::Piece;
//
//    bool addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) override {
//        return true;
//    }
//
//    static auto createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece*;
//};
