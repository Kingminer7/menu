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
      std::vector<Component*> m_components;
      Widget() {}
      void init() {}
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
      
      // @brief Register this option with the UI
      Widget *registerOption();
      // @brief Unregister this option with the UI
      Widget *unregisterOption();

      static Widget *create(std::string id) {
        return new Widget();
      }
  };
}