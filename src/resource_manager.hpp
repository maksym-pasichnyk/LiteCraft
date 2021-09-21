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

namespace physfs {
    struct filebuf : std::streambuf {
        filebuf() = default;
        ~filebuf() override {
            if (file != nullptr) {
                PHYSFS_close(file);
            }
        }

        auto open(const std::string& path) -> bool {
            if (file != nullptr) { return false; }
            file = PHYSFS_openRead(path.c_str());
            return file != nullptr;
        }

        auto is_open() const -> bool {
            return file != nullptr;
        }

        auto underflow() -> int_type override {
            if (PHYSFS_eof(file)) {
                return traits_type::eof();
            }
            const auto len = PHYSFS_read(file, tmp.data(), 1, tmp.size());
            if (len < 1) {
                return traits_type::eof();
            }
            setg(tmp.data(), tmp.data(), tmp.data() + len);
            return static_cast<int_type>(*gptr());
        }

        auto length() const -> size_t {
            return PHYSFS_fileLength(file);
        }

    private:
        PHYSFS_File* file = nullptr;
        std::array<char, 1024> tmp{};
    };

    struct ifstream : std::istream {
        explicit ifstream(const std::string& path) : std::istream(&buf) {
            if (!buf.open(path)) {
                setstate(ios_base::failbit);
            }
        }

        auto length() const -> size_t {
            return buf.length();
        }

    private:
        filebuf buf{};
    };

    static auto exists(const std::string& path) -> bool {
        return PHYSFS_exists(path.c_str());
    }
}

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
			stbi_vertical_flip(pixels, width, height, channels * sizeof(stbi_uc));
		}

		return NativeImage{
			.pixels = ImageDataPtr{pixels},
			.width = width,
			.height = height,
			.channels = channels
		};
	}

private:
	static void stbi_vertical_flip(void *image, int w, int h, int bytes_per_pixel) {
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
	void open(const std::string& path, Fn&& fn) {
        thread_local auto func = std::ref(fn);
        open_with_callback(path, [](std::istream& stream) { func.get()(stream); });
	}

    template <typename Fn>
    void iterate(const std::string& path, Fn&& fn) {
        thread_local auto func = std::ref(fn);
        iterate_with_callback(path, [](std::istream& stream) { func.get()(stream); });
    }

	virtual auto load(const std::string& path) -> std::optional<std::vector<char>> = 0;
	virtual auto contains(const std::string& path) -> bool = 0;

    virtual void open_with_callback(const std::string& path, void(*fn)(std::istream&)) = 0;
    virtual void iterate_with_callback(const std::string& path, void(*fn)(std::istream&)) = 0;
};

struct PhysFsResourcePack : ResourcePack {
	explicit PhysFsResourcePack(std::string path) : base_path(std::move(path)) {}

	auto contains(const std::string& path) -> bool override {
		return physfs::exists(get_full_path(path));
	}

	auto load(const std::string& path) -> std::optional<std::vector<char>> override {
        if (physfs::ifstream file{get_full_path(path)}) {
            std::vector<char> bytes(file.length());
            file.read(bytes.data(), bytes.size());
            return std::move(bytes);
        }
		return std::nullopt;
	}

	void open_with_callback(const std::string& path, void(*fn)(std::istream&)) override {
        physfs::ifstream stream{get_full_path(path)};
        fn(stream);
	}

    void iterate_with_callback(const std::string& directory, void(*fn)(std::istream&)) override {
        struct recursive_directory_iterator {
            static void next(const std::string& directory, void(*fn)(std::istream&)) {
                auto files = PHYSFS_enumerateFiles(directory.c_str());
                for (auto file = files; *file != nullptr; file++) {
                    const auto path = fmt::format("{}/{}", directory.c_str(), *file);

                    if (PHYSFS_isDirectory(path.c_str())) {
                        next(path, fn);
                    } else {
                        physfs::ifstream stream{path};
                        fn(stream);
                    }
                }
                PHYSFS_freeList(files);
            }
        };

        return recursive_directory_iterator::next(get_full_path(directory), fn);
    }

private:
	auto get_full_path(const std::string& path) const -> std::string {
		return fmt::format("{}/{}", base_path, path);
	}

	std::string base_path;
};

struct FolderResourcePack : ResourcePack {
	explicit FolderResourcePack(const std::string& path) : base_path(path) {}

	auto contains(const std::string& path) -> bool override {
		return std::filesystem::exists(get_full_path(path));
	}

	auto load(const std::string& path) -> std::optional<std::vector<char>> override {
		const auto full_path = get_full_path(path);
		if (std::filesystem::exists(full_path)) {
			std::vector<char> bytes(std::filesystem::file_size(full_path));
			std::ifstream stream(full_path, std::ios::binary);
			stream.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
			stream.close();
			return std::move(bytes);
		}
		return std::nullopt;
	}

    void open_with_callback(const std::string& path, void(*fn)(std::istream&)) override {
        std::ifstream stream(get_full_path(path), std::ios::binary);
        fn(stream);
    }

    void iterate_with_callback(const std::string& path, void(*fn)(std::istream&)) override {
        for (auto&& entry : std::filesystem::recursive_directory_iterator{get_full_path(path)}) {
            if (entry.is_regular_file()) {
                std::ifstream stream(entry.path(), std::ios::binary);
                fn(stream);
            }
        }
    }

private:
	auto get_full_path(const std::string& path) const -> std::filesystem::path {
		return base_path / path;
	}

	std::filesystem::path base_path;
};

struct ResourcePackManager {
	void add_resource_pack(std::unique_ptr<ResourcePack>&& pack) {
		packs.emplace_back(std::move(pack));
	}

	auto load(const std::string& path) -> std::optional<std::vector<char>> {
		for (auto& pack : packs) {
			if (auto bytes = pack->load(path)) {
				return std::move(bytes);
			}
		}
		return std::nullopt;
	}

	template <typename Fn>
	void for_each(const std::string& path, Fn&& fn) {
		for (auto& pack : packs) {
			pack->open(path, std::forward<Fn>(fn));
		}
	}

	auto load_texture_data(const std::string& name, bool flip) -> std::optional<NativeImage> {
		for (auto ext : {".png", ".tga"}) {
			if (auto bytes = load(name + ext)) {
				return NativeImage::read(*bytes, flip);
			}
		}
		return std::nullopt;
	}

    template <typename Fn>
    void iterate(const std::string& path, Fn&& fn) {
        for (auto& pack : packs) {
            pack->iterate(path, std::forward<Fn>(fn));
        }
    }

private:
	std::vector<std::unique_ptr<ResourcePack>> packs;
};
