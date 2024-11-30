#include "MenuButton.hpp"
#include "../utils/Summit.hpp"
#include "CocosMenu.hpp"

using namespace summit::ui;
using namespace geode::prelude;

bool initialized = false;

namespace summit::ui {

MenuButton *MenuButton::instance = nullptr;

bool MenuButton::init() {
  if (!CCMenu::init()) {
    return false;
  }

  instance = this;

  m_sprite = CCSprite::createWithSpriteFrameName("summitBtn.png"_spr);
  m_sprite->setScale(.4f);
  m_sprite->setID("sprite");
  addChild(m_sprite);
  setContentSize(m_sprite->getScaledContentSize());
  setContentSize(m_sprite->getScaledContentSize());
  m_sprite->setPosition(getContentSize() / 2);

  CCScene::get()->addChild(this);
  SceneManager::get()->keepAcrossScenes(this);

  setZOrder(9999999);
  setPosition({
    Menu::get()->getModValue<float>("ballPosX").unwrapOrDefault(),
    Menu::get()->getModValue<float>("ballPosY").unwrapOrDefault()
  });

  setID("summit-button"_spr);

  return true;
}

MenuButton *MenuButton::get() {
  if (instance)
    return instance;
  auto ret = new MenuButton();
  if (ret && ret->init()) {
    ret->autorelease();
    return ret;
  } else {
    delete ret;
    return nullptr;
  }
}

void MenuButton::registerWithTouchDispatcher() {
  CCTouchDispatcher::get()->addTargetedDelegate(this, -1234, true);
}

bool MenuButton::ccTouchBegan(CCTouch *touch, CCEvent *evt) {
  move = false;
  startPos = new CCPoint(touch->getLocation());
  if (getScaledContentSize().width / 2 <
      ccpDistance(m_sprite->getPosition(),
                  convertToNodeSpace(touch->getLocation()))) {
    log::info("Not within distance");
    return false;
  }
  return true;
}

void MenuButton::ccTouchEnded(CCTouch *touch, CCEvent *evt) {
  if (move)
    return;
  onPress();
}

void MenuButton::ccTouchMoved(CCTouch *touch, CCEvent *evt) {
  if (!move)
    if (ccpDistance(*startPos, touch->getLocation()) > 3)
      move = true;
  if (move) {
    auto pos = getPosition() + touch->getDelta();
    pos.x = std::clamp(pos.x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
    pos.y = std::clamp(pos.y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
    setPosition(pos);
    summit::Menu::get()->setModValue("ballPosX", pos.x);
    summit::Menu::get()->setModValue("ballPosY", pos.y);
  }
}

void MenuButton::onPress() { 
  CocosMenu::open();
 }

} // namespace summit::ui

// Hooks

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer){bool init(){if (!MenuLayer::init()) return false;
// haha init
if (!initialized) {
  MenuButton::get();
  initialized = true;
}
return true;
}
}
;