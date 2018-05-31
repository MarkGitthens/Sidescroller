#pragma once
#include <functional>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace Vulture2D {
    //TODO: I really need to rework this. I don't like the idea of having to bind a function to an event. 
    class EventHandler {
    public:
        static EventHandler& getInstance();
        typedef std::function<void(int)> EventFunc;
        void triggerEvent(std::string eventId);
        void subscribeToEvent(std::string eventId, std::string subscriberName, EventFunc func);
        void unsubscribe(std::string eventId, std::string subscriberName);

    private:
        ~EventHandler() { if (instance) { delete instance; } instance = nullptr; }
        EventHandler() { }
        EventHandler(EventHandler const&) {}
        EventHandler& operator=(EventHandler const& e) {}

        static EventHandler* instance;

        std::unordered_map<std::string, std::unordered_map<std::string, EventFunc>*> mSubscribedKeyEvents;
    };
}