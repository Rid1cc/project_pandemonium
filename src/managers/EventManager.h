#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <algorithm>

class EventManager {
public:
    using EventCallback = std::function<void()>;

    void subscribe(const std::string& eventName, EventCallback callback);
    void unsubscribe(const std::string& eventName, EventCallback callback);
    void triggerEvent(const std::string& eventName);

private:
    std::unordered_map<std::string, std::vector<EventCallback>> eventListeners;
};
