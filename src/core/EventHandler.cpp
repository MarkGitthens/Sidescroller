#include "EventHandler.h"

namespace Vulture2D {
    EventHandler* EventHandler::instance = nullptr;

    EventHandler& EventHandler::getInstance() {
        if (!instance) {
            instance = new EventHandler();
        }
        return *instance;
    }
}
