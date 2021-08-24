#pragma once

#include <optional>
#include <variant>
#include <vector>
#include <string>
#include <array>
#include <span>
#include <list>
#include <map>
#include <bit>

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

template <typename T>
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

    T& at(size_t i) {
        return value.at(i);
    }

    const T& at(size_t i) const {
        return value.at(i);
    }

    T& operator[](size_t i) {
        return value[i];
    }

    const T& operator[](size_t i) const {
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

    template <typename... Args>
    void emplace_back(Args&&... args) {
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

    template <typename T>
    void emplace(std::string name, T&& tag) {
        value.emplace(std::move(name), std::forward<T>(tag));
    }

    Tag& at(const std::string& name) {
        return value.at(name);
    }

    const Tag& at(const std::string& name) const {
        return value.at(name);
    }

    auto erase(const std::string& name) {
        return value.erase(name);
    }

    auto find(const std::string& name) {
        return value.find(name);
    }

    auto find(const std::string& name) const {
        return value.find(name);
    }

    bool contains(const std::string& name) const {
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

    template <typename... Args>
    void emplace_back(Args&&... args) {
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