#ifndef LOGGER_H
#define LOGGER_H

#include "loggerInterface.h"

#include <string>
#include <list>
#include <map>
#include <stdint.h>

class Logger : public LoggerInterface
{

public:

	Logger(std::string logName = "default", LogLevel messageLevel = LogLevel::NotSpecified);
	~Logger();

	void name(std::string logName) override;

	void Log(std::string message, std::string callStackString, uint32_t lineNumber, LogLevel messageLevel) override;

	void LogSimple(std::string message, LogLevel messageLevel = LogLevel::NotSpecified) override;

	std::string LogLevelAsString(LogLevel messageLevel) const override;

	uint32_t count(LogLevel messageLevel) const override;

	virtual uint32_t count() const override;

	void requestSave(void) override;

private:
	void _dumpMessagesToFile();
	std::string _getHeaderString() const;
	std::string _getLogString(const std::string & logLevel, const std::string & timestamp_ms, const std::string & callStack, const std::string & line, const std::string & message) const;

	LogLevel _minLevelSentToConsole;
	std::string _logName;

	MessageList _messages;
	std::map< LogLevel, uint32_t > _count;
	uint32_t _totalCount;
};

#endif
