#pragma once

#include "ResourceManager.hpp"

#include <set>
#include <mutex>
#include <unordered_set>
#include <list>
#include <string>
#include <Json.hpp>
#include <Texture.hpp>
#include <range/v3/all.hpp>

#include <thread>

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
    std::string path;
    NativeImage image;
    int originX;
    int originY;

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

    auto rect() const -> TextureRect {
        return TextureRect{
            originX,
            originY,
            image.width,
            image.height
        };
    }
};

struct SheetData {
	std::vector<TextureAtlasSprite> sprites;
	int width;
	int height;
};

struct TextureAtlasPack {
    struct Holder {
        std::string path;
        NativeImage image;
    };

    struct Slot {
        static auto from(int x, int y, int w, int h) -> Slot {
            return Slot {
                .rect = {x, y, w, h}
            };
        }

        auto canFit(int width, int height) const -> bool {
            return width <= rect.width && height <= rect.height;
        }

        auto addSlot(Holder* holderIn) -> bool {
            if (!canFit(holderIn->image.width, holderIn->image.height)) {
                return false;
            }
            if (holder == nullptr) {
                holder = holderIn;

                const auto originX = rect.x;
                const auto originY = rect.y;
                const auto width = holder->image.width;
                const auto height = holder->image.height;

                if (rect.width > width) {
                    subSlots.emplace_back(Slot::from(originX + width, originY, rect.width - width, height));
                }
                if (rect.height > height) {
                    subSlots.emplace_back(Slot::from(originX, originY + height, rect.width, rect.height - height));
                }

                return true;
            }

            for (auto& slot : subSlots) {
                if (slot.addSlot(holderIn)) {
                    return true;
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
                slot.getAllStitchSlots(std::forward<Fn>(fn));
            }
        }

        std::list<Slot> subSlots;
        Holder* holder = nullptr;
        TextureRect rect{};
    };

    void addSprite(std::string path, NativeImage image) {
        holders.emplace_back(std::make_unique<Holder>(Holder{std::move(path), std::move(image)}));
    }

    auto expandAndAllocateSlot(Holder* holder) -> bool {
        Slot* slot = nullptr;

        auto textureSize = std::max(
            currentWidth + holder->image.width,
            currentHeight + holder->image.height
        );

        slots.emplace_back(Slot::from(currentWidth, 0, textureSize - currentWidth, currentHeight));
        if (!slot && slots.back().canFit(holder->image.width, holder->image.height)) {
            slot = &slots.back();
        }
        slots.emplace_back(Slot::from(0, currentHeight, textureSize, textureSize - currentHeight));
        if (!slot && slots.back().canFit(holder->image.width, holder->image.height)) {
            slot = &slots.back();
        }
        currentWidth = textureSize;
        currentHeight = textureSize;

        return slot->addSlot(holder);
    }

    auto allocateSlot(Holder* holder) -> bool {
        for (auto& slot : slots) {
            if (slot.addSlot(holder)) {
                return true;
            }
        }

        return expandAndAllocateSlot(holder);
    }

    auto build() -> tl::optional<SheetData> {
        std::sort(holders.begin(), holders.end(), [](auto& b, auto& a) -> bool {
            return a->image.width < b->image.width || (a->image.width == b->image.width) && (a->image.height < b->image.height);
        });

        const auto textureSize = std::max(
            nextPowerOf2(holders.at(0)->image.width),
            nextPowerOf2(holders.at(0)->image.height)
        );
        currentWidth = textureSize;
        currentHeight = textureSize;

        slots.emplace_back(Slot::from(0, 0, textureSize, textureSize));
        for (auto&& holder : holders) {
            if (!allocateSlot(holder.get())) {
                return tl::nullopt;
            }
        }

        auto sprites = std::vector<TextureAtlasSprite>{};
        getAllSlots([&sprites](Slot *slot) {
            sprites.emplace_back(
                TextureAtlasSprite{
                    std::move(slot->holder->path),
                    std::move(slot->holder->image),
                    slot->rect.x,
                    slot->rect.y
                }
            );
        });

        return SheetData{
            std::move(sprites),
            currentWidth,
            currentHeight
        };
    }

