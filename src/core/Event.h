#pragma once
#include "Entity.h"

using std::string;
namespace Vulture2D {
    //Approach for generating ID's take from Oxygine framework.
#define getUniqueID(a, b, c, d) (((unsigned int) a) | ((unsigned int) b << 8) | ((unsigned int) c << 16) | ((unsigned int) d << 24))
#define getUniqueSystemID(a, b, c) getUniqueID(0x0, a, b, c)

    typedef unsigned int EventType;

    class Event {
    public:
        EventType getType() { return type; }

    protected:
        EventType type;
    };
}