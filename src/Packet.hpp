#pragma once

#include <Json.hpp>
#include <glm/vec3.hpp>
#include <block/BlockData.hpp>
#include <world/chunk/Chunk.hpp>

template <typename T>
concept Packet = requires {
    T::ID;
};

struct PacketHeader {
    int id;
    int size;

    static auto from(int id, int size) -> PacketHeader {
        return {.id = id, .size = size};
    }
};

struct PacketBuffer {
    std::span<const std::byte> data{};
    size_t read_offset = 0;

    static auto from(std::span<const std::byte> data) -> PacketBuffer {
        return { .data = data };
    }

    /**************************************************************************/

    auto read_bytes_to(std::span<std::byte> bytes) -> bool {
        if (read_offset + bytes.size() > data.size()) {
            return false;
        }
        std::memcpy(bytes.data(), data.data() + read_offset, bytes.size());
        read_offset += bytes.size();
        return true;
    }

    auto read_pointer() -> tl::optional<void*> {
        return read<void*>();
    }

    auto read_i8() -> tl::optional<int8_t> {
        return read<int8_t>();
    }

    auto read_i16() -> tl::optional<int16_t> {
        return read<int16_t>();
    }

    auto read_i32() -> tl::optional<int32_t> {
        return read<int32_t>();
    }

    auto read_i64() -> tl::optional<int64_t> {
        return read<int64_t>();
    }

    auto read_u8() -> tl::optional<uint8_t> {
        return read<uint8_t>();
    }

    auto read_u16() -> tl::optional<uint16_t> {
        return read<uint16_t>();
    }

    auto read_u32() -> tl::optional<uint32_t> {
        return read<int32_t>();
    }

    auto read_u64() -> tl::optional<uint64_t> {
        return read<uint64_t>();
    }

private:
    template <typename T>
    auto read() -> tl::optional<T> {
        std::array<std::byte, sizeof(T)> bytes{};
        if (read_bytes_to(bytes)) {
            return std::bit_cast<T>(bytes);
        }
        return tl::nullopt;
    }
};

struct PacketData {
    std::vector<std::byte> data{};
    size_t read_offset = 0;
    size_t write_offset = 0;

    static auto with_write_offset(size_t offset) -> PacketData {
        return {.data {offset}, .write_offset = offset};
    }

    static auto from(std::vector<std::byte> data) -> PacketData {
        return { .data = std::move(data) };
    }

    void write_bytes(std::span<const std::byte> bytes) {
        if (write_offset + bytes.size() > data.size()) {
            data.resize(write_offset + bytes.size());
        }
        std::memcpy(data.data() + write_offset, bytes.data(), bytes.size());
        write_offset += bytes.size();
    }

    void write_pointer(void* p) {
        write<void*>(p);
    }

    void write_i8(int8_t v) {
        write<int8_t>(v);
    }

    void write_i16(int16_t v) {
        write<int16_t>(v);
    }

    void write_i32(int32_t v) {
        write<int32_t>(v);
    }

    void write_i64(int64_t v) {
        write<int64_t>(v);
    }

    void write_u8(uint8_t v) {
        write<uint8_t>(v);
    }

    void write_u16(uint16_t v) {
        write<uint16_t>(v);
    }

    void write_u32(uint32_t v) {
        write<uint32_t>(v);
    }

    void write_u64(uint64_t v) {
        write<uint64_t>(v);
    }

    /**************************************************************************/

    auto read_bytes_to(std::span<std::byte> bytes) -> bool {
        if (read_offset + bytes.size() > data.size()) {
            return false;
        }
        std::memcpy(bytes.data(), data.data() + read_offset, bytes.size());
        read_offset += bytes.size();
        return true;
    }

    auto read_pointer() -> tl::optional<void*> {
        return read<void*>();
    }

    auto read_i8() -> tl::optional<int8_t> {
        return read<int8_t>();
    }

    auto read_i16() -> tl::optional<int16_t> {
        return read<int16_t>();
    }

    auto read_i32() -> tl::optional<int32_t> {
        return read<int32_t>();
    }

    auto read_i64() -> tl::optional<int64_t> {
        return read<int64_t>();
    }

    auto read_u8() -> tl::optional<uint8_t> {
        return read<uint8_t>();
    }

    auto read_u16() -> tl::optional<uint16_t> {
        return read<uint16_t>();
    }

    auto read_u32() -> tl::optional<uint32_t> {
        return read<int32_t>();
    }

    auto read_u64() -> tl::optional<uint64_t> {
        return read<uint64_t>();
    }

private:
    template <typename T>
    void write(T v) {
        const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(T)>>(v);
        write_bytes(bytes);
    }

    template <typename T>
    auto read() -> tl::optional<T> {
        std::array<std::byte, sizeof(T)> bytes{};
        if (read_bytes_to(bytes)) {
            return std::bit_cast<T>(bytes);
        }
        return tl::nullopt;
    }
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
    JoinGame,
    PlayerPositionLook,
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

    void read(PacketData& data) {}
    void write(PacketData& data) const {}
};

struct SEnableCompressionPacket {
    static constexpr auto ID = SPacketType::EnableCompression;

    void read(PacketData& data) {}
    void write(PacketData& data) const {}
};

