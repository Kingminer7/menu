#include "MenuButton.hpp"
#include "../../utils/Summit.hpp"
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

  setZOrder(9999998);
  auto x = Menu::get()->getModValue<float>("ballPosX").unwrapOrDefault();
  auto y = Menu::get()->getModValue<float>("ballPosY").unwrapOrDefault();
  x = std::clamp(x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
  y = std::clamp(y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
  setPosition({x, y});
  Menu::get()->setModValue("ballPosX", x);
  Menu::get()->setModValue("ballPosY", y);

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
  CCTouchDispatcher::get()->addTargetedDelegate(this, -9999999, true);
}

bool MenuButton::ccTouchBegan(CCTouch *touch, CCEvent *evt) {
  diff = getPosition() - touch->getLocation();
  startPos = new CCPoint(touch->getLocation());
  if (getScaledContentSize().width / 2 <
      ccpDistance(m_sprite->getPosition(),
                  convertToNodeSpace(touch->getLocation()))) {
    return false;
  }
  move = false;
  
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale * m_multiplier)));
  return true;
}

void MenuButton::ccTouchEnded(CCTouch *touch, CCEvent *evt) {
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale)));
  if (move)
    return;
  onPress();
}

void MenuButton::ccTouchMoved(CCTouch *touch, CCEvent *evt) {
  if (!move)
    if (ccpDistance(*startPos, touch->getLocation()) > 3)
      move = true;
  if (move) {
    auto pos = touch->getLocation() + diff;
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

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer){
  bool init(){
    if (!MenuLayer::init()) return false;
    if (!initialized) {
      MenuButton::get();
      initialized = true;
    }
    return true;
  }
};

#include <Geode/modify/CCScene.hpp>

class $modify(CCScene) {
  int getHighestChildZ() {
    int btnZ;
    auto btn = MenuButton::get();
    if (btn) {
      btnZ = btn->getZOrder();
      btn->setZOrder(-1);
    }
    auto highest = CCScene::getHighestChildZ();
    if (btn) btn->setZOrder(btnZ);
    return highest;
  }
};