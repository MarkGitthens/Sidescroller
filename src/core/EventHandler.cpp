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

    //TODO: Figure out a way to remove listeners with given data
    void EventHandler::removeListener(EventType type, Callback cb) {
        for (int i = 0; i < listeners.size(); i++) {

           // if (listeners.at(i).type == type && listeners.at(i).cb == cb) {
              //  listeners.erase(listeners.begin() + i);
           // }
        }
    }

    //Need to be able to propogate the event up the scenegraph eventually.
    void EventHandler::dispatchEvent(Event* event) {
        /*for (Listener l : listeners) {
            if (l.type == event->getType())
                l.cb(event);
        }*/
    }
}
