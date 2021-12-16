#pragma once

#include <thread>

#include <spdlog/spdlog.h>

#ifdef _WIN32
#include <windows.h>
#endif

template<typename T>
struct ThreadLocal {
    ThreadLocal() {
#ifdef _WIN32
        key = TlsAlloc();
#else
        pthread_key_create(&key, [] (void* p) {
            spdlog::info("Delete: {}", p);
            delete static_cast<T*>(p);
        });
#endif
    }
    ~ThreadLocal() {
#ifdef _WIN32
        TlsFree(key);
#else
        pthread_key_delete(key);
#endif
    }

    auto has_value() const -> bool {
        return get() != nullptr;
    }

    auto get() const -> T* {
#ifdef _WIN32
        return static_cast<T*>(TlsGetValue(key));
#else
        return static_cast<T*>(pthread_getspecific(key));
#endif
    }

    void set(T* p) const {
#ifdef _WIN32
        TlsSetValue(key, p);
#else
        pthread_setspecific(key, p);
#endif
    }

private:
#ifdef _WIN32
    DWORD key{};
#else
    pthread_key_t key;
#endif
};