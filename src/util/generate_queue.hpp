#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
struct generate_queue {
    void clear() {
        std::lock_guard _{mutex};
        queue = {};
    }
    bool empty() const {
        std::lock_guard _{mutex};
        return queue.empty();
    }
    size_t size() const {
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

private:
    std::mutex mutex;
    std::queue<T> queue;
};