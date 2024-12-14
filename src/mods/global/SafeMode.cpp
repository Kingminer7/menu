#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "SafeMode.hpp"

void SafeModeMod::init() {
    summit::Config::setValueIfUnset<bool>("global.safemode.enabled", true);
    toggled = summit::Config::getValue<bool>("global.safemode.enabled", true);
    lastToggled = toggled;
}

void SafeModeMod::update(float dt) {
    
}

void SafeModeMod::renderImGui() {
    ImGui::Checkbox("Safe Mode", &toggled);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Prevents completion of levels to prevent cheated completions.");
    }
    if (lastToggled != toggled) {
        lastToggled = toggled;
        onToggle(toggled);
    }
}

std::string SafeModeMod::getId() const {
    return "global.safemode";
}

std::string SafeModeMod::getTab() const {
    return "Global";
}

void SafeModeMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("global.safemode.enabled", toggled);
}

#include <Geode/modify/PlayLayer.hpp>
class $modify (PlayLayer) {
    void levelComplete() {
        if (summit::Config::getValue<bool>("global.safemode.enabled", false)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::levelComplete();
            m_isTestMode = orig;
        } else PlayLayer::levelComplete();
    }

    void destroyPlayer(PlayerObject *p, GameObject *g) {
        if (summit::Config::getValue<bool>("global.safemode.enabled", false)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::destroyPlayer(p,g);
            m_isTestMode = orig;
        } else PlayLayer::destroyPlayer(p,g);
    }
};