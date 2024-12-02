#pragma once

using namespace geode::prelude;

namespace summit::cocosui {
    class OptionNode : public CCMenu {
    protected:
        std::string m_id;
    public:
        std::string getID();
        static OptionNode *create(const std::string &id);
    };
}