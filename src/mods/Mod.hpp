#pragma once

namespace summit::mods {
    enum class OptionType {
        TOGGLE,
        INTEGER,
        FLOAT,
        STRING,
        BUTTON
    };

    class Mod {
        protected:
            std::string id;
            std::string name;
            std::string description;
            std::string tab;
            OptionType optionType;
        public:
            virtual void init() = 0;
            virtual void update() = 0;

            virtual bool isCheat() {return false;};
            std::string getId() {return id;};
            std::string getName() {return name;};
            std::string getDescription() {return description;};
            std::string getTab() {return tab;};
            OptionType getOptionType() {return optionType;};
    };

    void registerMod(Mod* mod, std::string tab);
    void createTab(std::string id, std::string name);

    std::vector<std::shared_ptr<Mod>> getMods();
    std::map<std::string, std::string> getTabs();
    std::vector<std::shared_ptr<Mod>> getModsInTab(std::string tab);
}

#define REGISTER_MOD(mod, tab) $execute{ summit::mods::registerMod(mod, tab); }