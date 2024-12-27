#ifndef LOGGER_CONTAINER_H
#define LOGGER_CONTAINER_H

#include <memory>

#include "ILogger.h"

namespace notifyBridgeLogger
{
    class LoggerContainer
    {
    public:
        static std::shared_ptr<ILogger> logger_;
    };
}


#endif // LOGGER_CONTAINER_H