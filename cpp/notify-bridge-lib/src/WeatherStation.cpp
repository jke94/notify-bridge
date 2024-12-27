#include <algorithm>
#include <vector>

#include "NotifyBridgeApi.h"
#include "WeatherStation.h"
#include "LoggerApi.h"
#include "NotifyBridgeApiResultTypes.h"

ApiResult WeatherStation::registerObserver(
    IObserver* observer,
    void(*notification)(float temp, float hum, float press)
) 
{
    ApiResult resultType = ApiResult::WTF;

    if(!observer)
    {
        resultType = ApiResult::FAILURE_ELEMENT_IS_NULL;

        LOG_VERBOSE("Size of observers list: ", observers_.size(), ". Observer ", observer, " is going to be added. Function result: ", resultType);

        return resultType;
    }

    LOG_VERBOSE("Size of observers list: ", observers_.size(), ". Observer ", observer, " is going to be added.");
    observers_.push_back(std::make_pair(observer, notification));

    resultType = ApiResult::SUCCESS;
    LOG_VERBOSE("Size of observers list: ", observers_.size(), ". Observer ", observer, " added. Function result: ", resultType);

    return resultType;
}

ApiResult WeatherStation::removeObserver(IObserver* observer) 
{
    ApiResult result = ApiResult::WTF;

    auto it = std::find_if(
        observers_.begin(), 
        observers_.end(),
        [&](const auto& pair) 
        {
            return pair.first == observer; 
        });
    
    if(it == observers_.end())
    {
        result = ApiResult::FAILURE_ELEMENT_NOT_FOUND;
        LOG_WARNING("Observer ", observer, " can not be removed because it's not in the list. Function result: ", result);

        return result;
    }

    LOG_VERBOSE("Size of observers list: ", observers_.size(), ". Observer ", observer, " is going to be removed.");
    observers_.erase(it);

    result = ApiResult::SUCCESS;
    LOG_VERBOSE("Size of observers list: ", observers_.size(), ". Observer ", observer, " removed. Function result: ", result);

    return result;
}

void WeatherStation::notifyObservers() 
{
    for (std::pair<IObserver*, void(*)(float, float, float)> observer : observers_) 
    {
        observer.second(temperature_, humidity_, pressure_);
    }
}    

void WeatherStation::setMeasurements(float temp, float hum, float press) 
{
    LOG_VERBOSE("Set measurement: tempereature=", temp, ", humidity=", hum, " and pressure=", press);
    temperature_ = temp;
    humidity_ = hum;
    pressure_ = press;
    notifyObservers();
}