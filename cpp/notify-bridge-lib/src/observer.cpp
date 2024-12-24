#include <algorithm>
#include <iostream>

#include "observer.h"
#include "observer_api.h"

void EventNotifier::AddSubscriber(IEventSubscriber* subscriber)
{
    if (subscriber)
    {
        subscribers_.push_back(subscriber);
    }
}

void EventNotifier::RemoveSubscriber(IEventSubscriber* subscriber)
{
    subscribers_.erase(std::remove(subscribers_.begin(), subscribers_.end(), subscriber), subscribers_.end());
}

void EventNotifier::Notify(EventType eventType, const std::string& message)
{
    for (auto* subscriber : subscribers_)
    {
        if (subscriber)
        {
            subscriber->OnEvent(message);
        }
    }
}
