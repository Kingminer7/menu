#include "SafeMode.hpp"

namespace summit::mods {

    void SafeMode::onToggle(CCObject *) {
        log::info("h");
        auto toggle = summit::Menu::get()->getModValue<bool>(id).unwrapOr(false);
        summit::Menu::get()->setModValue(id, !toggle);
    }

}

$on_mod(Loaded) {
    auto safeMode = summit::SMod();
    safeMode.name = "Safe Mode";
    safeMode.id = "global.safemode";
    safeMode.description = "Prevents completing levels.";
    safeMode.createNodeCB = []() {
        auto node = CCMenu::create();
        node->setContentSize({150, 30});
        auto label = CCLabelBMFont::create("test label", "bigFont.fnt");
        label->limitLabelWidth(115,1.f,0.05f);
        label->setAnchorPoint({0.f, 0.5f});
        node->addChildAtPosition(label, Anchor::Left, {5.f, 0.f});
        auto toggle = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"), CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"), nullptr, menu_selector(summit::mods::SafeMode::onToggle));
        toggle->setID("toggle");
        node->addChildAtPosition(toggle, Anchor::Right, {-5.f, 0.f});

        return node;
    };
    summit::Menu::get()->registerMod("global", safeMode);
}