#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "MainLevels.hpp"

void MainLevelsMod::init() {
    summit::Config::setValueIfUnset("bypass.mainlevelbypass.enabled", false);
    toggled = summit::Config::getValue<bool>("bypass.mainlevelbypass.enabled", false);
    lastToggled = toggled;
}

void MainLevelsMod::update() {
    
}

void MainLevelsMod::renderImGui() {
    ImGui::Checkbox("Main Level Bypass", &toggled);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Lets you play locked main levels");
    }
    if (lastToggled != toggled) {
        lastToggled = toggled;
        onToggle(toggled);
    }
}

std::string MainLevelsMod::getId() const {
    return "bypass.mainlevels";
}

std::string MainLevelsMod::getTab() const {
    return "Bypass";
}

void MainLevelsMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("bypass.mainlevelbypass.enabled", toggled);
}

#include <Geode/modify/GameLevelManager.hpp>
class $modify(GameLevelManager) {
    GJGameLevel *getMainLevel(int id, bool dGLS) {
        auto level = GameLevelManager::getMainLevel(id, dGLS);
        if (summit::Config::getValue<bool>("bypass.mainlevelbypass.enabled", false)) {
            level->m_requiredCoins = 0;
        }
        return level;
    }
};