#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>
#include <GL/gl3w.h>

#include <imgui.h>
#include <imgui_internal.h>

#include <utils/matches.hpp>
#include <core/Device.hpp>
#include <core/Event.hpp>
#include <core/Mesh.hpp>

#include <array>

struct ImGuiLayer {
    struct ImGuiContextDeleter {
        void operator()(ImGuiContext* ptr) {
            ImGui::DestroyContext(ptr);
        }
    };

    std::unique_ptr<ImGuiContext, ImGuiContextDeleter> ctx;
    std::unique_ptr<Mesh> mesh;

//    GLuint GlVersion;
    GLuint FontTexture;
    GLuint ShaderHandle;
    GLint AttribLocationTex;
    GLint AttribLocationProjMtx;

    GLenum last_active_texture;
    GLuint last_program;
    GLuint last_texture;
    GLuint last_sampler;
    GLuint last_array_buffer;
    GLuint last_vertex_array_object;
    GLint last_polygon_mode[2];
    GLint last_viewport[4];
    GLint last_scissor_box[4];
    GLenum last_blend_src_rgb;
    GLenum last_blend_dst_rgb;
    GLenum last_blend_src_alpha;
    GLenum last_blend_dst_alpha;
    GLenum last_blend_equation_rgb;
    GLenum last_blend_equation_alpha;
    GLboolean last_enable_blend;
    GLboolean last_enable_cull_face;
    GLboolean last_enable_depth_test;
    GLboolean last_enable_stencil_test;
    GLboolean last_enable_scissor_test;
    GLboolean last_enable_primitive_restart;

    ImGuiLayer(Window& window, Device& device) {
        const auto [width, height] = window.getWindowSize();

        IMGUI_CHECKVERSION();
        ctx.reset(ImGui::CreateContext());

        resize(width, height);

        auto colors = std::span(ctx->Style.Colors);

        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab]                    = ImLerp(colors[ImGuiCol_Header],       colors[ImGuiCol_TitleBgActive], 0.80f);
        colors[ImGuiCol_TabHovered]             = colors[ImGuiCol_HeaderHovered];
        colors[ImGuiCol_TabActive]              = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
        colors[ImGuiCol_TabUnfocused]           = ImLerp(colors[ImGuiCol_Tab],          colors[ImGuiCol_TitleBg], 0.80f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImLerp(colors[ImGuiCol_TabActive],    colors[ImGuiCol_TitleBg], 0.40f);
        colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        auto& io = ctx->IO;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        Init(device);
        CreateDeviceObjects(device);
    }

    ~ImGuiLayer() {
        Shutdown();
    }

    ImGuiIO& begin() {
        ImGui::SetCurrentContext(ctx.get());
        ImGui::NewFrame();
        return ctx->IO;
    }

    void end() {
        ImGui::Render();
        ImGui::SetCurrentContext(nullptr);
    }

    void flush() {
        auto viewport = ctx->Viewports[0];
        if (viewport->DrawDataP.Valid) {
            RenderDrawData(viewport->DrawDataP);
        }
    }

//    void update(float dt) {
//        auto& io = ctx->IO;
//        io.DeltaTime = dt;
//
//        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
//        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
//        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
//        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
//    }
//
//    void resize(int width, int height) {
//        auto& io = ctx->IO;
//        io.DisplaySize.x = static_cast<float>(width);
//        io.DisplaySize.y = static_cast<float>(height);
//        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
//    }
//
//    void keyEvent(int key, int action) {
//        auto& io = ctx->IO;
//
//        if (action == GLFW_PRESS) {
//            io.KeysDown[key] = true;
//        } else if (action == GLFW_RELEASE) {
//            io.KeysDown[key] = false;
//        }
//    }
//
//    void mouseMoveEvent(float x, float y) {
//        auto& io = ctx->IO;
//        io.MousePos = ImVec2(x, y);
//    }
//
//    void mouseButtonEvent(int button, int action) {
//        auto& io = ctx->IO;
//
//        if (action == GLFW_PRESS) {
//            io.MouseDown[button] = true;
//        } else if (action == GLFW_RELEASE) {
//            io.MouseDown[button] = false;
//        }
//    }

private:
    void Init(Device& device) {
        ImGuiIO& io = ctx->IO;

        io.BackendRendererUserData = nullptr;
        io.BackendRendererName = "OpenGL";

//        GLint major = 0;
//        GLint minor = 0;
//        glGetIntegerv(GL_MAJOR_VERSION, &major);
//        glGetIntegerv(GL_MINOR_VERSION, &minor);
//        if (major == 0 && minor == 0) {
//            sscanf(reinterpret_cast<const char *const>(glGetString(GL_VERSION)), "%d.%d", &major, &minor);
//        }
//        GlVersion = static_cast<GLuint>(major * 100 + minor * 10);
    }

