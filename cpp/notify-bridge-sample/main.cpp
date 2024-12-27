#include <iostream>
#include <vector>

#include "NotifyBridgeApi.h"

void logCallbackMessage(LOG_LEVEL logLevel, const char* logMessage);

void OnEventA(float temp, float hum, float press);
void OnEventB(float temp, float hum, float press);

std::ostream& operator<<(std::ostream& os, ApiResult result);
std::ostream& operator<<(std::ostream& os, LOG_LEVEL logLevel);

int main()
{
    LOGGER_INFRASTRUCTURE_RESULT initializeCallbackResult = initializeLogger(logCallbackMessage);

    std::vector<std::pair<IObserver*, void(*)(float, float, float)>> observers_ = 
    {
        {createObserver(), OnEventA},
        {createObserver(), OnEventB},
    };

    ApiResult initializationResult = initializeMeasurementTool();

    ApiResult display1Registration1 = registerObserver(observers_[0].first, observers_[0].second);
    ApiResult display1Registration2 = registerObserver(observers_[1].first, observers_[1].second);

    ApiResult setMeasurementResult1 = setMeasurements(25.5, 60, 1013.2);
    ApiResult setMeasurementResult2 = setMeasurements(24.8, 58, 1014.5);

    ApiResult removeResult = removeObserver(observers_[0].first);

    ApiResult setMeasurementResult3 = setMeasurements(35.8, 70, 1111.2);

    ApiResult display1Registration3 = registerObserver(observers_[0].first, observers_[0].second);

    ApiResult setMeasurementResult4 = setMeasurements(-1.8, 10, 900.2);

    for(std::pair<IObserver*, void(*)(float, float, float)> observer : observers_)
    {
        if(observer.first)
        {
            removeObserver(observer.first);
            deleteObserver(observer.first);
        }
    }

    return 0;
}

void OnEventA(float temp, float hum, float press)
{
    std::cout << "Hi! I am A - Display: Temperature = " << temp
                << "°C, Humidity = " << hum
                << "%, Pressure = " << press << " hPa"
                << std::endl;
}

void OnEventB(float temp, float hum, float press)
{
    std::cout << "Hi! I am B - Display: Temperature = " << temp
                << "°C, Humidity = " << hum
                << "%, Pressure = " << press << " hPa"
                << std::endl;
}

std::ostream& operator<<(std::ostream& os, ApiResult result)
{
    switch (result)
    {
        case ApiResult::SUCCESS:
            os << "SUCCESS";
            break;
        case ApiResult::FAILURE:
            os << "FAILURE";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, LOG_LEVEL logLevel)
{
    switch (logLevel)
    {
        case LOG_LEVEL::VERBOSE:
            os << "VERBOSE";
            break;
        case LOG_LEVEL::INFO:
            os << "INFO";
            break;
        case LOG_LEVEL::WARNING:
            os << "WARNING";
            break;
        case LOG_LEVEL::ERROR:
            os << "ERROR";
            break;
        case LOG_LEVEL::CRITICAL:
            os << "CRITICAL";
            break;
        default:
            os << "NO_LOG_LEVEL";
            break;
    }
    return os;    
}

void logCallbackMessage(LOG_LEVEL logLevel, const char* logMessage)
{
    std::cout << "[" << logLevel << "]" << logMessage << std::endl;
}