#ifndef WHEATHER_STATION_H
#define WHEATHER_STATION_H

#include <vector>

#include "NotifyBridgeApi.h"

class WeatherStation 
{
private:
    float temperature;
    float humidity;
    float pressure;
    std::vector<IObserver*> observers;

public:

    void registerObserver(IObserver* observer);
    void removeObserver(IObserver* observer);
    void notifyObservers();
    void setMeasurements(float temp, float hum, float press);
};

#endif // WHEATHER_STATION_H