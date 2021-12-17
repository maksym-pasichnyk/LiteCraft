#pragma once

#include <mutex>
#include <vector>
#include <string>
#include <imgui.h>
#include <spdlog/fmt/chrono.h>
#include <spdlog/sinks/base_sink.h>

struct ImLogger : public spdlog::sinks::base_sink<std::mutex> {
    void Draw(const char *title) {
        ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::BeginChild("Scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        clipper.Begin(static_cast<int>(lines.size()));
        while (clipper.Step()) {
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++) {
                const auto line = std::string_view(lines[static_cast<size_t>(line_no)]);
                ImGui::TextUnformatted(line.data(), line.data() + line.size());
            }
        }
        clipper.End();
        ImGui::PopStyleVar();

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override {
        switch (msg.level) {
            case spdlog::level::level_enum::trace:
                lines.emplace_back(fmt::format("[{0:%H:%M:%S}] [trace] {1}", msg.time, msg.payload));
                break;
            case spdlog::level::level_enum::debug:
                lines.emplace_back(fmt::format("[{0:%H:%M:%S}] [debug] {1}", msg.time, msg.payload));
                break;
            case spdlog::level::level_enum::info:
                lines.emplace_back(fmt::format("[{0:%H:%M:%S}] [info] {1}", msg.time, msg.payload));
                break;
            case spdlog::level::level_enum::warn:
                lines.emplace_back(fmt::format("[{0:%H:%M:%S}] [warn] {1}", msg.time, msg.payload));
                break;
            case spdlog::level::level_enum::err:
                lines.emplace_back(fmt::format("[{0:%H:%M:%S}] [error] {1}", msg.time, msg.payload));
                break;
            case spdlog::level::level_enum::critical:
                lines.emplace_back(fmt::format("[{0:%H:%M:%S}] [critical] {1}", msg.time, msg.payload));
                break;
            default:
                break;
        }

        if (lines.size() > 100) {
            lines.erase(lines.begin());
        }
    }
    void flush_() override {}
    void set_pattern_(const std::string& pattern) override {}
    void set_formatter_(std::unique_ptr<spdlog::formatter> sink_formatter) override {}

private:
    ImGuiListClipper clipper;
    std::vector<std::string> lines;
};