#pragma once

using namespace geode::prelude;

namespace summit::ui {
class CocosMenu : public Popup<> {
protected:
  bool setup() override;
  static CocosMenu *create();
public:
  static void open();
  static CocosMenu *get();
};
}