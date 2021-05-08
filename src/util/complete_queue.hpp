#pragma once

#include <mutex>
#include <queue>

template <typename T>
struct complete_queue {
    bool empty() const {
        std::unique_lock _{mutex};
        return queue.empty();
    }
    size_t size() const {
        std::unique_lock _{mutex};
        return queue.size();
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        std::unique_lock _{mutex};
        queue.emplace(std::forward<Args>(args)...);
    }

    std::optional<T> try_pop() {
        std::unique_lock _{mutex};
        if (queue.empty()) {
            return std::nullopt;
        }
        T res = std::move(queue.front());
        queue.pop();
        return std::move(res);
    }

    void clear() {
        std::unique_lock _{mutex};
        queue = {};
    }

    std::queue<T> release(std::queue<T> other) {
        std::unique_lock _{mutex};
        auto out = std::move(queue);
        queue = std::move(other);
        return std::move(out);
    }

    void swap(std::queue<T>& other) {
        std::unique_lock _{mutex};
        std::swap(queue, other);
    }

private:
    std::mutex mutex;
    std::queue<T> queue;
};