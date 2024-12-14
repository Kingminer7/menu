#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "Config.hpp"

void ConfigMods::init() {
    summit::Config::setValueIfUnset<bool>("config.showball", false);
    showBall = summit::Config::getValue<bool>("config.showball", false);
    lastShowBall = showBall;

    summit::Config::setValueIfUnset<float>("config.uiscale", 1.f);
    uiScale = summit::Config::getValue<float>("config.uiscale", 1.f);
    lastUiScale = uiScale;
    setScale(uiScale);

    summit::Config::setValueIfUnset<std::string>("config.font", "Carme");
    summit::Config::setValueIfUnset<std::string>("config.fontstyle", "Regular");
    currentFont = summit::Config::getValue<std::string>("config.font", "Carme");
    currentFontStyle = summit::Config::getValue<std::string>("config.fontstyle", "Regular");
    lastFont = currentFont;
    lastFontStyle = currentFontStyle;
    geode::queueInMainThread([this]() {
        setFont(currentFont, currentFontStyle);
    });
}

void ConfigMods::update(float dt) {
    
}

void ConfigMods::renderImGui() {
    #ifndef GEODE_IS_ANDROID
    ImGui::Checkbox("Show Ball", &showBall);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Show the ball to open the menu.");
    }
    if (showBall != lastShowBall) {
        onShowBall(showBall);
        lastShowBall = showBall;
    }
    #endif

    ImGui::InputFloat("UI Scale", &uiScale);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::SetTooltip("Change the scale of the UI.");
    }
    if (uiScale != lastUiScale) {
        onUiScale(uiScale);
        lastUiScale = uiScale;
    }

    // Dropdown of fonts
    if (ImGui::BeginCombo("Font", currentFont.c_str())) {
        for (auto font : getFonts()) {
            bool isSelected = (currentFont == font);
            setFont(font, "Regular");
            if (ImGui::Selectable(font.c_str(), isSelected)) {
                currentFont = font;
                summit::Config::setValue<std::string>("config.font", font);
            }
            ImGui::SameLine();
            ImGui::Text("%s", "test");
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        setFont(currentFont, currentFontStyle);
        ImGui::EndCombo();
    }

    // Dropdown of font styles usable with the current font
    if (ImGui::BeginCombo("Font Style", currentFontStyle.c_str())) {
        for (auto style : getFontStyles(currentFont)) {
            bool isSelected = (currentFontStyle == style);
            setFont(currentFont, style);
            if (ImGui::Selectable(style.c_str(), isSelected)) {
                currentFontStyle = style;
                summit::Config::setValue<std::string>("config.fontstyle", style);
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        setFont(currentFont, currentFontStyle);
        ImGui::EndCombo();
    }
}

std::string ConfigMods::getId() const {
    return "config";
}

std::string ConfigMods::getTab() const {
    return "Config";
}

void ConfigMods::onShowBall(bool value) {
    summit::Config::setValue<bool>("config.showball", value);
}

void ConfigMods::onUiScale(float value) {
    summit::Config::setValue<float>("config.uiscale", value);
    setScale(value);
}
