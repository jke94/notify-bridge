#include <memory>

#include "LoggerContainer.h"
#include "ILogger.h"

namespace notifyBridgeLogger
{
    std::shared_ptr<ILogger> LoggerContainer::logger_ = nullptr;
}