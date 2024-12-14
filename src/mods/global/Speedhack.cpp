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

void SpeedhackMod::update(float dt) {
    
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
    ImGui::SetNextItemWidth(70);
    ImGui::DragFloat("##SpeedhackInput", &value, 0.1f, 0.1f, 1000.0f);
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
    return "global.speedhack";
}

std::string SpeedhackMod::getTab() const {
    return "Global";
}

void SpeedhackMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("global.speedhack.enabled", toggled, false);
}

void SpeedhackMod::onValueChange(float value) {
    summit::Config::setValue<float>("global.speedhack.value", value);
}

#include <Geode/modify/CCScheduler.hpp>
class $modify(cocos2d::CCScheduler) {
    void update(float delta) {
        if (summit::Config::getValue<bool>("global.speedhack.enabled", false, false)) cocos2d::CCScheduler::update(delta * summit::Config::getValue<float>("global.speedhack.value", 1.0));
        else cocos2d::CCScheduler::update(delta);
    }
};


void SpeedAudioMod::init() {
    summit::Config::setValueIfUnset<bool>("global.speedhack.audio.enabled", false);
    speedAudio = summit::Config::getValue<bool>("global.speedhack.audio.enabled", false);
    lastSpeedAudio = speedAudio;
}

void SpeedAudioMod::update(float dt) {
    for (auto i = 0; i < 4; i++) {
        FMOD::Channel *channel;
        FMODAudioEngine::get()->m_system->getChannel(i + 126, &channel);
        if (channel) {
            FMOD::Sound* sound;
            channel->getCurrentSound(&sound);
            float freq;
            sound->getDefaults(&freq, nullptr);
            if (speedAudio && summit::Config::getValue<bool>("global.speedhack.enabled", false, false)) channel->setFrequency(freq * summit::Config::getValue<float>("global.speedhack.value", 1.0));
            else channel->setFrequency(freq);
        }
    }
}

void SpeedAudioMod::renderImGui() {
    ImGui::Checkbox("Speedhack Audio Sync", &speedAudio);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Speeds up audio to match speedhack.");
    }
    if (lastSpeedAudio != speedAudio) {
        lastSpeedAudio = speedAudio;
        onToggleSpeed(speedAudio);
    }
}

std::string SpeedAudioMod::getId() const {
    return "global.speedhack.audio";
}

std::string SpeedAudioMod::getTab() const {
    return "Global";
}

void SpeedAudioMod::onToggleSpeed(bool toggled) {
    summit::Config::setValue<bool>("global.speedhack.audio.enabled", toggled);
}