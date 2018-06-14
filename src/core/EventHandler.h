#pragma once
#include <functional>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include "Event.h"
#include "SceneHandler.h"

/* Event Handler implementation based off the following article.
    https://github.com/oxygine/oxygine-framework/wiki/events
    
*/
namespace Vulture2D {
    typedef std::function<void(Event*)> Callback;

    class EventHandler {
    public:
        int addListener(EventType type, Callback);
        void removeListener(EventType type, Callback);
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
