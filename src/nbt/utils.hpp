#pragma once

#include "nbt.hpp"
#include <string>
#include <istream>

struct NamedTag {
    std::string name;
    CompoundTag tag;
};

struct NbtUtil {
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
        auto tag = readTag<CompoundTag>(io);
        if (!tag.has_value()) {
            return std::nullopt;
        }

        return {std::move(*name), std::move(*tag)};
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

    static auto readID(std::istream &io) -> std::optional<ID> {
        if (auto i8 = readI8(io)) {
            return static_cast<ID>(*i8);
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

    template<typename T>
    static auto readTag(std::istream &io) -> std::optional<T> = delete;

    template<>
    static auto readTag(std::istream &io) -> std::optional<ByteTag> {
        if (auto i8 = readI8(io)) {
            return ByteTag{*i8};
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<ShortTag> {
        if (auto i16 = readI16(io)) {
            return ShortTag{*i16};
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<IntTag> {
        if (auto i32 = readI32(io)) {
            return IntTag{*i32};
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<LongTag> {
        if (auto i64 = readI64(io)) {
            return LongTag{*i64};
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<FloatTag> {
        if (auto f32 = readF32(io)) {
            return FloatTag{*f32};
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<DoubleTag> {
        if (auto f64 = readF64(io)) {
            return DoubleTag{*f64};
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<StringTag> {
        if (auto str = readString(io)) {
            return StringTag{std::move(*str)};
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<ListTag> {
        const auto id = readID(io);
        if (!id.has_value()) {
            return std::nullopt;
        }
        switch (*id) {
            case ID::END:
                return readListTag<EndTag>(io);
            case ID::BYTE:
                return readListTag<ByteTag>(io);
            case ID::SHORT:
                return readListTag<ShortTag>(io);
            case ID::INT:
                return readListTag<IntTag>(io);
            case ID::LONG:
                return readListTag<LongTag>(io);
            case ID::FLOAT:
                return readListTag<FloatTag>(io);
            case ID::DOUBLE:
                return readListTag<DoubleTag>(io);
            case ID::BYTE_ARRAY:
                return readListTag<ByteArrayTag>(io);
            case ID::STRING:
                return readListTag<StringTag>(io);
            case ID::LIST:
                return readListTag<ListTag>(io);
            case ID::COMPOUND:
                return readListTag<CompoundTag>(io);
            case ID::INT_ARRAY:
                return readListTag<IntArrayTag>(io);
            case ID::LONG_ARRAY:
                return readListTag<LongArrayTag>(io);
            default:
                return std::nullopt;
        }
    }

    template<typename T>
    static auto readListTag(std::istream &io) -> std::optional<ListTag> {
        if (auto len = readI32(io)) {
            const auto size = static_cast<size_t>(*len);

            ListTag list{};
            for (size_t i = 0; i < size; ++i) {
                if (auto v = readTag<T>(io)) {
                    list.emplace_back(std::move(*v));
                } else {
                    return std::nullopt;
                }
            }
            return list;
        }
        return std::nullopt;
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<ByteArrayTag> {
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

    template<>
    static auto readTag(std::istream &io) -> std::optional<IntArrayTag> {
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

    template<>
    static auto readTag(std::istream &io) -> std::optional<LongArrayTag> {
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

    template<typename T>
    static auto emplace(CompoundTag &ct, std::string name, std::istream &io, std::optional<T> (*read)(std::istream &)) -> bool {
        if (auto tag = read(io)) {
            ct.emplace(std::move(name), std::move(*tag));
            return true;
        }
        return false;
    };

    template<>
    static auto readTag(std::istream &io) -> std::optional<CompoundTag> {
        CompoundTag ct{};

        while (true) {
            auto id = readID(io);
            if (!id.has_value()) {
                return std::nullopt;
            }
            if (*id == ID::END) {
                return ct;
            }
            auto name = readString(io);
            if (!name.has_value()) {
                return std::nullopt;
            }
            switch (*id) {
                case ID::BYTE:
                    if (!emplace(ct, std::move(*name), io, &readTag<ByteTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::SHORT:
                    if (!emplace(ct, std::move(*name), io, &readTag<ShortTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::INT:
                    if (!emplace(ct, std::move(*name), io, &readTag<IntTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::LONG:
                    if (!emplace(ct, std::move(*name), io, &readTag<LongTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::FLOAT:
                    if (!emplace(ct, std::move(*name), io, &readTag<FloatTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::DOUBLE:
                    if (!emplace(ct, std::move(*name), io, &readTag<DoubleTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::BYTE_ARRAY:
                    if (!emplace(ct, std::move(*name), io, &readTag<ByteArrayTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::STRING:
                    if (!emplace(ct, std::move(*name), io, &readTag<StringTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::LIST: {
                    if (!emplace(ct, std::move(*name), io, &readTag<ListTag>)) {
                        return std::nullopt;
                    }
                    break;
                }
                case ID::COMPOUND:
                    if (!emplace(ct, std::move(*name), io, &readTag<CompoundTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::INT_ARRAY:
                    if (!emplace(ct, std::move(*name), io, &readTag<IntArrayTag>)) {
                        return std::nullopt;
                    }
                    break;
                case ID::LONG_ARRAY:
                    if (!emplace(ct, std::move(*name), io, &readTag<LongArrayTag>)) {
                        return std::nullopt;
                    }
                    break;
                default:
                    return std::nullopt;
            }
        }
    }

    template<>
    static auto readTag(std::istream &io) -> std::optional<EndTag> {
        return EndTag{};
    }
};