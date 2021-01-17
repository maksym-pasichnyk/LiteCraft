#pragma once

#include <vector>
#include <fstream>
#include <optional>
#include <filesystem>

#include "stb_image.hpp"

#include <ranges>
//#include <range/v3/all.hpp>

struct NativeImage {
	void* pixels = nullptr;
	int width = 0;
	int height = 0;
	int channels = 0;

	static NativeImage read(std::span<char> bytes) {
		auto data = reinterpret_cast<const unsigned char *>(bytes.data());

		int width, height, channels;
		auto pixels = stbi_load_from_memory(data, bytes.size(), &width, &height, &channels, 0);

		return NativeImage{
			.pixels = pixels,
			.width = width,
			.height = height,
			.channels = channels
		};
	}
};

struct ResourcePack {
	ResourcePack(std::filesystem::path path) : basePath(std::move(path)) {}

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

//	auto getResources(const std::filesystem::path& path) -> std::vector<std::vector<char>> {
//		auto directiories = std::filesystem::recursive_directory_iterator(getFullPath(path));
//
//		auto resources = directiories
//			| ranges::views::filter([] (auto& entry) { return !entry.is_directory(); })
//			| ranges::views::transform([](auto& entry) {
//				std::vector<char> bytes(std::filesystem::file_size(entry.path()));
//				std::ifstream stream(entry.path(), std::ios::binary);
//				stream.read(bytes.data(), bytes.size());
//				stream.close();
//				return std::move(bytes);
//			});
//		std::vector<std::vector<char>> out;
//		for (auto resource : resources) {
//			out.emplace_back(std::move(resource));
//		}
//		return std::move(out);
//	}

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

//	std::vector<std::vector<char>> getResources(const std::filesystem::path& path) {
//		return packs | ranges::views::transform([&path](auto& pack) { return pack->getResources(path); }) | ranges::actions::join;
//	}

	std::optional<NativeImage> loadTextureData(const std::string& name) {
		for (auto ext : {".png", ".tga"}) {
			if (auto bytes = loadFile(name + ext)) {
				return NativeImage::read(*bytes);
			}
		}
		return std::nullopt;
	}

private:
	std::vector<std::unique_ptr<ResourcePack>> packs;
};
