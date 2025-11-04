
#include "raylibLogging.h"

#include <stdio.h>
#include <stdarg.h>

#include "raylib.h"
#include "logger.h"

static LoggerPtr _raylibLogger = nullptr;

LogLevel convertRaylibLogLevel(int logLevel)
{
    switch (logLevel)
    {
        case LOG_FATAL:      return LogLevel::Critical;
        case LOG_ERROR:      return LogLevel::Error;
        case LOG_WARNING:    return LogLevel::Warning;
        case LOG_INFO:       return LogLevel::InfoLog;
        case LOG_DEBUG:      return LogLevel::Debug;
        case LOG_TRACE:      return LogLevel::Debug;
        case LOG_ALL:        return LogLevel::Debug;
        case LOG_NONE:       return LogLevel::NotSpecified;
        default:             return LogLevel::NotSpecified;
    }
}

void raylib_logging_function(int logLevel, const char *text, va_list args)
{
	if (_raylibLogger == nullptr)
	{
		_raylibLogger = std::make_shared<Logger>("Raylib", LogLevel::Debug);
	}

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), text, args);
	_raylibLogger->LogSimple(buffer, convertRaylibLogLevel(logLevel));
}