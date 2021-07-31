#ifdef _WIN32
#include <WinSock2.h>
#endif

#include <curl/curl.h>
#include <filesystem>
#include <physfs.h>
#include <fstream>

namespace {
    struct Bootstrap {
        Bootstrap() noexcept {
#ifdef _WIN32
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

            PHYSFS_init(nullptr);
            curl_global_init(CURL_GLOBAL_DEFAULT);

//            if (!std::filesystem::exists("client-extra.zip")) {
//                std::ofstream file{"client-extra.zip", std::ios::binary};
//                auto curl = curl_easy_init();
//                curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
//                curl_easy_setopt(curl, CURLOPT_URL, "https://codeload.github.com/InventivetalentDev/minecraft-assets/legacy.zip/refs/heads/1.17.1");
//                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char *ptr, size_t size, size_t nmemb, void *userdata) -> size_t {
//                    const auto nbytes = size * nmemb;
//                    auto file = static_cast<std::ofstream *>(userdata);
//                    file->write(ptr, static_cast<std::streamsize>(nbytes));
//                    return nbytes;
//                });
//                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
//                const auto ret = curl_easy_perform(curl);
//                curl_easy_cleanup(curl);
//            }

//            PHYSFS_mount("client-extra.zip", "/", 1);
//            PHYSFS_setRoot("client-extra.zip", "/InventivetalentDev-minecraft-assets-cf2c0bd");
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