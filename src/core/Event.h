#pragma once
#include <string>
#include <vector>

using std::string;
namespace Vulture2D {
    class Event {
    public:
        enum EventType {
            INT,
            FLOAT,
            STRING
        };

        Event(string name, EventType type, bool propogateUp = false) : event_name(name),
            type(type),
            propagateUp(propagateUp) {};
        ~Event();
        string getStringData();
        int getIntData();
        float getFloatData();
        string getName();
        EventType getDataType();

        void setData(string);
        void setData(int);
        void setData(float);
        void setName(string);

    private:
        int intData;
        float floatData;
        string stringData;

        EventType type;
        string event_name;
        bool propagateUp;
    };
}