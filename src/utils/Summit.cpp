#include "Summit.hpp"

namespace summit {

Menu *Menu::instance = nullptr;

Menu *Menu::get() {
  if (instance)
    return instance;
  instance = new Menu();
    return instance;
}

} // namespace summit

$on_mod(Loaded) {
  summit::mods::createTab("global", "Global");
  summit::mods::createTab("level", "Level");
  summit::mods::createTab("player", "Player");
  summit::mods::createTab("bypass", "Bypass");
}