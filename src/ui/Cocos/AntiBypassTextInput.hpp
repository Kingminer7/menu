#pragma once

using namespace geode::prelude;

namespace summit::cocosui {
    class ABTextInput : public TextInput {
        protected:
            bool init(float width, const std::string &placeholder, const std::string &font) {
                if (!TextInput::init(width, placeholder, font)) {
                    return false;
                }
                allowedChars = m_input->m_allowedChars;
                scheduleUpdate();
                return true;
            }
            std::string allowedChars;

        public:
            static ABTextInput *create(float width, const std::string &placeholder, const std::string &font) {
                auto ret = new ABTextInput();
                if (ret) {
                    if (ret->init(width, placeholder, font)) {
                        ret->autorelease();
                        return ret;
                    }
                }
                CC_SAFE_DELETE(ret);
                return nullptr;
            }

            void setAllowedChars(std::string chars) {
                m_input->setAllowedChars(chars);
                allowedChars = chars;
            };

            void update(float dt) override {
                m_input->setAllowedChars(allowedChars);
            }
    };
}