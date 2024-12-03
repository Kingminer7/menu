#include "NumberNode.hpp"
#include "AntiBypassTextInput.hpp"
#include "../../utils/Summit.hpp"

namespace summit::cocosui {
bool NumberNode::init() {
  if (!OptionNode::init()) {
    return false;
  }
  setAnchorPoint({0, 0});
  setContentSize({150, 30});

  m_label = CCLabelBMFont::create(m_name.c_str(), "bigFont.fnt");
  m_label->limitLabelWidth(95, .8f, 0.01f);
  m_label->setAnchorPoint({0, 0.5f});
  addChildAtPosition(m_label, Anchor::Left, {5, 2.5});

  m_value = summit::Menu::get()->getModValue<float>(m_id).unwrapOrDefault();
  m_input = ABTextInput::create(60.f, "Speed", "bigFont.fnt");
  m_input->setID("input"_spr);
  m_input->setScale(2.f/3);
  m_input->setString(fmt::format("{}", m_value));
  m_input->getInputNode()->setAllowedChars("1234567890.");
  m_input->setCallback([this](std::string str) {
    onInput(str);
  });
  addChildAtPosition(m_input, Anchor::Right, {-25 , 2.5});

  return true;
}

NumberNode *NumberNode::create(std::string id, std::string name,
                               std::string description) {
  auto ret = new NumberNode();
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

void NumberNode::onInput(std::string input) {
  m_value = std::stof(input);
  summit::Menu::get()->setModValue(m_id, m_value);
}
} // namespace summit::cocosui