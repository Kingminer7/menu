#pragma once

#include <Geode/Geode.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

namespace summit {

class Menu {
protected:
  static Menu *instance;
  matjson::Value modData;
  Menu () {
    modData = Mod::get()->getSavedValue<matjson::Value>("modData");
  }

public:
  template <typename T> Result<T> getModValue(std::string key) {
    return modData.get<T>(key);
  }

  template <typename T> void setModValue(std::string key, T value) {
    modData.set(key, value);
    Mod::get()->setSavedValue<matjson::Value>("modData", modData);
  }

  static Menu *get();
};

} // namespace summit