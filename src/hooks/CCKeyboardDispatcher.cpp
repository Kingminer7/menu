#include "../ui/Cocos/CocosMenu.hpp"

using namespace geode::prelude;
using namespace summit::cocosui;

#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        log::info("Pressed button");
        if (key == KEY_Tab && isKeyDown) {
            CocosMenu::open(true);
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};