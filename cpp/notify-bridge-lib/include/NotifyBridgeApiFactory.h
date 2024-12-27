#ifndef NOTIFY_BRIDGE_API_FACTORY_H
#define NOTIFY_BRIDGE_API_FACTORY_H

#include "NotifyBridgeApi.h"
#include "INotifyBridgeApiFactory.h"

class NotifyBridgeApiFactory : public INotifyBridgeApiFactory
{
public:
    NotifyBridgeApiFactory() = default;
    ~NotifyBridgeApiFactory() = default;

    IObserver* createDisplay() override;
    ApiResult deleteObserver(IObserver* observer) override;
};

#endif // NOTIFY_BRIDGE_API_FACTORY_H