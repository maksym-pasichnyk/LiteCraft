#pragma once

#include "resource_manager.hpp"

#include <set>
#include <string>
#include <range/v3/all.hpp>
#include <json/json.hpp>

#include <GL/gl3w.h>

struct TextureRect {
	int x;
	int y;
	int width;
	int height;
};

struct TextureUVCoordinateSet {
    float minU;
    float minV;
    float maxU;
    float maxV;

    inline constexpr float getInterpolatedU(float t) const {
        return (1 - t) * minU + t * maxU;
    }

    inline constexpr float getInterpolatedV(float t) const {
        return (1 - t) * minV + t * maxV;
    }
};


struct TextureAtlasSprite {
	struct Info {
		std::string path;
		NativeImage image;

		void *pixels() const {
			return image.pixels.get();
		}

		int width() const {
			return image.width;
		}

		int height() const {
			return image.height;
		}
	};

	Info info;
	int originX;
	int originY;

	TextureAtlasSprite(Info info, int originX, int originY)
		: info(std::move(info)), originX(originX), originY(originY) {}
};

struct SheetData {
	std::vector<TextureAtlasSprite> sprites;
	int width;
	int height;

	SheetData(std::vector<TextureAtlasSprite>&& sprites, int width, int height)
		: sprites(std::move(sprites))
		, width(width)
		, height(height) {}
};

struct TextureAtlasPack {
	struct Holder {
		TextureAtlasSprite::Info info;
		int width;
		int height;

		Holder(TextureAtlasSprite::Info info)
			: info(std::move(info))
			, width(info.width())
			, height(info.height()) {}
	};

	struct Slot {
		Slot() = default;

		Slot(int x, int y, int w, int h) : rect{x, y, w, h} {}

		bool canFit(int width, int height) {
			return width <= rect.width && height <= rect.height;
		}

		bool addSlot(Holder* holderIn) {
			if (canFit(holderIn->width, holderIn->height)) {
				if (holder == nullptr) {
					holder = holderIn;

					int originX = rect.x;
					int originY = rect.y;
					int w = holder->width;
					int h = holder->height;

					if (rect.width > w) {
						subSlots.emplace_back(new Slot(originX + w, originY, rect.width - w, h));
					}
					if (rect.height > h) {
						subSlots.emplace_back(new Slot(originX, originY + h, rect.width, rect.height - h));
					}

					return true;
				}

				for (auto& slot : subSlots) {
					if (slot->addSlot(holderIn)) {
						return true;
					}
				}
			}
			return false;
		}

		template <typename Fn>
		void getAllStitchSlots(Fn&& fn) {
			if (holder != nullptr) {
				fn(this);
			}

			for (auto& slot : subSlots) {
				slot->getAllStitchSlots(std::forward<Fn>(fn));
			}
		}

		std::vector<std::unique_ptr<Slot>> subSlots;
		Holder* holder = nullptr;
		TextureRect rect;
	};

	void addSprite(std::string path, NativeImage image) {
		holders.emplace_back(std::make_unique<Holder>(TextureAtlasSprite::Info{std::move(path), std::move(image)}));
	}

	bool expandAndAllocateSlot(Holder* holder) {
		Slot* slot = nullptr;

		int textureSize = std::max(
			/*nextPowerOf2*/(currentWidth + holder->width),
			/*nextPowerOf2*/(currentHeight + holder->height)
		);

		slots.reserve(2);
		slots.emplace_back(std::make_unique<Slot>(currentWidth, 0, textureSize - currentWidth, currentHeight));
		if (slots.back()->canFit(holder->width, holder->height)) {
			slot = slots.back().get();
		}
		slots.emplace_back(std::make_unique<Slot>(0, currentHeight, textureSize, textureSize - currentHeight));
		if (!slot && slots.back()->canFit(holder->width, holder->height)) {
			slot = slots.back().get();
		}
		currentWidth = textureSize;
		currentHeight = textureSize;

		return slot->addSlot(holder);
	}

	bool allocateSlot(Holder* holder) {
		for (auto& slot : slots) {
			if (slot->addSlot(holder)) {
				return true;
			}
		}

		return expandAndAllocateSlot(holder);
	}

	std::optional<SheetData> build() {
		std::sort(holders.begin(), holders.end(), [](auto& b, auto& a) -> bool {
			return a->width < b->width || (a->width == b->width) && (a->height < b->height);
		});

		const auto textureSize = std::max(
			nextPowerOf2(holders[0]->width),
			nextPowerOf2(holders[0]->height)
		);
		currentWidth = textureSize;
		currentHeight = textureSize;

		slots.emplace_back(new Slot(0, 0, textureSize, textureSize));
		for (auto&& holder : holders) {
			if (!allocateSlot(holder.get())) {
				return std::nullopt;
			}
		}

		std::vector<TextureAtlasSprite> sprites;
		getAllSlots([&sprites](Slot *slot) {
			sprites.emplace_back(std::move(slot->holder->info), slot->rect.x, slot->rect.y);
		});

		return SheetData(std::move(sprites), currentWidth, currentHeight);
	}

	template <typename Fn>
	void getAllSlots(Fn&& fn) {
		for (auto&& slot : slots) {
			slot->getAllStitchSlots(std::forward<Fn>(fn));
		}
	}

	inline static constexpr unsigned nextPowerOf2(unsigned n) noexcept {
		n--;
		n |= n >> 1u;
		n |= n >> 2u;
		n |= n >> 4u;
		n |= n >> 8u;
		n |= n >> 16u;
		n++;
		return n;
	}

private:
	std::vector<std::unique_ptr<Holder>> holders;
	std::vector<std::unique_ptr<Slot>> slots;

