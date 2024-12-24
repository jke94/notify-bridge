#include "observer_api.h"
#include "observer.h"
#include <map>

// Manejador global del EventNotifier
static EventNotifier notifier;

// Map para convertir los punteros de C# a instancias concretas
static std::map<void*, IEventSubscriber*> subscribersMap;

// Implementación de las funciones exportadas
ApiResult AddSubscriber(void* subscriber)
{
    if (!subscriber)
        return ApiResult::FAILURE;

    auto it = subscribersMap.find(subscriber);
    if (it != subscribersMap.end())
        return ApiResult::FAILURE; // Ya registrado

    IEventSubscriber* cppSubscriber = static_cast<IEventSubscriber*>(subscriber);
    notifier.AddSubscriber(cppSubscriber);
    subscribersMap[subscriber] = cppSubscriber;

    return ApiResult::SUCCESS;
}

ApiResult RemoveSubscriber(void* subscriber)
{
    auto it = subscribersMap.find(subscriber);
    if (it == subscribersMap.end())
        return ApiResult::FAILURE;

    notifier.RemoveSubscriber(it->second);
    subscribersMap.erase(it);

    return ApiResult::SUCCESS;
}

void NotifySubscribers(EventType eventType, const char* message)
{
    notifier.Notify(eventType, message ? message : "");
}