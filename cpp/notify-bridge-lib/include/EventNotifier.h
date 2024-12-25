#ifndef ENVENT_NOTIFIER_H
#define ENVENT_NOTIFIER_H

#include "observer_api.h"
#include "IEventNotifier.h"
#include <vector>
#include <string>

class EventNotifier : public IEventNotifier
{
public:
    void addSubscriber(IObserver* observer);
    void removeSubscriber(IObserver* observer);
    void notify(EventType eventType, const std::string& message);

private:
    std::vector<IObserver*> subscribers_;
};

#endif // ENVENT_NOTIFIER_H
