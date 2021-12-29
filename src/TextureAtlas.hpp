#pragma once

#include "ResourceManager.hpp"

#include <set>
#include <string>
#include <Json.hpp>
#include <Texture.hpp>
#include <range/v3/all.hpp>

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

        auto channels() const -> int {
            return image.channels;
        }

		auto pixels() const -> void* {
			return image.pixels.get();
		}

		auto width() const -> int {
			return image.width;
		}

		auto height() const -> int {
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

    auto expandAndAllocateSlot(Holder* holder) -> bool {
        Slot* slot = nullptr;

        auto textureSize = std::max(
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

    auto allocateSlot(Holder* holder) -> bool {
        for (auto& slot : slots) {
            if (slot->addSlot(holder)) {
                return true;
            }
        }

        return expandAndAllocateSlot(holder);
    }

    auto build() -> tl::optional<SheetData> {
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
                return tl::nullopt;
            }
        }

        auto sprites = std::vector<TextureAtlasSprite>{};
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

struct AnimationFrame {
    size_t index;
    glm::i64 time;
};

struct TextureAnimation {
    NativeImage image;
    std::string location;

    glm::f32 remaining_time = 0;
    size_t current_frame = 0;

    bool interpolate;
    std::vector<AnimationFrame> frames;
};

struct TextureAtlasItem {
    glm::i32 x;
    glm::i32 y;
    glm::i32 width;
    glm::i32 height;
    TextureUVCoordinateSet coords;
};

struct TextureManager {
    Texture2D atlas;
    tl::optional<SheetData> sheet;
    TextureAtlasPack pack;
    std::set<std::string> images;
    std::map<std::string, TextureAtlasItem> items;
    std::vector<TextureAnimation> animations;
    std::vector<glm::u8vec4> pixels;

    void tick(float delta) {
        auto flag = false;

        for (auto& animation : animations) {
            animation.remaining_time += delta;
            if (animation.remaining_time < glm::f32(animation.frames[animation.current_frame].time) / 20.0f) {
                continue;
            }
            flag = true;
            animation.remaining_time = 0;
            animation.current_frame = (animation.current_frame + 1) % animation.frames.size();

            auto& texture = items.at(animation.location);

            const auto rect = TextureRect {
                texture.x,
                texture.y,
                texture.width,
                texture.height
            };

            int i2 = animation.image.channels * texture.width * texture.height * animation.frames[animation.current_frame].index;
            if (animation.image.channels == 3) {
                for (int y = rect.y; y < rect.y + rect.height; y++) {
                    auto i = y * sheet->width + rect.x;

                    for (int x = 0; x < rect.width; x++, i++) {
                        pixels[i][0] = reinterpret_cast<unsigned char*>(animation.image.pixels.get())[i2++];
                        pixels[i][1] = reinterpret_cast<unsigned char*>(animation.image.pixels.get())[i2++];
                        pixels[i][2] = reinterpret_cast<unsigned char*>(animation.image.pixels.get())[i2++];
                        pixels[i][3] = 0xFF;
                    }
                }
            } else if (animation.image.channels == 4) {
                for (int y = rect.y; y < rect.y + rect.height; y++) {
                    auto i = y * sheet->width + rect.x;

                    for (int x = 0; x < rect.width; x++, i++) {
                        pixels[i][0] = reinterpret_cast<unsigned char*>(animation.image.pixels.get())[i2++];
                        pixels[i][1] = reinterpret_cast<unsigned char*>(animation.image.pixels.get())[i2++];
                        pixels[i][2] = reinterpret_cast<unsigned char*>(animation.image.pixels.get())[i2++];
                        pixels[i][3] = reinterpret_cast<unsigned char*>(animation.image.pixels.get())[i2++];
                    }
                }
            } else {
                spdlog::error("unsupported format [channels = {}]", animation.image.channels);
            }
        }
        if (flag) {
            atlas.setPixels(pixels);
        }
    }

    auto get_texture(const std::string& name) const -> TextureUVCoordinateSet {
        if (auto it = items.find(name); it != items.end()) {
            return it->second.coords;
        }
        return TextureUVCoordinateSet{0, 0, 0, 0};
    }

    void load_texture(ResourceManager& resources, const std::string& name) {
        if (items.contains(name)) {
            return;
        }
        images.emplace(name);

        const auto location = ResourceLocation::from(name).get_location();
        auto data = read_texture(resources, location).value();
        if (auto anim = read_animation(resources, data, location)) {
            auto pixels = new std::byte[data.width * data.width * data.channels];
            for (size_t i = 0; i < data.width * data.width * data.channels; ++i) {
                pixels[i] = data.pixels[i];
            }
            pack.addSprite(name, NativeImage{
                .pixels = NativeImage::ImageData{pixels},
                .width = data.width,
                .height = data.width,
                .channels = data.channels,
            });
            anim->image = std::move(data);
            anim->location = name;
            animations.emplace_back(std::move(*anim));
        } else {
            pack.addSprite(name, std::move(data));
        }
    }

    auto read_animation(ResourceManager& resources, const NativeImage& data, const std::string& path) -> tl::optional<TextureAnimation> {
        return resources
            .open(fmt::format("assets/minecraft/textures/{}.png.mcmeta", path))
            .and_then([](auto&& resource) { return Json::Read::read(*resource.io); })
            .map([&](auto&& meta) -> TextureAnimation {
                auto&& animation = meta.at("animation");
                const auto frame_time = animation.value_or("frametime", glm::i64(1));
                const auto interpolate = animation.value_or("interpolate", false);

                return TextureAnimation{
                    .interpolate = interpolate,
                    .frames = animation
                        .find("frames")
                        .and_then([](auto&& v) { return v.as_array(); })
                        .map_or_else(
                            [&](auto&& frames) -> std::vector<AnimationFrame> {
                                auto out = std::vector<AnimationFrame>{};
                                for (auto&& frame : frames) {
                                    if (auto index = frame.as_i64()) {
                                        out.emplace_back(AnimationFrame{
                                            .index = static_cast<size_t>(*index),
                                            .time = frame_time
                                        });
                                    } else {
                                        out.emplace_back(AnimationFrame{
                                            .index = static_cast<size_t>(frame.at("index").as_i64().value()),
                                            .time = frame_time * frame.at("frameTime").as_i64().value()
                                        });
                                    }
                                }
                                return out;
                            },
                            [&]() -> std::vector<AnimationFrame> {
                                auto frames = std::vector<AnimationFrame>(data.height / data.width);
                                for (size_t i = 0; i < frames.size(); ++i) {
                                    frames[i] = AnimationFrame{
                                        .index = i,
                                        .time = frame_time
                                    };
                                }
                                return frames;
                            }
                        )
                };
            });
    }

    void build() {
		sheet = pack.build();

		for (const auto &sprite : sheet->sprites) {
            auto& item = items[sprite.info.path];
            const auto rect = TextureRect{
                sprite.originX,
                sprite.originY,
                sprite.info.width(),
                sprite.info.height()
            };
            item.x = rect.x;
            item.y = rect.y;
            item.width = rect.width;
            item.height = rect.height;
            item.coords = TextureUVCoordinateSet{
                .minU = glm::f32(rect.x) / glm::f32(sheet->width),
                .minV = glm::f32(rect.y) / glm::f32(sheet->height),
                .maxU = glm::f32(rect.x + rect.width) / glm::f32(sheet->width),
                .maxV = glm::f32(rect.y + rect.height) / glm::f32(sheet->height),
            };
		}
    }

    void upload() {
        pixels = std::vector<glm::u8vec4>(sheet->width * sheet->height);

        for (auto& sprite : sheet->sprites) {
            const auto rect = TextureRect {
                sprite.originX,
                sprite.originY,
                sprite.info.width(),
                sprite.info.height()
            };

            int i2 = 0;
            if (sprite.info.channels() == 3) {
                for (int y = rect.y; y < rect.y + rect.height; y++) {
                    auto i = y * sheet->width + rect.x;

                    for (int x = 0; x < rect.width; x++, i++) {
                        pixels[i][0] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
                        pixels[i][1] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
                        pixels[i][2] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
                        pixels[i][3] = 0xFF;
                    }
                }
            } else if (sprite.info.channels() == 4) {
                for (int y = rect.y; y < rect.y + rect.height; y++) {
                    auto i = y * sheet->width + rect.x;

                    for (int x = 0; x < rect.width; x++, i++) {
                        pixels[i][0] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
                        pixels[i][1] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
                        pixels[i][2] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
                        pixels[i][3] = reinterpret_cast<unsigned char*>(sprite.info.pixels())[i2++];
                    }
                }
            } else {
                spdlog::error("unsupported format [channels = {}]", sprite.info.channels());
            }
        }

        atlas = Texture2D(sheet->width, sheet->height, vk::Format::eR8G8B8A8Unorm);
        atlas.setPixels(pixels);
    }

    static auto instance() -> TextureManager& {
        static TextureManager manager;
        return manager;
    }

private:
    static auto read_texture(ResourceManager& resources, const std::string& name) -> tl::optional<NativeImage> {
        for (auto ext : {"png", "tga"}) {
            if (auto bytes = resources.load(fmt::format("assets/minecraft/textures/{}.{}", name, ext))) {
                return NativeImage::read(*bytes, false);
            }
        }
        return tl::nullopt;
    }
};