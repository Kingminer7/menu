#pragma once

#include "Summit.hpp"

namespace summit::hooks {
    bool registerHook(geode::Hook *hook, std::string id);
    bool toggleHook(geode::Hook *hook);
}