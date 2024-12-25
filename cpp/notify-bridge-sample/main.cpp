#include <iostream>
#include "observer_api.h"

int main()
{
    // TODO: Invesigate "addSubscriber"
    IEventSubscriber* subscriberA = createSubscriber();
    std::cout << "Subscriber created: " << subscriberA << std::endl;

    ApiResult createSubscribeResult = addSubscriber(subscriberA);

    if (createSubscribeResult != ApiResult::SUCCESS)
    {
        std::cout << "Failed to add subscriber" << std::endl;

        return -1;
    }

    std::cout << "Subscriber added successfully" << std::endl;

    ApiResult notifyResult;
    notifyResult = notifySubscribers(EventType::EVENT_A, "Hello, world!");
    notifyResult = notifySubscribers(EventType::EVENT_B, "Bye bye!");

    ApiResult removeSubscriberResult = removeSubscriber(subscriberA);

    if (removeSubscriberResult != ApiResult::SUCCESS)
    {
        std::cout << "Failed to remove subscriber" << std::endl;

        return -1;
    }

    std::cout << "Subscriber removed successfully" << std::endl;



    return 0;
}