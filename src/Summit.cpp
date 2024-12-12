#include "Summit.hpp"

namespace summit {
    matjson::Value Config::config = matjson::Value::object();
    matjson::Value Config::temp = matjson::Value::object();
    bool Config::initialized = false;
    ui::UIType Config::uiType = ui::UIType::ImGui;

    ui::UIType Config::getUIType() {
        return uiType;
    }

    void Config::setUIType(ui::UIType type) {
        uiType = type;
    }
}

$on_mod(Loaded) {
    geode::log::info("{}", summit::Config::getValue<std::string>("awesome", "not awesome"));
}
