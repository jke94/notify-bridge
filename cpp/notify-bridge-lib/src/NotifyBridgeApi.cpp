#include <memory>

#include "NotifyBridgeApi.h"
#include "Display.h"
#include "WeatherStation.h"

std::shared_ptr<WeatherStation> wheatherStation_ = nullptr;

extern "C" API_EXPORT IObserver* createObserver()
{
    IObserver* display = new Display();
    
    return display;
}

extern "C" API_EXPORT ApiResult registerObserver(
    IObserver* observer, 
    void(*notification)(float, float, float)
)
{
    wheatherStation_->registerObserver(observer, notification);

    return ApiResult::SUCCESS; // TODO: Implement logic.
}

extern "C" API_EXPORT ApiResult removeObserver(IObserver* observer)
{
    wheatherStation_->removeObserver(observer);

    return ApiResult::SUCCESS; // TODO: Implement logic.
}

extern "C" API_EXPORT ApiResult deleteObserver(IObserver* observer)
{
    delete observer;

    return ApiResult::SUCCESS;
}

// Operations to simulate that patterns works correctly.

extern "C" API_EXPORT ApiResult initializeMeasurementTool()
{
    if(!wheatherStation_)
    {
        wheatherStation_ = std::make_shared<WeatherStation>();
    }

    return ApiResult::SUCCESS;
}

extern "C" API_EXPORT ApiResult setMeasurements(float temp, float hum, float press)
{
    wheatherStation_->setMeasurements(temp, hum, press);

    return ApiResult::SUCCESS; // TODO: Implement logic.
}