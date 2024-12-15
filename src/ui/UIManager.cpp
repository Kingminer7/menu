#include "UIManager.hpp"
#include <imgui-cocos.hpp>
#include "imgui/FontManager.hpp"
#include "../Summit.hpp"

namespace summit::ui {
    std::map<std::string, UIStyle*> styles = {};
    UIStyle* currentStyle = nullptr;
    float uiScale = 1.f;

    float getUIScale() {
        return uiScale;
    }

    void setUIScale(float scale) {
        uiScale = scale;
    }

    void registerStyle(UIStyle* style) {
        styles[style->getName()] = style;
    }

    UIStyle* getStyle(std::string type, std::string style) {
        return styles[style];
    }

    std::vector<std::string> getStyles() {
        std::vector<std::string> styleNames;
        for (auto& [name, style] : styles) {
            styleNames.push_back(name);
        }
        return styleNames;
    }

    void setStyle(std::string style) {
        if (styles.find(style) == styles.end()) {
            geode::log::warn("Could not find style {}", style);
            return;
        }
        currentStyle = styles[style];
    }

    UIStyle* getCurrentStyle() {
        return currentStyle;
    }
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        for (auto& [name, style] : summit::ui::styles) {
            style->init();
        }

        summit::ui::imgui::init();

        summit::ui::setStyle(summit::Config::getValue<std::string>("config.uistyle", "ImGui Tabbed"));
    }).draw([] {
        for (auto& [name, style] : summit::ui::styles) {
        }
        if (summit::ui::getCurrentStyle() != nullptr)
            summit::ui::getCurrentStyle()->draw();
    }); 
}
