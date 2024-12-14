#pragma once

namespace summit::ui::imgui {
    void draw();
    void init();

    float getScale();
    void setScale(float newScale);
    
    std::vector<std::string> getFonts();
    std::vector<std::string> getFontStyles();
    std::vector<std::string> getFontStyles(std::string font);
    std::map<std::pair<std::string, std::string>, ImFont*> getImFonts();
    bool setFont(std::string font, std::string style);
    bool pushFont(std::string font, std::string style);
    void popFont();
    bool isFontStyleSupported(std::string font, std::string style);
}
