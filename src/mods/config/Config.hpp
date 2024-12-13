#pragma once

#include "../Mods.hpp"

class ConfigMods : public summit::mods::Mod {
    private:
        float lastKnownImGuiScale = 1.f;
        float uiScale = 1.f;
        float lastUiScale = 1.f;
    public:
        void init() override;
        void update() override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
        void onUiScaleChange(float value);
};

REGISTER_MOD(new ConfigMods());