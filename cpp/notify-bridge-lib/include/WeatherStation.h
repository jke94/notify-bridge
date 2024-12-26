#ifndef WHEATHER_STATION_H
#define WHEATHER_STATION_H

#include <vector>
#include<map>

#include "NotifyBridgeApi.h"

class WeatherStation 
{
private:
    float temperature;
    float humidity;
    float pressure;
    std::vector<std::pair<IObserver*, void(*)(float temp, float hum, float press)>> observers_;

public:

    void registerObserver(
        IObserver* observer,
        void(*notification)(float temp, float hum, float press)
    );
    void removeObserver(IObserver* observer);
    void notifyObservers();
    void setMeasurements(float temp, float hum, float press);
};

#endif // WHEATHER_STATION_H