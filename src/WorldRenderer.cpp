#include "WorldRenderer.hpp"
#include "client/render/model/Models.hpp"

#include <CommandBuffer.hpp>
#include <GraphicsBuffer.hpp>

#include <Time.hpp>
#include <TextureAtlas.hpp>
#include <block/AbstractBlock.hpp>

WorldRenderer::WorldRenderer(int renderDistance) : frustum(renderDistance) {
    _createUniforms();

    mesh.setSubmeshCount(1);
    mesh.setSubmesh(0, SubMesh{0, 0});

    entityMaterial = Material::LoadFromResources("craft:materials/entity.material");
    opaqueMaterial = Material::LoadFromResources("craft:materials/opaque.material");
    cutoutMaterial = Material::LoadFromResources("craft:materials/cutout.material");
    transparentMaterial = Material::LoadFromResources("craft:materials/transparent.material");

    entityMaterial.SetConstantBuffer(0, uniforms[0]);

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

    auto builder = ModelVertexBuilder{};
    for (auto chunk : chunkToRenders) {
        for (auto entity : chunk->tileEntities) {
            ModelComponent::render(builder, *Models::models.get("geometry.humanoid").value(), glm::vec3(entity.pos));
        }
    }
    if (!builder.indices.empty()) {
        mesh.setIndexBufferParams(builder.indices.size(), sizeof(glm::u32));
        mesh.setIndexBufferData(std::as_bytes(std::span(builder.indices)), 0);

        mesh.setVertexBufferParams(builder.vertices.size(), sizeof(BlockVertex));
        mesh.setVertexBufferData(std::as_bytes(std::span(builder.vertices)), 0);

        mesh.setSubmesh(0, SubMesh{
            .indexCount = static_cast<glm::i32>(builder.indices.size()),
            .indexOffset = 0
        });
    }
    cmd.drawMesh(mesh, entityMaterial, 0);

    _drawChunks(cmd, opaqueMaterial, RenderType::Opaque);
    _drawChunks(cmd, cutoutMaterial, RenderType::Cutout);
    _drawChunks(cmd, transparentMaterial, RenderType::Transparent);
}

void WorldRenderer::_drawChunks(CommandBuffer cmd, const Material &material, RenderType renderType) {
    for (auto chunk : chunkToRenders) {
        if (chunk->mesh.getIndexCount() == 0) {
            continue;
        }
        cmd.drawMesh(chunk->mesh, material, static_cast<int>(renderType));
    }
}
void WorldRenderer::_createUniforms() {
    // todo: move to Blaze
    uniforms.emplace_back(GraphicsBuffer::Target::Constant, sizeof(CameraConstants));
}