#pragma once

#include "ChunkRenderData.hpp"
#include "ChunkRenderCache.hpp"
#include "util/generate_queue.hpp"
#include "util/complete_queue.hpp"
#include "client/world/ClientWorld.hpp"

#include <memory>
#include <ranges>
#include <thread>
#include <range/v3/algorithm.hpp>

struct ChunkRenderDispatcher {
    std::vector<std::thread> workers{};

    generate_queue<std::pair<ChunkRenderData*, std::unique_ptr<ChunkRenderCache>>> tasks;
    complete_queue<ChunkRenderData*> uploadTasks;

//    std::stop_source stop_source;
    bool request_stop = false;

    explicit ChunkRenderDispatcher() {
        workers.emplace_back(&ChunkRenderDispatcher::runLoop, this/*, stop_source.get_token()*/);
    }

    ~ChunkRenderDispatcher() {
        request_stop = true;
//        stop_source.request_stop();
        uploadTasks.clear();
        tasks.clear();
        ranges::for_each(workers, std::mem_fn(&std::thread::join));
        workers.clear();
    }

    void runChunkUploads() {
        while (auto data = uploadTasks.try_pop()) {
            (*data)->update();
        }
    }

    static void render(RenderBuffer& rb, ChunkRenderCache& blocks) {
        extern void renderBlocks(RenderBuffer& rb, ChunkRenderCache& blocks);

        renderBlocks(rb, blocks);
    }

    void runLoop(/*std::stop_token&& token*/) {
        while (/*!token.stop_requested()*/!request_stop) {
            while (auto task = tasks.try_pop()) {
                auto [data, cache] = std::move(*task);
                render(data->rb, *cache);
                uploadTasks.emplace(data);

                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }

    static auto createRenderCache(ClientWorld& world, glm::i32 chunk_x, glm::i32 chunk_z) -> std::unique_ptr<ChunkRenderCache> {
        auto cache = std::make_unique<ChunkRenderCache>(chunk_x, chunk_z);

        size_t i = 0;
        for (glm::i32 z = chunk_z - 1; z <= chunk_z + 1; z++) {
            for (glm::i32 x = chunk_x - 1; x <= chunk_x + 1; x++) {
                auto chunk = world.getChunk(x, z);
                if (chunk == nullptr) {
                    return nullptr;
                }
                cache->chunks[i++] = chunk;
            }
        }

        return cache;
    }

    void rebuild(ClientWorld& world, ChunkRenderData& renderData, glm::i32 chunk_x, glm::i32 chunk_z, bool immediate) {
        if (auto cache = createRenderCache(world, chunk_x, chunk_z)) {
            if (immediate) {
                render(renderData.rb, *cache);
                renderData.update();
            } else {
                tasks.emplace(&renderData, std::move(cache));
            }
        }
    }
};
