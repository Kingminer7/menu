#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Noclip.hpp"

void NoclipMod::init() {
    summit::Config::setValueIfUnset<bool>("player.noclip.enabled", false);
    noclip = summit::Config::getValue<bool>("player.noclip.enabled", false);
    lastNoclip = noclip;

    summit::Config::setValueIfUnset<bool>("player.noclip.player1", true);
    player1 = summit::Config::getValue<bool>("player.noclip.player1", true);
    lastPlayer1 = player1;

    summit::Config::setValueIfUnset<bool>("player.noclip.player2", true);
    player2 = summit::Config::getValue<bool>("player.noclip.player2", true);
    lastPlayer2 = player2;
}

void NoclipMod::update(float dt) {
    
}

void NoclipMod::renderImGui() {
    ImGui::Checkbox("Noclip", &noclip);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Prevents you from dying.");
    }
    ImGui::SameLine(ImGui::GetWindowWidth() - 35);
    ImGui::SetNextItemWidth(100);
    if (ImGui::Button(" > ")) ImGui::OpenPopup("Noclip");
        if (ImGui::BeginPopup("Noclip")) {
        ImGui::Checkbox("Player 1", &player1);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
        {
            ImGui::SetTooltip("Prevents player 1 from dying.");
        }
        if (lastPlayer1 != player1) {
            lastPlayer1 = player1;
            summit::Config::setValue<bool>("player.noclip.player1", player1);
        }
            
        ImGui::Checkbox("Player 2", &player2);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
        {
            ImGui::SetTooltip("Prevents player 2 from dying.");
        }
        if (lastPlayer2 != player2) {
            lastPlayer2 = player2;
            summit::Config::setValue<bool>("player.noclip.player2", player2);
        }

        ImGui::EndPopup();
    }
    if (lastNoclip != noclip) {
        lastNoclip = noclip;
        onNoclip(noclip);
    }
}

std::string NoclipMod::getId() const {
    return "player.noclip";
}

std::string NoclipMod::getTab() const {
    return "Player";
}

void NoclipMod::onNoclip(bool toggled) {
    summit::Config::setValue<bool>("player.noclip.enabled", toggled);
}

void NoclipMod::onPlayer1(bool toggled) {
    summit::Config::setValue<bool>("player.noclip.player1", toggled);
}

void NoclipMod::onPlayer2(bool toggled) {
    summit::Config::setValue<bool>("player.noclip.player2", toggled);
}

#include <Geode/modify/PlayLayer.hpp>
class $modify (PlayLayer) {
    void destroyPlayer(PlayerObject *player, GameObject *obj) {
        if (!summit::Config::getValue<bool>("player.noclip.enabled", false) || obj == m_anticheatSpike) {
            PlayLayer::destroyPlayer(player, obj);
            return;
        }
        if ((m_player1 == player && !summit::Config::getValue<bool>("player.noclip.player1", false)) || (m_player2 == player && !summit::Config::getValue<bool>("player.noclip.player2", false))) {
            PlayLayer::destroyPlayer(player, obj);
            return;
        }
    }
};
