#pragma once
#include <functional>
#include <vector>
#include "events/Event.h"

namespace Vulture2D {

    typedef std::function<void(Event*)> Callback;

    class EventHandler {
    public:
        EventHandler() : listeners() {};
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
