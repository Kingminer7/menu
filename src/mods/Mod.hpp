#pragma once

namespace summit::mods {
    class Mod {
        public:
            virtual void init() = 0;
            virtual void update() = 0;
            virtual bool isCheat() {return false;};
            virtual std::string getName() = 0;
            virtual std::string getID() = 0;
            virtual std::string getDescription() = 0;
    };

    void registerMod(Mod* mod, std::string tab);
    void createTab(std::string name, std::string id);

    enum class OptionType {
        TOGGLE,
        INTEGER,
        FLOAT,
        STRING,
        BUTTON
    };
}

#define REGISTER_MOD(mod, tab) $execute{ summit::mods::registerMod(mod, tab); }