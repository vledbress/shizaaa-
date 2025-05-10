#include <vector>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>



class Event {
public:
    virtual ~Event() = default;
};

class KeyPressEvent : public Event {
public:
    KeyPressEvent(int key, int scancode, int action, int mods)
        : key(key), scancode(scancode), action(action), mods(mods) {
    }

    int getKey() const {
        return key;
    }

    int getScancode() const {
        return scancode;
    }

    int getAction() const {
        return action;
    }

    int getMods() const {
        return mods;
    }

private:
    int key;       // ��� ������� (GLFW key code)
    int scancode;  // �������� �������
    int action;    // �������� (GLFW_PRESS, GLFW_RELEASE)
    int mods;      // ������������ (��������, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL)
};


class EventManager {
public:
    template<typename EventType>
    using EventCallback = std::function<void(const EventType&)>;

    template<typename EventType>
    void subscribe(const EventCallback<EventType>& callback) {
        auto& handlers = getHandlers<EventType>();
        handlers.push_back(callback);
    }

    template<typename EventType>
    void emit(const EventType& event) {
        auto& handlers = getHandlers<EventType>();
        for (auto& handler : handlers) {
            handler(event);
        }
    }

private:

    template<typename EventType>
    std::vector<EventCallback<EventType>>& getHandlers() {
        static std::vector<EventCallback<EventType>> handlers;
        return handlers;
    }
};



