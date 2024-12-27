#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <string>

template <typename... Args>
std::string build_message(const Args&... args) 
{
    std::ostringstream stream;
    int dummy[] = {0, (stream << args, 0)...};
    return stream.str();
}

void logVerbose(const char* file, const char* function, const int line, const std::string& message);
void logInfo(const char* file, const char* function, const int line, const std::string& message);
void logWarning(const char* file, const char* function, const int line, const std::string& message);
void logError(const char* file, const char* function, const int line, const std::string& message);
void logCritical(const char* file, const char* function, const int line, const std::string& message);

#endif // LOGGER_H