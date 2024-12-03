#include "ToggleNode.hpp"
#include "../../utils/Summit.hpp"

namespace summit::cocosui {
bool ToggleNode::init() {
  if (!OptionNode::init()) {
    return false;
  }
  setAnchorPoint({0, 0});
  setContentSize({150, 30});

  m_label = CCLabelBMFont::create(m_name.c_str(), "bigFont.fnt");
  m_label->limitLabelWidth(115, .8f, 0.01f);
  m_label->setAnchorPoint({0, 0.5f});
  addChildAtPosition(m_label, Anchor::Left, {5, 2.5});

  m_toggler = CCMenuItemToggler::createWithStandardSprites(
      this, menu_selector(ToggleNode::onToggle), 0.675f);
  m_toggler->setID("toggler"_spr);
  m_toggler->toggle(summit::Menu::get()->getModValue<bool>(m_id).unwrapOrDefault());
  m_toggler->updateSprite();
  addChildAtPosition(m_toggler, Anchor::Right, {-15 , 2.5});

  return true;
}

ToggleNode *ToggleNode::create(std::string id, std::string name,
                               std::string description) {
  auto ret = new ToggleNode();
  if (ret) {
    ret->m_id = id;
    ret->m_name = name;
    ret->m_description = description;
    if (ret->init()) {
      ret->autorelease();
      return ret;
    }
  }
  CC_SAFE_DELETE(ret);
  return nullptr;
}

void ToggleNode::onToggle(CCObject *sender) {
  auto toggler = dynamic_cast<CCMenuItemToggler *>(sender);
  if (toggler) {
    summit::Menu::get()->setModValue<bool>(m_id, !toggler->isToggled());
  }
}
} // namespace summit::cocosui