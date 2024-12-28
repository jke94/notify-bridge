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
    LOG_VERBOSE("Trying to remove observer ", observer);
    
    delete observer;

    return ApiResult::SUCCESS;
}