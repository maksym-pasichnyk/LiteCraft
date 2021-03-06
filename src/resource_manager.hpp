#pragma once

#include <span>
#include <memory>
#include <vector>
#include <fstream>
#include <optional>
#include <filesystem>

#include "stb_image.hpp"

#include <ranges>
#include <cstring>
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

	static NativeImage read(std::span<char> bytes, bool flip) {
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
	explicit ResourcePack(std::filesystem::path path) : basePath(std::move(path)) {}

	std::filesystem::path getFullPath(const std::filesystem::path& path) {
		return basePath / path;
	}

	inline bool contains(const std::string& path) {
		const auto file_path = basePath / path;
		return std::filesystem::exists(file_path);
	}

	inline auto loadFile(const std::filesystem::path& path) -> std::optional<std::vector<char>> {
		const auto filePath = getFullPath(path);
		if (std::filesystem::exists(filePath)) {
			std::vector<char> bytes(std::filesystem::file_size(filePath));
			std::ifstream stream(filePath, std::ios::binary);
			stream.read(bytes.data(), bytes.size());
			stream.close();
			return std::move(bytes);
		}
		return std::nullopt;
	}

    template <typename Fn>
    void loadResources(const std::filesystem::path& path, Fn&& fn) {
        for (const auto& e : std::filesystem::recursive_directory_iterator(getFullPath(path))) {
            if (e.is_regular_file()) {
                std::vector<char> bytes(std::filesystem::file_size(e.path()));
                std::ifstream stream(e.path(), std::ios::binary);
                stream.read(bytes.data(), bytes.size());
                stream.close();

                fn(bytes);
            }
        }
    }

private:
	std::filesystem::path basePath;
};

struct ResourceManager {
	void addResourcePack(std::unique_ptr<ResourcePack>&& resourcePack) {
		packs.emplace_back(std::move(resourcePack));
	}

	std::optional<std::vector<char>> loadFile(const std::filesystem::path& path) {
		for (auto& pack : packs) {
			if (auto value = pack->loadFile(path)) {
				return std::move(value);
			}
		}
		return std::nullopt;
	}

	template <typename Fn>
    void loadResources(const std::filesystem::path& path, Fn&& fn) {
        for (auto& pack : packs) {
            pack->loadResources(path, std::forward<Fn>(fn));
        }
    }

	std::optional<NativeImage> loadTextureData(const std::string& name, bool flip) {
		for (auto ext : {".png", ".tga"}) {
			if (auto bytes = loadFile(name + ext)) {
				return NativeImage::read(*bytes, flip);
			}
		}
		return std::nullopt;
	}

private:
	std::vector<std::unique_ptr<ResourcePack>> packs;
};
