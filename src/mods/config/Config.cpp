#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Config.hpp"

void ConfigMods::init() {
    summit::Config::setValueIfUnset("config.uiscale", 1.0f);
    uiScale = summit::Config::getValue<float>("config.uiscale", 1.0f);
    lastUiScale = uiScale;
}

void ConfigMods::update() {
    
}

void ConfigMods::renderImGui() {
    // ImGui::GetStyle().ScaleAllSizes(uiScale / lastKnownImGuiScale);
    // lastKnownImGuiScale = uiScale;
    // ImGui::InputFloat("UI Scale", &uiScale, 0.1f, 0.1f, "%.1f");
    // if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    // {
    //     ImGui::SetTooltip("Speeds up the game speed.");
    // }
    // if (lastUiScale != uiScale) {
    //     lastUiScale = uiScale;
    //     onUiScaleChange(uiScale);
    // }
}

std::string ConfigMods::getId() const {
    return "config";
}

std::string ConfigMods::getTab() const {
    return "Config";
}

void ConfigMods::onUiScaleChange(float value) {
    summit::Config::setValue<float>("config.uiscale", value);
}