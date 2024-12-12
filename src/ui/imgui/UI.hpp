#pragma once

namespace summit::ui::imgui {
    class UI {
        protected:
            UI(){};
            static UI* instance;
        public:
            static UI* get();
            
            void draw();
    };

    // @brief Shortcut to get the UI instance
    UI *get() {
        return UI::get();
    }
}