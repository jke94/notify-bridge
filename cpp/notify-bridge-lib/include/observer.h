#ifndef OBSERVER_H
#define OBSERVER_H

#include "observer_api.h"
#include <vector>
#include <string>

// Clase abstracta para los suscriptores
class IEventSubscriber
{
public:
    virtual ~IEventSubscriber() = default;
    virtual void OnEvent(const std::string& message) = 0;
};

// Clase que gestiona los suscriptores y eventos
class EventNotifier
{
public:
    void AddSubscriber(IEventSubscriber* subscriber);
    void RemoveSubscriber(IEventSubscriber* subscriber);
    void Notify(EventType eventType, const std::string& message);

private:
    std::vector<IEventSubscriber*> subscribers_;
};

#endif // OBSERVER_H
