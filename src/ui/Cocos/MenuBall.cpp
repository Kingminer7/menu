#include "MenuBall.hpp"
#include "../../utils/Summit.hpp"
#include "CocosMenu.hpp"

using namespace summit::cocosui;
using namespace geode::prelude;

bool initialized = false;

namespace summit::cocosui {

MenuBall *MenuBall::instance = nullptr;

bool MenuBall::init() {
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

MenuBall *MenuBall::get() {
  if (instance)
    return instance;
  auto ret = new MenuBall();
  if (ret && ret->init()) {
    ret->autorelease();
    return ret;
  } else {
    delete ret;
    return nullptr;
  }
}

void MenuBall::registerWithTouchDispatcher() {
  CCTouchDispatcher::get()->addTargetedDelegate(this, -9999999, true);
}

bool MenuBall::ccTouchBegan(CCTouch *touch, CCEvent *evt) {
  if (CocosMenu::get()) return false;
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

void MenuBall::ccTouchEnded(CCTouch *touch, CCEvent *evt) {
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale)));
  if (move)
    return;
  onPress();
}

void MenuBall::ccTouchMoved(CCTouch *touch, CCEvent *evt) {
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

void MenuBall::onPress() { 
  CocosMenu::open();
 }

} // namespace summit::cocosui

bool firstML = false;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer){
  bool init(){
    if (!MenuLayer::init()) return false;
    if (!initialized) {
      MenuBall::get();
      initialized = true;
    }
    if (!firstML && summit::Menu::get()->getModValue<bool>("shownAlphaMessage").unwrapOrDefault() == false && Mod::get()->getVersion().getTag()->value == VersionTag::Alpha) {
      firstML = true;
      queueInMainThread([this]() {
        geode::createQuickPopup("Summit Menu", "Alpha builds will rarely recieve support. Bugs you find are more than likely already known or fixed.", "Ok", "Do not show again", [this](auto, bool dontShow) {
        if (dontShow) summit::Menu::get()->setModValue("shownAlphaMessage", true);
      });
      });
    }
    return true;
  }
};

#include <Geode/modify/CCScene.hpp>

class $modify(CCScene) {
  int getHighestChildZ() {
    int btnZ;
    auto btn = MenuBall::get();
    if (btn) {
      btnZ = btn->getZOrder();
      btn->setZOrder(-1);
    }
    auto highest = CCScene::getHighestChildZ();
    if (btn) btn->setZOrder(btnZ);
    return highest;
  }
};