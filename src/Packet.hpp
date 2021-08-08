#pragma once

#include "block/BlockData.hpp"
#include <glm/vec3.hpp>

template <typename T>
concept Packet = requires {
    T::ID;
};

struct PacketHeader {
    int id;
    int size;
};

struct Chunk;

enum class ProtocolType {
    HANDSHAKING = -1,
    PLAY = 0,
    STATUS = 1,
    LOGIN = 2
};

enum class SPacketType {
    EncryptionRequest,
    EnableCompression,
    LoginSuccess,
    LoadChunk,
    UnloadChunk,
    SpawnPlayer,
    ChangeBlock,
};

enum class CPacketType {
    Handshake,
    LoginStart,
    EncryptionResponse,
    Position,
    PlayerDigging
};

/**************************************************************************************************************/

struct SEncryptionRequestPacket {
    static constexpr auto ID = SPacketType::EncryptionRequest;
};

struct SEnableCompressionPacket {
    static constexpr auto ID = SPacketType::EnableCompression;
};

struct SLoginSuccessPacket {
    static constexpr auto ID = SPacketType::LoginSuccess;
};

struct SLoadChunkPacket {
    static constexpr auto ID = SPacketType::LoadChunk;

    Chunk* chunk;
    int x;
    int z;
};

struct SUnloadChunkPacket {
    static constexpr auto ID = SPacketType::UnloadChunk;

    int x;
    int z;
};

struct SSpawnPlayerPacket {
    static constexpr auto ID = SPacketType::SpawnPlayer;

    glm::vec3 pos;
};

struct SChangeBlockPacket {
    static constexpr auto ID = SPacketType::ChangeBlock;

    glm::ivec3 pos;
    BlockData data;
};

/**************************************************************************************************************/

struct CHandshakePacket {
    static constexpr auto ID = CPacketType::Handshake;

    int version;
    ProtocolType type;
};

struct CLoginStartPacket {
    static constexpr auto ID = CPacketType::LoginStart;
};

struct CEncryptionResponsePacket {
    static constexpr auto ID = CPacketType::EncryptionResponse;
};

struct PositionPacket {
    static constexpr auto ID = CPacketType::Position;

    glm::vec3 pos;
};

struct CPlayerDiggingPacket {
    static constexpr auto ID = CPacketType::PlayerDigging;

    glm::ivec3 pos;
    glm::ivec3 dir;
};