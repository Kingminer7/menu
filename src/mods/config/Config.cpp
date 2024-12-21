#include <imgui-cocos.hpp>
#include "../../Summit.hpp"
#include "../../ui/imgui/FontManager.hpp"
#include "../../ui/UIManager.hpp"
#include "Config.hpp"

void ConfigMods::init() {
    summit::Config::setValueIfUnset<bool>("config.showball", false);
    showBall = summit::Config::getValue<bool>("config.showball", false);

    summit::Config::setValueIfUnset<float>("config.uiscale", 1.f);
    uiScale = summit::Config::getValue<float>("config.uiscale", 1.f);
    summit::ui::setUIScale(uiScale);

    summit::Config::setValueIfUnset<std::string>("config.font", "Carme");
    summit::Config::setValueIfUnset<std::string>("config.fontstyle", "Regular");
    currentFont = summit::Config::getValue<std::string>("config.font", "Carme");
    currentFontStyle = summit::Config::getValue<std::string>("config.fontstyle", "Regular");
    geode::log::info("Selected font: {}", currentFont);
    geode::queueInMainThread([this]() {
        summit::ui::imgui::setFont(currentFont, currentFontStyle);
    });

    #ifndef GEODE_IS_ANDROID
    auto widget = summit::ui::widgets::Widget::create("config.showball")
        ->addToggle("config.showball.toggle", [this](bool toggled) {
            onShowBall(toggled);
        }, &showBall)
        ->setLabel("Show Ball")
        ->setDescription("Show the ball to open the menu.")
        ->setTab("Config");
    summit::ui::registerWidget(widget);
    #endif

    auto widget2 = summit::ui::widgets::Widget::create("config.uiscale")
        ->addFloatInput("config.uiscale.input", [this](float value) {
            onUiScale(value);
        }, "input", uiScale, 0.1f, 2.f)
        ->setLabel("UI Scale")
        ->setDescription("Change the scale of the UI.")
        ->setTab("Config");
    summit::ui::registerWidget(widget2);

    std::map<std::string, std::pair<std::string, std::string>> fonts;
    for (auto font : summit::ui::imgui::getFonts()) {
        fonts[font] = {font, "Regular"};
    }

    auto widget3 = summit::ui::widgets::Widget::create("config.font")
        ->setLabel("Font")
        ->setDescription("Change the font of the UI.")
        ->addDropdown("config.font.dropdown", [this](int selected) {
            currentFont = summit::ui::imgui::getFonts()[selected];
            geode::log::info("Selected font: {}", currentFont);
            summit::Config::setValue<std::string>("config.font", currentFont);
            geode::queueInMainThread([this]() {
                summit::ui::imgui::setFont(currentFont, currentFontStyle);
            });
        }, summit::ui::imgui::getFonts(), currentFont, fonts)
        ->setTab("Config");
    summit::ui::registerWidget(widget3);

    std::map<std::string, std::pair<std::string, std::string>> fontStyles;
    for (auto style : summit::ui::imgui::getFontStyles(currentFont)) {
        fontStyles[style] = {currentFont, style};
    }

    auto widget4 = summit::ui::widgets::Widget::create("config.fontstyle")
        ->setLabel("Font Style")
        ->setDescription("Change the style of the font.")
        ->addDropdown("config.fontstyle.dropdown", [this](int selected) {
            currentFontStyle = summit::ui::imgui::getFontStyles()[selected];
            summit::Config::setValue<std::string>("config.fontstyle", currentFontStyle);
            geode::queueInMainThread([this]() {
                summit::ui::imgui::setFont(currentFont, currentFontStyle);
            });
        }, summit::ui::imgui::getFontStyles(), currentFontStyle, fontStyles)
        ->setTab("Config");
    summit::ui::registerWidget(widget4);
}

void ConfigMods::update(float dt) {
    
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
    summit::ui::setUIScale(value);
}
