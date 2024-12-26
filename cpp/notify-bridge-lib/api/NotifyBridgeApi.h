#ifndef NOTIFY_BRIDGE_API_H
#define NOTIFY_BRIDGE_API_H

#include <iostream>
#include <list>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #ifdef EXPORT_SYMBOLS
        #define API_EXPORT __declspec(dllexport)
    #else
        #define API_EXPORT __declspec(dllimport)
    #endif
    #elif defined(__linux__) || defined(__APPLE__)
        #define API_EXPORT __attribute__((visibility("default")))
    #else
        #define API_EXPORT
#endif

enum class ApiResult
{
    SUCCESS = 0,
    FAILURE = 1
};

class IObserver 
{
    public:
        virtual ~IObserver(){};
        virtual void update(float temperature, float humidity, float pressure) = 0;
};

extern "C" API_EXPORT IObserver* createObserver();
extern "C" API_EXPORT ApiResult registerObserver(IObserver* observer);
extern "C" API_EXPORT ApiResult removeObserver(IObserver* observer);

// INFRASTRUCTURE: Operations to simulate events to launch notifications to the clients.
extern "C" API_EXPORT ApiResult setMeasurements(float temp, float hum, float press);

#endif // NOTIFY_BRIDGE_API_H