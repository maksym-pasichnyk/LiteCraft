#pragma once

#include <thread>
#include <windows.h>

template<typename T>
struct ThreadLocal {
    ThreadLocal() {
        key = TlsAlloc();
//        pthread_key_create(&key, [] (void* p) {
//            delete static_cast<T*>(p);
//        });
    }
    ~ThreadLocal() {
        TlsFree(key);
//        pthread_key_delete(key);
    }
    auto has_value() const -> bool {
        return get() != nullptr;
    }

    auto get() const -> T* {
        return static_cast<T*>(TlsGetValue(key));
//        return static_cast<T*>(pthread_getspecific(key));
    }

    void set(T* p) const {
        TlsSetValue(key, p);
//        pthread_setspecific(key, p);
    }

private:
    DWORD key{};
//    pthread_key_t key;
};