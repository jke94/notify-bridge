#ifndef I_EVENT_NOTIFIER_H
#define I_EVENT_NOTIFIER_H

#include <string>
#include "observer_api.h"

class IEventNotifier
{
public:
    virtual ~IEventNotifier() {};
    virtual void addSubscriber(IObserver* observer) = 0;
    virtual void removeSubscriber(IObserver* observer) = 0;
    virtual void notify(EventType eventType, const std::string& message) = 0;
};

#endif // I_EVENT_NOTIFIER_H