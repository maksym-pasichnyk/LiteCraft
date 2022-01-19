#ifdef _WIN32
#include <WinSock2.h>
#endif

#include <spdlog/spdlog.h>
//#include <curl/curl.h>
#include <filesystem>
#include <physfs.h>
#include <fstream>

static auto write_to_file(char *ptr, size_t size, size_t nmemb, void *userdata) -> size_t {
    const auto nbytes = size * nmemb;
    auto file = static_cast<std::ofstream *>(userdata);
    file->write(ptr, static_cast<std::streamsize>(nbytes));
    return nbytes;
}

namespace {
    struct Bootstrap {
        Bootstrap() noexcept {
#ifdef _WIN32
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
            PHYSFS_init(nullptr);
            PHYSFS_mount(std::filesystem::current_path().string().c_str(), nullptr, 1);
        }

        ~Bootstrap() {
            PHYSFS_deinit();
//            curl_global_cleanup();

#ifdef _WIN32
            WSACleanup();
#endif
        }
    };

    Bootstrap bootstrap{};
}