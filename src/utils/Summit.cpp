#include "Summit.hpp"

namespace summit {

Menu *Menu::instance = nullptr;

Menu *Menu::get() {
  if (instance)
    return instance;
  instance = new Menu();
    return instance;
}

bool Menu::createTab(std::string id, std::string name) {
  for (auto &tab : tabs)
    if (tab.id == id)
      return false;
  Tab tab = {};
  tab.name = name;
  tab.id = id;
  tabs.push_back(tab);
  return true;
}

std::vector<Tab> Menu::getTabs() {
  return tabs;
}

bool Menu::removeTab(std::string id) {
  for (auto it = tabs.begin(); it != tabs.end(); it++)
    if (it->id == id) {
      tabs.erase(it);
      return true;
    }
  return false;
}

bool Menu::registerMod(std::string tab, SMod mod) {
  for (auto &t : tabs)
    if (t.id == tab) {
      t.mods.push_back(mod);
      return true;
    }
  return false;
}

bool Menu::unregisterMod(std::string tab, std::string id) {
  for (auto &t : tabs)
    if (t.id == tab) {
      for (auto it = t.mods.begin(); it != t.mods.end(); it++)
        if (it->id == id) {
          t.mods.erase(it);
          return true;
        }
    }
  return false;
}

} // namespace summit

$on_mod(Loaded) {
  summit::Menu::get()->createTab("global", "Global");
  summit::Menu::get()->createTab("player", "Player");
  summit::Menu::get()->createTab("bypass", "Bypass");
  summit::Menu::get()->createTab("creator", "Creator");
  summit::Menu::get()->createTab("level", "Level");
  summit::Menu::get()->createTab("settings", "Settings");
  
  auto s = summit::SMod();
  s.id = "test";
  s.name = "Test";
  s.description = "This is a test mod";
  summit::Menu::get()->registerMod("global", s);
}