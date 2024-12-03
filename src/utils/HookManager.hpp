using namespace geode::prelude;

namespace summit::HookManager {
  bool disableHook(std::string id);
  bool enableHook(std::string id);
  bool registerHook(std::string id, Hook* hook);
} // namespace summit