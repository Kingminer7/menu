#pragma once

#include <Geode/Geode.hpp>
#include <matjson.hpp>
#include "../mods/Mod.hpp"

using namespace geode::prelude;

namespace summit {

class Menu {
protected:
  static Menu* instance;
  matjson::Value modData;
  matjson::Value tempData;
  Menu() {
    modData = Mod::get()->getSavedValue<matjson::Value>("modData");
  }
  std::vector<summit::mods::Mod> mods;
public:
  template <typename T>
  Result<T> getModValue(std::string key) {
    return modData.get<T>(key);
  }

  template <typename T>
  void setModValue(std::string key, T value) {
    modData.set(key, value);
    Mod::get()->setSavedValue<matjson::Value>("modData", modData);
  }

  template <typename T>
  void setModValueIfMissing(std::string key, T value) {
    if (!modData.contains(key)) {
      modData.set(key, value);
      Mod::get()->setSavedValue<matjson::Value>("modData", modData);
    }
  }

  template <typename T>
  Result<T> getTempValue(std::string key) {
    return tempData.get<T>(key);
  }

  template <typename T>
  void setTempValue(std::string key, T value) {
    tempData.set(key, value);
  }

  template <typename T>
  void setTempValueIfMissing(std::string key, T value) {
    if (!tempData.contains(key)) {
      tempData.set(key, value);
    }
  }

  static Menu* get();
};

} // namespace summit