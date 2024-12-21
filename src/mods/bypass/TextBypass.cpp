#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "TextBypass.hpp"

void TextBypassMod::init() {
    summit::Config::setValueIfUnset<bool>("bypass.textlengthbypass.enabled", false);
    lengthBypass = summit::Config::getValue<bool>("bypass.textlengthbypass.enabled", false);
    summit::Config::setValueIfUnset<bool>("bypass.textcharbypass.enabled", false);
    charBypass = summit::Config::getValue<bool>("bypass.textcharbypass.enabled", false);

    auto widget = summit::ui::widgets::Widget::create("bypass.textbypass")
        ->addToggle("bypass.textbypass.length", [this](bool toggled) {
            onLengthBypass(toggled);
        }, &lengthBypass)
        ->setLabel("Text Length Bypass")
        ->setDescription("Removes the limit from text boxes")
        ->setTab("Bypass");
    summit::ui::registerWidget(widget);

    auto widget2 = summit::ui::widgets::Widget::create("bypass.textbypass")
        ->addToggle("bypass.textbypass.char", [this](bool toggled) {
            onCharBypass(toggled);
        }, &charBypass)
        ->setLabel("Character Filter Bypass")
        ->setDescription("Removes the character filter from text boxes")
        ->setTab("Bypass");
    summit::ui::registerWidget(widget2);
}

void TextBypassMod::update(float dt) {
    
}

std::string TextBypassMod::getId() const {
    return "bypass.textbypass";
}

std::string TextBypassMod::getTab() const {
    return "Bypass";
}

void TextBypassMod::onLengthBypass(bool toggled) {
    summit::Config::setValue<bool>("bypass.textlengthbypass.enabled", toggled);
}

void TextBypassMod::onCharBypass(bool toggled) {
    summit::Config::setValue<bool>("bypass.textcharbypass.enabled", toggled);
}

#include <Geode/modify/CCTextInputNode.hpp>
class $modify (CCTextInputNode) {
    struct Fields {
        int m_origLength = 0;
        std::string m_origChars = "";
    };
    void updateLabel(std::string p0) {
        if (summit::Config::getValue<bool>("bypass.textlengthbypass.enabled", false)) {
            if (m_maxLabelLength != INT_MAX) {
                m_fields->m_origLength = m_maxLabelLength;
                setMaxLabelLength(INT_MAX);
            }
        } else if (m_maxLabelLength == INT_MAX) setMaxLabelLength(m_fields->m_origLength);

        if (summit::Config::getValue<bool>("bypass.textcharbypass.enabled", false)) {
            if (m_allowedChars != "`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ") {
                m_fields->m_origChars = m_allowedChars;
                setAllowedChars("`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ");
            }
        } else if (m_allowedChars == "`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ") setAllowedChars(m_fields->m_origChars);

        CCTextInputNode::updateLabel(p0);
    }
};