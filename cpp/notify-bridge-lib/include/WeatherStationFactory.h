#ifndef WEATHER_STATION_FACTORY_H
#define WEATHER_STATION_FACTORY_H

#include <memory>
#include "IWeatherStationFactory.h"
#include "IWeatherStation.h"
#include "WeatherStation.h"

class WeatherStationFactory : public IWeatherStationFactory
{
public:
    WeatherStationFactory() = default;
    std::shared_ptr<IWeatherStation> getWeatherStation() override;
    void setMeasurements(float temp, float hum, float press) override;
};

#endif // WEATHER_STATION_CONTAINER_H