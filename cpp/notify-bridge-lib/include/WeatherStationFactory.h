#ifndef WEATHER_STATION_FACTORY_H
#define WEATHER_STATION_FACTORY_H

#include <memory>
#include "IWeatherStation.h"
#include "WeatherStation.h"

std::shared_ptr<IWeatherStation> weatherStation_;

class WeatherStationFactory
{
private:
    
public:
    WeatherStationFactory() = default;
    std::shared_ptr<IWeatherStation> getWeatherStation()
    {
        if(!weatherStation_)
        {
            weatherStation_ = std::make_shared<WeatherStation>();
        }

        return weatherStation_;
    }

    void setMeasurements(float temp, float hum, float press)
    {
        weatherStation_->setMeasurements(temp, hum, press);
    }
};

#endif // WEATHER_STATION_CONTAINER_H