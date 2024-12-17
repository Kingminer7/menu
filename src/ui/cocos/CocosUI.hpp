#pragma once

#include "../../UIManager.hpp"
#include <imgui-cocos.hpp>

namespace summit::ui::cocos {
    class CocosUI : public UIStyle {
        protected:
            bool visible = false;
        public:
            void init() override;
            std::string getName() override;
            void open() override;
            void close() override;
            void toggle() override;
            void draw() override;
    };
}

REGISTER_STYLE(summit::ui::cocos::CocosUI);