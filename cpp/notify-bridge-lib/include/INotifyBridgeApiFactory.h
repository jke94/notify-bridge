#ifndef I_NOTIFY_BRIDGE_API_FACTORY_H
#define I_NOTIFY_BRIDGE_API_FACTORY_H

#include "NotifyBridgeApi.h"

class INotifyBridgeApiFactory
{
public:
    virtual ~INotifyBridgeApiFactory() {};
    virtual IObserver* createDisplay() = 0;
    virtual ApiResult deleteObserver(IObserver* observer) = 0;
};

#endif // I_NOTIFY_BRIDGE_API_FACTORY_H