#ifndef I_WHEATHER_STATION_H
#define I_WHEATHER_STATION_H

#include "NotifyBridgeApi.h"

class IWeatherStation
{
public:
    virtual ~IWeatherStation(){};
    virtual ApiResult registerObserver(
        IObserver* observer,
        void(*notification)(float temp, float hum, float press)
    ) = 0;
    virtual ApiResult removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual void setMeasurements(float temp, float hum, float press) = 0;  
};

#endif // I_WHEATHER_STATION_H