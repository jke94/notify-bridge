#include <algorithm>
#include <iostream>

#include "EventNotifier.h"
#include "observer_api.h"

void EventNotifier::addSubscriber(IEventSubscriber* subscriber)
{
    if (subscriber)
    {
        subscribers_.push_back(subscriber);
    }
}

void EventNotifier::removeSubscriber(IEventSubscriber* subscriber)
{
    subscribers_.erase(std::remove(subscribers_.begin(), subscribers_.end(), subscriber), subscribers_.end());
}

void EventNotifier::notify(EventType eventType, const std::string& message)
{
    for (auto* subscriber : subscribers_)
    {
        if (subscriber)
        {
            subscriber->OnEvent(message);
        }
    }
}
