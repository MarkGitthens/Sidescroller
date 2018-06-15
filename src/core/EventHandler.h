#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "Event.h"
#include "SceneHandler.h"

/* Event Handler implementation based off the following article.
    https://github.com/oxygine/oxygine-framework/wiki/events
    
*/
namespace Vulture2D {
    //Approach for generating ID's take from Oxygine framework.
#define getUniqueID(a, b, c, d) (((unsigned int) a) | ((unsigned int) b << 8) | ((unsigned int) c << 16) | ((unsigned int) d << 24))
#define getUniqueSystemID(a, b, c) getUniqueID(0x0, a, b, c)

    typedef std::function<void(Event*)> Callback;

    class EventHandler {
    public:
        int addListener(EventType type, Callback);
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
