#ifndef OBSERVER_API_H
#define OBSERVER_API_H

#include <cstdint>
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

// Enum para representar tipos de eventos
enum class EventType
{
    EVENT_A = 0,
    EVENT_B = 1,
    EVENT_C = 2
};

// Resultado de las operaciones
enum class ApiResult
{
    SUCCESS = 0,
    FAILURE = 1
};

class IEventSubscriber
{
public:
    virtual ~IEventSubscriber() {};
    virtual void OnEvent(const std::string& message) = 0;
};

// Prototipos de las funciones exportadas

extern "C" API_EXPORT IEventSubscriber* createSubscriber();
extern "C" API_EXPORT ApiResult addSubscriber(IEventSubscriber* subscriber);
extern "C" API_EXPORT ApiResult removeSubscriber(IEventSubscriber* subscriber);
extern "C" API_EXPORT ApiResult notifySubscribers(EventType eventType, const char* message);

#endif // OBSERVER_API_H
