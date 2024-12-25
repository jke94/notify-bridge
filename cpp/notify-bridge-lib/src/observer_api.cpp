#include "observer_api.h"
#include "EventNotifier.h"
#include "Observer.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <string>
#include <vector>

// Manejador global del EventNotifier
static EventNotifier notifier;

// Map para convertir los punteros de C# a instancias concretas
static std::vector<IObserver*> subscribersVector;

IObserver* createObserver()
{
    return new Observer();
}

ApiResult addObserver(IObserver* observer)
{
    if (!observer)
    {
        return ApiResult::FAILURE;
    }

    if(std::find(subscribersVector.begin(), subscribersVector.end(), observer) != subscribersVector.end())
    {
        return ApiResult::FAILURE; // Observer already added.
    }

    notifier.addSubscriber(observer);
    subscribersVector.push_back(observer);

    return ApiResult::SUCCESS;
}

ApiResult removeObserver(IObserver* observer)
{
    if(std::find(subscribersVector.begin(), subscribersVector.end(), observer) == subscribersVector.end())
    {
        return ApiResult::FAILURE; // Observer not found.
    }

    subscribersVector.erase(
        std::remove(
            subscribersVector.begin(), 
            subscribersVector.end(), 
            observer), 
            subscribersVector.end());

    return ApiResult::SUCCESS;
}

ApiResult notifySubscribers(EventType eventType, const char* message)
{
    notifier.notify(eventType, message ? message : "");

    return ApiResult::SUCCESS; // TODO: Improve to manage errors.
}