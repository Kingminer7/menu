#include <imgui-cocos.hpp>
#include "UI.hpp"
#include "../../mods/Mods.hpp"

namespace summit::ui::imgui {
    UI* UI::instance = nullptr;

    UI* UI::get() {
        if (!instance) {
            instance = new UI();
        }
        return instance;
    }

    static int awesomeInt = 0;

    void UI::draw() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoResize;
        for (auto tab : summit::mods::getTabs()) {
            if (ImGui::Begin(tab.c_str(), nullptr, window_flags)) {
                for (auto mod : summit::mods::getModsInTab(tab)) {
                    mod.second->renderImGui();
                }
            }
            ImGui::SetWindowSize(ImVec2(200, 200));
            ImGui::End();   
        }
    }
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
    }).draw([] {
        summit::ui::imgui::get()->draw();
    });
}