    template <typename Fn>
    void getAllSlots(Fn&& fn) {
        for (auto&& slot : slots) {
            slot.getAllStitchSlots(std::forward<Fn>(fn));
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
    std::list<Slot> slots;

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
    TextureRect rect;
    glm::ivec2 atlasSize;

    [[nodiscard]] auto get_coords() const -> TextureUVCoordinateSet {
        return TextureUVCoordinateSet{
            .minU = glm::f32(rect.x) / glm::f32(atlasSize.x),
            .minV = glm::f32(rect.y) / glm::f32(atlasSize.y),
            .maxU = glm::f32(rect.x + rect.width) / glm::f32(atlasSize.x),
            .maxV = glm::f32(rect.y + rect.height) / glm::f32(atlasSize.y),
        };
    }
};

struct TextureManager {
    std::mutex mutex{};

    Texture2D atlas;
    TextureAtlasPack pack;
    std::vector<glm::u8vec4> pixels;
    std::vector<TextureAnimation> animations;
    std::map<std::string, TextureAtlasItem> items;

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

            auto&& sprite = items.at(animation.location);
            upload(animation.image, sprite.rect, animation.frames[animation.current_frame].index);
        }
        if (flag) {
            atlas.setPixels(pixels);
        }
    }

    auto get_texture(const std::string& name) const -> TextureUVCoordinateSet {
        if (auto it = items.find(name); it != items.end()) {
            return it->second.get_coords();
        }
        return TextureUVCoordinateSet{0, 0, 0, 0};
    }

    void load_texture(const std::string& name) {
        if (items.contains(name)) {
            return;
        }
        items.emplace(name, TextureAtlasItem{});

        const auto location = ResourceLocation::from(name);

        auto data = read_texture(location).value();
        if (auto anim = read_animation(data, location)) {
            auto new_pixels = new glm::u8[data.width * data.width * data.channels];
            for (size_t i = 0; i < data.width * data.width * data.channels; ++i) {
                new_pixels[i] = data.pixels[i];
            }
            pack.addSprite(name, NativeImage{
                .pixels = NativeImage::ImageData{new_pixels},
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

    auto read_animation(const NativeImage& data, const ResourceLocation& location) -> tl::optional<TextureAnimation> {
        return Resources::open(fmt::format("assets/{}/textures/{}.png.mcmeta", location.get_namespace(), location.get_location()))
            .and_then([](auto&& resource) { return Json::Read::read(*resource); })
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
		auto sheet = pack.build();

        pixels = std::vector<glm::u8vec4>(sheet->width * sheet->height);
        atlas = Texture2D(sheet->width, sheet->height, vk::Format::eR8G8B8A8Unorm);

		for (auto&& sprite : sheet->sprites) {
            auto& item = items.at(sprite.path);
            item.rect = TextureRect{
                sprite.originX,
                sprite.originY,
                sprite.width(),
                sprite.height()
            };
            item.atlasSize = glm::ivec2(sheet->width, sheet->height);
            upload(sprite.image, item.rect, 0);
		}
        atlas.setPixels(pixels);
    }

    void upload(const NativeImage& image, const TextureRect& rect, size_t frame) {
        auto offset = image.channels * rect.width * rect.height * frame;
        if (image.channels == 3) {
            for (int y = rect.y; y < rect.y + rect.height; y++) {
                auto i = y * atlas.width() + rect.x;

                for (int x = 0; x < rect.width; x++, i++) {
                    pixels[i][0] = image.pixels[offset++];
                    pixels[i][1] = image.pixels[offset++];
                    pixels[i][2] = image.pixels[offset++];
                    pixels[i][3] = 0xFF;
                }
            }
        } else if (image.channels == 4) {
            for (int y = rect.y; y < rect.y + rect.height; y++) {
                auto i = y * atlas.width() + rect.x;

                for (int x = 0; x < rect.width; x++, i++) {
                    pixels[i][0] = image.pixels[offset++];
                    pixels[i][1] = image.pixels[offset++];
                    pixels[i][2] = image.pixels[offset++];
                    pixels[i][3] = image.pixels[offset++];
                }
            }
        } else {
            spdlog::error("unsupported format [channels = {}]", image.channels);
        }
    }

    static auto instance() -> TextureManager& {
        static TextureManager manager;
        return manager;
    }

private:
    static auto read_texture(const ResourceLocation& location) -> tl::optional<NativeImage> {
        for (auto ext : {"png", "tga"}) {
            const auto path = fmt::format("assets/{}/textures/{}.{}", location.get_namespace(), location.get_location(), ext);
            if (auto resource = Resources::get(path)) {
                return NativeImage::read(resource->bytes(), false);
            }
        }
        return tl::nullopt;
    }
};