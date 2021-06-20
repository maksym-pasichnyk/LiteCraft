#pragma once

#include <thread>

template<typename T>
struct ThreadLocal {
    ThreadLocal() {
        pthread_key_create(&key, [] (void* p) {
            delete static_cast<T*>(p);
        });
    }
    ~ThreadLocal() {
        pthread_key_delete(key);
    }
    bool has_value() const {
        return get() != nullptr;
    }

    T* get() const {
        return static_cast<T*>(pthread_getspecific(key));
    }

    void set(T* p) const {
        pthread_setspecific(key, p);
    }

private:
    pthread_key_t key;
};