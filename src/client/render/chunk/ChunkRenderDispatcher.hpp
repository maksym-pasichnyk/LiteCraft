#pragma once

#include "ChunkRenderData.hpp"
#include "ChunkRenderCache.hpp"
#include "client/world/ClientWorld.hpp"

#include <block/Block.hpp>
#include <block/BlockStates.hpp>

#include <memory>
#include <ranges>
#include <thread>
#include <range/v3/algorithm.hpp>
#include <util/generate_queue.hpp>
#include <util/complete_queue.hpp>

struct ChunkRenderDispatcher {
    struct ChunkRenderTask {
        ChunkRenderData* data;
        std::unique_ptr<ChunkRenderCache> cache;
    };

    std::vector<std::thread> workers{};

    generate_queue<ChunkRenderTask> tasks;
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

    void runLoop(/*std::stop_token&& token*/) {
        while (/*!token.stop_requested()*/!request_stop) {
            while (auto task = tasks.try_pop()) {
                render(task->data, *task->cache);
                uploadTasks.emplace(task->data);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

    static void tessellate(RenderLayerBuilder& builder, const ModelFace& quad, const glm::ivec3& pos) {
        builder.quad();

        const auto texture = TextureManager::instance().get_texture(quad.texture);
        for (auto&& vertex : quad.vertices) {
            const auto [x, y, z] = vertex.pos + glm::vec3(pos);
            const auto u = texture.getInterpolatedU(vertex.uv.x);
            const auto v = texture.getInterpolatedV(vertex.uv.y);
            builder.vertex(x, y, z, u, v, 0xFF, 0xFF, 0xFF, 0xFFFF, 1.0f);
        }
    }

    static void tessellate(RenderLayerBuilder& builder, const glm::ivec3& pos, const Model& model) {
        for (auto&& [face, quads] : model.faces) {
            // todo: check if side culled

            for (auto&& quad : quads) {
                tessellate(builder, quad, pos);
            }
        }

        for (auto&& quad : model.quads) {
            tessellate(builder, quad, pos);
        }
    }

    static void render(ChunkRenderData* data, ChunkRenderCache& blocks) {
        data->rb.clear();

        const auto start = blocks.coords.getStartBlock();

        for (int x = start.x; x < start.x + 16; x++) {
            for (int z = start.z; z < start.z + 16; z++) {
                for (int y = 0; y < 256; y++) {
                    const auto pos = glm::ivec3{x, y, z};
                    const auto state = blocks.getData(pos);
                    const auto block = state.getBlock();

                    auto builder = data->rb.get(block->getRenderType());

                    switch (block->getRenderShape()) {
                        case BlockRenderShape::MODEL:
                            tessellate(builder, pos, *BlockStates::get(block)->get_model(state));
                            break;
                        case BlockRenderShape::ENTITY:
                            data->tmpTileEntities.emplace_back(TileEntity{.pos = pos, .state = state});
                            break;
                        case BlockRenderShape::INVISIBLE:
                            break;
                    }
//                renderLiquid(pos, block, rb, blocks);
                }
            }
        }
    }

    void rebuild(ClientWorld& world, ChunkRenderData& data, glm::i32 x, glm::i32 z, bool immediate) {
        if (auto cache = createRenderCache(world, x, z)) {
            if (immediate) {
                render(&data, *cache);
                data.update();
            } else {
                tasks.emplace(ChunkRenderTask{&data, std::move(cache)});
            }
        }
    }
};
