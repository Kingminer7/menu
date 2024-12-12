#pragma once

#include "Summit.hpp"

namespace summit::hooks {
    bool registerHook(geode::Hook *hook, std::string id);
    bool toggleeHook(geode::Hook *hook);
}