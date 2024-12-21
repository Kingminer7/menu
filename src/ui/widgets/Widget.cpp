#include <imgui-cocos.hpp>
#include "Widget.hpp"

namespace summit::ui::widgets
{
  Widget *Widget::addToggle(std::string id, std::function<void(bool toggled)> callback, bool *toggleVal)
  {
    m_components.push_back(new Toggle{id, "Toggle", toggleVal, callback});
    return this;
  }

  Widget *Widget::addButton(std::string id, std::function<void()> callback)
  {
    m_components.push_back(new Button{id, "Button", callback});
    return this;
  }

  Widget *Widget::addFloatInput(std::string id, std::function<void(float value)> callback, std::string inputType, float value, float min, float max)
  {
    m_components.push_back(new FloatInput{id, "FloatInput", value, callback, min, max, inputType});
    return this;
  }

  Widget *Widget::remove(std::string id)
  {
    for (auto it = m_components.begin(); it != m_components.end(); it++)
    {
      if ((*it)->id == id)
      {
        m_components.erase(it);
        delete *it;
        break;
      }
    }
    return this;
  }

  Widget *Widget::setLabel(std::string label)
  {
    m_label = label;
    return this;
  }

  Widget *Widget::setDescription(std::string desc)
  {
    m_description = desc;
    return this;
  }

  Widget *Widget::setTab(std::string tab) {
    m_tab = tab;
    return this;
  }

  Widget *Widget::registerOption(std::string tab)
  {
    return this;
  }

  Widget *Widget::unregisterOption()
  {
    return this;
  }

  std::string Widget::getId()
  {
    return m_id;
  }

  std::string Widget::getLabel()
  {
    return m_label;
  }

  std::string Widget::getDescription()
  {
    return m_description;
  }

  std::string Widget::getTab()
  {
    return m_tab;
  }

  std::vector<Component *> Widget::getComponents()
  {
    return m_components;
  }

  Component *Widget::getComponent(std::string id)
  {
    for (auto it = m_components.begin(); it != m_components.end(); it++)
    {
      if ((*it)->id == id)
      {
        return *it;
      }
    }
    return nullptr;
  }

  void Widget::imRender() {
    int i = 0;
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
      if (i > 0) ImGui::SameLine();
      i++;
      if ((*it)->type == "Toggle") {
        Toggle *t = static_cast<Toggle*>(*it);
        ImGui::Checkbox(fmt::format("##{}", t->id).c_str(), t->toggled);
        if (*t->toggled != t->lastToggled) {
          t->lastToggled = *t->toggled;
          t->callback(*t->toggled);
        }
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else if ((*it)->type == "Button") {
        Button *b = static_cast<Button*>(*it);
        if (ImGui::Button(b->id.c_str())) {
          b->callback();
        }
        
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else if ((*it)->type == "FloatInput") {
        FloatInput *f = static_cast<FloatInput*>(*it);
        if (f->inputType == "input") {
          ImGui::SetNextItemWidth(70);
          ImGui::InputFloat(fmt::format("##{}", f->id).c_str(), &f->value);
        } else if (f->inputType == "slider") {
          ImGui::SetNextItemWidth(70);
          ImGui::SliderFloat(fmt::format("##{}", f->id).c_str(), &f->value, f->min, f->max);
        } else if (f->inputType == "step") {
          ImGui::SetNextItemWidth(70);
          ImGui::DragFloat(fmt::format("##{}", f->id).c_str(), &f->value, 0.1f, f->min, f->max);
        }
        if (f->value != f->lastValue) {
          f->lastValue = f->value;
          f->callback(f->value);
        }
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else {
        geode::log::warn("Component {} in {} has an unrecognized component type: {}!", (*it)->id, m_id, (*it)->type);
      }
    }
    if (!m_label.empty())
    {
      if (i > 0) ImGui::SameLine();
      ImGui::Text("%s", m_label.c_str());
    }
    if (!m_description.empty())
    {
      if (ImGui::IsItemHovered())
      {
        ImGui::BeginTooltip();
        ImGui::Text("%s", m_description.c_str());
        ImGui::EndTooltip();
      }
    }
  }

  cocos2d::CCNode *Widget::createCocosNode()
  {
    return nullptr;
  }

  Widget *Widget::create(std::string id)
  {
    return new Widget(id);
  }

}
