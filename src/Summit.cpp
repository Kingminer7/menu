#include "mods/Mods.hpp"
#include "Summit.hpp"

namespace summit {
    matjson::Value Config::config = matjson::Value::object();
    matjson::Value Config::temp = matjson::Value::object();
    bool Config::initialized = false;
    std::string Config::uiType = "";
    bool Config::isVisible = true;

    std::string Config::getUIType() {
        if (uiType == "") {
            Config::setValueIfUnset<std::string>("config.uitype", "imgui");
            uiType = Config::getValue<std::string>("config.uitype", "imgui");
        }
        return uiType;
    }

    void Config::setUIType(std::string type) {
        uiType = type;
        setValue<std::string>("config.uitype", type);
    }

    void Config::initialize() {
        if (!initialized) {
            config = matjson::parse(geode::Mod::get()->getSavedValue<std::string>("config")).unwrapOrDefault();
            temp = matjson::Value::object();
            initialized = true;
        } else {
            #ifdef GEODE_DEBUG
            geode::log::warn("Config already initialized!");
            #endif
        }
    }

    void Config::toggleVisibility() {
        isVisible = !isVisible;
    }
    bool Config::getVisibility() {
        return isVisible;
    }
}

UpdateManager *UpdateManager::get() {
    if (!instance) instance = new UpdateManager();
    return instance;
}

void UpdateManager::update(float dt)  {
    for (auto& [id, mod] : summit::mods::getMods()) {
        mod->update(dt);
    }
}

UpdateManager* UpdateManager::instance = nullptr;

$on_mod(Loaded) {
    // lol
    UpdateManager::get();
}