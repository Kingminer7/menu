#pragma once

#include "../Mods.hpp"
#include "../../ui/imgui/ImGuiMain.hpp"

using namespace summit::ui::imgui;

class ConfigMods : public summit::mods::Mod {
    private:
        bool showBall = false;
        bool lastShowBall = false;
        float uiScale = 1.f;
        float lastUiScale = 1.f;
        std::string currentFont = "Carme";
        std::string currentFontStyle = "Regular";
        std::string lastFont = "Carme";
        std::string lastFontStyle = "Regular";
    public:
        void init() override;
        void update(float dt) override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
        void onShowBall(bool value);
        void onUiScale(float value);
};

REGISTER_MOD(new ConfigMods());