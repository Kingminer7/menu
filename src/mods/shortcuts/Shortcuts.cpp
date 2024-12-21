#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Shortcuts.hpp"

void ShortcutsMod::init() {
    auto widget = summit::ui::widgets::Widget::create("shortcuts")
        ->addButton("Settings", []() {
            OptionsLayer* layer = OptionsLayer::create();
            cocos2d::CCScene* scene = cocos2d::CCDirector::get()->getRunningScene();
            int z = scene->getHighestChildZ();
            if(z == INT_MAX) return;
            layer->setZOrder(z + 1);
            layer->showLayer(false);
            layer->removeFromParentAndCleanup(false);
            scene->addChild(layer);
        })
        ->setDescription("Opens Settings")
        ->setTab("Shortcuts");
    summit::ui::registerWidget(widget);
}

void ShortcutsMod::update(float dt) {
    
}



std::string ShortcutsMod::getId() const {
    return "shortcuts";
}

std::string ShortcutsMod::getTab() const {
    return "Shortcuts";
}
