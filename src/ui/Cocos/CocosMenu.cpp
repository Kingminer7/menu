#include "CocosMenu.hpp"
// #include "OptionNode.hpp"
#include "../../mods/Mod.hpp"
#include "../../utils/Summit.hpp"
#include "ToggleNode.hpp"

namespace summit::cocosui {

    bool CocosMenu::setup() {
        m_currentMenu = Menu::get()->getTempValue<std::string>("currentMenu").unwrapOr("global");
        if (auto bg = m_mainLayer->getChildByType<CCScale9Sprite>(0)) {
            bg->setID("bg"_spr);
            bg->setZOrder(-10);
        }
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
        bg->setZOrder(-1);
        m_mainLayer->addChild(bg);

        for (auto tab : mods::getTabs()) {
            auto sprite = CCScale9Sprite::create("square02b_small.png");
            sprite->setScale(0.5f);
            sprite->setScaledContentSize({85.f, 20.f});
            sprite->setOpacity(100);
            sprite->setID("bg");
            CCLabelBMFont *label = CCLabelBMFont::create(tab.second.c_str(), "bigFont.fnt");
            label->limitLabelWidth(80, .575f, 0.01f);
            label->setPosition({42.5f, 10.f});
            label->setID("label");
            auto btn = CCMenuItemSpriteExtra::create(
                sprite,
                this, menu_selector(CocosMenu::onTab)
            );
            btn->addChild(label);
            btn->setID(tab.first);

            tabBtnMenu->addChild(btn);
            tabBtnMenu->updateLayout();
            m_menuBtns.push_back(btn);

            auto menu = ScrollLayer::create({300.f, 280.f});
            menu->setID(tab.first);
            tabHolder->addChild(menu);

            if (tab.first == m_currentMenu) {
                sprite->setColor({50, 50, 50});
            } else {
                menu->setVisible(false);
                sprite->setColor({0, 0, 0});
            }

            m_menus.push_back(menu);

            auto toggler = ToggleNode::create("mods.safemode.enabled", "Safe Mode");
            toggler->setPosition({0, 250});
            menu->m_contentLayer->addChild(toggler);

            for (auto mod : mods::getModsInTab(tab.first)) {
                
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
        auto s = m_mainLayer->getScale();
        m_mainLayer->setScale(0.0f);
        CCScene::get()->addChild(this, 9999999);
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