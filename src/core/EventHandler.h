#pragma once
#include <functional>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include "Event.h"
#include "SceneHandler.h"

namespace Vulture2D {
    class EventHandler {
    public:
        static EventHandler& getInstance();


    private:
        ~EventHandler() { if (instance) { delete instance; } instance = nullptr; }
        EventHandler() { }
        EventHandler(EventHandler const&) {}
        EventHandler& operator=(EventHandler const& e) {}

        static EventHandler* instance;
    };
}
