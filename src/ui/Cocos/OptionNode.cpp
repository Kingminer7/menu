#include "OptionNode.hpp"

namespace summit::cocosui {
    std::string OptionNode::getID() {
        return m_id;
    }

    std::string OptionNode::getName() {
        return m_name;
    }

    std::string OptionNode::getDescription() {
        return m_description;
    }

    OptionNode *OptionNode::create(std::string id, std::string name, std::string description) {
        auto ret = new OptionNode();
        if (ret && ret->init()) {
            ret->m_id = id;
            ret->m_name = name;
            ret->m_description = description;
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}