#include <iostream>

#include "NotifyBridgeApi.h"

std::ostream& operator<<(std::ostream& os, ApiResult result);

int main()
{
    IObserver* display1 = createObserver();
    IObserver* display2 = createObserver();

    ApiResult display1Registration1 = registerObserver(display1);
    ApiResult display1Registration2 = registerObserver(display2);

    ApiResult setMeasurementResult1 = setMeasurements(25.5, 60, 1013.2);
    ApiResult setMeasurementResult2 = setMeasurements(24.8, 58, 1014.5);

    ApiResult removeResult = removeObserver(display2);

    ApiResult setMeasurementResult3 = setMeasurements(35.8, 70, 1111.2);

    delete display1;
    delete display2;

    return 0;
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