#pragma once

using namespace geode::prelude;

namespace summit::cocosui {
class CocosMenu : public Popup<> {
protected:
  bool setup() override;
  static CocosMenu *create();
  CCMenu *tabBtnMenu;
  CCMenuItemSpriteExtra *m_backBtn;
  
  std::vector<ScrollLayer *> m_menus;
  std::vector<CCMenuItemSpriteExtra *> m_menuBtns;
  std::string m_currentMenu;
public:
  void show() override;
  static void open(bool closeIfOpen = false);
  static CocosMenu *get();
  void onTab(CCObject *sender);
};
}