	int currentWidth;
	int currentHeight;
};

struct TextureAtlasTextureItem {
	std::string name;
	std::vector<TextureUVCoordinateSet> textures;

	TextureUVCoordinateSet operator[](int i) const {
		return textures[i];
	}

	TextureUVCoordinateSet get(int i) const {
		return textures[i];
	}
};

struct ParsedAtlasNodeElement {
	std::string path;
//	std::optional<rgb24> overlay_color;
//	std::optional<rgb24> tint_color;
};

struct ParsedAtlasNode {
	ParsedAtlasNode(std::string name) : name(std::move(name)) {}

	std::string name;
	int quad;
	std::vector<ParsedAtlasNodeElement> elements;
};

struct Texture {

};

struct TextureAtlas /*: Texture*/ {
	std::optional<SheetData> sheet;
	std::string texture_name;
	int padding;
	int num_mip_levels;

//	sf::Texture texture;
	GLuint texture;

//	TextureAtlasTextureItem* pMissingTexture;

	std::map<std::string, TextureAtlasTextureItem> items;

	void _readElement(const Json& data, ParsedAtlasNodeElement& element) {
		if (data.is_string()) {
			element.path = data.to_string();
		} else {
			element.path = data.at("path").to_string();
//			if (auto overlay_color = value.get("overlay_color")) {
//				element.overlay_color = overlay_color->as_string();
//			}
//			if (auto tint_color = value.get("tint_color")) {
//				element.tint_color = tint_color->get<std::string>();
//			}
		}
	}

	void _readNode(const Json& data, ParsedAtlasNode& node) {
		node.quad = data.value("quad", 0);

		auto elements = data.at("textures");
		if (elements.is_array()) {
			for (auto& element : elements.to_array()) {
				_readElement(element, node.elements.emplace_back());
			}
		} else {
			_readElement(elements, node.elements.emplace_back());
		}
	}

	void _loadAtlasNodes(const Json& data, std::vector<ParsedAtlasNode>& nodes) {
		for (auto& [key, val] : data.to_object()) {
			_readNode(val, nodes.emplace_back(key));
		}
	}

	void loadMetaFile(ResourcePackManager& resources) {
        TextureAtlasPack textureAtlasPack{};
        std::vector<ParsedAtlasNode> nodes{};

        resources.for_each("textures/terrain_texture.json", [&, this](std::istream& stream) {
            auto terrain_texture = Json::Read::read(stream).value();

//            auto resource_pack_name = terrain_texture.at("resource_pack_name").get<std::string>();
//            texture_name = terrain_texture.at("texture_name").get<std::string>();
//            padding = terrain_texture.at("padding").get<int>();
//            num_mip_levels = terrain_texture.at("num_mip_levels").get<int>();
            _loadAtlasNodes(terrain_texture.at("texture_data"), nodes);

            auto require_textures = nodes
                | ranges::views::transform(&ParsedAtlasNode::elements)
                | ranges::views::join
                | ranges::views::transform(&ParsedAtlasNodeElement::path)
                | ranges::views::unique;

            for (const auto &path : require_textures) {
				if (auto resource = resources.load_texture_data(path, true)) {
                	textureAtlasPack.addSprite(path, *std::move(resource));
				}
            }
        });

        fmt::print("build texture atlas\n");

		sheet = textureAtlasPack.build();

		std::map<std::string, std::reference_wrapper<const TextureAtlasSprite>> sprites;
		for (const auto &sprite : sheet->sprites) {
			sprites.emplace(sprite.info.path, sprite);
		}

		for (const auto &node : nodes) {
			auto& item = items[node.name];

			item.textures.reserve(node.elements.size());
			for (const auto &element : node.elements) {
				const auto& sprite = sprites.at(element.path).get();

				TextureRect rect{
                    sprite.originX,
                    sprite.originY,
                    sprite.info.width(),
                    sprite.info.height()
				};

				auto& textureUvCoordinateSet = item.textures.emplace_back();
				textureUvCoordinateSet.minU = float(rect.x) / float(sheet->width);
				textureUvCoordinateSet.minV = float(rect.y) / float(sheet->height);
				textureUvCoordinateSet.maxU = float(rect.x + rect.width) / float(sheet->width);
				textureUvCoordinateSet.maxV = float(rect.y + rect.height) / float(sheet->height);
			}
		}
	}

	auto getTextureItem(const std::string& name) -> TextureAtlasTextureItem* {
		return &items.at(name);
	}

	void loadTexture(/*TextureManager* textureManager*/) /*override*/ {
		std::vector<uint8_t> pixels(sheet->width * sheet->height * 4);

		for (auto& sprite : sheet->sprites) {
			TextureRect rect {
				sprite.originX,
				sprite.originY,
				sprite.info.width(),
				sprite.info.height()
			};

			int i2 = 0;
			for (int y = rect.y; y < rect.y + rect.height; y++) {
				auto i = (y * sheet->width + rect.x) * 4;

				for (int x = 0; x < rect.width; x++) {
					pixels[i++] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
					pixels[i++] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
					pixels[i++] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
					pixels[i++] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
				}
			}
		}

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sheet->width, sheet->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

//		texture.create(sheet->width, sheet->height);
//		texture.update(pixels.data());
//		texture.generateMipmap();
	}
};