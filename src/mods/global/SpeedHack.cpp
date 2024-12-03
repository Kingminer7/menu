#include "../Mod.hpp"
#include "../../utils/Summit.hpp"
#include "../../utils/HookManager.hpp"

namespace summit::mods {
    class Speedhack : public Mod {
    public:
        void init() override {
            optionType = OptionType::FLOAT;
            tab = "global";
            id = "speedhack";
            name = "Speedhack";
            description = "Change the game speed.";
            valueName = "mods.speedhack.speed";
            summit::Menu::get()->setModValueIfMissing<float>(valueName, 1.0);
            summit::Menu::get()->setModValueIfMissing<bool>("mods.speedhack.enabled", false);
        }

        void update() override {
            // if (summit::Menu::get()->getModValue<float> (valueName).unwrapOr(1.f) != 1.0) {
            //     if (!summit::Menu::get()->getModValue<bool>("mods.speedhack.enabled").unwrapOr(false)) {
            //         summit::HookManager::enableHook("mods.speedhack.ccsupdate");
            //         summit::Menu::get()->setModValue("mods.speedhack.enabled", true);
            //     }
            // } else {
            //     if (summit::Menu::get()->getModValue<bool>("mods.speedhack.enabled").unwrapOr(false)) {
            //         summit::HookManager::disableHook("mods.speedhack.ccsupdate");
            //         summit::Menu::get()->setModValue("mods.speedhack.enabled", false);
            //     }
            // }
        }
    };

    REGISTER_MOD(new Speedhack());
}

#include <Geode/modify/CCScheduler.hpp>
class $modify(CCScheduler) {
    void update(float delta) {
        CCScheduler::update(delta);
    }

    static void onModify(auto& self) {
        Result<Hook*> res = self.getHook("cocos2d::CCScheduler::update");
        if (res.isErr()) {
            log::error("Failed to hook: {}", res.unwrapErr());
            return;
        }
        std::shared_ptr<Hook> hook = std::make_shared<Hook>(res.unwrap());
        summit::HookManager::registerHook("mods.speedhack.ccsupdate", res.unwrap());
    }
};