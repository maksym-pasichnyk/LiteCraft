#include "CraftServer.hpp"
#include "world/ServerWorld.hpp"
#include "world/ChunkManager.hpp"

#include <functional>
#include <transform.hpp>

// todo: fix cleanup crash (wait for chunk tasks finished? check around chunks?)

CraftServer::CraftServer(int viewDistance, ResourceManager& resources) : resources(resources), viewDistance(viewDistance) {
    packets.bind<CHandshakePacket, &CraftServer::processHandshake>();
    packets.bind<CLoginStartPacket, &CraftServer::processLoginStart>();
    packets.bind<CEncryptionResponsePacket, &CraftServer::processEncryptionResponse>();
    packets.bind<PositionPacket, &CraftServer::processPlayerPosition>();
    packets.bind<CPlayerDiggingPacket, &CraftServer::processPlayerDigging>();
//    packets.bind<SChangeBlockPacket, &CraftServer::processChangeBlock>();

    listener = TcpListener::bind(SocketAddr::from(Ipv4Addr::localhost(), 0)).value();
    listener.set_blocking(false);

    world = std::make_unique<ServerWorld>(this, viewDistance);

    workers.emplace_back(&CraftServer::runLoop, this/*, stop_source.get_token()*/);
}

void CraftServer::runLoop(/*std::stop_token &&token*/) {
    while (/*!token.stop_requested()*/!request_stop) {
        while (auto connection = listener.accept()) {
            auto player = ecs.create();
            ecs.emplace<Transform>(player, glm::vec3{0, 0, 0}, glm::vec2{0, 0});
            ecs.emplace<Connection>(player, player, connection->first);
        }

        ecs.view<Connection>().each([this](auto& connection) {
            packets.handlePackets(*this, connection);
        });

        ecs.view<Connection>().each([this](auto& connection) {
            world->manager->tick(connection);
        });

//            const auto stride = (world->manager->viewDistance + 10 + 2) * 2 + 1;
//            if (world->manager->holders.size() > stride * stride) {
//                std::erase_if(world->manager->holders, [this](auto &it) {
//                    const auto pos = ChunkPos::from(it.first);
//                    const auto distance = ChunkManager::getChunkDistance(last_player_position, pos);
//                    if (distance > (world->manager->viewDistance + 10)) {
//                        for (size_t i = 0; i < 7; ++i) {
////                            if (it.second->chunks[i].has_value()) {
////                                fmt::print("{}\n", it.second->chunks[i]->get().use_count());
////                                fmt::print("{}\n", it.second->chunks[i]->get().use_count());
////                                fmt::print("\n");
////                            }
//                            if (it.second->chunks[i].has_value() && !it.second->chunks[i]->ready()) {
//                                return false;
//                            }
//                        }
//                        return true;
//                    }
//                    return false;
//                });
//            }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void CraftServer::processHandshake(Connection& connection, const CHandshakePacket& packet) {
}

void CraftServer::processLoginStart(Connection& connection, const CLoginStartPacket& packet) {
    connection.send(SEncryptionRequestPacket{});
}

void CraftServer::processEncryptionResponse(Connection& connection, const CEncryptionResponsePacket& packet) {
    connection.send(SEnableCompressionPacket{});
    connection.send(SLoginSuccessPacket{});

    const auto position = glm::vec3{0, 63, 10};
    const auto rotation = glm::vec2{};

    ecs.replace<Transform>(connection.player, position, rotation);
//    ecs.view<Connection>().each([&position](auto e, auto&& c) {
//        c.send(SSpawnPlayerPacket{position});
//    });
    connection.send(SJoinGamePacket{});
    connection.send(SPlayerPositionLookPacket{position, rotation});

    world->manager->setPlayerTracking(connection, ChunkPos::from(glm::ivec3(position)), true);
}

void CraftServer::processPlayerPosition(Connection& connection, const PositionPacket &packet) {
    const auto pos = ChunkPos::from(glm::ivec3(packet.pos));
    const auto last_pos = ChunkPos::from(glm::ivec3(ecs.get<Transform>(connection.player).position));

    if (pos != last_pos) {
        world->manager->updatePlayerPosition(connection, pos, last_pos);
    }

    ecs.get<Transform>(connection.player).position = packet.pos;
//    ecs.view<Connection>().each([&connection, &packet](auto e, auto&& c) {
//        if (c.player != conection.player) {
////            c.send(SSpawnPlayerPacket{position});
//        }
//    });
}

void CraftServer::processPlayerDigging(Connection& _, const CPlayerDiggingPacket& packet) {
    const auto pos = packet.pos;
    const auto [x, z] = ChunkPos::from(pos);

    auto chunk = world->getChunk(x, z);
    if (chunk != nullptr) {
        const auto new_block = Blocks::AIR->getDefaultState();
        const auto old_block = chunk->getData(pos);
        if (chunk->setData(pos, new_block)) {
            world->manager->lightManager->update(*world, pos.x, pos.y, pos.z, old_block, new_block);

            ecs.view<Connection>().each([&pos, &new_block](auto& connection) {
                connection.send(SChangeBlockPacket{
                    .pos = pos,
                    .block = new_block
                });
            });
        } else {
            ecs.view<Connection>().each([&pos, &old_block](auto& connection) {
                connection.send(SChangeBlockPacket{
                    .pos = pos,
                    .block = old_block
                });
            });
        }
    }
}

//void CraftServer::processChangeBlock(Connection & connection, const SChangeBlockPacket &packet) {
//    const auto pos = packet.pos;
//
//    const auto [chunk_x, chunk_z] = ChunkPos::from(pos);
//
//    auto chunk = world->getChunk(chunk_x, chunk_z);
//    if (chunk != nullptr) {
//        const auto new_block = packet.data;
//        const auto old_block = chunk->getData(pos);
//        if (chunk->setData(pos, new_block)) {
//            world->manager->lightManager->update(*world, pos.x, pos.y, pos.z, old_block, new_block);
//
//            connection.send(SChangeBlockPacket{
//                .pos = pos,
//                .data = new_block
//            });
//        } else {
//            connection.send(SChangeBlockPacket{
//                .pos = pos,
//                .data = old_block
//            });
//        }
//    }
//}
