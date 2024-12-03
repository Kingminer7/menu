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
            std::string valueName;
            OptionType optionType;
        public:
            virtual ~Mod() = default;
            virtual void init() = 0;
            virtual void update() = 0;

            virtual bool isCheat() {return false;};
            std::string getId() {return id;};
            std::string getName() {return name;};
            std::string getDescription() {return description;};
            std::string getTab() {return tab;};
            std::string getValueName() {return valueName;};
            OptionType getOptionType() {return optionType;};
    };

    void registerMod(Mod* mod);
    void createTab(std::string id, std::string name);

    std::vector<std::shared_ptr<Mod>> getMods();
    std::unordered_map<std::string, std::string> getTabs();
    std::vector<std::shared_ptr<Mod>> getModsInTab(std::string tab);
}

#define REGISTER_MOD(mod) $execute{ summit::mods::registerMod(mod); }