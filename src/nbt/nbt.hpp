#pragma once

#include <optional>
#include <istream>
#include <variant>
#include <vector>
#include <string>
#include <array>
#include <span>
#include <list>
#include <map>
#include <bit>

struct Nbt {
    struct Tag;

    struct EndTag {};

    struct ByteTag {
        int8_t value;
    };

    struct ShortTag {
        int16_t value;
    };

    struct IntTag {
        int32_t value;
    };

    struct LongTag {
        int64_t value;
    };

    struct FloatTag {
        float value;
    };

    struct DoubleTag {
        double value;
    };

    struct StringTag {
        std::string value;
    };

    template<typename T>
    struct ArrayTag {
        ArrayTag() = default;
        explicit ArrayTag(std::vector<T> value) : value(std::move(value)) {}

        size_t size() const {
            return value.size();
        }

        size_t capacity() const {
            return value.capacity();
        }

        void reserve(size_t count) {
            value.reserve(count);
        }

        void resize(size_t size) {
            value.resize(size);
        }

        void clear() {
            value.clear();
        }

        T &at(size_t i) {
            return value.at(i);
        }

        const T &at(size_t i) const {
            return value.at(i);
        }

        T &operator[](size_t i) {
            return value[i];
        }

        const T &operator[](size_t i) const {
            return value[i];
        }

        auto begin() {
            return value.begin();
        }

        auto begin() const {
            return value.begin();
        }

        auto end() {
            return value.end();
        }

        auto end() const {
            return value.end();
        }

        auto rbegin() {
            return value.rbegin();
        }

        auto rbegin() const {
            return value.rbegin();
        }

        auto rend() {
            return value.end();
        }

        auto rend() const {
            return value.rend();
        }

        template<typename... Args>
        void emplace_back(Args &&...args) {
            value.emplace_back(std::forward<Args>(args)...);
        }

    private:
        std::vector<T> value;
    };

    using ByteArrayTag = ArrayTag<int8_t>;
    using IntArrayTag = ArrayTag<int32_t>;
    using LongArrayTag = ArrayTag<int64_t>;

    struct CompoundTag {
        CompoundTag() = default;
        explicit CompoundTag(std::map<std::string, Tag> value) : value(std::move(value)) {}

        auto size() const {
            return value.size();
        }

        void clear() {
            value.clear();
        }

        auto begin() {
            return value.begin();
        }

        auto begin() const {
            return value.begin();
        }

        auto end() {
            return value.end();
        }

        auto end() const {
            return value.end();
        }

        template<typename T>
        void emplace(std::string name, T &&tag) {
            value.emplace(std::move(name), std::forward<T>(tag));
        }

        Tag &at(const std::string &name) {
            return value.at(name);
        }

        const Tag &at(const std::string &name) const {
            return value.at(name);
        }

        auto erase(const std::string &name) {
            return value.erase(name);
        }

        auto find(const std::string &name) {
            return value.find(name);
        }

        auto find(const std::string &name) const {
            return value.find(name);
        }

        bool contains(const std::string &name) const {
            return value.contains(name);
        }

    private:
        std::map<std::string, Tag> value;
    };

    struct ListTag {
        ListTag() = default;
        explicit ListTag(std::vector<Tag> value) : value(std::move(value)) {}

        size_t size() const {
            return value.size();
        }

        size_t capacity() const {
            return value.capacity();
        }

        void reserve(size_t count) {
            value.reserve(count);
        }

        void resize(size_t size) {
            value.resize(size);
        }

        void clear() {
            value.clear();
        }

        Tag &at(size_t i) {
            return value.at(i);
        }

        const Tag &at(size_t i) const {
            return value.at(i);
        }

        Tag &operator[](size_t i) {
            return value[i];
        }

        const Tag &operator[](size_t i) const {
            return value[i];
        }

        auto begin() {
            return value.begin();
        }

        auto begin() const {
            return value.begin();
        }

        auto end() {
            return value.end();
        }

        auto end() const {
            return value.end();
        }

        auto rbegin() {
            return value.rbegin();
        }

