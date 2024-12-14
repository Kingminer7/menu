#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Noclip.hpp"

void NoclipMod::init() {
    summit::Config::setValueIfUnset<bool>("player.noclip.enabled", true);
    toggled = summit::Config::getValue<bool>("player.noclip.enabled", true);
    lastToggled = toggled;
}

void NoclipMod::update(float dt) {
    
}

void NoclipMod::renderImGui() {
    ImGui::Checkbox("Noclip", &toggled);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Prevents you from dying.");
    }
    ImGui::SameLine(ImGui::GetWindowWidth() - 30);
    ImGui::SetNextItemWidth(50);
    ImGui::Button(">");
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
}

#include <Geode/modify/PlayLayer.hpp>
class $modify (PlayLayer) {
    void destroyPlayer(PlayerObject *player, GameObject *obj) {
        if (!summit::Config::getValue<bool>("player.noclip.enabled", false) || obj == m_anticheatSpike) PlayLayer::destroyPlayer(player, obj);
    }
};