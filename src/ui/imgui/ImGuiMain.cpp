#include <imgui-cocos.hpp>
#include "ImGuiMain.hpp"
#include "../../Summit.hpp"
#include "../../mods/Mods.hpp"

namespace summit::ui::imgui {
    static float scale = 1.f;
    bool wasMouseDown = false;
    std::string dragging = "";
    ImVec2 dragOffset = ImVec2(0, 0);
    ImVec2 windowPos = ImVec2(30, 30);
    bool firstDraw = true;
    // font, style
    std::map<std::pair<std::string, std::string>, ImFont*> imfonts = {};

    void draw() {
        // TODO: this
        if (!summit::Config::getVisibility() || summit::Config::getUIType() != "imgui") return;
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoMove;
        for (auto tab : summit::mods::getTabs()) {
            ImGui::Begin(tab.c_str(), nullptr, window_flags);
            ImGui::SetWindowFontScale(1.f/3 * scale);
            ImGui::SetWindowSize(ImVec2(225.f * scale, 300.f * scale));
            if (firstDraw) {
                ImGui::SetWindowPos(windowPos);
                windowPos = ImVec2(windowPos.x + 235 * scale, windowPos.y);
            }
            auto drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(
                ImGui::GetWindowPos(),
                ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + ImGui::GetWindowHeight()),
                IM_COL32(47, 49, 66, 240)
            );
            drawList->AddRectFilled(
                ImGui::GetWindowPos(),
                ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 30 * scale),
                IM_COL32(0, 174, 255, 255)
            );
            if (ImGui::GetIO().MouseDown[0]) {
                if (wasMouseDown) {
                    if (dragging == tab) {
                        ImGui::SetWindowPos(ImVec2(ImGui::GetWindowPos().x + ImGui::GetIO().MouseDelta.x, ImGui::GetWindowPos().y + ImGui::GetIO().MouseDelta.y));
                    }
                } else {
                    if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 30 * scale))) {
                        dragging = tab;
                        dragOffset = ImVec2(ImGui::GetIO().MousePos.x - ImGui::GetWindowPos().x, ImGui::GetIO().MousePos.y - ImGui::GetWindowPos().y);
                    }
                }
            } else {
                wasMouseDown = false;
                dragging = "";
            }
            ImGui::SetWindowFontScale(.5f * scale);
            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize(tab.c_str()).x / 2, 4 * scale));
            ImGui::Text("%s", tab.c_str());
            ImGui::SetCursorPos(ImVec2(8, 38 * scale));
            ImGui::SetWindowFontScale(1.f/3 * scale);
            for (auto mod : summit::mods::getModsInTab(tab)) {
                mod.second->renderImGui();
            }
            ImGui::End();
        }
        firstDraw = false;
        if (ImGui::GetIO().MouseDown[0]) {
            wasMouseDown = true;
        }
    }

    std::string currentFont = "Carme";
    std::string currentFontStyle = "Regular";

    float getScale() {
        return scale;
    }

    void setScale(float newScale) {
        scale = newScale;
    }

    std::vector<std::string> fonts = {
        "Alegreya",
        "Assistant",
        "Carme",
        "Lato",
        "Montserrat",
        "Nunito",
        "OpenSans",
        "OpenSansCondensed",
        "OpenSansSemiCondensed",
        "Poppins",
        "Roboto",
        "SourceCodePro",
        "Ubuntu"
    };

    std::vector<std::string> fontStyles = {
        "Black",
        "BlackItalic",
        "Bold",
        "BoldItalic",
        "ExtraBold",
        "ExtraBoldItalic",
        "ExtraLight",
        "ExtraLightItalic",
        "Italic",
        "Light",
        "LightItalic",
        "Medium",
        "MediumItalic",
        "Regular",
        "SemiBold",
        "SemiBoldItalic",
        "Thin",
        "ThinItalic"
    };

    std::map<std::string, std::vector<std::string>> availableStyles = {
        {"Alegreya", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"Assistant", {"Bold", "ExtraBold", "ExtraLight", "Light", "Medium", "Regular", "SemiBold"}},
        {"Carme", {"Regular"}},
        {"Lato", {"Black", "BlackItalic", "Bold", "BoldItalic", "Italic", "Light", "LightItalic", "Regular", "Thin", "ThinItalic"}},
        {"Montserrat", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic", "Thin", "ThinItalic"}},
        {"Nunito", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"OpenSans", {"Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"OpenSansCondensed", {"Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"OpenSansSemiCondensed", {"Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic"}},
        {"Poppins", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic", "Thin", "ThinItalic"}},
        {"Roboto", {"Black", "BlackItalic", "Bold", "BoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "Thin", "ThinItalic"}},
        {"SourceCodePro", {"Black", "BlackItalic", "Bold", "BoldItalic", "ExtraBold", "ExtraBoldItalic", "ExtraLight", "ExtraLightItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular", "SemiBold", "SemiBoldItalic" }},
        {"Ubuntu", {"Bold", "BoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular"}}
    };

    bool setFont(std::string font, std::string style) {
        if (isFontStyleSupported(font, style)) {
            auto imfont = imfonts[{font, style}];
            ImGui::GetIO().FontDefault = imfont;
            return true;
        } else {
            geode::log::warn("Font style {} is not supported for font {}", style, font);
            if (imfonts.find({font, "Regular"}) == imfonts.end()) {
                geode::log::warn("Could not find regular font for {}", font);
                return false;
            }
            auto imfont = imfonts[{font, "Regular"}];
            
            ImGui::GetIO().FontDefault = imfont;
            return true;
        }
    }

    bool isFontStyleSupported(std::string font, std::string style) {
        return std::find(availableStyles[font].begin(), availableStyles[font].end(), style) != availableStyles[font].end();
    }

    std::vector<std::string> getFonts() {
        return fonts;
    }

    std::vector<std::string> getFontStyles() {
        return fontStyles;
    }

    std::vector<std::string> getFontStyles(std::string font) {
        return availableStyles[font];
    }

    void init() {
        for (auto& [font, styles] : availableStyles) {
            for (auto& style : styles) {
                if (!std::filesystem::exists(geode::Mod::get()->getResourcesDir() / (font + "-" + style + ".ttf"))) {
                    geode::log::warn("Could not find font file for {}-{}", font, style);
                    continue;
                }    
                auto* imfont = ImGui::GetIO().Fonts->AddFontFromFileTTF((geode::Mod::get()->getResourcesDir() / (font + "-" + style + ".ttf")).string().c_str(), 48.0f);
                imfonts[{font, style}] = imfont;
            }
        }
        if (imfonts.find({"Carme", "Regular"}) != imfonts.end())
            ImGui::GetIO().FontDefault = imfonts[{"Carme", "Regular"}];
    }

    std::map<std::pair<std::string, std::string>, ImFont*> getImFonts() {
        return imfonts;
    }

}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        summit::ui::imgui::init();
    }).draw([] {
        summit::ui::imgui::draw();
    });
}
