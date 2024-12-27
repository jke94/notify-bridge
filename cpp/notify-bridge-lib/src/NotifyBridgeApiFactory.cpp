#include "NotifyBridgeApi.h"
#include "NotifyBridgeApiFactory.h"
#include "Display.h"

IObserver* NotifyBridgeApiFactory::createDisplay()
{
    return new Display();
}

ApiResult NotifyBridgeApiFactory::deleteObserver(IObserver* observer)
{
    delete observer;

    return ApiResult::SUCCESS;
}