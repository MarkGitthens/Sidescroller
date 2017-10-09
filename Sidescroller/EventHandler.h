#pragma once
#include <functional>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

class EventHandler {
public:
    static EventHandler& getInstance();
    typedef std::function<void(int)> EventFunc;
    void triggerEvent(std::string eventId);
    void listenEvent(std::string eventId, std::string subscriberName, EventFunc func);
    void removeFromEvent(std::string eventId, std::string subscriberName);

private:
    ~EventHandler() { if (instance) { delete instance; } instance = nullptr; }
    EventHandler() { }
    EventHandler(EventHandler const&) {}
    EventHandler& operator=(EventHandler const& e) {}

    static EventHandler* instance;

    std::unordered_map<std::string, std::unordered_map<std::string,EventFunc>*> mSubscribedKeyEvents;
};