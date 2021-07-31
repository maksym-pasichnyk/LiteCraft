#ifdef _WIN32
#include <WinSock2.h>
#endif

#include <fmt/format.h>
#include <curl/curl.h>
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
            curl_global_init(CURL_GLOBAL_DEFAULT);

            PHYSFS_mount("Vanilla_Behavior_Pack_1.16.220.zip", "/behavior_packs/vanilla", 1);
            PHYSFS_mount("Vanilla_Resource_Pack_1.16.220.zip", "/resource_packs/vanilla", 1);
        }

        ~Bootstrap() {
            PHYSFS_deinit();
            curl_global_cleanup();

#ifdef _WIN32
            WSACleanup();
#endif
        }
    };

    Bootstrap bootstrap{};
}