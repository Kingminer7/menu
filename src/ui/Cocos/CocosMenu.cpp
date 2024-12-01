#include "CocosMenu.hpp"
#include "../../utils/Summit.hpp"

namespace summit::ui {

    bool CocosMenu::setup() {
        m_currentMenu = Menu::get()->getTempValue<std::string>("currentMenu").unwrapOr("global");
        m_mainLayer->getChildByType<CCScale9Sprite>(0)->setID("bg"_spr);
        m_mainLayer->setID("main-layer"_spr);
        m_buttonMenu->setID("button-menu"_spr);
        m_backBtn = m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(0);
        m_backBtn->setID("back-btn"_spr);

        tabBtnMenu = CCMenu::create();
        tabBtnMenu->setID("tab-btn-menu"_spr);
        tabBtnMenu->setPosition({ 10, 10 });
        auto layout = AxisLayout::create(Axis::Column);
        layout->setAxisAlignment(AxisAlignment::End);
        layout->setAxisReverse(true);
        tabBtnMenu->setLayout(layout);
        tabBtnMenu->setContentSize({85.f, 280.f});
        tabBtnMenu->ignoreAnchorPointForPosition(true);
        m_mainLayer->addChild(tabBtnMenu);

        CCMenu *tabHolder = CCMenu::create();
        tabHolder->setID("tab-holder"_spr);
        tabHolder->setPosition({ 105, 10 });
        tabHolder->setContentSize({ 300.f, 280.f });
        m_mainLayer->addChild(tabHolder);

        CCScale9Sprite *bg = CCScale9Sprite::create("square02b_001.png");
        bg->setContentSize({ 300.f, 280.f });
        bg->setOpacity(100);
        bg->setColor({ 0, 0, 0 });
        bg->setID("tab-bg"_spr);
        bg->setPosition({ 105, 10 });
        bg->ignoreAnchorPointForPosition(true);
        m_mainLayer->addChild(bg);

        for (auto &tab : summit::Menu::get()->getTabs()) {
            auto sprite = CCScale9Sprite::create("square02b_001.png");
            sprite->setContentSize({85.f, 20.f});
            sprite->setOpacity(100);
            sprite->setID("bg");
            CCLabelBMFont *label = CCLabelBMFont::create(tab.name.c_str(), "bigFont.fnt");
            label->limitLabelWidth(80, .575f, 0.01f);
            label->setPosition({42.5f, 10.f});
            label->setID("label");
            auto btn = CCMenuItemSpriteExtra::create(
                sprite,
                this, menu_selector(CocosMenu::onTab)
            );
            btn->addChild(label);
            btn->setID(tab.id);

            tabBtnMenu->addChild(btn);
            tabBtnMenu->updateLayout();
            m_menuBtns.push_back(btn);

            auto menu = ScrollLayer::create({300.f, 280.f});
            menu->setID(tab.id);
            tabHolder->addChild(menu);

            if (tab.id == m_currentMenu) {
                sprite->setColor({50, 50, 50});
            } else {
                menu->setVisible(false);
                sprite->setColor({0, 0, 0});
            }

            for (SMod mod : tab.mods) {
                auto node = mod.createNode();
                menu->addChild(node);
            }
        }

        return true;
    }

    CocosMenu *CocosMenu::create() {
        auto ret = new CocosMenu();
        if (ret->initAnchored(420.f, 300.f)) {
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

    void CocosMenu::show() {
        CCScene::get()->addChild(this, 9999999);
        auto s = m_mainLayer->getScale();
        m_mainLayer->setScale(0.0f);
        m_mainLayer->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5f, s), 1.2f));
    }

    void CocosMenu::onTab(CCObject *sender) {
        auto btn = dynamic_cast<CCMenuItemSpriteExtra *>(sender);
        if (!btn) return;
        auto id = btn->getID();
        if (id == m_currentMenu) return;
        for (auto &menu : m_menus) {
            if (menu->getID() == m_currentMenu)
                menu->setVisible(false);
            if (menu->getID() == id)
                menu->setVisible(true);
        }
        for (auto &btn : m_menuBtns) {
            if (btn->getID() == m_currentMenu)
                btn->getChildByType<CCScale9Sprite>(0)->setColor({0, 0, 0});
            if (btn->getID() == id)
                btn->getChildByType<CCScale9Sprite>(0)->setColor({50, 50, 50});
        }
        m_currentMenu = id;
    }
}