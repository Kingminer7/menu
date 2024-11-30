#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace summit::ui {

    class MenuButton : public CCMenu {
    protected:
        static MenuButton *instance;
        
        bool move = false;
        CCPoint *startPos;
        
        CCSprite *m_sprite;

        bool init() override;
        bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
        void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
        void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
        void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override {
            ccTouchEnded(touch, event);
        }
        void registerWithTouchDispatcher() override;

    public:
        static MenuButton *get();
        void onPress();
    };

}