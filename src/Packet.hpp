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

/**************************************************************************************************************/

struct SLoadChunkPacket {
    static constexpr int ID = 0;

    Chunk* chunk;
    int x;
    int z;
};

struct SUnloadChunkPacket {
    static constexpr int ID = 1;

    int x;
    int z;
};

struct SSpawnPlayerPacket {
    static constexpr int ID = 2;

    glm::vec3 pos;
};

struct SChangeBlockPacket {
    static constexpr int ID = 3;

    glm::ivec3 pos;
    BlockData data;
};

/**************************************************************************************************************/

struct CHandshakePacket {
    static constexpr int ID = 0;

    int version;
    ProtocolType type;
};

struct PositionPacket {
    static constexpr int ID = 1;

    glm::vec3 pos;
};

struct CPlayerDiggingPacket {
    static constexpr int ID = 2;

    glm::ivec3 pos;
    glm::ivec3 dir;
};