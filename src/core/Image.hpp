#pragma once

#include <glm/glm.hpp>
#include <cstdlib>
#include <vector>
#include <array>
#include <span>

struct ImageInfo {
    glm::u32 width;
    glm::u32 height;
};

struct ImageData {
    static ImageData create(glm::u32 width, glm::u32 height) {
        return ImageData(width, height);
    }

    template <typename Fn>
    void map(Fn&& fn) {
        size_t i = 0;
        for (int y = 0; y < _info.height; ++y) {
            for (int x = 0; x < _info.width; ++x) {
                _pixels[i] = fn(_info, glm::ivec2{x, y}, _pixels[i]);
                i += 1;
            }
        }
    }

    void set(glm::u32 x, glm::u32 y, const glm::u8vec4& color) {
        _pixels[static_cast<size_t>(x) + static_cast<size_t>(y) * _info.width] = color;
    }

    glm::u8vec4 get(glm::u32 x, glm::u32 y) {
        return _pixels[static_cast<size_t>(x) + static_cast<size_t>(y) * _info.width];
    }

    ImageInfo info() const {
        return _info;
    }

    std::span<const glm::u8vec4> pixels() const {
        return _pixels;
    }

private:
    ImageData() = default;
    ImageData(glm::u32 width, glm::u32 height)
            : _info{width, height}
            , _pixels(width * height) {}

    ImageInfo _info{};
    std::vector<glm::u8vec4> _pixels{};
};

struct ImageExport {
    static void save(const ImageData& data, const char* file_name) {
        static constexpr auto BYTES_PER_PIXEL = sizeof(glm::u8vec4);
        static constexpr auto FILE_HEADER_SIZE = 14;
        static constexpr auto INFO_HEADER_SIZE = 40;

        const auto [width, height] = data.info();
        const auto pixels = std::as_bytes(data.pixels());
        const auto widthInBytes = width * BYTES_PER_PIXEL;
        const auto paddingSize = (4 - (widthInBytes) % 4) % 4;
        const auto stride = widthInBytes + paddingSize;
        const auto fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

        std::array<uint8_t, 3> padding = {0, 0, 0};

        std::array<uint8_t, FILE_HEADER_SIZE + INFO_HEADER_SIZE> header{
            'B', 'M', /// signature
            0, 0, 0, 0, /// image file size in bytes
            0, 0, 0, 0, /// reserved
            0, 0, 0, 0, /// start of pixel array

            0, 0, 0, 0, /// header size
            0, 0, 0, 0, /// image width
            0, 0, 0, 0, /// image height
            0, 0,       /// number of color planes
            0, 0,       /// bits per pixel
            0, 0, 0, 0, /// compression
            0, 0, 0, 0, /// image size
            0, 0, 0, 0, /// horizontal resolution
            0, 0, 0, 0, /// vertical resolution
            0, 0, 0, 0, /// colors in color table
            0, 0, 0, 0, /// important color count
        };

        header[2] = (unsigned char) (fileSize);
        header[3] = (unsigned char) (fileSize >> 8);
        header[4] = (unsigned char) (fileSize >> 16);
        header[5] = (unsigned char) (fileSize >> 24);
        header[10] = (unsigned char) (FILE_HEADER_SIZE + INFO_HEADER_SIZE);
        header[14 + 0] = (unsigned char) (INFO_HEADER_SIZE);
        header[14 + 4] = (unsigned char) (width);
        header[14 + 5] = (unsigned char) (width >> 8);
        header[14 + 6] = (unsigned char) (width >> 16);
        header[14 + 7] = (unsigned char) (width >> 24);
        header[14 + 8] = (unsigned char) (height);
        header[14 + 9] = (unsigned char) (height >> 8);
        header[14 + 10] = (unsigned char) (height >> 16);
        header[14 + 11] = (unsigned char) (height >> 24);
        header[14 + 12] = (unsigned char) (1);
        header[14 + 14] = (unsigned char) (BYTES_PER_PIXEL * 8);

        auto file = fopen(file_name, "wb");
        fwrite(header.data(), 1, FILE_HEADER_SIZE + INFO_HEADER_SIZE, file);

        for (int i = 0; i < height; i++) {
            fwrite(pixels.subspan(i * widthInBytes).data(), BYTES_PER_PIXEL, width, file);
            fwrite(padding.data(), 1, paddingSize, file);
        }
        fclose(file);
    }
};

/*
    #include <glm/gtc/noise.hpp>

    std::array offsets {
        glm::vec2{0.0f, 0.0f},
        glm::vec2{1.0f, -1.0f},
        glm::vec2{2.0f, -2.0f},
        glm::vec2{3.0f, -3.0f},
        glm::vec2{4.0f, -4.0f},
        glm::vec2{5.0f, -5.0f},
        glm::vec2{6.0f, -6.0f},
        glm::vec2{7.0f, -7.0f},
        glm::vec2{8.0f, -8.0f},
    };

    auto image = ImageData::create(16 * 10, 16 * 10);
    image.map([&offsets](const ImageInfo& info, const glm::ivec2& p, const glm::u8vec4& color) -> glm::u8vec4 {
        const auto fx = (((float)p.x) / ((float)16.0f) - 0.5f);
        const auto fy = (((float)p.y) / ((float)16.0f) - 0.5f);

        float scale = 1.0f;
        float persistence = 0.5f;
        float lacunarity = 2.0f;

        float amplitude = 1.0f;
        float frequency = 1.0f;

        float val = 0;
        float max_val = 0;

        for (auto offset : offsets) {
            float sx = (fx + offset.x) / scale * frequency;
            float sy = (fy + offset.y) / scale * frequency;

            float noise = (glm::perlin(glm::vec2(sx, sy)) + 1.0f) * 0.5f;
            val += noise * amplitude;
            max_val += amplitude;

            amplitude *= persistence;
            frequency *= lacunarity;
        }

        float f = val / max_val;

        if (f < 0.6f) {
            return {255, 255, 255, 255};
        }

        return {0, 255, 0, 255};
    });
    ImageExport::save(image, "image5.bmp");
*/