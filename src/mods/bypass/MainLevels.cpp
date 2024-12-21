#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "MainLevels.hpp"

void MainLevelsMod::init() {
    summit::Config::setValueIfUnset<bool>("bypass.mainlevelbypass.enabled", false);
    toggled = summit::Config::getValue<bool>("bypass.mainlevelbypass.enabled", false);
    auto widget = summit::ui::widgets::Widget::create("bypass.mainlevels")
        ->addToggle("bypass.mainlevels.toggle", [this](bool toggled) {
            onToggle(toggled);
        }, &toggled)
        ->setLabel("Main Level Bypass")
        ->setDescription("Lets you play locked main levels")
        ->setTab("Bypass");
    summit::ui::registerWidget(widget);
}

void MainLevelsMod::update(float dt) {
    
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