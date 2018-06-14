#pragma once
#include <string>
#include <vector>

#include "Entity.h"
using std::string;
namespace Vulture2D {
    enum EventType {
        CLICK//enumarate different possible default EventTypes here.
    };

    class Event {
    public:
        Event(string name, EventType type, bool propogateUp = false) : type(type),
            propagateUp(propagateUp) {};

        EventType getType();
        bool propogatesUp();
        void setPropogatesUp(bool);

    private:
        Entity* target;
        EventType type;
        bool propagateUp;
    };
}