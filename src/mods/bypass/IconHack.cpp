#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "IconHack.hpp"

void IconHackMod::init() {
    summit::Config::setValueIfUnset("bypass.iconhack.enabled", false);
    toggled = summit::Config::getValue<bool>("bypass.iconhack.enabled", false);
    lastToggled = toggled;
}

void IconHackMod::update() {
    
}

void IconHackMod::renderImGui() {
    ImGui::Checkbox("Icon Hack", &toggled);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Lets you use any icon");
    }
    if (lastToggled != toggled) {
        lastToggled = toggled;
        onToggle(toggled);
    }
}

std::string IconHackMod::getId() const {
    return "bypass.iconhack";
}

std::string IconHackMod::getTab() const {
    return "bypass";
}

void IconHackMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("bypass.iconhack.enabled", toggled);
}

#include <Geode/modify/GameManager.hpp>
class $modify(GameManager) {
    bool isIconUnlocked(int p0, IconType p1) {
        if (summit::Config::getValue<bool>("mods.iconhack.enabled", false)) {
            return true;
        }
        return GameManager::isIconUnlocked(p0, p1);
    }

    bool isColorUnlocked(int p0, UnlockType p1) {
        if (summit::Config::getValue<bool>("mods.iconhack.enabled", false)) {
            return true;
        }
        return GameManager::isColorUnlocked(p0, p1);
    }
};