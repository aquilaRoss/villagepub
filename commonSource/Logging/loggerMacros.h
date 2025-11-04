#ifndef LOGGER_MACROS_H
#define LOGGER_MACROS_H

#include "loggerInterface.h"

LoggerPtr LoggerGetDefault(void);

#define CRITICAL_EXPANDED(fn, line, msg) \
  do { \
    LoggerGetDefault()->Log(msg, std::string(fn), line, LogLevel::Critical); \
  } while (0)

#define ERROR_EXPANDED(fn, line, msg) \
  do { \
    LoggerGetDefault()->Log(msg, std::string(fn), line, LogLevel::Error); \
  } while (0)

#define WARNING_EXPANDED(fn, line, msg) \
  do { \
    LoggerGetDefault()->Log(msg, std::string(fn), line, LogLevel::Warning); \
  } while (0)

#define INFO_EXPANDED(fn, line, msg) \
  do { \
    LoggerGetDefault()->Log(msg, std::string(fn), line, LogLevel::InfoLog); \
  } while (0)

#define DEBUG_EXPANDED(fn, line, msg) \
  do { \
    LoggerGetDefault()->Log(msg, std::string(fn), line, LogLevel::Debug); \
  } while (0)

#define LOG_CRITICAL(msg) CRITICAL_EXPANDED(__FUNCTION__, __LINE__, (msg))
#define LOG_ERROR(msg) ERROR_EXPANDED(__FUNCTION__, __LINE__, (msg))
#define LOG_WARNING(msg) WARNING_EXPANDED(__FUNCTION__, __LINE__, (msg))
#define LOG_INFO(msg) INFO_EXPANDED(__FUNCTION__, __LINE__, (msg))
#define LOG_DEBUG(msg) DEBUG_EXPANDED(__FUNCTION__, __LINE__, (msg))

#endif // LOGGER_MACROS_H