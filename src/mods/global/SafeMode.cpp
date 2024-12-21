#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "SafeMode.hpp"

void SafeModeMod::init() {
    summit::Config::setValueIfUnset<bool>("global.safemode.enabled", true);
    toggled = summit::Config::getValue<bool>("global.safemode.enabled", true);
    auto widget = summit::ui::widgets::Widget::create("global.safemode")
        ->addToggle("global.safemode.toggle", [this](bool toggled) {
            onToggle(toggled);
        }, &toggled)
        ->setLabel("Safe Mode")
        ->setDescription("Prevents completion of levels to prevent cheated completions.")
        ->setTab("Global");
    summit::ui::registerWidget(widget);
}

void SafeModeMod::update(float dt) {
    
}

std::string SafeModeMod::getId() const {
    return "global.safemode";
}

std::string SafeModeMod::getTab() const {
    return "Global";
}

void SafeModeMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("global.safemode.enabled", toggled);
    geode::log::info("Safe Mode toggled: {}", toggled);
}

#include <Geode/modify/PlayLayer.hpp>
class $modify (PlayLayer) {
    void levelComplete() {
        if (summit::Config::getValue<bool>("global.safemode.enabled", true)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::levelComplete();
            m_isTestMode = orig;
        } else PlayLayer::levelComplete();
    }

    void destroyPlayer(PlayerObject *p, GameObject *g) {
        if (summit::Config::getValue<bool>("global.safemode.enabled", true)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::destroyPlayer(p,g);
            m_isTestMode = orig;
        } else PlayLayer::destroyPlayer(p,g);
    }
};