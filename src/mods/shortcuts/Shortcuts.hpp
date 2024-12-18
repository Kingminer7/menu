#pragma once

#include "../Mods.hpp"

class ShortcutsMod : public summit::mods::Mod {
    protected:
        cocos2d::SEL_MenuHandler m_settingsCall;
    public:
        void init() override;
        void update(float dt) override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
};

REGISTER_MOD(new ShortcutsMod());
