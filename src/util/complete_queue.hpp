#pragma once

#include <mutex>
#include <queue>
#include <tl/optional.hpp>

template <typename T>
struct complete_queue {
    bool empty() const {
        std::lock_guard _{mutex};
        return queue.empty();
    }
    size_t size() /*const*/ {
        std::lock_guard _{mutex};
        return queue.size();
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        std::lock_guard _{mutex};
        queue.emplace(std::forward<Args>(args)...);
    }

    tl::optional<T> try_pop() {
        std::lock_guard _{mutex};
        if (queue.empty()) {
            return tl::nullopt;
        }
        T res = std::move(queue.front());
        queue.pop();
        return std::move(res);
    }

    void clear() {
        std::lock_guard _{mutex};
        queue = {};
    }

    std::queue<T> release(std::queue<T> other) {
        std::lock_guard _{mutex};
        auto out = std::move(queue);
        queue = std::move(other);
        return std::move(out);
    }

    void swap(std::queue<T>& other) {
        std::lock_guard _{mutex};
        std::swap(queue, other);
    }

private:
    std::mutex mutex;
    std::queue<T> queue;
};