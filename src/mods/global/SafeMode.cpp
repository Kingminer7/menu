#include "../Mod.hpp"
#include "../../utils/Summit.hpp"

namespace summit::mods {
    class SafeMode : public Mod {
    public:
        void init() override {
            optionType = OptionType::TOGGLE;
            tab = "global";
            id = "safemode";
            name = "Safe Mode";
            description = "Prevents you from completing a level.";
            valueName = "mods.safemode.enabled";
            summit::Menu::get()->setModValueIfMissing<bool>(valueName, true);
        }

        void update() override {
            
        }
    };

    REGISTER_MOD(new SafeMode());
}

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayer) {
    void levelComplete() {
        if (summit::Menu::get()->getModValue<bool>("mods.safemode.enabled").unwrapOr(false)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::levelComplete();
            m_isTestMode = orig;
        } else PlayLayer::levelComplete();
    }

    void destroyPlayer(PlayerObject *p, GameObject *g) {
        if (summit::Menu::get()->getModValue<bool>("mods.safemode.enabled").unwrapOr(false)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::destroyPlayer(p,g);
            m_isTestMode = orig;
        } else PlayLayer::destroyPlayer(p,g);
    }

    void resetLevel() {

    }
};