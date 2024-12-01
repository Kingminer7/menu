#include "../utils/Summit.hpp"

namespace summit::mods {

    class SafeMode : public summit::SMod {
        public:
            void onToggle(CCObject *);
    };

}