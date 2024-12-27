#ifndef LOGGER_API_H
#define LOGGER_API_H

#include "Logger.h"

#define LOG_VERBOSE(...) logVerbose(__FILE__, __FUNCTION__, __LINE__, build_message(__VA_ARGS__))
#define LOG_INFO(...) logInfo(__FILE__, __FUNCTION__, __LINE__, build_message(__VA_ARGS__))
#define LOG_WARNING(...) logWarning(__FILE__, __FUNCTION__, __LINE__, build_message(__VA_ARGS__))
#define LOG_ERROR(...) logError(__FILE__, __FUNCTION__, __LINE__, build_message(__VA_ARGS__))
#define LOG_CRITICAL(...) logCritical(__FILE__, __FUNCTION__, __LINE__, build_message(__VA_ARGS__))

#endif // LOGGER_API_H