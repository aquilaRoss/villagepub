
#include "raylib.h" // For GetTime and 

#include "logger.h"

static LoggerPtr _defaultLogger = std::make_shared<Logger>("Default", LogLevel::Debug);

LoggerPtr LoggerGetDefault(void)
{
	return _defaultLogger;
}

Logger::Logger(std::string logName, LogLevel messageLevel):
	_minLevelSentToConsole(messageLevel),
	_totalCount(0)
{
	name(logName);

	_count[LogLevel::Critical] = 0;
	_count[LogLevel::Error] = 0;
	_count[LogLevel::Warning] = 0;
	_count[LogLevel::InfoLog] = 0;
	_count[LogLevel::Debug] = 0;
	_count[LogLevel::NotSpecified] = 0;
}

Logger::~Logger()
{
	_dumpMessagesToFile();
}

void Logger::name(std::string logName)
{
	if (logName.length() > 0)
	{
		_logName = logName;// "Data/logs/" + logName;

		/*
		FILE * _logFile = fopen(std::string(_logName + ".log").c_str(), "a");

		if (_logFile != 0)
		{
			std::string logMessage = "\n\nNew Logger attaching to File.....\n";
			fputs(logMessage.c_str(), _logFile);
			fclose(_logFile);
		}
		*/
	}
}

void Logger::Log(std::string message, std::string callStackString, uint32_t lineNumber, LogLevel messageLevel)
{
	std::string logMessage = _getLogString(LogLevelAsString(messageLevel), std::to_string(GetTime()), callStackString, std::to_string(lineNumber), message);

	LogSimple(logMessage, messageLevel);
}

void Logger::LogSimple(std::string message, LogLevel messageLevel)
{
	if (messageLevel <= _minLevelSentToConsole && _logName.length() > 0)
	{
		std::string messageUsed = message + +"\n";
		_count[messageLevel] = _count[messageLevel] + 1;
		_totalCount++;

		printf(messageUsed.c_str());

		_messages.push_back(messageUsed);

		if (_messages.size() > 100)
		{
			_dumpMessagesToFile();
		}
	}
}

std::string Logger::LogLevelAsString(LogLevel messageLevel) const
{
	switch (messageLevel)
	{
	case Critical:
		return "Critical";
		break;
	case Error:
		return "Error";
		break;
	case Warning:
		return "Warning";
		break;
	case InfoLog:
		return "Info";
		break;
	case Debug:
		return "Debug";
		break;
	case NotSpecified:
		return "Not Specified";
		break;
	default:
		return "Unknown";
		break;
	}
}

uint32_t Logger::count(LogLevel messageLevel) const
{
	const auto & countIterator = _count.find(messageLevel);

	if (countIterator != _count.end())
	{
		return countIterator->second;
	}
	else
	{
		return UINT32_MAX;
	}
}

uint32_t Logger::count() const
{
	return _totalCount;
}

void Logger::requestSave(void)
{
	_dumpMessagesToFile();
}

void Logger::_dumpMessagesToFile()
{
	std::string fileName(_logName + ".log");

	FILE * plogFile = fopen(fileName.c_str(), "r");

	if (plogFile != 0)
	{
		// We opened it in read mode, this means it exists, close it and log to it with "a" for append.
		fclose(plogFile);
	}
	else
	{
		// we FAILED to open it in "r" which means (hopefully) that it doesnt exist, lets try "w"
		// which should create it or blank it if it exists so we can add the header.
		plogFile = fopen(fileName.c_str(), "w");

		if (plogFile != 0)
		{
			// We opened it "w", lets put the header.
			fputs(_getHeaderString().c_str(), plogFile);
			fclose(plogFile);
		}
	}

	plogFile = fopen(std::string(_logName + ".log").c_str(), "a");

	if (plogFile != 0)
	{
		for (auto currentMessage : _messages)
		{
			fputs(currentMessage.c_str(), plogFile);
		}
		_messages.clear();
		fclose(plogFile);
	}
}

std::string Logger::_getHeaderString() const
{
	return _getLogString("Level", "Time", "Function", "Line", "Message");
}

std::string Logger::_getLogString(const std::string & logLevel, const std::string & timestamp_ms, const std::string & callStack, const std::string & line, const std::string & message) const
{
	return logLevel + "," + timestamp_ms + "(ms)," + callStack + "()," + line + "," + message;
}