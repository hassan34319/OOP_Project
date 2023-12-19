#include "Event.h"

Event::Event(EventType type) : eventType(type) {}

bool Event::operator==(const Event& other) const {
    return eventType == other.eventType;
}
