#include "Event.h"

namespace Vulture2D {
    string Event::getStringData() {
        return stringData;
    }

    int Event::getIntData() {
        return intData;
    }

    float Event::getFloatData() {
        return floatData;
    }

    string Event::getName() {
        return event_name
    }

    EventType Event::getType() {
        return type;
    }

    void Event::setData(string data) {
        stringData = data;
    }

    void Event::setData(int data) {
        intData = data;
    }

    void Event::setData(float data) {
        floatData = data;
    }

    void Event::setName(string name) {
        event_name = name;
    }
}
