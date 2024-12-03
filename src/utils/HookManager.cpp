#include "HookManager.hpp"

namespace summit::HookManager {
    std::map<std::string, Hook*> m_hooks;
    bool disableHook(std::string id) {
        auto hook = m_hooks.find(id);
        if (hook == m_hooks.end()) {
            return false;
        }
        auto res = hook->second->disable();
        if (auto err = res.err()) {
            log::info("Failed to disable hook {}: {}", hook->first, err);
        }
        return true;
    }
    bool enableHook(std::string id) {
        auto hook = m_hooks.find(id);
        if (hook == m_hooks.end()) {
            return false;
        }
        auto res = hook->second->enable();
        if (auto err = res.err()) {
            log::info("Failed to enable hook {}: {}", hook->first, err);
        }
        return true;
    }
    bool registerHook(std::string id, Hook* hook) {
        if (m_hooks.find(id) != m_hooks.end()) {
            return false;
        }
        log::info("Registering hook {}", id);
        m_hooks[id] = hook;
        return true;
    }
}