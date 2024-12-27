#include <mutex>
#include <sstream>

#include "LoggerWrapper.h"

namespace notifyBridgeLogger
{
    std::mutex mutex_;
    std::mutex mutexSetMinimunLog_;

    void LoggerWrapper::setLoggerCallback(void(*logCallback)(LOG_LEVEL logLevel, const char* logMessage))
    {
        logCallback_ = logCallback;
    }

    void LoggerWrapper::logVerbose(const char *file, const char *function, const int line, const std::string &message)
    {
        log(file, function, line, LOG_LEVEL::VERBOSE, message);
    }

    void LoggerWrapper::logInfo(const char *file, const char *function, const int line, const std::string &message)
    {
        log(file, function, line, LOG_LEVEL::INFO, message);     
    }

    void LoggerWrapper::logWarning(const char *file, const char *function, const int line, const std::string &message)
    {
        log(file, function, line, LOG_LEVEL::WARNING, message);     
    }

    void LoggerWrapper::logError(const char *file, const char *function, const int line, const std::string &message)
    {
        log(file, function, line, LOG_LEVEL::ERROR, message);     
    }

    void LoggerWrapper::logCritical(const char *file, const char *function, const int line, const std::string &message)
    {
        log(file, function, line, LOG_LEVEL::CRITICAL, message);
    }

    void LoggerWrapper::log(const char *file, const char *function, const int line, LOG_LEVEL logLevel, const std::string &message)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        std::stringstream ss;

        ss << "[" << file << "|" << function << "|" << line << "]";
        ss << " " << message;

        logCallback_(logLevel, ss.str().c_str());
    }
}