#pragma once

#include <map>
#include <bit>
#include <span>
#include <list>
#include <array>
#include <vector>
#include <string>
#include <istream>
#include <variant>
#include <Iter.hpp>
#include <util/match.hpp>
#include <tl/optional.hpp>
#include <spdlog/spdlog.h>

struct Nbt {
	struct Tag;

	struct End {};
	using Byte = int8_t;
	using Short = int16_t;
	using Int = int32_t;
	using Long = int64_t;
	using Float = float;
	using Double = double;
	using String = std::string;

	template<typename T>
	struct Array {
		Array() = default;
		explicit Array(std::vector<T> value) : value(std::move(value)) {}

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

	using ByteArray = Array<int8_t>;
	using IntArray = Array<int32_t>;
	using LongArray = Array<int64_t>;

	struct Compound {
		Compound() = default;
		explicit Compound(std::map<std::string, Tag> value) : value(std::move(value)) {}
		explicit Compound(std::initializer_list<std::pair<const std::string, Tag>> v) : value(v) {}

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
		void emplace(std::string name, T&& tag) {
			value.emplace(std::move(name), std::forward<T>(tag));
		}

		Tag& at(const std::string &name) {
			return value.at(name);
		}

		const Tag& at(const std::string &name) const {
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

	struct List {
		List() = default;
		explicit List(std::vector<Tag> value) : value(std::move(value)) {}

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

		Tag& at(size_t i) {
			return value.at(i);
		}

		const Tag& at(size_t i) const {
			return value.at(i);
		}

		Tag& operator[](size_t i) {
			return value[i];
		}

		const Tag& operator[](size_t i) const {
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

    using Value = std::variant<
        End,
        Byte,
        Short,
        Int,
        Long,
        Float,
        Double,
        String,
        ByteArray,
        IntArray,
        LongArray,
        List,
        Compound
    >;

	struct Tag {
        Tag() noexcept : m_storage(End{}) {}

        Tag(const Tag&) noexcept = default;
        Tag(const End&) noexcept : m_storage(End{}) {}
        Tag(const Byte& v) noexcept : m_storage(v) {}
        Tag(const Short& v) noexcept : m_storage(v) {}
        Tag(const Int& v) noexcept : m_storage(v) {}
        Tag(const Long& v) noexcept : m_storage(v) {}
        Tag(const Float& v) noexcept : m_storage(v) {}
        Tag(const Double& v) noexcept : m_storage(v) {}
        Tag(const String& v) noexcept : m_storage(v) {}
        Tag(const ByteArray& v) noexcept : m_storage(v) {}
        Tag(const IntArray& v) noexcept : m_storage(v) {}
        Tag(const LongArray& v) noexcept : m_storage(v) {}
        Tag(const List& v) noexcept : m_storage(v) {}
        Tag(const Compound& v) noexcept : m_storage(v) {}

        Tag(Tag&&) noexcept = default;
        Tag(End&&) noexcept : m_storage(End{}) {}
        Tag(Byte&& v) noexcept : m_storage(v) {}
        Tag(Short&& v) noexcept : m_storage(v) {}
        Tag(Int&& v) noexcept : m_storage(v) {}
        Tag(Long&& v) noexcept : m_storage(v) {}
        Tag(Float&& v) noexcept : m_storage(std::move(v)) {}
        Tag(Double&& v) noexcept : m_storage(std::move(v)) {}
        Tag(String&& v) noexcept : m_storage(std::move(v)) {}
        Tag(ByteArray&& v) noexcept : m_storage(std::move(v)) {}
        Tag(IntArray&& v) noexcept : m_storage(std::move(v)) {}
        Tag(LongArray&& v) noexcept : m_storage(std::move(v)) {}
        Tag(List&& v) noexcept : m_storage(std::move(v)) {}
        Tag(Compound&& v) noexcept : m_storage(std::move(v)) {}

		Tag(std::initializer_list<std::pair<const std::string, Tag>> v) noexcept : m_storage(Compound{v}) {}

//		template <typename T> requires (!std::is_same_v<std::decay_t<T>, Tag>)
//		Tag(T&& obj) : Tag(Serialize<std::decay_t<T>>::to_tag(std::forward<T>(obj))) {}

        Tag& operator=(Tag&&) = default;
        Tag& operator=(const Tag&) = default;

		template<typename T>
		operator T() const {
			return Deserialize<std::decay_t<T>>::from_tag(*this).value();
		}

        template<typename T>
        auto get() const -> T const& {
            return std::get<T>(m_storage);
        }

        Value m_storage;
	};

	struct TreeRoot {
        std::string name;
        Compound root;
	};

	struct Read;
	struct Dump;

	template<typename T>
	struct Serialize {
		static auto to_tag(const T& val) -> Tag;/* {
			return End{};
		}*/
	};

	template<typename T>
	struct Deserialize {
		static auto from_tag(const Tag& obj) -> tl::optional<T>;/* {
			return tl::nullopt;
		}*/
	};
};

template <typename T> requires (
    std::is_same_v<T, float> ||
    std::is_same_v<T, double>
)
struct Nbt::Serialize<T> {
    static auto to_tag(const T& val) -> Tag {
        return val;
    }
};

template <typename T> requires (
    std::is_same_v<T, int8_t> ||
    std::is_same_v<T, uint8_t>
)
struct Nbt::Serialize<T> {
    static auto to_tag(const T& val) -> Tag {
        return static_cast<Byte>(val);
    }
};

template <typename T> requires (
    std::is_same_v<T, int16_t> ||
    std::is_same_v<T, uint16_t>
)
struct Nbt::Serialize<T> {
    static auto to_tag(const T& val) -> Tag {
        return static_cast<Short>(val);
    }
};

template <typename T> requires (
    std::is_same_v<T, int32_t> ||
    std::is_same_v<T, uint32_t>
)
struct Nbt::Serialize<T> {
    static auto to_tag(const T& val) -> Tag {
        return static_cast<Int>(val);
    }
};

template <typename T> requires (
    std::is_same_v<T, int64_t> ||
    std::is_same_v<T, uint64_t>
)
struct Nbt::Serialize<T> {
    static auto to_tag(const T& val) -> Tag {
        return static_cast<Long>(val);
    }
};

template<typename T, size_t N>
struct Nbt::Serialize<std::array<T, N>> {
    static auto to_tag(const std::array<T, N>& elements) -> Tag {
        return cpp_iter(elements).map([](auto element) -> Tag { return std::move(element); }).collect();
    }
};

template<typename T>
struct Nbt::Serialize<std::vector<T>> {
    static auto to_tag(const std::vector<T> &elements) -> Tag {
        return cpp_iter(elements).map([](auto element) -> Tag { return std::move(element); }).collect();
    }
};

template<typename K, typename V, typename P, typename A>
struct Nbt::Serialize<std::map<K, V, P, A>> {
    static auto to_tag(const std::map<K, V, P, A> &elements) -> Tag {
        auto obj = Nbt::Compound{};
        for (auto&& [k, v] : elements) {
            obj.emplace(std::get<String>(Tag(k).m_storage), Tag(v));
        }
        return obj;
    }
};

template <typename T> requires (
	std::is_same_v<T, float> ||
	std::is_same_v<T, double>
)
struct Nbt::Deserialize<T> {
	using Result = tl::optional<T>;

	static auto from_tag(const Tag& tag) -> Result {
		return match(tag.m_storage,
			[](const String& tag) -> Result {
				return static_cast<T>(std::stod(tag));
			},
			[](const Byte& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Short& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Int& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Float& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Double& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const auto&) -> Result {
				return tl::nullopt;
			}
		);
	}
};

template <typename T> requires (
	std::is_same_v<T, int8_t> ||
	std::is_same_v<T, int16_t> ||
	std::is_same_v<T, int32_t> ||
	std::is_same_v<T, int64_t> ||
	std::is_same_v<T, uint8_t> ||
	std::is_same_v<T, uint16_t> ||
	std::is_same_v<T, uint32_t> ||
	std::is_same_v<T, uint64_t>
)
struct Nbt::Deserialize<T> {
	using Result = tl::optional<T>;

	static auto from_tag(const Tag& tag) -> Result {
		return match(tag.m_storage,
			[](const String& tag) -> Result {
				return static_cast<T>(std::stoll(tag));
			},
			[](const Byte& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Short& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Int& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Float& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const Double& tag) -> Result {
				return static_cast<T>(tag);
			},
			[](const auto&) -> Result {
				return tl::nullopt;
			}
		);
	}
};

template<typename T, size_t N>
struct Nbt::Deserialize<std::array<T, N>> {
	template <size_t... I>
	static auto to_array(const List& elements, std::index_sequence<I...>) -> std::array<T, N> {
		return { elements.at(I)... };
	}

	static auto from_tag(const Tag& tag) -> tl::optional<std::array<T, N>> {
		return to_array(std::get<List>(tag.m_storage), std::make_index_sequence<N>{});
	}
};

template<typename T>
struct Nbt::Deserialize<std::vector<T>> {
	static auto from_tag(const Tag& tag) -> tl::optional<std::vector<T>> {
		return cpp_iter(std::get<List>(tag.m_storage)).map([](const auto& element) -> T { return element; }).collect();
	}
};

struct Nbt::Read {
	static auto read(std::istream &&io) -> tl::optional<TreeRoot> {
		return read(io);
	}

	static auto read(std::istream &io) -> tl::optional<TreeRoot> {
		if (readID(io).value_or(ID::END) != ID::COMPOUND) {
			return tl::nullopt;
		}
		auto name = readString(io);
		if (!name.has_value()) {
			return tl::nullopt;
		}
		auto tag = readCompound(io);
		if (!tag.has_value()) {
			return tl::nullopt;
		}
		return TreeRoot{
            .name = std::move(*name),
            .root = std::move(*tag)
        };
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

	static auto readID(std::istream &io) -> tl::optional<ID> {
		if (auto i8 = readI8(io)) {
			return static_cast<ID>(*i8);
		}
		return tl::nullopt;
	}

	static auto readI8(std::istream &io) -> tl::optional<int8_t> {
		std::array<char, 1> bytes{};
		io.read(&bytes[0], 1);
		if (io.fail()) {
			return tl::nullopt;
		}
		return std::bit_cast<int8_t>(bytes);
	}

	static auto readI16(std::istream &io) -> tl::optional<int16_t> {
		std::array<char, 2> bytes{};
		io.read(&bytes[1], 1);
		io.read(&bytes[0], 1);
		if (io.fail()) {
			return tl::nullopt;
		}
		return std::bit_cast<int16_t>(bytes);
	}

	static auto readI32(std::istream &io) -> tl::optional<int32_t> {
		std::array<char, 4> bytes{};
		io.read(&bytes[3], 1);
		io.read(&bytes[2], 1);
		io.read(&bytes[1], 1);
		io.read(&bytes[0], 1);
		if (io.fail()) {
			return tl::nullopt;
		}
		return std::bit_cast<int32_t>(bytes);
	}

	static auto readI64(std::istream &io) -> tl::optional<int64_t> {
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
			return tl::nullopt;
		}
		return std::bit_cast<int64_t>(bytes);
	}

	static auto readF32(std::istream &io) -> tl::optional<float> {
		if (auto i32 = readI32(io)) {
			return std::bit_cast<float>(*i32);
		}
		return tl::nullopt;
	}

	static auto readF64(std::istream &io) -> tl::optional<double> {
		if (auto i64 = readI64(io)) {
			return std::bit_cast<double>(*i64);
		}
		return tl::nullopt;
	}

	static auto readString(std::istream &io) -> tl::optional<std::string> {
		if (auto size = readI16(io)) {
			std::string str(static_cast<size_t>(*size), '\0');
			io.read(str.data(), static_cast<std::streamsize>(str.size()));
			if (io.fail()) {
				return tl::nullopt;
			}
			return str;
		}
		return tl::nullopt;
	}

	static auto readList(std::istream &io) -> tl::optional<List> {
		const auto id = readID(io);
		if (!id.has_value()) {
			return tl::nullopt;
		}
		const auto len = readI32(io);
		if (!len.has_value()) {
			return tl::nullopt;
		}

		List list{};
		for (size_t i = 0; i < static_cast<size_t>(*len); ++i) {
			if (auto v = read(io, *id)) {
				list.emplace_back(std::move(*v));
			} else {
				return tl::nullopt;
			}
		}
		return list;
	}

	static auto readCompound(std::istream &io) -> tl::optional<Compound> {
		Compound ct{};

		while (const auto id = readID(io)) {
			if (*id == ID::END) {
				return ct;
			}

			auto name = readString(io);
			if (!name.has_value()) {
				return tl::nullopt;
			}

			auto value = read(io, *id);
			if (!value.has_value()) {
				return tl::nullopt;
			}

			ct.emplace(std::move(*name), std::move(*value));
		}
		return tl::nullopt;
	}

	static auto readByteArray(std::istream &io) -> tl::optional<ByteArray> {
		if (auto len = readI32(io)) {
			const auto size = static_cast<size_t>(*len);

			ByteArray array{};
			array.reserve(size);
			for (size_t i = 0; i < size; ++i) {
				if (auto v = readI8(io)) {
					array.emplace_back(*v);
				} else {
					return tl::nullopt;
				}
			}
			return array;
		}
		return tl::nullopt;
	}

	static auto readIntArray(std::istream &io) -> tl::optional<IntArray> {
		if (auto len = readI32(io)) {
			const auto size = static_cast<size_t>(*len);

			IntArray array{};
			array.reserve(size);
			for (size_t i = 0; i < size; ++i) {
				if (auto v = readI32(io)) {
					array.emplace_back(*v);
				} else {
					return tl::nullopt;
				}
			}
			return array;
		}
		return tl::nullopt;
	}

	static auto readLongArray(std::istream &io) -> tl::optional<LongArray> {
		if (auto len = readI32(io)) {
			const auto size = static_cast<size_t>(*len);

			LongArray array{};
			array.reserve(size);
			for (size_t i = 0; i < size; ++i) {
				if (auto v = readI64(io)) {
					array.emplace_back(*v);
				} else {
					return tl::nullopt;
				}
			}
			return array;
		}
		return tl::nullopt;
	}

	static auto read(std::istream &io, ID id) -> tl::optional<Tag> {
		switch (id) {
			case ID::END: return End{};
			case ID::BYTE: return readI8(io);
			case ID::SHORT: return readI16(io);
			case ID::INT: return readI32(io);
			case ID::LONG: return readI64(io);
			case ID::FLOAT: return readF32(io);
			case ID::DOUBLE: return readF64(io);
			case ID::STRING: return readString(io);
			case ID::LIST: return readList(io);
			case ID::COMPOUND: return readCompound(io);
			case ID::BYTE_ARRAY: return readByteArray(io);
			case ID::INT_ARRAY: return readIntArray(io);
			case ID::LONG_ARRAY: return readLongArray(io);
			default: return tl::nullopt;
		}
	}
};

//static auto operator<<(std::ostream& out, const Nbt::Tag& tag) noexcept -> std::ostream& {
////    Nbt::Dump::dump(out, tag);
//    return out;
//}
//
//static auto operator<<(std::ostream&& out, const Nbt::Tag& tag) noexcept -> std::ostream&& {
////    Nbt::Dump::dump(out, tag);
//    return std::move(out);
//}
//
//static auto operator>>(std::istream& in, Nbt::Tag& tag) noexcept -> std::istream& {
//    tag = Nbt::Read::read(in).value();
//    return in;
//}
//
//static auto operator>>(std::istream&& in, Nbt::Tag& tag) noexcept -> std::istream&& {
//    tag = Nbt::Read::read(in).value();
//    return std::move(in);
//}