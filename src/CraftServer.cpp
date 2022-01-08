#include "CraftServer.hpp"
#include "world/ServerWorld.hpp"
#include "world/ChunkManager.hpp"

#include <Json.hpp>
#include <functional>
#include <transform.hpp>

// todo: fix cleanup crash (wait for chunk tasks finished? check around chunks?)

CraftServer::CraftServer(int viewDistance) : viewDistance(viewDistance) {
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
            handler.handlePackets(*this, connection);
        });

        while (auto pos = world->manager->complete.try_pop()) {
            const auto [x, z] = *pos;
            auto chunk = world->manager->getChunk(x, z).get();

            ecs.view<Connection>().each([o = chunk->to_json(), x = x, z = z](auto& connection) {
                connection.send(SLoadChunkPacket{o, x, z});
            });
//            world->manager->complete.emplace(*pos);
            break;
        }

//        ecs.view<Connection>().each([this](auto& connection) {
//            world->manager->tick(connection);
//        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void CraftServer::onPacket(Connection& connection, const CHandshakePacket& packet) {
}

void CraftServer::onPacket(Connection& connection, const CLoginStartPacket& packet) {
    connection.send(SEncryptionRequestPacket{});
}

void CraftServer::onPacket(Connection& connection, const CEncryptionResponsePacket& packet) {
    connection.send(SEnableCompressionPacket{});
    connection.send(SLoginSuccessPacket{});

    const auto position = glm::vec3{0, 63, 10};
    const auto rotation = glm::vec2{};

    ecs.replace<Transform>(connection.player, position, rotation);
    ecs.view<Connection>().each([&position, player = connection.player](auto e, auto&& c) {
        if (e != player) {
            c.send(SSpawnPlayerPacket{position});
        }
    });
    connection.send(SJoinGamePacket{});
    connection.send(SPlayerPositionLookPacket{position, rotation});

    world->manager->setPlayerTracking(connection, ChunkPos::from(glm::ivec3(position)), true);
}

void CraftServer::onPacket(Connection& connection, const PositionPacket &packet) {
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

void CraftServer::onPacket(Connection& _, const CPlayerDiggingPacket& packet) {
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
