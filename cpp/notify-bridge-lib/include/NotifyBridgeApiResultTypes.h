#ifndef NOTIFY_BRIDGE_API_RESULT_TYPES_H
#define NOTIFY_BRIDGE_API_RESULT_TYPES_H

#include <iostream>

#include "NotifyBridgeApi.h"

std::ostream& operator<<(std::ostream& os, const LOGGER_INFRASTRUCTURE_RESULT& result);
std::ostream& operator<<(std::ostream& os, const ApiResult& result);

#endif // NOTIFY_BRIDGE_API_RESULT_TYPES_H