struct SLoginSuccessPacket {
    static constexpr auto ID = SPacketType::LoginSuccess;

    void read(PacketData& data) {}
    void write(PacketData& data) const {}
};

struct SLoadChunkPacket {
    static constexpr auto ID = SPacketType::LoadChunk;

    glm::i32 x;
    glm::i32 z;
    glm::i32 sections{};
    std::vector<std::byte> bytes{};

    static auto from(Chunk const& chunk) -> SLoadChunkPacket {
        auto sections = 0;
        auto bytes = std::vector<std::byte>{};
        for (size_t i = 0; i < chunk.sections.size(); ++i) {
            if (!chunk.sections[i]) {
                continue;
            }

            sections |= 1 << i;

            auto blocks = std::as_bytes(std::span(chunk.sections[i]->blocks));
            bytes.insert(bytes.end(), blocks.begin(), blocks.end());
        }
        return {
            .x = chunk.coords.x,
            .z = chunk.coords.z,
            .sections = sections,
            .bytes = std::move(bytes)
        };
    }

    void read(PacketData& data) {
        x = data.read_i32().value();
        z = data.read_i32().value();
        sections = data.read_i32().value();
        bytes.resize(data.read_u64().value());
        data.read_bytes_to(bytes);
    }

    void write(PacketData& data) const {
        data.write_i32(x);
        data.write_i32(z);
        data.write_i32(sections);
        data.write_u64(bytes.size());
        data.write_bytes(bytes);
    }
};

struct SUnloadChunkPacket {
    static constexpr auto ID = SPacketType::UnloadChunk;

    int x;
    int z;

    void read(PacketData& data) {
        x = data.read_i32().value();
        z = data.read_i32().value();
    }

    void write(PacketData& data) const {
        data.write_i32(x);
        data.write_i32(z);
    }
};

struct SSpawnPlayerPacket {
    static constexpr auto ID = SPacketType::SpawnPlayer;

    glm::vec3 pos;

    void read(PacketData& data) {
        pos.x = data.read_i32().value();
        pos.y = data.read_i32().value();
        pos.z = data.read_i32().value();
    }

    void write(PacketData& data) const {
        data.write_i32(pos.x);
        data.write_i32(pos.y);
        data.write_i32(pos.z);
    }
};

struct SJoinGamePacket {
    static constexpr auto ID = SPacketType::JoinGame;

    void read(PacketData& data) {}
    void write(PacketData& data) const {}
};

struct SPlayerPositionLookPacket {
    static constexpr auto ID = SPacketType::PlayerPositionLook;

    glm::vec3 pos;
    glm::vec2 rot;

    void read(PacketData& data) {
        pos.x = data.read_i32().value();
        pos.y = data.read_i32().value();
        pos.z = data.read_i32().value();
    }

    void write(PacketData& data) const {
        data.write_i32(pos.x);
        data.write_i32(pos.y);
        data.write_i32(pos.z);
    }
};

struct SChangeBlockPacket {
    static constexpr auto ID = SPacketType::ChangeBlock;

    glm::ivec3 pos;
    BlockData block;

    void read(PacketData& data) {
        pos.x = data.read_i32().value();
        pos.y = data.read_i32().value();
        pos.z = data.read_i32().value();
        block = std::bit_cast<BlockData>(data.read_u32().value());
    }

    void write(PacketData& data) const {
        data.write_i32(pos.x);
        data.write_i32(pos.y);
        data.write_i32(pos.z);
        data.write_u32(std::bit_cast<uint32_t>(block));
    }
};

/**************************************************************************************************************/

struct CHandshakePacket {
    static constexpr auto ID = CPacketType::Handshake;

    int version;
    ProtocolType type;

    void read(PacketData& data) {}
    void write(PacketData& data) const {}
};

struct CLoginStartPacket {
    static constexpr auto ID = CPacketType::LoginStart;

    void read(PacketData& data) {}
    void write(PacketData& data) const {}
};

struct CEncryptionResponsePacket {
    static constexpr auto ID = CPacketType::EncryptionResponse;

    void read(PacketData& data) {}
    void write(PacketData& data) const {}
};

struct PositionPacket {
    static constexpr auto ID = CPacketType::Position;

    glm::vec3 pos;

    void read(PacketData& data) {
        pos.x = data.read_i32().value();
        pos.y = data.read_i32().value();
        pos.z = data.read_i32().value();
    }

    void write(PacketData& data) const {
        data.write_i32(pos.x);
        data.write_i32(pos.y);
        data.write_i32(pos.z);
    }
};

struct CPlayerDiggingPacket {
    static constexpr auto ID = CPacketType::PlayerDigging;

    glm::ivec3 pos;
    glm::ivec3 dir;

    void read(PacketData& data) {
        pos.x = data.read_i32().value();
        pos.y = data.read_i32().value();
        pos.z = data.read_i32().value();
        dir.x = data.read_i32().value();
        dir.y = data.read_i32().value();
        dir.z = data.read_i32().value();
    }

    void write(PacketData& data) const {
        data.write_i32(pos.x);
        data.write_i32(pos.y);
        data.write_i32(pos.z);
        data.write_i32(dir.x);
        data.write_i32(dir.y);
        data.write_i32(dir.z);
    }
};