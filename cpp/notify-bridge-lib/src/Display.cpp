#include <iostream>

#include "Display.h"

void Display::update(float temperature, float humidity, float pressure)
{
    std::cout << "I am observer " << this 
                << ", Display: Temperature = " << temperature
                << "°C, Humidity = " << humidity
                << "%, Pressure = " << pressure << " hPa"
                << std::endl;    
}