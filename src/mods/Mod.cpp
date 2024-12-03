#include "Mod.hpp"

namespace summit::mods {
    static std::vector<std::shared_ptr<Mod>> mods;
    static std::map<std::string, std::string> tabs;

    void registerMod(Mod* mod) {
        mods.push_back(std::shared_ptr<Mod>(mod));
        mod->init();
    };

    void createTab(std::string id, std::string name) {
        tabs[id] = name;
    };

    std::vector<std::shared_ptr<Mod>> getMods() {
        return mods;
    };

    std::map<std::string, std::string> getTabs() {
        return tabs;
    };

    std::vector<std::shared_ptr<Mod>> getModsInTab(std::string tab) {
        std::vector<std::shared_ptr<Mod>> tabMods;
        for (auto mod : mods) {
            if (mod->getTab() == tab) {
                tabMods.push_back(mod);
            }
        }
        return tabMods;
    };

    std::shared_ptr<Mod> getMod(std::string id) {
        for (auto mod : mods) {
            if (mod->getId() == id) {
                return mod;
            }
        }
        return nullptr;
    };
}