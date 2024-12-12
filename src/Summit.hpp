#pragma once

#include <Geode/Geode.hpp>
#include "HookManager.hpp"

namespace summit {
    namespace ui {
        enum class UIType {
            ImGui,
            Cocos
        };
    }
    class Config {
        private:
            Config() {};
        protected:
            static matjson::Value config;
            static matjson::Value temp;
            static bool initialized;
            static ui::UIType uiType;
        public:
            static void initialize() {
                if (!initialized) {
                    config = geode::Mod::get()->getSavedValue<matjson::Value>("config");
                    temp = matjson::Value::object();
                    initialized = true;
                } else {
                    geode::log::warn("Config already initialized!");
                }
            }
            template <typename T>
            static void setValue(std::string key, T value, bool saved = true) {
                if (saved) {
                    config.set(key, value);
                    geode::Mod::get()->setSavedValue<matjson::Value>("config", config);
                }
                else temp.set(key, value);
            }


            template <typename T>
            static void setValueIfUnset(std::string key, T value, bool saved = true) {
                if (saved) {
                    if (!config.contains(key)) {
                        config.set(key, value);
                        geode::Mod::get()->setSavedValue<matjson::Value>("config", config);
                    }
                }
                else if (!temp.contains(key)) temp.set(key, value);
            }

            template <typename T>
            static T getValue(std::string key, T defaultValue, bool saved = true) {
                if (saved) return config.get<T>(key).unwrapOr(defaultValue);
                else return temp.get<T>(key).unwrapOr(defaultValue);
            }

            static void setUIType(ui::UIType type);
            static ui::UIType getUIType();
    };
}