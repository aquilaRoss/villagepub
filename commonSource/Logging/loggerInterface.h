#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include <string>
#include <list>
#include <memory>
#include <stdint.h>

enum LogLevel {
	Critical = 0,
	Error,
	Warning,
	InfoLog,
	Debug,
	NotSpecified
};

class LogEntry
{
public:
	LogEntry(std::string message, std::string callstackInfo, LogLevel level, uint32_t timeStamp) :
		Level(level), TimeStamp(timeStamp), Message(message), CallStackInfo(callstackInfo)
	{};
	LogLevel Level;
	uint32_t TimeStamp;
	std::string Message;
	std::string CallStackInfo;
};

using MessageList = std::list<std::string>;
using LogEntryList = std::list<LogEntry>;

class LoggerInterface
{
public:
	virtual ~LoggerInterface() {}

	virtual void name(std::string logName) = 0;

	virtual void Log(std::string message, std::string callStackString = "UnknownFunction", uint32_t lineNumber = 0, LogLevel messageLevel = LogLevel::NotSpecified) = 0;

	virtual void LogSimple(std::string message, LogLevel messageLevel = LogLevel::NotSpecified) = 0;

	virtual std::string LogLevelAsString(LogLevel messageLevel) const = 0;

	virtual uint32_t count(LogLevel messageLevel) const = 0;

	virtual uint32_t count() const = 0;

	virtual void requestSave(void) = 0;
private:
};

using LoggerPtr = std::shared_ptr<LoggerInterface>;

#endif // LOGGER_INTERFACE_H