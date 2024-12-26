#include <algorithm>
#include <vector>

#include "NotifyBridgeApi.h"
#include "WeatherStation.h"

void WeatherStation::registerObserver(IObserver* observer) 
{
    observers.push_back(observer);
}

void WeatherStation::removeObserver(IObserver* observer) 
{
    observers.erase(std::find(observers.begin(), observers.end(), observer));
}

void WeatherStation::notifyObservers() 
{
    for (IObserver* observer : observers) 
    {
        observer->update(temperature, humidity, pressure);
    }
}

void WeatherStation::setMeasurements(float temp, float hum, float press) 
{
    temperature = temp;
    humidity = hum;
    pressure = press;
    notifyObservers();
}