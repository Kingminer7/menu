#include "ImGuiTabbed.hpp"
#include "../../../mods/Mods.hpp"

namespace summit::ui::imgui::tabbed {
    
    void ImGuiTabbed::init() {
    }

    std::string ImGuiTabbed::getName() {
        return "ImGui Tabbed";
    }
    
    void ImGuiTabbed::open() {
        visible = true;
    }

    void ImGuiTabbed::close() {
        visible = false;
    }

    void ImGuiTabbed::toggle() {
        if (visible) close();
        else open();
    }

    void ImGuiTabbed::draw() {
        if (!visible || getCurrentStyle() != this) return;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove;
        for (auto tab : summit::mods::getTabs()) {
            ImGui::Begin(tab.c_str(), nullptr, window_flags);
            ImGui::GetIO().FontGlobalScale = 1.f/3 * summit::ui::getUIScale();
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
                ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 25 * summit::ui::getUIScale()),
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
            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize(tab.c_str()).x / 2, 4 * summit::ui::getUIScale()));
            ImGui::Text("%s", tab.c_str());
            ImGui::SetCursorPos(ImVec2(8, 33 * summit::ui::getUIScale()));
            // for (auto mod : summit::mods::getModsInTab(tab)) {
            //     mod.second->renderImGui();
            // }
            // for (auto widget : summit::ui::getWidgets(tab)) {
            //   widget.second->imRender();
            // }
            ImGui::End();
        }
        firstDraw = false;
        if (ImGui::GetIO().MouseDown[0]) {
            wasMouseDown = true;
        }
    }
}
