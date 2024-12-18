#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Shortcuts.hpp"

void ShortcutsMod::init() {
    m_settingsCall = menu_selector(MenuLayer::onOptions);
}

void ShortcutsMod::update(float dt) {
    
}

void ShortcutsMod::renderImGui() {
    if (ImGui::Button("Safe Mode")) {
        m_settingsCall(nullptr);
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Opens Settings");
    }
}

std::string ShortcutsMod::getId() const {
    return "shortcuts";
}

std::string ShortcutsMod::getTab() const {
    return "Shortcuts";
}
