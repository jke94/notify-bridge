#include <iostream>

#include "observer_api.h"

int main()
{
    IObserver* observerA = createObserver();
    std::cout << "Observer created: " << observerA << std::endl;

    ApiResult createSubscribeResult = addObserver(observerA);

    if (createSubscribeResult != ApiResult::SUCCESS)
    {
        std::cout << "Failed to add subscriber" << std::endl;

        return -1;
    }

    std::cout << "Observer added successfully" << std::endl;

    ApiResult notifyResult;
    notifyResult = notifySubscribers(EventType::EVENT_A, "Hello, world!");
    notifyResult = notifySubscribers(EventType::EVENT_B, "Bye bye!");

    ApiResult removeObserverResult = removeObserver(observerA);

    if (removeObserverResult != ApiResult::SUCCESS)
    {
        std::cout << "Failed to remove observer" << std::endl;

        return -1;
    }

    std::cout << "Observer removed successfully" << std::endl;



    return 0;
}