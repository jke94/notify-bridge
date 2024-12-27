#ifndef WHEATHER_STATION_H
#define WHEATHER_STATION_H

#include <vector>
#include <map>

#include "NotifyBridgeApi.h"
#include "IWeatherStation.h"

class WeatherStation : public IWeatherStation
{
private:
    float temperature_;
    float humidity_;
    float pressure_;
    std::vector<std::pair<IObserver*, void(*)(float temp, float hum, float press)>> observers_;

public:

    ApiResult registerObserver(
        IObserver* observer,
        void(*notification)(float temp, float hum, float press)
    ) override;
    ApiResult removeObserver(IObserver* observer) override;
    void notifyObservers() override;
    void setMeasurements(float temp, float hum, float press) override;
};

#endif // WHEATHER_STATION_H