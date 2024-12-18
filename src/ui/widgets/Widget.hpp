namespace summit::ui::widgets {
  class Widget {
    protected:
      std::map<std::string, std::function<void(bool toggled)>> callbacks;
    public:
      // these all return the widget so you can call things like myWidget->addThing()->setThat() etc
      Widget *addToggle(bool default, std::string id, std::function<void(bool toggled)> callback);
  };
}