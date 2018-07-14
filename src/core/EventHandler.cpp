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

    void EventHandler::removeListener(int id) {
        for (int i = 0; i < listeners.size(); i++) {
            if (listeners.at(i).id == id) {
                listeners.erase(listeners.begin() + i);
            }
        }
    }

    void EventHandler::dispatchEvent(Event* event) {
        for (Listener l : listeners) {
            if (l.type == event->getType())
                l.cb(event); 
        }
    }
}
