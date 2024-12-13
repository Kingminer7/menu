#include <imgui-cocos.hpp>
#include "Widget.hpp"

namespace summit::ui::widgets {
  Widget *Widget::addToggle(std::string id, std::function<void(bool toggled)> callback, bool default_) {
    m_components.push_back(new Toggle{id, default_, callback});
    return this;
  }

  Widget *Widget::addButton(std::string id, std::function<void()> callback) {
    m_components.push_back(new Button{id, callback});
    return this;
  }

  Widget *Widget::addInput(std::string id, std::function<void(std::string value)> callback, std::string type, int maxChars, std::string default_) {
    m_components.push_back(new Input{id, default_, type, maxChars, callback});
    return this;
  }

  Widget *Widget::remove(std::string id) {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
      if ((*it)->id == id) {
        m_components.erase(it);
        delete *it;
        break;
      }
    }
    return this;
  }

  Widget *Widget::setLabel(std::string label) {
    m_label = label;
    return this;
  }

  Widget *Widget::setDescription(std::string desc) {
    m_description = desc;
    return this;
  }

  Widget *Widget::registerOption(std::string tab) {
    return this;
  }

  Widget *Widget::unregisterOption() {
    return this;
  }


  std::string Widget::getId() {
    return m_id;
  }

  std::string Widget::getLabel() {
    return m_label;
  }

  std::string Widget::getDescription() {
    return m_description;
  }

  std::string Widget::getTab() {
    return m_tab;
  }

  std::vector<Component*> Widget::getComponents() {
    return m_components;
  }

  Component *Widget::getComponent(std::string id) {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
      if ((*it)->id == id) {
        return *it;
      }
    }
    return nullptr;
  }

  void Widget::imRender() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
      if (Toggle *t = static_cast<Toggle*>(*it)) {
        ImGui::Checkbox(t->id.c_str(), &t->toggled);
         
      }
    }
  }

  cocos2d::CCNode *Widget::createCocosNode() {
    return nullptr;
  }

  Widget *Widget::create(std::string id) {
    return new Widget(id);
  }
  
}