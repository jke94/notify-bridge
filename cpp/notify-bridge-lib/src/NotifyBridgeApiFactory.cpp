#include "NotifyBridgeApi.h"
#include "NotifyBridgeApiFactory.h"
#include "Display.h"
#include "LoggerApi.h"

IObserver* NotifyBridgeApiFactory::createDisplay()
{
    return new Display();
}

ApiResult NotifyBridgeApiFactory::deleteObserver(IObserver* observer)
{
    LOG_VERBOSE("Trying to remove observer ", observer);
    
    delete observer;

    return ApiResult::SUCCESS;
}