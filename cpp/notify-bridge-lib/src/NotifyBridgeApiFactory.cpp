#include "NotifyBridgeApi.h"
#include "NotifyBridgeApiFactory.h"
#include "Display.h"
#include "LoggerApi.h"

IObserver* NotifyBridgeApiFactory::createDisplay()
{
    LOG_VERBOSE("Trying to create observer.");

    IObserver* observer = new Display();

    LOG_VERBOSE("Created observer: ", observer);

    return observer;
}

ApiResult NotifyBridgeApiFactory::deleteObserver(IObserver* observer)
{
    ApiResult apiResult = ApiResult::WTF;

    if(!observer)
    {
        apiResult = ApiResult::FAILURE_ELEMENT_IS_NULL;

        LOG_VERBOSE("Observer is null. Function result: ", apiResult);

        return apiResult;
    }

    LOG_VERBOSE("Trying to remove observer ", observer);
    
    delete observer;

    apiResult = ApiResult::SUCCESS;

    LOG_VERBOSE("Observer removed. Function result: ", apiResult);

    return apiResult;
}