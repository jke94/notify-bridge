#ifndef LOGGER_WRAPPER_H
#define LOGGER_WRAPPER_H

#include <functional>
#include <string>

#include "ILogger.h"

namespace notifyBridgeLogger
{
    class LoggerWrapper : public ILogger
    {

    public:
        LoggerWrapper() = default;

        void logVerbose(const char* file, const char* function, const int line, const std::string& message) override;
        void logInfo(const char* file, const char* function, const int line, const std::string& message) override;
        void logWarning(const char* file, const char* function, const int line, const std::string& message) override;
        void logError(const char* file, const char* function, const int line, const std::string& message) override;
        void logCritical(const char* file, const char* function, const int line, const std::string& message) override;

        void setLoggerCallback(void(*logCallback)(LOG_LEVEL logLevel, const char* logMessage)) override;

    private:

        void log(const char* file, const char* function, const int line, LOG_LEVEL logLevel, const std::string& message);
        void(*logCallback_)(LOG_LEVEL logLevel, const char* logMessage) = nullptr;
    };
}

#endif