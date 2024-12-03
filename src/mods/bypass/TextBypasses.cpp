#include "../Mod.hpp"
#include "../../utils/Summit.hpp"
#include <climits>

namespace summit::mods {
    class CharLimitBypass : public Mod {
    public:
        void init() override {
            optionType = OptionType::TOGGLE;
            tab = "bypass";
            id = "charlimitbypass";
            name = "Character Limit Bypass";
            description = "Remove character limits from text fields.";
            valueName = "mods.charlimitbypass.enabled";
            summit::Menu::get()->setModValueIfMissing<bool>(valueName, false);
        }

        void update() override {
            
        }
    };

    class CharFilterBypass : public Mod {
    public:
        void init() override {
            optionType = OptionType::TOGGLE;
            tab = "bypass";
            id = "charfilterbypass";
            name = "Character Filter Bypass";
            description = "Remove character filters from text fields.";
            valueName = "mods.charfilterbypass.enabled";
            summit::Menu::get()->setModValueIfMissing<bool>(valueName, false);
        }

        void update() override {
            
        }
    };

    REGISTER_MOD(new CharLimitBypass());
    REGISTER_MOD(new CharFilterBypass());
}

#include <Geode/modify/CCTextInputNode.hpp>
class $modify (CCTextInputNode) {
    struct Fields {
        int m_origLength = 0;
        std::string m_origChars = "";
    };
    void updateLabel(std::string p0) {
        if (summit::Menu::get()->getModValue<bool>("mods.charlimitbypass.enabled").unwrapOr(false)) {
            if (m_maxLabelLength != INT_MAX) {
                m_fields->m_origLength = m_maxLabelLength;
                setMaxLabelLength(INT_MAX);
            }
        } else if (m_maxLabelLength == INT_MAX) setMaxLabelLength(m_fields->m_origLength);

        if (summit::Menu::get()->getModValue<bool>("mods.charfilterbypass.enabled").unwrapOr(false)) {
            if (m_allowedChars != "`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ") {
                m_fields->m_origChars = m_allowedChars;
                setAllowedChars("`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?");
            }
        } else if (m_allowedChars == "`1234567890-=qwertyuiop[]\\asdfghjkl;'cxzvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?") setAllowedChars(m_fields->m_origChars);

        CCTextInputNode::updateLabel(p0);
    }
};