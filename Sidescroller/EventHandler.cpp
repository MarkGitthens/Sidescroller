#include "EventHandler.h"

EventHandler* EventHandler::instance = nullptr;

EventHandler& EventHandler::getInstance() {
    if (!instance) {
        instance = new EventHandler();
    }
    return *instance;
}

// Trigger the eventId and call all of the subscribed functions.
void EventHandler::triggerEvent(std::string eventId) {
    if (mSubscribedKeyEvents.find(eventId) != mSubscribedKeyEvents.end()) {
        std::thread([&, eventId]() {
            for (auto pair : *mSubscribedKeyEvents[eventId]) {
                pair.second(0);
            }
        }).detach();
    }
}

// Listen to a new eventId as a subscriber and assign the function to be called when 
// the event is triggered.
void EventHandler::listenEvent(std::string eventId, std::string subscriberName, EventFunc func) {
    // Check to make sure that the event id doesn't already exist
    if (mSubscribedKeyEvents.find(eventId) == mSubscribedKeyEvents.end()) {
        // If the eventId already exists, assign a new subscriber to the event
        mSubscribedKeyEvents.emplace(eventId, new std::unordered_map<std::string,EventFunc>());
    }
    mSubscribedKeyEvents[eventId]->emplace(subscriberName,func);
}

// Remove a subscriberName from an eventId
void EventHandler::removeFromEvent(std::string eventId, std::string subscriberName) {
    // Check to make sure that the event id exists
    auto item = mSubscribedKeyEvents.find(eventId);
    if (item != mSubscribedKeyEvents.end()) {
        if (item->second->find(subscriberName) != item->second->end()) {
            item->second->erase(subscriberName);
        }
    }
}