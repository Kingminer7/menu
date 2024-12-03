#pragma once

using namespace geode::prelude;

namespace summit::cocosui {
    class OptionNode : public CCMenu {
    protected:
        std::string m_id;
        std::string m_name;
        std::string m_description;
    public:
        std::string getID();
        std::string getName();
        std::string getDescription();

        static OptionNode *create(std::string id, std::string name, std::string description = "");
    };
}