        auto rbegin() const {
            return value.rbegin();
        }

        auto rend() {
            return value.end();
        }

        auto rend() const {
            return value.rend();
        }

        template<typename... Args>
        void emplace_back(Args &&...args) {
            value.emplace_back(std::forward<Args>(args)...);
        }

    private:
        std::vector<Tag> value;
    };

    struct Tag : std::variant<
         EndTag,
         ByteTag,
         ShortTag,
         IntTag,
         LongTag,
         FloatTag,
         DoubleTag,
         StringTag,
         ByteArrayTag,
         IntArrayTag,
         LongArrayTag,
         ListTag,
         CompoundTag
    > {
        using variant::variant;
    };
    
    struct NamedTag {
        std::string name;
        CompoundTag tag;
    };

    struct Read;
    struct Dump;
};

struct Nbt::Read {
    static auto read(std::istream &&io) -> std::optional<NamedTag> {
        return read(io);
    }

    static auto read(std::istream &io) -> std::optional<NamedTag> {
        if (readID(io).value_or(ID::END) != ID::COMPOUND) {
            return std::nullopt;
        }
        auto name = readString(io);
        if (!name.has_value()) {
            return std::nullopt;
        }
        auto tag = readCompound(io);
        if (!tag.has_value()) {
            return std::nullopt;
        }
        return NamedTag{std::move(*name), std::move(*tag)};
    }

private:
    enum class ID {
        END = 0,
        BYTE = 1,
        SHORT = 2,
        INT = 3,
        LONG = 4,
        FLOAT = 5,
        DOUBLE = 6,
        BYTE_ARRAY = 7,
        STRING = 8,
        LIST = 9,
        COMPOUND = 10,
        INT_ARRAY = 11,
        LONG_ARRAY = 12,
    };

    static auto readID(std::istream &io) -> std::optional<ID> {
        if (auto i8 = readI8(io)) {
            return static_cast<ID>(*i8);
        }
        return std::nullopt;
    }
    
    static auto readI8(std::istream &io) -> std::optional<int8_t> {
        std::array<char, 1> bytes{};
        io.read(&bytes[0], 1);
        if (io.fail()) {
            return std::nullopt;
        }
        return std::bit_cast<int8_t>(bytes);
    }

    static auto readI16(std::istream &io) -> std::optional<int16_t> {
        std::array<char, 2> bytes{};
        io.read(&bytes[1], 1);
        io.read(&bytes[0], 1);
        if (io.fail()) {
            return std::nullopt;
        }
        return std::bit_cast<int16_t>(bytes);
    }

    static auto readI32(std::istream &io) -> std::optional<int32_t> {
        std::array<char, 4> bytes{};
        io.read(&bytes[3], 1);
        io.read(&bytes[2], 1);
        io.read(&bytes[1], 1);
        io.read(&bytes[0], 1);
        if (io.fail()) {
            return std::nullopt;
        }
        return std::bit_cast<int32_t>(bytes);
    }

    static auto readI64(std::istream &io) -> std::optional<int64_t> {
        std::array<char, 8> bytes{};
        io.read(&bytes[7], 1);
        io.read(&bytes[6], 1);
        io.read(&bytes[5], 1);
        io.read(&bytes[4], 1);
        io.read(&bytes[3], 1);
        io.read(&bytes[2], 1);
        io.read(&bytes[1], 1);
        io.read(&bytes[0], 1);
        if (io.fail()) {
            return std::nullopt;
        }
        return std::bit_cast<int64_t>(bytes);
    }

    static auto readF32(std::istream &io) -> std::optional<float> {
        if (auto i32 = readI32(io)) {
            return std::bit_cast<float>(*i32);
        }
        return std::nullopt;
    }

    static auto readF64(std::istream &io) -> std::optional<double> {
        if (auto i64 = readI64(io)) {
            return std::bit_cast<double>(*i64);
        }
        return std::nullopt;
    }

    static auto readString(std::istream &io) -> std::optional<std::string> {
        if (auto size = readI16(io)) {
            std::string str(static_cast<size_t>(*size), '\0');
            io.read(str.data(), static_cast<std::streamsize>(str.size()));
            if (io.fail()) {
                return std::nullopt;
            }
            return str;
        }
        return std::nullopt;
    }

