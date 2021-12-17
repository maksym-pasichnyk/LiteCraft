#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Material.hpp>
#include <client/render/chunk/ChunkRenderDispatcher.hpp>

enum class RenderLayer;

struct Material;
struct CommandBuffer;
struct GraphicsBuffer;
struct ChunkRenderData;
struct ChunkRenderDispatcher;

struct CameraConstants {
    glm::mat4 transform;
    glm::vec4 position;
};

struct WorldRenderer {
    Material entityMaterial;
    Material opaqueMaterial;
    Material cutoutMaterial;
    Material transparentMaterial;

    ChunkRenderDispatcher dispatcher{};
    std::vector<GraphicsBuffer> uniforms{};
    std::vector<ChunkRenderData*> chunkToRenders{};

    WorldRenderer();
    void drawTerrain(CommandBuffer cmd);

private:
    void _drawChunks(CommandBuffer cmd, const Material& material, RenderLayer layer);
    void _createUniforms();
};
