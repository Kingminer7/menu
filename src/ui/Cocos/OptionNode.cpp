#include "OptionNode.hpp"

namespace summit::cocosui {
    std::string OptionNode::getID() {
        return m_id;
    }

    OptionNode *OptionNode::create(const std::string &id) {
        auto ret = new OptionNode();
        if (ret && ret->init()) {
            ret->m_id = id;
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}