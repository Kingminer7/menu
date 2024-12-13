#pragma once

#include "../Mods.hpp"

class MainLevelsMod : public summit::mods::Mod {
    private:
        bool toggled = false;
        bool lastToggled = false;
    public:
        void init() override;
        void update() override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
        void onToggle(bool toggled);
};

REGISTER_MOD(new MainLevelsMod());