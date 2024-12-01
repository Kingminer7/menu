#include "Mod.hpp"
#include "../utils/Summit.hpp"

namespace summit::mods {
    class SafeMode : public Mod {
    public:
        void init() override {
            summit::Menu::get()->setModValueIfMissing<bool>("mods.safemode.enabled", true);
        }

        void update() override {
            
        }
        
        std::string getName() override {
            return "Safe Mode";
        };
        std::string getID() override {
            return "safemode";
        };
        std::string getDescription() override {
            return "Prevents you from beating levels.";
        };
    };

    REGISTER_MOD(new SafeMode(), "general");
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
};