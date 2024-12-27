#ifndef NOTIFY_BRIDGE_API_H
#define NOTIFY_BRIDGE_API_H

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
    virtual void update(
    float temp, 
    float hum, 
    float press,
    void(*notification)(float, float, float)) = 0;
};

/**
 * Create observer.
 */
extern "C" API_EXPORT IObserver* createObserver();

/**
 * Register observer and it's reaction.
 */
extern "C" API_EXPORT ApiResult registerObserver(
    IObserver* observer, 
    void(*notification)(float, float, float)
);

/**
 * Remove observer from the list.
 */
extern "C" API_EXPORT ApiResult removeObserver(IObserver* observer);

/**
 * Free memory. Delete observer.
 */
extern "C" API_EXPORT ApiResult deleteObserver(IObserver* observer);

// INFRASTRUCTURE: Operations to simulate events to launch notifications to the clients.

/**
 * Initialization measurement tool to emit events.
 */
extern "C" API_EXPORT ApiResult initializeMeasurementTool();

/**
 * Set measurements. After to be implemented observer pattern it will notifty to the observers.
 */
extern "C" API_EXPORT ApiResult setMeasurements(float temp, float hum, float press);

#endif // NOTIFY_BRIDGE_API_H