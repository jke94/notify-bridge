#ifndef SUSCRIBER_H
#define SUSCRIBER_H

#include <iostream>
#include <string>
#include "observer_api.h"

class Observer : public IObserver
{
public:
    Observer() = default;

    void OnEvent(const std::string& message) override
    {
        // TODO: Implementar
        std::cout << "I am subscriber " << this << ". Event received: " << message << std::endl;
    }
};

#endif // SUSCRIBER_H