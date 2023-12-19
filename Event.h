#pragma once
#include "EventType.h"

class Event {
public:
    Event(EventType type);

    bool operator==(const Event& other) const;

    EventType eventType;

private:
};
