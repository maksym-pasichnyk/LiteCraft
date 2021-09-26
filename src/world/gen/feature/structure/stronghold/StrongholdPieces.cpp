//#include "StrongholdPieces.hpp"
//#include <block/Blocks.hpp>
//#include <block/PaneBlock.hpp>
//#include <block/DoorBlock.hpp>
//#include <block/WallTorchBlock.hpp>
//#include <block/AbstractButtonBlock.hpp>
//
//struct StrongholdStones : BlockSelector {
//    auto select(Random& random, int x, int y, int z, bool wall) -> BlockData override {
//        if (wall) {
//            float f = random.nextFloat();
//            if (f < 0.2F) {
//                return Blocks::CRACKED_STONE_BRICKS->getDefaultState();
//            } else if (f < 0.5F) {
//                return Blocks::MOSSY_STONE_BRICKS->getDefaultState();
//            } else if (f < 0.55F) {
//                return Blocks::INFESTED_STONE_BRICKS->getDefaultState();
//            } else {
//                return Blocks::STONE_BRICKS->getDefaultState();
//            }
//        }
//        return Blocks::CAVE_AIR->getDefaultState();
//    }
//};
//
//int StrongholdPieces::totalWeight = 0;
//std::vector<StrongholdPieces::PieceWeight> StrongholdPieces::structurePieceList{};
//std::optional<StrongholdPieces::Factory> StrongholdPieces::strongComponentType = std::nullopt;
//
//static constexpr std::array PIECE_WEIGHTS {
//    StrongholdPieces::PieceWeight{0, StrongholdPieces::Factory::from<StrongholdPieces::Straight>(), 40, 0, 0},
//    StrongholdPieces::PieceWeight{1, StrongholdPieces::Factory::from<StrongholdPieces::Prison>(), 5, 5, 0},
//    StrongholdPieces::PieceWeight{2, StrongholdPieces::Factory::from<StrongholdPieces::LeftTurn>(), 20, 0},
//    StrongholdPieces::PieceWeight{3, StrongholdPieces::Factory::from<StrongholdPieces::RightTurn>(), 20, 0},
//    StrongholdPieces::PieceWeight{4, StrongholdPieces::Factory::from<StrongholdPieces::RoomCrossing>(), 10, 6},
//    StrongholdPieces::PieceWeight{5, StrongholdPieces::Factory::from<StrongholdPieces::StairsStraight>(), 5, 5},
//    StrongholdPieces::PieceWeight{6, StrongholdPieces::Factory::from<StrongholdPieces::Stairs>(), 5, 5},
//    StrongholdPieces::PieceWeight{7, StrongholdPieces::Factory::from<StrongholdPieces::Crossing>(), 5, 4},
//    StrongholdPieces::PieceWeight{8, StrongholdPieces::Factory::from<StrongholdPieces::ChestCorridor>(), 5, 4},
//    StrongholdPieces::PieceWeight{9, StrongholdPieces::Factory::from<StrongholdPieces::Library>(), 10, 2, 4},
//    StrongholdPieces::PieceWeight{10, StrongholdPieces::Factory::from<StrongholdPieces::PortalRoom>(), 10, 2, 5}
//};
//
//void StrongholdPieces::prepareStructurePieces() {
//    structurePieceList.clear();
//
//    for (auto& pieceweight : PIECE_WEIGHTS) {
//        pieceweight.instancesSpawned = 0;
//        structurePieceList.emplace_back(pieceweight);
//    }
//
//    strongComponentType = std::nullopt;
//}
//
//auto StrongholdPieces::canAddStructurePieces() -> bool {
//    bool flag = false;
//    totalWeight = 0;
//
//    for (const auto& pieceweight : structurePieceList) {
//        if (pieceweight.instancesLimit > 0 && pieceweight.instancesSpawned < pieceweight.instancesLimit) {
//            flag = true;
//        }
//
//        totalWeight += pieceweight.pieceWeight;
//    }
//
//    return flag;
//}
//
//auto StrongholdPieces::findAndCreatePieceFactory(const Factory& factory, std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
//    return factory.createPiece(pieces, random, x, y, z, facing, componentIndex);
//}
//
//auto StrongholdPieces::generatePieceFromSmallDoor(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
//    if (!canAddStructurePieces()) {
//        return nullptr;
//    }
//
//    if (strongComponentType.has_value()) {
//        auto piece = findAndCreatePieceFactory(*strongComponentType, pieces, random, x, y, z, facing, componentIndex);
//        strongComponentType = std::nullopt;
//        if (piece != nullptr) {
//            return piece;
//        }
//    }
//
//    for (int i = 0; i < 5; ++i) {
//        auto total_weight = random.nextInt(totalWeight);
//        for (auto &pieceweight : structurePieceList) {
//            total_weight -= pieceweight.pieceWeight;
//            if (total_weight < 0) {
//                if (!pieceweight.canSpawnMoreStructuresOfType(componentIndex) || stairs->lastPlaced.has_value() && pieceweight.id == stairs->lastPlaced->id) {
//                    break;
//                }
//
//                auto piece = findAndCreatePieceFactory(pieceweight.factory, pieces, random, x, y, z, facing, componentIndex);
//                if (piece != nullptr) {
//                    ++pieceweight.instancesSpawned;
//                    stairs->lastPlaced = pieceweight;
//                    if (!pieceweight.canSpawnMoreStructures()) {
//                        std::erase(structurePieceList, pieceweight);
//                    }
//
//                    return piece;
//                }
//            }
//        }
//    }
//
//    const auto bb = Corridor::findPieceBox(pieces, random, x, y, z, facing);
//    if (bb.has_value() && bb->minY > 1) {
//        return new Corridor(componentIndex, *bb, facing);
//    }
//    return nullptr;
//}
//
//auto StrongholdPieces::generateAndAddPiece(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> StructurePiece* {
//    if (componentIndex <= 50 && std::abs(x - stairs->getBoundingBox().minX) <= 112 && std::abs(z - stairs->getBoundingBox().minZ) <= 112) {
//        auto piece = generatePieceFromSmallDoor(stairs, pieces, random, x, y, z, facing, componentIndex + 1);
//        if (piece != nullptr) {
//            pieces.emplace_back(piece);
//            stairs->pendingChildren.emplace_back(piece);
//        }
//        return piece;
//    }
//    return nullptr;
//}
//
//void StrongholdPieces::Piece::placeDoor(WorldGenRegion& region, Random& random, const BoundingBox& bb, Door door, int x, int y, int z) {
//    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();
//    const auto OAK_DOOR = Blocks::OAK_DOOR->getDefaultState();
//    const auto IRON_DOOR = Blocks::IRON_DOOR->getDefaultState();
//    const auto IRON_BARS = Blocks::IRON_BARS->getDefaultState();
//    const auto STONE_BUTTON = Blocks::STONE_BUTTON->getDefaultState();
//    const auto STONE_BRICKS = Blocks::STONE_BRICKS->getDefaultState();
//
//    switch (door) {
//        case Door::OPENING:
//            fillWithBlocks(region, bb, x, y, z, x + 3 - 1, y + 3 - 1, z, CAVE_AIR, CAVE_AIR, false);
//            break;
//        case Door::WOOD_DOOR:
//            setBlockState(region, STONE_BRICKS, x, y, z, bb);
//            setBlockState(region, STONE_BRICKS, x, y + 1, z, bb);
//            setBlockState(region, STONE_BRICKS, x, y + 2, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 1, y + 2, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 2, y + 2, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 2, y + 1, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 2, y, z, bb);
//            setBlockState(region, OAK_DOOR, x + 1, y, z, bb);
//            setBlockState(region, OAK_DOOR.set<DoorBlock::HALF>(DoubleBlockHalf::UPPER), x + 1, y + 1, z, bb);
//            break;
//        case Door::GRATES:
//            setBlockState(region, CAVE_AIR, x + 1, y, z, bb);
//            setBlockState(region, CAVE_AIR, x + 1, y + 1, z, bb);
//            setBlockState(region, IRON_BARS.set<PaneBlock::WEST>(true), x, y, z, bb);
//            setBlockState(region, IRON_BARS.set<PaneBlock::WEST>(true), x, y + 1, z, bb);
//            setBlockState(region, IRON_BARS.set<PaneBlock::EAST>(true).set<PaneBlock::WEST>(true), x, y + 2, z, bb);
//            setBlockState(region, IRON_BARS.set<PaneBlock::EAST>(true).set<PaneBlock::WEST>(true), x + 1, y + 2, z, bb);
//            setBlockState(region, IRON_BARS.set<PaneBlock::EAST>(true).set<PaneBlock::WEST>(true), x + 2, y + 2, z, bb);
//            setBlockState(region, IRON_BARS.set<PaneBlock::EAST>(true), x + 2, y + 1, z, bb);
//            setBlockState(region, IRON_BARS.set<PaneBlock::EAST>(true), x + 2, y, z, bb);
//            break;
//        case Door::IRON_DOOR:
//            setBlockState(region, STONE_BRICKS, x, y, z, bb);
//            setBlockState(region, STONE_BRICKS, x, y + 1, z, bb);
//            setBlockState(region, STONE_BRICKS, x, y + 2, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 1, y + 2, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 2, y + 2, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 2, y + 1, z, bb);
//            setBlockState(region, STONE_BRICKS, x + 2, y, z, bb);
//            setBlockState(region, IRON_DOOR, x + 1, y, z, bb);
//            setBlockState(region, IRON_DOOR.set<DoorBlock::HALF>(DoubleBlockHalf::UPPER), x + 1, y + 1, z, bb);
//            setBlockState(region, STONE_BUTTON.set<AbstractButtonBlock::FACING>(Direction::NORTH), x + 2, y + 1, z + 1, bb);
//            setBlockState(region, STONE_BUTTON.set<AbstractButtonBlock::FACING>(Direction::SOUTH), x + 2, y + 1, z - 1, bb);
//            break;
//        default:
//            break;
//    }
//}
//
//auto StrongholdPieces::Piece::getNextComponentNormal(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int x, int y) -> StructurePiece* {
//    if (coordBaseMode) {
//        switch (auto direction = *coordBaseMode) {
//            case Direction::NORTH:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX + x, bounds.minY + y, bounds.minZ - 1, direction, getComponentType());
//            case Direction::SOUTH:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX + x, bounds.minY + y, bounds.maxZ + 1, direction, getComponentType());
//            case Direction::WEST:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX - 1, bounds.minY + y, bounds.minZ + x, direction, getComponentType());
//            case Direction::EAST:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.maxX + 1, bounds.minY + y, bounds.minZ + x, direction, getComponentType());
//            default:
//                break;
//        }
//    }
//
//    return nullptr;
//}
//
//auto StrongholdPieces::Piece::getNextComponentX(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int y, int z) -> StructurePiece* {
//    if (coordBaseMode) {
//        switch (auto direction = *coordBaseMode) {
//            case Direction::NORTH:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX - 1, bounds.minY + y, bounds.minZ + z, Direction::WEST, getComponentType());
//            case Direction::SOUTH:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX - 1, bounds.minY + y, bounds.minZ + z, Direction::WEST, getComponentType());
//            case Direction::WEST:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX + z, bounds.minY + y, bounds.minZ - 1, Direction::NORTH, getComponentType());
//            case Direction::EAST:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX + z, bounds.minY + y, bounds.minZ - 1, Direction::NORTH, getComponentType());
//            default:
//                break;
//        }
//    }
//
//    return nullptr;
//}
//
//auto StrongholdPieces::Piece::getNextComponentZ(Stairs2* stairs, std::vector<StructurePiece*>& pieces, Random& random, int y, int z) -> StructurePiece* {
//    if (coordBaseMode) {
//        switch (auto direction = *coordBaseMode) {
//            case Direction::NORTH:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.maxX + 1, bounds.minY + y, bounds.minZ + z, Direction::EAST, getComponentType());
//            case Direction::SOUTH:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.maxX + 1, bounds.minY + y, bounds.minZ + z, Direction::EAST, getComponentType());
//            case Direction::WEST:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX + z, bounds.minY + y, bounds.maxZ + 1, Direction::SOUTH, getComponentType());
//            case Direction::EAST:
//                return StrongholdPieces::generateAndAddPiece(stairs, pieces, random, bounds.minX + z, bounds.minY + y, bounds.maxZ + 1, Direction::SOUTH, getComponentType());
//            default:
//                break;
//        }
//    }
//
//    return nullptr;
//}
//
//void StrongholdPieces::Straight::buildComponent(StructurePiece* piece, std::vector<StructurePiece*>& pieces, Random& random) {
//    auto stairs = dynamic_cast<Stairs2*>(piece);
//
//    getNextComponentNormal(stairs, pieces, random, 1, 1);
//    if (expandsX) {
//        getNextComponentX(stairs, pieces, random, 1, 2);
//    }
//
//    if (expandsZ) {
//        getNextComponentZ(stairs, pieces, random, 1, 2);
//    }
//}
//
//bool StrongholdPieces::Straight::addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) {
//    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();
//    const auto WALL_TORCH = Blocks::WALL_TORCH->getDefaultState();
//    const auto WALL_TORCH_EAST = WALL_TORCH.set<WallTorchBlock::FACING>(Direction::EAST);
//    const auto WALL_TORCH_WEST = WALL_TORCH.set<WallTorchBlock::FACING>(Direction::WEST);
//
//    StrongholdStones STRONGHOLD_STONES{};
//
//    fillWithRandomizedBlocks(region, bb, 0, 0, 0, 4, 4, 6, true, random, STRONGHOLD_STONES);
//    placeDoor(region, random, bb, entryDoor, 1, 1, 0);
//    placeDoor(region, random, bb, Door::OPENING, 1, 1, 6);
//    randomlyPlaceBlock(region, bb, random, 0.1F, 1, 2, 1, WALL_TORCH_EAST);
//    randomlyPlaceBlock(region, bb, random, 0.1F, 3, 2, 1, WALL_TORCH_WEST);
//    randomlyPlaceBlock(region, bb, random, 0.1F, 1, 2, 5, WALL_TORCH_EAST);
//    randomlyPlaceBlock(region, bb, random, 0.1F, 3, 2, 5, WALL_TORCH_WEST);
//    if (expandsX) {
//        fillWithBlocks(region, bb, 0, 1, 2, 0, 3, 4, CAVE_AIR, CAVE_AIR, false);
//    }
//
//    if (expandsZ) {
//        fillWithBlocks(region, bb, 4, 1, 2, 4, 3, 4, CAVE_AIR, CAVE_AIR, false);
//    }
//    return true;
//}
//
//bool StrongholdPieces::Corridor::addComponentParts(WorldGenRegion& region, TemplateManager& templates, ChunkGenerator& generator, Random& random, const BoundingBox& bb, const ChunkPos& chunkPos, const BlockPos& blockPos) {
//    const auto CAVE_AIR = Blocks::CAVE_AIR->getDefaultState();
//    const auto STONE_BRICKS = Blocks::STONE_BRICKS->getDefaultState();
//
//    for (int i = 0; i < steps; ++i) {
//        setBlockState(region, STONE_BRICKS, 0, 0, i, bb);
//        setBlockState(region, STONE_BRICKS, 1, 0, i, bb);
//        setBlockState(region, STONE_BRICKS, 2, 0, i, bb);
//        setBlockState(region, STONE_BRICKS, 3, 0, i, bb);
//        setBlockState(region, STONE_BRICKS, 4, 0, i, bb);
//
//        for (int j = 1; j <= 3; ++j) {
//            setBlockState(region, STONE_BRICKS, 0, j, i, bb);
//            setBlockState(region, CAVE_AIR, 1, j, i, bb);
//            setBlockState(region, CAVE_AIR, 2, j, i, bb);
//            setBlockState(region, CAVE_AIR, 3, j, i, bb);
//            setBlockState(region, STONE_BRICKS, 4, j, i, bb);
//        }
//
//        setBlockState(region, STONE_BRICKS, 0, 4, i, bb);
//        setBlockState(region, STONE_BRICKS, 1, 4, i, bb);
//        setBlockState(region, STONE_BRICKS, 2, 4, i, bb);
//        setBlockState(region, STONE_BRICKS, 3, 4, i, bb);
//        setBlockState(region, STONE_BRICKS, 4, 4, i, bb);
//    }
//
//    return true;
//}
/*auto StrongholdPieces::Piece::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Piece(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::Straight::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Straight(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::Crossing::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Crossing(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::RoomCrossing::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new RoomCrossing(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::Stairs::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Stairs(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::Stairs2::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Stairs2(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::StairsStraight::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new StairsStraight(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::Corridor::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Corridor(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::ChestCorridor::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new ChestCorridor(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::LeftTurn::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new LeftTurn(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::RightTurn::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new RightTurn(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::Prison::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Prison(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::PortalRoom::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new PortalRoom(componentIndex, bb, facing);
    }
    return nullptr;
}

auto StrongholdPieces::Library::createPiece(std::vector<StructurePiece*>& pieces, Random& random, int x, int y, int z, Direction facing, int componentIndex) -> Piece* {
    const auto bb = BoundingBox::getComponentToAddBoundingBox(x, y, z, -1, -1, 0, 5, 5, 7, facing);
    if (canStrongholdGoDeeper(bb) && !StructurePiece::hasIntersecting(pieces, bb)) {
        return new Library(componentIndex, bb, facing);
    }
    return nullptr;
}*/

