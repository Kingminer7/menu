#include <Geode/Geode.hpp>

#include <imgui-cocos.hpp>

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
	        // this runs after imgui has been setup,
			        // its a callback as imgui will be re initialized when toggling fullscreen,
					        // so use this to setup any themes and or fonts!
							    }).draw([] {
								        ImGui::Begin("My awesome window");

										        ImGui::Button("Awesome button");
												        
														        ImGui::End();
																    });
																	}

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
	}
};