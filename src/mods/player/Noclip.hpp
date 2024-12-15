#pragma once

#include "../Mods.hpp"

class NoclipMod : public summit::mods::Mod {
    private:
        bool noclip = false;
        bool lastNoclip = false;

        bool player1 = true;
        bool lastPlayer1 = true;

        bool player2 = true;
        bool lastPlayer2 = true;
    public:
        void init() override;
        void update(float dt) override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
        void onNoclip(bool toggled);
        void onPlayer1(bool toggled);
        void onPlayer2(bool toggled);
};

REGISTER_MOD(new NoclipMod());