#include "NotifyBridgeApi.h"
#include "NotifyBridgeApiFactory.h"
#include "WeatherStationFactory.h"

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

// Operations to simulate that patterns works correctly.

extern "C" API_EXPORT ApiResult initializeMeasurementTool()
{
    ApiResult apiResult = ApiResult::FAILURE;

    WeatherStationFactory weatherStationFactory;

    if(weatherStationFactory.getWeatherStation())
    {
        apiResult = ApiResult::SUCCESS;
    }

    return apiResult;
}

extern "C" API_EXPORT ApiResult setMeasurements(float temp, float hum, float press)
{
    WeatherStationFactory weatherStationFactory;
    weatherStationFactory.setMeasurements(temp, hum, press);

    return ApiResult::SUCCESS; // TODO: Implement logic.
}