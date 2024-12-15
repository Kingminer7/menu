#pragma once

#include "../../UIManager.hpp"
#include <imgui-cocos.hpp>

namespace summit::ui::imgui::tabbed {
    class ImGuiTabbed : public UIStyle {
        protected:
            bool visible = false;
            bool render = false;
            bool wasMouseDown = false;
            std::string dragging = "";
            ImVec2 dragOffset = ImVec2(0, 0);
            ImVec2 windowPos = ImVec2(30, 30);
            bool firstDraw = true;
        public:
            void init() override;
            std::string getName() override;
            void open() override;
            void close() override;
            void toggle() override;
            void draw() override;
    };
}

REGISTER_STYLE(summit::ui::imgui::tabbed::ImGuiTabbed);