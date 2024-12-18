#pragma once

#include "../Mods.hpp"

class ShortcutsMod : public summit::mods::Mod {
    public:
        void init() override;
        void update(float dt) override;
        void renderImGui() override;
        std::string getId() const override;
        std::string getTab() const override;
};

REGISTER_MOD(new ShortcutsMod());