    static auto readList(std::istream &io) -> std::optional<ListTag> {
        const auto id = readID(io);
        if (!id.has_value()) {
            return std::nullopt;
        }
        const auto len = readI32(io);
        if (!len.has_value()) {
            return std::nullopt;
        }

        const auto size = static_cast<size_t>(*len);

        ListTag list{};
        for (size_t i = 0; i < size; ++i) {
            if (auto v = read(io, *id)) {
                list.emplace_back(std::move(*v));
            } else {
                return std::nullopt;
            }
        }
        return list;
    }

    static auto readCompound(std::istream &io) -> std::optional<CompoundTag> {
        CompoundTag ct{};

        while (const auto id = readID(io)) {
            if (*id == ID::END) {
                return ct;
            }

            auto name = readString(io);
            if (!name.has_value()) {
                return std::nullopt;
            }

            auto value = read(io, *id);
            if (!value.has_value()) {
                return std::nullopt;
            }

            ct.emplace(std::move(*name), std::move(*value));
        }
        return std::nullopt;
    }

    static auto readByteArray(std::istream &io) -> std::optional<ByteArrayTag> {
        if (auto len = readI32(io)) {
            const auto size = static_cast<size_t>(*len);

            ByteArrayTag array{};
            array.reserve(size);
            for (size_t i = 0; i < size; ++i) {
                if (auto v = readI8(io)) {
                    array.emplace_back(*v);
                } else {
                    return std::nullopt;
                }
            }
            return array;
        }
        return std::nullopt;
    }

    static auto readIntArray(std::istream &io) -> std::optional<IntArrayTag> {
        if (auto len = readI32(io)) {
            const auto size = static_cast<size_t>(*len);

            IntArrayTag array{};
            array.reserve(size);
            for (size_t i = 0; i < size; ++i) {
                if (auto v = readI32(io)) {
                    array.emplace_back(*v);
                } else {
                    return std::nullopt;
                }
            }
            return array;
        }
        return std::nullopt;
    }

    static auto readLongArray(std::istream &io) -> std::optional<LongArrayTag> {
        if (auto len = readI32(io)) {
            const auto size = static_cast<size_t>(*len);

            LongArrayTag array{};
            array.reserve(size);
            for (size_t i = 0; i < size; ++i) {
                if (auto v = readI64(io)) {
                    array.emplace_back(*v);
                } else {
                    return std::nullopt;
                }
            }
            return array;
        }
        return std::nullopt;
    }

    static auto read(std::istream &io, ID id) -> std::optional<Tag> {
        switch (id) {
            case ID::END:
                return EndTag{};
            case ID::BYTE:
                if (auto i8 = readI8(io)) {
                    return ByteTag{*i8};
                }
                return std::nullopt;
            case ID::SHORT:
                if (auto i16 = readI16(io)) {
                    return ShortTag{*i16};
                }
                return std::nullopt;
            case ID::INT:
                if (auto i32 = readI32(io)) {
                    return IntTag{*i32};
                }
                return std::nullopt;
            case ID::LONG:
                if (auto i64 = readI64(io)) {
                    return LongTag{*i64};
                }
                return std::nullopt;
            case ID::FLOAT:
                if (auto f32 = readF32(io)) {
                    return FloatTag{*f32};
                }
                return std::nullopt;
            case ID::DOUBLE:
                if (auto f64 = readF64(io)) {
                    return DoubleTag{*f64};
                }
                return std::nullopt;
            case ID::STRING:
                if (auto str = readString(io)) {
                    return StringTag{std::move(*str)};
                }
                return std::nullopt;
            case ID::LIST: return readList(io);
            case ID::COMPOUND: return readCompound(io);
            case ID::BYTE_ARRAY: return readByteArray(io);
            case ID::INT_ARRAY: return readIntArray(io);
            case ID::LONG_ARRAY: return readLongArray(io);
            default: return std::nullopt;
        }
    }
};