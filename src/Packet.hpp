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

struct SUnloadChunkPacket {
    static constexpr int ID = 1;

    int x;
    int z;
};

struct Chunk;

struct SLoadChunkPacket {
    static constexpr int ID = 2;

    Chunk* chunk;
    int x;
    int z;
};

struct SpawnPlayerPacket {
    static constexpr int ID = 1;

    glm::vec3 pos;
};

struct PositionPacket {
    static constexpr int ID = 2;

    glm::vec3 pos;
};

struct SChangeBlockPacket {
    static constexpr int ID = 3;

    glm::ivec3 pos;
    BlockData data;
};