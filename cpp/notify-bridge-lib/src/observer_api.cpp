#include "observer_api.h"
#include "EventNotifier.h"
#include <map>
#include <iostream>
#include <string>

// Manejador global del EventNotifier
static EventNotifier notifier;

// Map para convertir los punteros de C# a instancias concretas
static std::map<void*, IEventSubscriber*> subscribersMap;

class Subscriber : public IEventSubscriber
{
public:
    Subscriber() = default;

    void OnEvent(const std::string& message) override
    {
        // TODO: Implementar
        std::cout << "I am subscriber " << this << ". Event received: " << message << std::endl;
    }
};

IEventSubscriber* createSubscriber()
{
    return new Subscriber();
}

ApiResult addSubscriber(IEventSubscriber* subscriber)
{
    if (!subscriber)
    {
        return ApiResult::FAILURE;
    }

    auto it = subscribersMap.find(subscriber);
    if (it != subscribersMap.end())
    {
        return ApiResult::FAILURE; // Ya registrado
    }

    IEventSubscriber* cppSubscriber = static_cast<IEventSubscriber*>(subscriber);
    notifier.addSubscriber(cppSubscriber);
    subscribersMap[subscriber] = cppSubscriber;

    return ApiResult::SUCCESS;
}

ApiResult removeSubscriber(IEventSubscriber *subscriber)
{
    auto it = subscribersMap.find(subscriber);

    if (it == subscribersMap.end())
    {
        return ApiResult::FAILURE;        
    }

    notifier.removeSubscriber(it->second);
    subscribersMap.erase(it);

    return ApiResult::SUCCESS;
}

ApiResult notifySubscribers(EventType eventType, const char* message)
{
    notifier.notify(eventType, message ? message : "");

    return ApiResult::SUCCESS; // TODO: Improve to manage errors.
}