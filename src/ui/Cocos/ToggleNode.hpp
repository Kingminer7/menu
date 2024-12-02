#pragma once

#include "OptionNode.hpp"

using namespace geode::prelude;

namespace summit::cocosui {
    class ToggleNode : public OptionNode {
        protected:
            bool init();
        public:
            void onToggle(CCObject *sender);
            CCLabelBMFont *m_label;
            CCMenuItemToggler *m_toggler;
            static ToggleNode *create(std::string id, std::string name, std::string description = "");
    };
}