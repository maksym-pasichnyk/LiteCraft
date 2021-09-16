#pragma once

#include <array>
#include <istream>
#include <optional>
#include <zlib-ng.h>

struct zlib_streambuf : std::streambuf {
    explicit zlib_streambuf(std::streambuf* sbuf) : sbuf(sbuf) {
        stream.zalloc = nullptr;
        stream.zfree = nullptr;
        stream.opaque = nullptr;
        stream.next_in = nullptr;
        stream.avail_in = 0;
        stream.next_out = nullptr;
        stream.avail_out = 0;

        zng_inflateInit2(&stream, 15 + 32);
    }

    ~zlib_streambuf() override {
        zng_inflateEnd(&stream);
    }

    int_type underflow() override {
        if (gptr() && (gptr() < egptr())) {
            return traits_type::to_int_type(*gptr());
        }

        if (stream.next_in == nullptr) {
            stream.next_in = reinterpret_cast<uint8_t*>(in.data());
            stream.avail_in = sbuf->sgetn(in.data(), static_cast<std::streamsize>(in.size()));
        }

        if (stream.avail_in == 0) {
            setg(out.data(), out.data(), out.data());
            return traits_type::eof();
        }

        stream.avail_out = out.size();
        stream.next_out = reinterpret_cast<uint8_t*>(out.data());

        const auto ret = zng_inflate(&stream, Z_NO_FLUSH);
        if (ret != Z_STREAM_END && ret != Z_OK && ret != Z_BUF_ERROR) {
            setg(out.data(), out.data(), out.data());
            return traits_type::eof();
        }

        setg(out.data(), out.data(), out.data() + (out.size() - stream.avail_out));

        if (stream.avail_out != 0) {
            stream.next_in = nullptr;
        }

        return gptr() == egptr() ? traits_type::eof() : traits_type::to_int_type(*gptr());
    }

private:
    std::streambuf* sbuf;
    zng_stream stream{};
    std::array<char, 4096> in{};
    std::array<char, 8192> out{};
};

