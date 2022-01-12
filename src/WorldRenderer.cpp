#include "WorldRenderer.hpp"

#include <CommandBuffer.hpp>
#include <GraphicsBuffer.hpp>

#include <Time.hpp>
#include <TextureAtlas.hpp>
#include <block/AbstractBlock.hpp>

WorldRenderer::WorldRenderer(int renderDistance) : frustum(renderDistance) {
    _createUniforms();

//    entityMaterial = Material::LoadFromResources("craft:materials/entity.material");
    opaqueMaterial = Material::LoadFromResources("craft:materials/opaque.material");
    cutoutMaterial = Material::LoadFromResources("craft:materials/cutout.material");
    transparentMaterial = Material::LoadFromResources("craft:materials/transparent.material");

    opaqueMaterial.SetTexture(1, TextureManager::instance().atlas);
    opaqueMaterial.SetConstantBuffer(0, uniforms[0]);

    cutoutMaterial.SetTexture(1, TextureManager::instance().atlas);
    cutoutMaterial.SetConstantBuffer(0, uniforms[0]);

    transparentMaterial.SetTexture(1, TextureManager::instance().atlas);
    transparentMaterial.SetConstantBuffer(0, uniforms[0]);
}

void WorldRenderer::tick() {
    TextureManager::instance().tick(Time::getDeltaTime());
}

void WorldRenderer::drawTerrain(CommandBuffer cmd) {
    dispatcher.runChunkUploads();

    _drawChunks(cmd, opaqueMaterial, RenderLayer::Opaque);
    _drawChunks(cmd, cutoutMaterial, RenderLayer::Cutout);
    _drawChunks(cmd, transparentMaterial, RenderLayer::Transparent);
}
void WorldRenderer::_drawChunks(CommandBuffer cmd, const Material &material, RenderLayer layer) {
    for (auto chunk : chunkToRenders) {
        if (chunk->mesh.getIndexCount() == 0) {
            continue;
        }
        cmd.drawMesh(chunk->mesh, material, static_cast<int>(layer));
    }
}
void WorldRenderer::_createUniforms() {
    // todo: move to Blaze
    uniforms.emplace_back(GraphicsBuffer::Target::Constant, sizeof(CameraConstants));
}