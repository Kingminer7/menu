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

      Widget *remove(std::string id);

      // @brief Sets the label of the widget
      Widget *setLabel(std::string label);
      // @brief Sets the description of the widget
      Widget *setDescription(std::string desc);
      
      // @brief Register this option to a tab in the UI
      Widget *registerOption(std::string tab);
      // @brief Unregister this option from the UI
      Widget *unregisterOption();

      // @brief Create a new widget
      static Widget *create(std::string id) {
        return new Widget(id);
      }
  };
}