#pragma once

#include "streambuf.hpp"
#include <istream>

struct zlib_istream : std::istream {
    explicit zlib_istream(std::istream& io) : std::istream(&zbuf), zbuf(io.rdbuf()) {}

private:
    zlib_streambuf zbuf;
};