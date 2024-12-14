#pragma once

#include "../Mods.hpp"

class SpeedhackMod : public summit::mods::Mod {
    private:
        bool toggled = false;
        bool lastToggled = false;
        float value = 1.f;
        float lastValue = 1.f;
    public:
        void init() override;
        void update(float dt) override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
        void onToggle(bool toggled);
        void onValueChange(float value);
};

REGISTER_MOD(new SpeedhackMod());

class SpeedAudioMod : public summit::mods::Mod {
    private:
        bool speedAudio = false;
        bool lastSpeedAudio = false;
    public:
        void init() override;
        void update(float dt) override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
        void onToggleSpeed(bool toggled);
};

REGISTER_MOD(new SpeedAudioMod());