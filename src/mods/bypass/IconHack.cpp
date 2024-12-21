#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "IconHack.hpp"

void IconHackMod::init() {
    summit::Config::setValueIfUnset<bool>("bypass.iconhack.enabled", false);
    toggled = summit::Config::getValue<bool>("bypass.iconhack.enabled", false);
    auto widget = summit::ui::widgets::Widget::create("bypass.iconhack")
        ->addToggle("bypass.iconhack.toggle", [this](bool toggled) {
            onToggle(toggled);
        }, &toggled)
        ->setLabel("Icon Hack")
        ->setDescription("Lets you use icons you haven't unlocked")
        ->setTab("Bypass");
    summit::ui::registerWidget(widget);
}

void IconHackMod::update(float dt) {
    
}

std::string IconHackMod::getId() const {
    return "bypass.iconhack";
}

std::string IconHackMod::getTab() const {
    return "Bypass";
}

void IconHackMod::onToggle(bool toggled) {
    summit::Config::setValue<bool>("bypass.iconhack.enabled", toggled);
}

#include <Geode/modify/GameManager.hpp>
class $modify(GameManager) {
    bool isIconUnlocked(int p0, IconType p1) {
        if (summit::Config::getValue<bool>("bypass.iconhack.enabled", false)) {
            return true;
        }
        return GameManager::isIconUnlocked(p0, p1);
    }

    bool isColorUnlocked(int p0, UnlockType p1) {
        if (summit::Config::getValue<bool>("bypass.iconhack.enabled", false)) {
            return true;
        }
        return GameManager::isColorUnlocked(p0, p1);
    }
};