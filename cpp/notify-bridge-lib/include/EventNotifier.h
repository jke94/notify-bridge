#ifndef ENVENT_NOTIFIER_H
#define ENVENT_NOTIFIER_H

#include "observer_api.h"
#include "IEventNotifier.h"
#include <vector>
#include <string>

class EventNotifier : public IEventNotifier
{
public:
    void addSubscriber(IEventSubscriber* subscriber);
    void removeSubscriber(IEventSubscriber* subscriber);
    void notify(EventType eventType, const std::string& message);

private:
    std::vector<IEventSubscriber*> subscribers_;
};

#endif // ENVENT_NOTIFIER_H
