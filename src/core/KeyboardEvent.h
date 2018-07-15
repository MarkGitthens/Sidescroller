#pragma once
#include "Event.h"

namespace Vulture2D {
    class KeyboardEvent : public Event {
    public:
        KeyboardEvent() {};
        KeyboardEvent(EventType type, int id) : keyID(id) {
            this->type = type;
        };
        enum {
            _start = getUniqueID('s', 'k', 0, 0),
            KeyPress,
            KeyReleased,
            KeyHeld
        };

        int keyID;
    };
}