#include "EventHandler.h"

namespace Vulture2D {
    int EventHandler::addListener(EventType type, Callback cb) {
        Listener listener;
        listener.type = type;
        listener.cb = cb;
        listener.id = lastID++;

        listeners.push_back(listener);

        return lastID;
    }

    //TODO: Need to be able to propogate the event up the scenegraph eventually.
    void EventHandler::dispatchEvent(Event* event) {
        for (Listener l : listeners) {
            if (l.type == event->getType())
                l.cb(event); 
        }
    }
}
