#ifndef I_WEATHER_STATION_FACTORY_H
#define I_WEATHER_STATION_FACTORY_H

#include <memory>

#include "IWeatherStation.h"

class IWeatherStationFactory
{
public:
    ~IWeatherStationFactory(){};
    virtual std::shared_ptr<IWeatherStation> getWeatherStation() = 0;
    virtual void setMeasurements(float temp, float hum, float press) = 0;    
};



#endif // WEATHER_STATION_CONTAINER_H