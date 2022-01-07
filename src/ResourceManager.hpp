#pragma once

#include <span>
#include <memory>
#include <vector>
#include <cstring>
#include <fstream>
#include <physfs.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <tl/optional.hpp>
#include <spdlog/spdlog.h>

#include "stb_image.hpp"
#include "Resources.hpp"

struct ResourceLocation {
    static auto from(const std::string& name) {
        using namespace std::string_literals;
        const auto pos = name.find(':');
        if (pos != std::string::npos) {
            return ResourceLocation(std::array{
                name.substr(0, pos),
                name.substr(pos + 1)
            });
        }
        return ResourceLocation(std::array{"minecraft"s, name});
    }

    [[nodiscard]] auto get_namespace() && -> std::string {
        return std::move(_parts[0]);
    }

    [[nodiscard]] auto get_location() && -> std::string {
        return std::move(_parts[1]);
    }

    [[nodiscard]] auto get_namespace() const& -> const std::string& {
        return _parts[0];
    }

    [[nodiscard]] auto get_location() const& -> const std::string& {
        return _parts[1];
    }

private:
    explicit ResourceLocation(std::array<std::string, 2> parts) : _parts(std::move(parts)) {}

    std::array<std::string, 2> _parts;
};

struct NativeImage {
	struct ImageDataFree {
		void operator()(glm::u8 ptr[]) {
			stbi_image_free(ptr);
		}
	};

	using ImageData = std::unique_ptr<glm::u8[], ImageDataFree>;

	ImageData pixels;
	int width = 0;
	int height = 0;
	int channels = 0;

	static auto read(std::span<const char> bytes, bool flip) -> tl::optional<NativeImage> {
		auto data = reinterpret_cast<const unsigned char *>(bytes.data());

		int width = 0, height = 0, channels = 0;
		auto pixels = stbi_load_from_memory(data, bytes.size(), &width, &height, &channels, 0);
        if (pixels == nullptr) {
            stbi_load_from_memory(data, bytes.size(), &width, &height, &channels, 0);
            return tl::nullopt;
        }
		if (flip) {
			stbi_vertical_flip(pixels, width, height, channels * sizeof(stbi_uc));
		}
		return NativeImage{
			.pixels = ImageData{static_cast<glm::u8*>(static_cast<void*>(pixels))},
			.width = width,
			.height = height,
			.channels = channels
		};
	}

private:
	static void stbi_vertical_flip(void *image, int w, int h, int bytes_per_pixel) {
		const auto bytes_per_row = static_cast<size_t>(w) * bytes_per_pixel;
		auto *bytes = reinterpret_cast<stbi_uc *>(image);

		std::array<stbi_uc, 2048> temp{};
		for (int row = 0; row < (h >> 1); row++) {
			auto row0 = bytes + row * bytes_per_row;
			auto row1 = bytes + (h - row - 1) * bytes_per_row;
			// swap row0 with row1
			auto bytes_left = bytes_per_row;
			while (bytes_left) {
				const auto bytes_copy = std::min(bytes_left, temp.size());
				std::memcpy(temp.data(), row0, bytes_copy);
				std::memcpy(row0, row1, bytes_copy);
				std::memcpy(row1, temp.data(), bytes_copy);
				row0 += bytes_copy;
				row1 += bytes_copy;
				bytes_left -= bytes_copy;
			}
		}
	}
};

struct ResourceManager {
    template <typename Fn>
    static void enumerate(const std::string& path, Fn&& fn) {
        if (!PHYSFS_exists(path.c_str())) {
            return;
        }
        recursive_directory_iterator::next(path, fn);
    }

private:
    struct recursive_directory_iterator {
        static void next(const std::string& directory, void(*fn)(std::istream&)) {
            auto files = PHYSFS_enumerateFiles(directory.c_str());
            for (auto file = files; *file != nullptr; file++) {
                const auto path = fmt::format("{}/{}", directory.c_str(), *file);

                if (PHYSFS_isDirectory(path.c_str())) {
                    next(path, fn);
                } else if (ResourceStream stream{path}) {
                    fn(stream);
                }
            }
            PHYSFS_freeList(files);
        }
    };
};
