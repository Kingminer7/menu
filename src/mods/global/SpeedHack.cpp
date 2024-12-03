#include "../Mod.hpp"
#include "../../utils/Summit.hpp"

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
        }

        void update() override {
            
        }
    };

    REGISTER_MOD(new Speedhack());
}