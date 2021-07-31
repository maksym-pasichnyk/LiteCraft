#pragma once

#include <span>
#include <memory>
#include <vector>
#include <ranges>
#include <cstring>
#include <fstream>
#include <optional>
#include <physfs.h>
#include <filesystem>
#include <fmt/format.h>

#include "stb_image.hpp"

//#include <range/v3/all.hpp>

struct NativeImage {
    struct ImageDataPtrFree {
        void operator()(void* ptr) {
            stbi_image_free(ptr);
        }
    };

    using ImageDataPtr = std::unique_ptr<void, ImageDataPtrFree>;

    ImageDataPtr pixels;
	int width = 0;
	int height = 0;
	int channels = 0;

	static auto read(std::span<char> bytes, bool flip) -> NativeImage {
		auto data = reinterpret_cast<const unsigned char *>(bytes.data());

		int width, height, channels;
		auto pixels = stbi_load_from_memory(data, bytes.size(), &width, &height, &channels, 0);

		if (flip) {
            stbi__vertical_flip(pixels, width, height, channels * sizeof(stbi_uc));
		}

		return NativeImage{
			.pixels = ImageDataPtr{pixels},
			.width = width,
			.height = height,
			.channels = channels
		};
	}

private:
    static void stbi__vertical_flip(void *image, int w, int h, int bytes_per_pixel) {
        size_t bytes_per_row = (size_t) w * bytes_per_pixel;
        stbi_uc temp[2048];
        auto *bytes = reinterpret_cast<stbi_uc *>(image);

        for (int row = 0; row < (h >> 1); row++) {
            stbi_uc *row0 = bytes + row * bytes_per_row;
            stbi_uc *row1 = bytes + (h - row - 1) * bytes_per_row;
            // swap row0 with row1
            size_t bytes_left = bytes_per_row;
            while (bytes_left) {
                size_t bytes_copy = (bytes_left < sizeof(temp)) ? bytes_left : sizeof(temp);
                std::memcpy(temp, row0, bytes_copy);
                std::memcpy(row0, row1, bytes_copy);
                std::memcpy(row1, temp, bytes_copy);
                row0 += bytes_copy;
                row1 += bytes_copy;
                bytes_left -= bytes_copy;
            }
        }
    }
};

struct ResourcePack {
    ResourcePack() = default;
    virtual ~ResourcePack() = default;

    template <typename Fn>
    void load(const std::string& path, Fn&& fn) {
        if (const auto bytes = load(path)) {
            fn(*bytes);
        }
    }

    virtual auto load(const std::string& path) -> std::optional<std::vector<char>> = 0;
    virtual auto contains(const std::string& path) -> bool = 0;
};

struct PhysFsResourcePack : ResourcePack {
    explicit PhysFsResourcePack(std::string path) : basePath(std::move(path)) {}

    auto contains(const std::string& path) -> bool override {
        return PHYSFS_exists(getFullPath(path).c_str());
    }

    auto load(const std::string& path) -> std::optional<std::vector<char>> override {
        auto file = PHYSFS_openRead(getFullPath(path).c_str());
        if (file != nullptr) {
            std::vector<char> bytes(PHYSFS_fileLength(file));
            PHYSFS_readBytes(file, bytes.data(), bytes.size());
            PHYSFS_close(file);
            return std::move(bytes);
        }
        return std::nullopt;
    }

private:
    auto getFullPath(const std::string& path) const -> std::string {
        return fmt::format("{}/{}", basePath, path);
    }

    std::string basePath;
};

struct FolderResourcePack : ResourcePack {
    explicit FolderResourcePack(std::string path) : basePath(std::move(path)) {}

    auto contains(const std::string& path) -> bool override {
		return std::filesystem::exists(getFullPath(path));
	}

	auto load(const std::string& path) -> std::optional<std::vector<char>> override {
		const auto full_path = getFullPath(path);
		if (std::filesystem::exists(full_path)) {
		    std::vector<char> bytes(std::filesystem::file_size(full_path));
			std::ifstream stream(full_path, std::ios::binary);
			stream.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
			stream.close();
			return std::move(bytes);
		}
		return std::nullopt;
	}

private:
    auto getFullPath(const std::string& path) const -> std::filesystem::path {
        return basePath / path;
    }

	std::filesystem::path basePath;
};

struct ResourcePackManager {
	void addResourcePack(std::unique_ptr<ResourcePack>&& resourcePack) {
		packs.emplace_back(std::move(resourcePack));
	}

	auto load(const std::string& path) -> std::optional<std::vector<char>> {
		for (auto& pack : packs) {
			if (auto value = pack->load(path)) {
				return std::move(value);
			}
		}
		return std::nullopt;
	}

    template <typename Fn>
    void loadAllVersionsOf(const std::string& path, Fn&& fn) {
        for (auto& pack : packs) {
            pack->load(path, std::forward<Fn>(fn));
        }
    }

    auto loadTextureData(const std::string& name, bool flip) -> std::optional<NativeImage> {
		for (auto ext : {".png", ".tga"}) {
			if (auto bytes = load(name + ext)) {
				return NativeImage::read(*bytes, flip);
			}
		}
		return std::nullopt;
	}

private:
	std::vector<std::unique_ptr<ResourcePack>> packs;
};
