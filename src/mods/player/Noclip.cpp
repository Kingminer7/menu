#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Noclip.hpp"

void NoclipMod::init() {
    summit::Config::setValueIfUnset("player.noclip.enabled", true);
    toggled = summit::Config::getValue<bool>("player.noclip.enabled", true);
    lastToggled = toggled;
}

void NoclipMod::update() {
    
}

void NoclipMod::renderImGui() {
    ImGui::Checkbox("Noclip", &toggled);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Prevents you from dying.");
    }
    if (lastToggled != toggled) {
        lastToggled = toggled;
        onToggle(toggled);
    }
}

std::string NoclipMod::getId() const {
    return "player.noclip";
}

std::string NoclipMod::getTab() const {
    return "Player";
}

void NoclipMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("player.noclip.enabled", toggled);

    geode::log::info("Safe mode toggled: {}", toggled);
}

#include <Geode/modify/PlayLayer.hpp>
class $modify (PlayLayer) {
    void destroyPlayer(PlayerObject *player, GameObject *obj) {
        if (!summit::Config::getValue("player.noclip.enabled", false) || obj == m_anticheatSpike) PlayLayer::destroyPlayer(player, obj);
    }
};