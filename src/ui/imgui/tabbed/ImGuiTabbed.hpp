#pragma once

#include "../../UIManager.hpp"

namespace summit::ui::imgui::tabbed {
    class ImGuiTabbed : public UIStyle {
        protected:
            bool visible = true;
        public:
            void init() override;
            std::string getName() override;
            void open() override;
            void close() override;
            void draw() override;
    };
}

REGISTER_STYLE(summit::ui::imgui::tabbed::ImGuiTabbed);