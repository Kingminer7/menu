#include <imgui-cocos.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include "UI.hpp"
#include "../../Summit.hpp"
#include "../../mods/Mods.hpp"

namespace summit::ui::imgui {
    UI* UI::instance = nullptr;
    static int scale = 1;
    UI* UI::get() {
        if (!instance) {
            instance = new UI();
        }
        return instance;
    }

    bool wasMouseDown = false;
    std::string dragging = "";
    ImVec2 dragOffset = ImVec2(0, 0);
    ImVec2 windowPos = ImVec2(30, 30);
    bool firstDraw = true;

    void UI::draw() {
        if (!summit::Config::getVisibility()) return;
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoMove;
        for (auto tab : summit::mods::getTabs()) {
            ImGui::Begin(tab.c_str(), nullptr, window_flags);
            ImGui::SetWindowFontScale(1.5f);
            ImGui::SetWindowSize(ImVec2(225, 300));
            if (firstDraw) {
                ImGui::SetWindowPos(windowPos);
                windowPos = ImVec2(windowPos.x + 235, windowPos.y);
            }
            auto drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(
                ImGui::GetWindowPos(),
                ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + ImGui::GetWindowHeight()),
                IM_COL32(47, 49, 66, 240)
            );
            drawList->AddRectFilled(
                ImGui::GetWindowPos(),
                ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 30),
                IM_COL32(0, 174, 255, 255)
            );
            if (ImGui::GetIO().MouseDown[0]) {
                if (wasMouseDown) {
                    if (dragging == tab) {
                        ImGui::SetWindowPos(ImVec2(ImGui::GetWindowPos().x + ImGui::GetIO().MouseDelta.x, ImGui::GetWindowPos().y + ImGui::GetIO().MouseDelta.y));
                    }
                } else {
                    if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 30))) {
                        geode::log::info("Rect: ({}, {}), ({}, {})", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 30);
                        geode::log::info("Mouse: ({}, {})", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
                        geode::log::info("Dragging {}", tab);
                        dragging = tab;
                        dragOffset = ImVec2(ImGui::GetIO().MousePos.x - ImGui::GetWindowPos().x, ImGui::GetIO().MousePos.y - ImGui::GetWindowPos().y);
                    }
                }
            } else {
                wasMouseDown = false;
                dragging = "";
            }
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(tab.c_str()).x) / 2);
            ImGui::Text(TextUnformatted(tab.c_str()));
            ImGui::SetWindowFontScale(1.0f);
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

    // currentFont = Font::Carme;
    // currentFontStyle = FontStyle::Regular;

    void UI::init() {
      auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((geode::Mod::get()->getResourcesDir() / "CarmeRegular.ttf").string().c_str(), 16.0f);
      ImGui::GetIO().FontDefault = font;
    }
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        summit::ui::imgui::get()->init();
    }).draw([] {
        summit::ui::imgui::get()->draw();
    });
}
