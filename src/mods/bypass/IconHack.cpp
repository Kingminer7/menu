#include "../Mod.hpp"
#include "../../utils/Summit.hpp"

namespace summit::mods {
    class IconHack : public Mod {
    public:
        void init() override {
            optionType = OptionType::TOGGLE;
            tab = "bypass";
            id = "iconhack";
            name = "Icon Hack";
            description = "Unlock all icons.";
            valueName = "mods.iconhack.enabled";
            summit::Menu::get()->setModValueIfMissing<bool>(valueName, false);
        }

        void update() override {
            
        }
    };

    REGISTER_MOD(new IconHack());
}

#include <Geode/modify/GameManager.hpp>
class $modify(GameManager) {
    bool isIconUnlocked(int p0, IconType p1) {
        if (summit::Menu::get()->getModValue<bool>("mods.iconhack.enabled").unwrapOr(false)) {
            return true;
        }
        return GameManager::isIconUnlocked(p0, p1);
    }

    bool isColorUnlocked(int p0, UnlockType p1) {
        if (summit::Menu::get()->getModValue<bool>("mods.iconhack.enabled").unwrapOr(false)) {
            return true;
        }
        return GameManager::isColorUnlocked(p0, p1);
    }
};