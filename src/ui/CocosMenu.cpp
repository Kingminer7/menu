#include "CocosMenu.hpp"

namespace summit::ui {

    bool CocosMenu::setup() {
        return true;
    }

    CocosMenu *CocosMenu::create() {
        auto ret = new CocosMenu();
        if (ret->initAnchored(500.f, 320.f)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }

    CocosMenu *CocosMenu::get() {
        if (CCScene::get()->getChildByType<CocosMenu>(0)) {
            return CCScene::get()->getChildByType<CocosMenu>(0);
        }
        return nullptr;
    }

    void CocosMenu::open() {
        auto menu = CocosMenu::get();
        if (!menu) {
            menu = CocosMenu::create();
            menu->show();
        }
    }

}