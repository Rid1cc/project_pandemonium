#include "EventManager.h"

/* f.e.

void onEventTriggered() {
    std::cout << "Event triggered!" << std::endl;
}

int main() {
    eventManager.subscribe("myEvent", onEventTriggered);
    eventManager.triggerEvent("myEvent"); // This will call onEventTriggered
    return 0;
}

*/

void EventManager::subscribe(const std::string& eventName, EventCallback callback) {
    eventListeners[eventName].push_back(callback);
}

void EventManager::unsubscribe(const std::string& eventName, EventCallback callback) {
    auto& listeners = eventListeners[eventName];
    listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
        [&callback](const EventCallback& cb) {
            return callback.target<void()>() == cb.target<void()>();
        }), listeners.end());
}

void EventManager::triggerEvent(const std::string& eventName) {
    auto& listeners = eventListeners[eventName];
    for (auto& listener : listeners) {
        listener();
    }
}

