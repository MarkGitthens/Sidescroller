#pragma once
#include "../Entity.h"

using std::string;
namespace Vulture2D {
    //Approach for generating ID's take from Oxygine framework.
    constexpr unsigned int getUniqueID(unsigned int a, unsigned int b, unsigned int c, unsigned int d) { return (((unsigned int)a) | ((unsigned int)b << 8) | ((unsigned int)c << 16) | ((unsigned int)d << 24)); }
    constexpr unsigned int getUniqueSystemID(unsigned int a, unsigned int b, unsigned int c) { return getUniqueID(0x0, a, b, c); }

    typedef unsigned int EventType;

    class Event {
    public:
        Event() : type(0), action() {};
        EventType getType() { return type; }

    protected:
        std::string action;
        EventType type;
    };
}