#include "ImGuiTabbed.hpp"
#include <imgui-cocos.hpp>
#include "../../../mods/Mods.hpp"

namespace summit::ui::imgui::tabbed {
    bool wasMouseDown = false;
    std::string dragging = "";
    ImVec2 dragOffset = ImVec2(0, 0);
    ImVec2 windowPos = ImVec2(30, 30);
    bool firstDraw = true;
    
    void ImGuiTabbed::init() {
    }

    std::string ImGuiTabbed::getName() {
        return "ImGui Tabbed";
    }
    
    void ImGuiTabbed::open() {

    }

    void ImGuiTabbed::close() {
        
    }

    void ImGuiTabbed::draw() {
        if (!visible || getCurrentStyle() != this) return;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove;
        for (auto tab : summit::mods::getTabs()) {
            ImGui::Begin(tab.c_str(), nullptr, window_flags);
            ImGui::SetWindowFontScale(1.f/3 * summit::ui::getUIScale());
            ImGui::SetWindowSize(ImVec2(225.f * summit::ui::getUIScale(), 300.f * summit::ui::getUIScale()));
            if (firstDraw) {
                ImGui::SetWindowPos(windowPos);
                windowPos = ImVec2(windowPos.x + 235 * summit::ui::getUIScale(), windowPos.y);
            }
            auto drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(
                ImGui::GetWindowPos(),
                ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + ImGui::GetWindowHeight()),
                IM_COL32(47, 49, 66, 240)
            );
            drawList->AddRectFilled(
                ImGui::GetWindowPos(),
                ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 30 * summit::ui::getUIScale()),
                IM_COL32(0, 174, 255, 255)
            );
            if (ImGui::GetIO().MouseDown[0]) {
                if (wasMouseDown) {
                    if (dragging == tab) {
                        ImGui::SetWindowPos(ImVec2(ImGui::GetWindowPos().x + ImGui::GetIO().MouseDelta.x, ImGui::GetWindowPos().y + ImGui::GetIO().MouseDelta.y));
                    }
                } else {
                    if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 30 * summit::ui::getUIScale()))) {
                        dragging = tab;
                        dragOffset = ImVec2(ImGui::GetIO().MousePos.x - ImGui::GetWindowPos().x, ImGui::GetIO().MousePos.y - ImGui::GetWindowPos().y);
                    }
                }
            } else {
                wasMouseDown = false;
                dragging = "";
            }
            ImGui::SetWindowFontScale(.5f * summit::ui::getUIScale());
            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize(tab.c_str()).x / 2, 4 * summit::ui::getUIScale()));
            ImGui::Text("%s", tab.c_str());
            ImGui::SetCursorPos(ImVec2(8, 38 * summit::ui::getUIScale()));
            ImGui::SetWindowFontScale(1.f/3 * summit::ui::getUIScale());
            for (auto mod : summit::mods::getModsInTab(tab)) {
                mod.second->renderImGui();
            }
            ImGui::End();
        }
        firstDraw = false;
        if (ImGui::GetIO().MouseDown[0]) {
            wasMouseDown = true;
        }
    }
}