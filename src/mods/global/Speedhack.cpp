#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Speedhack.hpp"

void SpeedhackMod::init() {
    summit::Config::setValueIfUnset<bool>("global.speedhack.enabled", false, false);
    toggled = summit::Config::getValue<bool>("global.speedhack.enabled", false, false);
    summit::Config::setValueIfUnset<float>("global.speedhack.value", 1.f);
    value = summit::Config::getValue<float>("global.speedhack.value", 1.f);

    auto widget = summit::ui::widgets::Widget::create("global.speedhack")
        ->addToggle("global.speedhack.toggle", [this](bool toggled) {
            onToggle(toggled);
        }, &toggled)
        ->addFloatInput("global.speedhack.value", [this](float value) {
            onValueChange(value);
        }, "input", value, 0.1f, 1000.0f)
        ->setLabel("Speedhack")
        ->setDescription("Speeds up the game speed.")
        ->setTab("Global");
    summit::ui::registerWidget(widget);
}

void SpeedhackMod::update(float dt) {
    
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

    auto widget = summit::ui::widgets::Widget::create("global.speedhack.audio")
        ->addToggle("global.speedhack.audio.toggle", [this](bool toggled) {
            onToggleSpeed(toggled);
        }, &speedAudio)
        ->setLabel("Speedhack Audio Sync")
        ->setDescription("Speeds up audio to match speedhack.")
        ->setTab("Global");
    summit::ui::registerWidget(widget);
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

std::string SpeedAudioMod::getId() const {
    return "global.speedhack.audio";
}

std::string SpeedAudioMod::getTab() const {
    return "Global";
}

void SpeedAudioMod::onToggleSpeed(bool toggled) {
    summit::Config::setValue<bool>("global.speedhack.audio.enabled", toggled);
}