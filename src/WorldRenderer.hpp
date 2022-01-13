#pragma once

#include <vector>
#include "camera.hpp"
#include <glm/glm.hpp>
#include <Material.hpp>
#include <client/render/ViewFrustum.hpp>
#include <client/render/chunk/ChunkRenderDispatcher.hpp>

enum class RenderType;

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
    Mesh mesh{};
    Camera camera{};
    Material entityMaterial;
    Material opaqueMaterial;
    Material cutoutMaterial;
    Material transparentMaterial;

    ViewFrustum frustum;
    ChunkRenderDispatcher dispatcher{};
    std::vector<GraphicsBuffer> uniforms{};
    std::vector<ChunkRenderData*> chunkToRenders{};

    explicit WorldRenderer(int renderDistance);

    void tick();
    void drawTerrain(CommandBuffer cmd);

private:
    void _drawChunks(CommandBuffer cmd, const Material& material, RenderType renderType);
    void _createUniforms();
};
