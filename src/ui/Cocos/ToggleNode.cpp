#include "ToggleNode.hpp"

namespace summit::cocosui {
    bool ToggleNode::init() {
        if (!OptionNode::init()) {
            return false;
        }
        setAnchorPoint({0, 0});
        setContentSize({150, 30});

        m_label = CCLabelBMFont::create("Toggle", "bigFont.fnt");
        m_label->limitLabelWidth(120, .8f, 0.01f);
        m_label->setAnchorPoint({0, 0.5f});
        addChildAtPosition(m_label, Anchor::Left, {5, 2.5});

        m_toggler = CCMenuItemToggler::create(
            CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"),
            CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
            this, menu_selector(ToggleNode::onToggle)
        );
        m_toggler->setAnchorPoint({1, 0.5f});
        m_toggler->setID("toggler"_spr);
        m_toggler->setScale(0.675);
        addChildAtPosition(m_toggler, Anchor::Right, {-5, 2.5});

        return true;
    }

    ToggleNode *ToggleNode::create(const std::string& id){
        auto ret = new ToggleNode();
        if (ret && ret->init()) {
            ret->m_id = id;
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    void ToggleNode::onToggle(CCObject *sender) {
        auto toggler = dynamic_cast<CCMenuItemToggler*>(sender);
        log::info("Test");
        if (toggler) {
            log::info("Test2");
        }
    }
}