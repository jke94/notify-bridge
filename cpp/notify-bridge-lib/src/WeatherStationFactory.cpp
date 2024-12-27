#include <memory>

#include "WeatherStationFactory.h"

std::shared_ptr<IWeatherStation> weatherStation_;

std::shared_ptr<IWeatherStation> WeatherStationFactory::getWeatherStation()
{
    if(!weatherStation_)
    {
        weatherStation_ = std::make_shared<WeatherStation>();
    }

    return weatherStation_;
}

void WeatherStationFactory::setMeasurements(float temp, float hum, float press)
{
    weatherStation_->setMeasurements(temp, hum, press);
}