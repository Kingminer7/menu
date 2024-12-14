#pragma once

#include "../Mods.hpp"

class TextBypassMod : public summit::mods::Mod {
    private:
        bool lengthBypass = false;
        bool lastLengthBypass = false;
        bool charBypass = false;
        bool lastCharBypass = false;
    public:
        void init() override;
        void update(float dt) override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
        void onLengthBypass(bool toggled);
        void onCharBypass(bool toggled);
};

REGISTER_MOD(new TextBypassMod());