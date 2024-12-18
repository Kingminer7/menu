#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Shortcuts.hpp"

void ShortcutsMod::init() {
    
}

void ShortcutsMod::update(float dt) {
    
}

void ShortcutsMod::renderImGui() {
    if (ImGui::Button("Settings")) {
        OptionsLayer* layer = OptionsLayer::create();
        int z = cocos2d::CCDirector::get()->getRunningScene()->getHighestChildZ();
        if(z == INT_MAX) return;
        layer->setZOrder(z + 1);
        layer->showLayer(false);
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
