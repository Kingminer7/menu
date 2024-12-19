#pragma once

namespace summit::ui::widgets {

  struct Component {
    std::string id;
  };
  struct Toggle : Component {
    bool toggled = false;
    std::function<void(bool toggled)> callback;
  };
  struct Button : Component {
    std::function<void()> callback;
  };
  struct Input : Component {
    std::string value;
    // text, integer, float. anything else is custom and will be the limiting chars
    std::string type = "text";
    int maxChars = 0;
    std::function<void(std::string value)> callback;
  };

  class Widget {
    protected:
      std::string m_id;
      std::string m_label;
      std::string m_description;
      std::string m_tab;
      std::vector<Component*> m_components;
      Widget(std::string id) {
        m_id = id;
      }
    public:
      // these all return the widget so you can call things like myWidget->addThing()->setThat() etc
      // @brief Adds a toggle to the widget
      Widget *addToggle(std::string id, std::function<void(bool toggled)> callback, bool default_);
      // @brief Adds a button to the widget
      Widget *addButton(std::string id, std::function<void()> callback);
      // @brief Adds an input to the widget
      Widget *addInput(std::string id, std::function<void(std::string value)> callback, std::string type, int maxChars, std::string default_);

      // @brief Removes a component from the widget.
      Widget *remove(std::string id);

      // @brief Sets the label of the widget
      Widget *setLabel(std::string label);
      // @brief Sets the description of the widget
      Widget *setDescription(std::string desc);
      
      // @brief Register this option to a tab in the UI
      Widget *registerOption(std::string tab);
      // @brief Unregister this option from the UI
      Widget *unregisterOption();

      // @brief Get the ID of the widget
      std::string getId();

      // @brief Get the label of the widget
      std::string getLabel();
      // @brief Get the description of the widget
      std::string getDescription();
      // @brief Get the tab of the widget
      std::string getTab();
      // @brief Get the components of the widget
      std::vector<Component*> getComponents();
      // @brief Get a component by ID
      Component *getComponent(std::string id);

      void imRender();
      cocos2d::CCNode *createCocosNode();

      // @brief Create a new widget
      static Widget *create(std::string id);
  };
}