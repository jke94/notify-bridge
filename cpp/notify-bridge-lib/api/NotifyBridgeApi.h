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

enum class LOG_LEVEL
{
    VERBOSE = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

enum class LOGGER_INFRASTRUCTURE_RESULT
{
    /** Something was wrong, contact with the logger author. */
    WTF = -1,

    /** OK, logger callback has initialize correctly. */
    OK,

    /** Failure, You've already initialized the logger! */
    FAILURE_HEY_YOU_HAVE_ALREADY_INITIALIZE_THE_LOGGER,

    /** Failure, callback logger is null! */
    FAILURE_CALLBACK_LOGGER_IS_NULL,

    /** Failure, you are trying configure log minimun level log callback before to initialize! */
    FAILURE_CALLBACK_IS_NULL_PLEASE_INITIALIZE_FIRST_THE_CALLBACK_BEFORE_TO_SET_MIN_LOGGER_LEVEL,
};

/*  Infrastructure. Logger inicialization callback to get library logs. */
extern "C" API_EXPORT LOGGER_INFRASTRUCTURE_RESULT initializeLogger(void(*logCallback)(LOG_LEVEL logLevel, const char* logMessage));

enum class ApiResult
{
    WTF = -1,
    SUCCESS = 0,
    FAILURE = 1,
    FAILURE_ELEMENT_NOT_FOUND = 2,
    FAILURE_ELEMENT_IS_NULL = 3
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

/**
 * Infrasctructure operations. Initialization measurement tool to emit events.
 */
extern "C" API_EXPORT ApiResult initializeMeasurementTool();

/**
 * Infrasctructure operations. Set measurements. After to be implemented observer pattern it will notifty to the observers.
 */
extern "C" API_EXPORT ApiResult setMeasurements(float temp, float hum, float press);

#endif // NOTIFY_BRIDGE_API_H