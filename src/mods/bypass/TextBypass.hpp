#pragma once

#include "../Mods.hpp"

class TextBypassMod : public summit::mods::Mod {
    private:
        bool lengthBypass = false;
        bool charBypass = false;
    public:
        void init() override;
        void update(float dt) override;
        std::string getId() const override;
        std::string getTab() const override;
        void onLengthBypass(bool toggled);
        void onCharBypass(bool toggled);
};

REGISTER_MOD(new TextBypassMod());