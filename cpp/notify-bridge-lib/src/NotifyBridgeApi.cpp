#include "NotifyBridgeApi.h"
#include "NotifyBridgeApiFactory.h"
#include "WeatherStationFactory.h"
#include "LoggerContainer.h"
#include "LoggerWrapper.h"
#include "LoggerApi.h"

using namespace notifyBridgeLogger;

extern "C" API_EXPORT LOGGER_INFRASTRUCTURE_RESULT initializeLogger(
    void(*logCallback)(LOG_LEVEL logLevel, const char* logMessage)
)
{
    LOGGER_INFRASTRUCTURE_RESULT result = LOGGER_INFRASTRUCTURE_RESULT::WTF;
    
    if(LoggerContainer::logger_)
    {
        result = LOGGER_INFRASTRUCTURE_RESULT::FAILURE_HEY_YOU_HAVE_ALREADY_INITIALIZE_THE_LOGGER;

        LOG_VERBOSE("Fail! Logger have been already initialized. Function result: ", result);
    
        return result;
    }

    LoggerContainer::logger_ = std::make_shared<LoggerWrapper>();
    LoggerContainer::logger_->setLoggerCallback(logCallback);

    result = LOGGER_INFRASTRUCTURE_RESULT::OK;

    LOG_VERBOSE("Logger has been initialized: ", &logCallback, "Function result: ", result);

    return result;
}

extern "C" API_EXPORT IObserver* createObserver()
{
    NotifyBridgeApiFactory notifyBridgeApiFactory;
    IObserver* display = notifyBridgeApiFactory.createDisplay();
    
    return display;
}

extern "C" API_EXPORT ApiResult registerObserver(
    IObserver* observer, 
    void(*notification)(float, float, float)
)
{
    WeatherStationFactory weatherStationFactory;
    weatherStationFactory.getWeatherStation()->registerObserver(observer, notification);

    return ApiResult::SUCCESS; // TODO: Implement logic.
}

extern "C" API_EXPORT ApiResult removeObserver(IObserver* observer)
{
    WeatherStationFactory weatherStationFactory;
    weatherStationFactory.getWeatherStation()->removeObserver(observer);

    return ApiResult::SUCCESS; // TODO: Implement logic.
}

extern "C" API_EXPORT ApiResult deleteObserver(IObserver* observer)
{
    NotifyBridgeApiFactory notifyBridgeApiFactory;
    ApiResult apiResult = notifyBridgeApiFactory.deleteObserver(observer);

    return apiResult;
}

// Operations to simulate that abserver pattern works correctly.

extern "C" API_EXPORT ApiResult initializeMeasurementTool()
{
    ApiResult apiResult = ApiResult::FAILURE;

    WeatherStationFactory weatherStationFactory;
    
    auto weatherStation = weatherStationFactory.getWeatherStation();

    if(weatherStation)
    {
        apiResult = ApiResult::SUCCESS;
    }

    LOG_VERBOSE("Initialiced measurement tool: ", weatherStation);

    return apiResult;
}

extern "C" API_EXPORT ApiResult setMeasurements(float temp, float hum, float press)
{
    WeatherStationFactory weatherStationFactory;
    weatherStationFactory.setMeasurements(temp, hum, press);

    return ApiResult::SUCCESS; // TODO: Implement logic.
}