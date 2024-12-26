#ifndef DISPLAY_H
#define DISPLAY_H

#include "NotifyBridgeApi.h"

class Display : public IObserver 
{
public:
    void update(float temperature, float humidity, float pressure) override;
};

#endif // DISPLAY_H