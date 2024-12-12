#include "mods/Mods.hpp"
#include "Summit.hpp"

namespace summit {
    matjson::Value Config::config = matjson::Value::object();
    matjson::Value Config::temp = matjson::Value::object();
    bool Config::initialized = false;
    ui::UIType Config::uiType = ui::UIType::ImGui;

    ui::UIType Config::getUIType() {
        return uiType;
    }

    void Config::setUIType(ui::UIType type) {
        uiType = type;
    }
}

class UpdateManager : public cocos2d::CCObject {
    protected:
        UpdateManager() {
            cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(UpdateManager::update), this, 0, false);
        }
        static UpdateManager *instance;
    public:
        static UpdateManager *get() {
            if (!instance) instance = new UpdateManager();
            return instance;
        }
        void update(float dt) {
            for (auto& [id, mod] : summit::mods::getMods()) {
                mod->update();
            }
        }
};

UpdateManager* UpdateManager::instance = nullptr;

$on_mod(Loaded) {
    // lol
    UpdateManager::get();
}