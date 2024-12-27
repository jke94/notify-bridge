#ifndef I_WHEATHER_STATION_H
#define I_WHEATHER_STATION_H

class IWeatherStation
{
public:
    virtual ~IWeatherStation(){};
    virtual void registerObserver(
        IObserver* observer,
        void(*notification)(float temp, float hum, float press)
    ) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual void setMeasurements(float temp, float hum, float press) = 0;  
};

#endif // I_WHEATHER_STATION_H