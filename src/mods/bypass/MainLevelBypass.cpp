#include "../Mod.hpp"
#include "../../utils/Summit.hpp"

namespace summit::mods {
    class MainLevelBypass : public Mod {
    public:
        void init() override {
            optionType = OptionType::TOGGLE;
            tab = "bypass";
            id = "mainlevelbypass";
            name = "Main Levels Bypass";
            description = "Allows you to access the main levels without meeting coin requirements.";
            valueName = "mods.mainlevelbypass.enabled";
            summit::Menu::get()->setModValueIfMissing<bool>(valueName, false);
        }

        void update() override {
            
        }
    };

    REGISTER_MOD(new MainLevelBypass());
}

#include <Geode/modify/GameLevelManager.hpp>
class $modify(GameLevelManager) {
    GJGameLevel *getMainLevel(int id, bool dGLS) {
        auto level = GameLevelManager::getMainLevel(id, dGLS);
        if (summit::Menu::get()->getModValue<bool>("mods.mainlevelbypass.enabled").unwrapOr(false)) {
            level->m_requiredCoins = 0;
        }
        return level;
    }
};