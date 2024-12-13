#pragma once

namespace summit::mods {
    class Mod {
        public:
            virtual void init() = 0;
            virtual void update() = 0;
            virtual void renderImGui() = 0;
            virtual std::string getId() const = 0;
            virtual std::string getTab() const = 0;
    };
    void registerMod(Mod *mod);
    std::unordered_map<std::string, Mod*> getMods();
    Mod* getMod(std::string id);

    void registerTab(std::string tab);
    std::vector<std::string> getTabs();
    std::unordered_map<std::string, Mod*> getModsInTab(std::string tab);

    #define REGISTER_MOD(mod) $execute{ summit::mods::registerMod(mod); }
    #define REGISTER_TAB(tab) $execute{ summit::mods::registerTab(tab); }
}