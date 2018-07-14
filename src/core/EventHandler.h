#pragma once
#include <functional>
#include <vector>
#include "Event.h"

namespace Vulture2D {

    typedef std::function<void(Event*)> Callback;

    class EventHandler {
    public:
        int addListener(EventType type, Callback);
        void removeListener(int id);
        void dispatchEvent(Event*);

    private:
        int lastID = 0;

        struct Listener {
            int id;
            Callback cb;
            EventType type;
        };
        std::vector<Listener> listeners;
    };
}
