#include <algorithm>
#include <iostream>

#include "EventNotifier.h"
#include "observer_api.h"

void EventNotifier::addSubscriber(IObserver* observer)
{
    if (observer)
    {
        subscribers_.push_back(observer);
    }
}

void EventNotifier::removeSubscriber(IObserver* observer)
{
    subscribers_.erase(std::remove(subscribers_.begin(), subscribers_.end(), observer), subscribers_.end());
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
