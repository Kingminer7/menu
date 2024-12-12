#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Speedhack.hpp"

void SpeedhackMod::init() {
    summit::Config::setValueIfUnset<bool>("global.speedhack.enabled", false, false);
    toggled = summit::Config::getValue<bool>("global.speedhack.enabled", false, false);
    lastToggled = toggled;
    summit::Config::setValueIfUnset<float>("global.speedhack.value", 1.f);
    value = summit::Config::getValue<float>("global.speedhack.value", 1.f);
    lastValue = value;
}

void SpeedhackMod::update() {
    
}

void SpeedhackMod::renderImGui() {
    ImGui::Checkbox("Speedhack", &toggled);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Speeds up the game speed.");
    }
    if (lastToggled != toggled) {
        lastToggled = toggled;
        onToggle(toggled);
    }
    ImGui::SameLine();
    ImGui::DragFloat("Speed", &value, 0.1f, 0.1f, 1000.0f);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Speeds up the game speed.");
    }
    if (lastValue != value) {
        lastValue = value;
        onValueChange(value);
    }
    
}

std::string SpeedhackMod::getId() const {
    return "TestMod";
}

std::string SpeedhackMod::getTab() const {
    return "Global";
}

void SpeedhackMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("global.speedhack.enabled", toggled, false);

    geode::log::info("Speedhack toggled: {}", toggled);
}

void SpeedhackMod::onValueChange(float value) {
    summit::Config::setValue<float>("global.speedhack.value", value);

    geode::log::info("Speedhack value changed: {}", value);
}

#include <Geode/modify/CCScheduler.hpp>
class $modify(cocos2d::CCScheduler) {
    void update(float delta) {
        if (summit::Config::getValue("global.speedhack.enabled", false)) cocos2d::CCScheduler::update(delta * summit::Config::getValue("global.speedhack.value", 1.0));
        else cocos2d::CCScheduler::update(delta);
    }
};
