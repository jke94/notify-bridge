#include <algorithm>
#include <vector>

#include "NotifyBridgeApi.h"
#include "WeatherStation.h"

void WeatherStation::registerObserver(
    IObserver* observer,
    void(*notification)(float temp, float hum, float press)
) 
{
    observers_.push_back(std::make_pair(observer, notification));
}

void WeatherStation::removeObserver(IObserver* observer) 
{
    auto it = std::find_if(observers_.begin(), observers_.end(),
                [&](const auto& pair) {
                    return pair.first == observer; 
                });

    observers_.erase(it);
}

void WeatherStation::notifyObservers() 
{
    for (std::pair<IObserver*, void(*)(float, float, float)> observer : observers_) 
    {
        observer.second(temperature, humidity, pressure);
    }
}    

void WeatherStation::setMeasurements(float temp, float hum, float press) 
{
    temperature = temp;
    humidity = hum;
    pressure = press;
    notifyObservers();
}