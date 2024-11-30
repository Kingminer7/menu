#include "CocosMenu.hpp"
#include "MenuButton.hpp"

using namespace geode::prelude;
using namespace summit::ui;

#include <Geode/modify/CCScene.hpp>

class $modify(CCScene) {
    int getHighestChildZ() {
        auto btn = MenuButton::get();
        auto menu = CocosMenu::get();
        int btnZ;
        int menuZ;

        if (btn) {
            btnZ = btn->getZOrder();
            btn->setZOrder(-1);
        }

        if (menu) {
            menuZ = menu->getZOrder();
            menu->setZOrder(-1);
        }

        auto highest = CCScene::getHighestChildZ();
        
        if (menu) menu->setZOrder(menuZ);
        if (btn) btn->setZOrder(btnZ);

        return highest;
    }
};