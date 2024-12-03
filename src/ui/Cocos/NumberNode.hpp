#pragma once

#include "OptionNode.hpp"

using namespace geode::prelude;

namespace summit::cocosui {
    class NumberNode : public OptionNode {
        protected:
            bool init();
        public:
            float m_value = 0;
            void onInput(std::string input);
            CCLabelBMFont *m_label;
            TextInput *m_input;
            static NumberNode *create(std::string id, std::string name, std::string description = "");
    };
}