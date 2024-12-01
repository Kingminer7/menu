#pragma once

#include <Geode/Geode.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

namespace summit {

class SMod {
  public:
    std::string id;
    std::string name;
    std::string description;
    CCNode *createNode() {
      throw std::runtime_error("createNode not implemented");

    }
};

struct Tab {
  std::string id;
  std::string name;
  std::vector<SMod> mods;
};

class Menu {
protected:
  static Menu* instance;
  matjson::Value modData;
  matjson::Value tempData;
  Menu() {
    modData = Mod::get()->getSavedValue<matjson::Value>("modData");
  }
  std::vector<Tab> tabs;
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
  Result<T> getTempValue(std::string key) {
    return tempData.get<T>(key);
  }

  template <typename T>
  void setTempValue(std::string key, T value) {
    tempData.set(key, value);
  }

  bool createTab(std::string id, std::string name);
  std::vector<Tab> getTabs();
  bool removeTab(std::string id);

  bool registerMod(std::string tab, SMod mod);
  bool unregisterMod(std::string tab, std::string id);

  static Menu* get();
};

} // namespace summit