    void Shutdown() {
        auto &io = ctx->IO;

        if (ShaderHandle != 0) {
            glDeleteProgram(ShaderHandle);
            ShaderHandle = 0;
        }

        if (FontTexture != 0) {
            glDeleteTextures(1, &FontTexture);
            io.Fonts->SetTexID(nullptr);
            FontTexture = 0;
        }
        io.BackendRendererName = nullptr;
        io.BackendRendererUserData = nullptr;
    }

    void BackupRenderState() {
        glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint *) &last_active_texture);
        glActiveTexture(GL_TEXTURE0);
        glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *) &last_program);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *) &last_texture);
        glGetIntegerv(GL_SAMPLER_BINDING, (GLint*)&last_sampler);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint *) &last_array_buffer);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&last_vertex_array_object);
        glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
        glGetIntegerv(GL_VIEWPORT, last_viewport);
        glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
        glGetIntegerv(GL_BLEND_SRC_RGB, (GLint *) &last_blend_src_rgb);
        glGetIntegerv(GL_BLEND_DST_RGB, (GLint *) &last_blend_dst_rgb);
        glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint *) &last_blend_src_alpha);
        glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint *) &last_blend_dst_alpha);
        glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint *) &last_blend_equation_rgb);
        glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint *) &last_blend_equation_alpha);
        last_enable_blend = glIsEnabled(GL_BLEND);
        last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
        last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
        last_enable_stencil_test = glIsEnabled(GL_STENCIL_TEST);
        last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);
        last_enable_primitive_restart = /*(GlVersion >= 310) ?*/ glIsEnabled(GL_PRIMITIVE_RESTART)/* : GL_FALSE*/;
    }

    void RestoreRenderState() {
        glUseProgram(last_program);
        glBindTexture(GL_TEXTURE_2D, last_texture);
        glBindSampler(0, last_sampler);
        glActiveTexture(last_active_texture);
        glBindVertexArray(last_vertex_array_object);
        glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
        glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
        glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
        if (last_enable_blend) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
        if (last_enable_cull_face) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }
        if (last_enable_depth_test) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
        if (last_enable_stencil_test) {
            glEnable(GL_STENCIL_TEST);
        } else {
            glDisable(GL_STENCIL_TEST);
        }
        if (last_enable_scissor_test) {
            glEnable(GL_SCISSOR_TEST);
        } else {
            glDisable(GL_SCISSOR_TEST);
        }
        if (last_enable_primitive_restart) {
            glEnable(GL_PRIMITIVE_RESTART);
        } else {
            glDisable(GL_PRIMITIVE_RESTART);
        }
        glPolygonMode(GL_FRONT_AND_BACK, (GLenum) last_polygon_mode[0]);
        glViewport(last_viewport[0], last_viewport[1], (GLsizei) last_viewport[2], (GLsizei) last_viewport[3]);
        glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei) last_scissor_box[2], (GLsizei) last_scissor_box[3]);
    }

    void RenderDrawData(ImDrawData& data) {
        const auto fb_width = static_cast<int>(data.DisplaySize.x * data.FramebufferScale.x);
        const auto fb_height = static_cast<int>(data.DisplaySize.y * data.FramebufferScale.y);
        if (fb_width <= 0 || fb_height <= 0) {
            return;
        }

        BackupRenderState();
        SetupRenderState(data, fb_width, fb_height, mesh->vao);

        const auto clip_off = data.DisplayPos;         // (0,0) unless using multi-viewports
        const auto clip_scale = data.FramebufferScale; // (1,1) unless using retina display which are often (2,2)

        for (const auto& cmd_list : std::span(data.CmdLists, data.CmdListsCount)) {
            mesh->SetVertices(std::span(cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size));
            mesh->SetIndices(std::span(cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size));

            for (const auto& cmd : std::span(cmd_list->CmdBuffer.Data, cmd_list->CmdBuffer.Size)) {
                if (cmd.UserCallback != nullptr) {
                    if (cmd.UserCallback == ImDrawCallback_ResetRenderState) {
                        SetupRenderState(data, fb_width, fb_height, mesh->vao);
                    } else {
                        cmd.UserCallback(cmd_list, &cmd);
                    }
                } else {
                    const glm::vec2 clip_min{
                        (cmd.ClipRect.x - clip_off.x) * clip_scale.x,
                        (cmd.ClipRect.y - clip_off.y) * clip_scale.y
                    };

                    const glm::vec2 clip_max{
                        (cmd.ClipRect.z - clip_off.x) * clip_scale.x,
                        (cmd.ClipRect.w - clip_off.y) * clip_scale.y
                    };

                    if (clip_min.x < static_cast<float>(fb_width) && clip_min.y < static_cast<float>(fb_height) && clip_max.x >= 0.0f && clip_max.y >= 0.0f) {
                        const auto clip_size = glm::ivec2(clip_max - clip_min);

                        glScissor(
                            static_cast<int>(clip_min.x),
                            static_cast<int>(static_cast<float>(fb_height) - clip_max.y),
                            clip_size.x,
                            clip_size.y
                        );

                        glBindTextureUnit(0, (GLuint) (intptr_t) cmd.GetTexID());

                        const auto ElemCount = static_cast<GLsizei>(cmd.ElemCount);
                        const auto IndexType = sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
                        const auto IdxOffset = static_cast<std::byte*>(nullptr) + cmd.IdxOffset * sizeof(ImDrawIdx);

                        glDrawElements(GL_TRIANGLES, ElemCount, IndexType, IdxOffset);
                    }
                }
            }
        }

        RestoreRenderState();
    }

    bool CreateFontsTexture() {
        auto Fonts = ctx->IO.Fonts;

        unsigned char* pixels;
        int width, height;
        Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

        glCreateTextures(GL_TEXTURE_2D, 1, &FontTexture);
        glTextureStorage2D(FontTexture, 1, GL_RGBA8, width, height);
        glTextureParameteri(FontTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(FontTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//#ifdef GL_UNPACK_ROW_LENGTH
//        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
//#endif
        glTextureSubImage2D(FontTexture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        Fonts->SetTexID((ImTextureID)(intptr_t)FontTexture);
        return true;
    }

    bool CreateDeviceObjects(Device& device) {
        using namespace std::string_view_literals;

        const auto vertex_shader = R"(
            #version 450

            out gl_PerVertex {
                vec4 gl_Position;
            };

            in vec2 Position;
            in vec2 UV;
            in vec4 Color;

            uniform mat4 ProjMtx;

            out struct {
                vec2 UV;
                vec4 Color;
            } Frag;

            void main() {
                gl_Position = ProjMtx * vec4(Position, 0, 1);

                Frag.UV = UV;
                Frag.Color = Color;
            }
        )"sv;

        const auto fragment_shader = R"(
            #version 450

            layout (location = 0) out vec4 Out_Color;

            uniform sampler2D Texture;

            in struct {
                vec2 UV;
                vec4 Color;
            } Frag;

            void main() {
                Out_Color = Frag.Color * texture(Texture, Frag.UV);
            }
        )"sv;

        ShaderHandle          = device.createShader(vertex_shader, fragment_shader);
        AttribLocationTex     = glGetUniformLocation(ShaderHandle, "Texture");
        AttribLocationProjMtx = glGetUniformLocation(ShaderHandle, "ProjMtx");

        const auto AttribLocationVtxPos   = static_cast<GLuint>(glGetAttribLocation(ShaderHandle, "Position"));
        const auto AttribLocationVtxUV    = static_cast<GLuint>(glGetAttribLocation(ShaderHandle, "UV"));
        const auto AttribLocationVtxColor = static_cast<GLuint>(glGetAttribLocation(ShaderHandle, "Color"));

        const std::array attributes {
            VertexArrayAttrib{AttribLocationVtxPos,   2, GL_FLOAT,         GL_FALSE, static_cast<GLuint>(offsetof(ImDrawVert, pos))},
            VertexArrayAttrib{AttribLocationVtxUV,    2, GL_FLOAT,         GL_FALSE, static_cast<GLuint>(offsetof(ImDrawVert, uv))},
            VertexArrayAttrib{AttribLocationVtxColor, 4, GL_UNSIGNED_BYTE, GL_TRUE,  static_cast<GLuint>(offsetof(ImDrawVert, col))},
        };

        const std::array bindings {
            VertexArrayBinding{AttribLocationVtxPos,   0},
            VertexArrayBinding{AttribLocationVtxUV,    0},
            VertexArrayBinding{AttribLocationVtxColor, 0}
        };

        mesh = std::make_unique<Mesh>(attributes, bindings, sizeof(ImDrawVert), GL_STREAM_DRAW);

        CreateFontsTexture();
        return true;
    }

    void SetupRenderState(ImDrawData& data, int fb_width, int fb_height, GLuint vertex_array_object) {
        // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
        glEnable(GL_SCISSOR_TEST);
        glDisable(GL_PRIMITIVE_RESTART);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        GLenum current_clip_origin = 0;
        glGetIntegerv(GL_CLIP_ORIGIN, (GLint *) &current_clip_origin);
        const auto clip_origin_lower_left = current_clip_origin != GL_UPPER_LEFT;

        glViewport(0, 0, static_cast<GLsizei>(fb_width), static_cast<GLsizei>(fb_height));
        const auto L = data.DisplayPos.x;
        const auto R = data.DisplayPos.x + data.DisplaySize.x;
        const auto T = data.DisplayPos.y;
        const auto B = data.DisplayPos.y + data.DisplaySize.y;
        const auto projection = glm::ortho(L, R, clip_origin_lower_left ? B : T, clip_origin_lower_left ? T : B, -1.0f, 1.0f);
        glUseProgram(ShaderHandle);
        glUniform1i(AttribLocationTex, 0);
        glUniformMatrix4fv(AttribLocationProjMtx, 1, GL_FALSE, glm::value_ptr(projection));
        glBindSampler(0, 0);
        glBindVertexArray(vertex_array_object);
    }
};