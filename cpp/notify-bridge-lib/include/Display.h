#ifndef DISPLAY_H
#define DISPLAY_H

#include "NotifyBridgeApi.h"

class Display : public IObserver 
{
public:
    void update(
        float temp, 
        float hum, 
        float press,
        void(*notification)(float, float, float)) override;
};

#endif // DISPLAY_H