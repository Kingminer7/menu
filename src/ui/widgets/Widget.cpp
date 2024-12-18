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

  Widget *Widget::registerOption() {
    return this;
  }

  Widget *Widget::unregisterOption() {
    return this;
  }
}