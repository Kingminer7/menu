#include "../Summit.hpp"
#include "../ui/UIManager.hpp"

#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes keyCode, bool isDown, bool isRepeat) {
        if (keyCode == cocos2d::enumKeyCodes::KEY_Tab && isDown) {
            summit::ui::getCurrentStyle()->toggle();
            return true;
        }
        return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(keyCode, isDown, isRepeat);
    }
};