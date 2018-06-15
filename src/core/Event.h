#pragma once
#include <string>
#include <vector>

#include "Entity.h"
using std::string;
namespace Vulture2D {

    typedef unsigned int EventType;

    class Event {
    public:
        Event(string name, EventType type, bool propagates = false) : type(type),
            propagates(propagates) {};
        virtual ~Event() {}

        EventType getType() { return type; }
        bool propagatesUp() { return propagates; }
        void setPropogatesUp(bool flag) { propagates = flag; }

    private:
        Entity* target;
        EventType type;
        bool propagates;
    };
}