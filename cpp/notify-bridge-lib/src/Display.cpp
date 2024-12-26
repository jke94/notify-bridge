#include <iostream>
#include <functional>

#include "Display.h"

void Display::update(float temp, float hum, float press, void(*notification)(float, float, float))
{
    if(notification)
    {
        notification(temp, hum, press);
    }
}