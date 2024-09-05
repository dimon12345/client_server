#include "LineLogger.h"

LineLogger::LineLogger() : _ready(false) {
}

void LineLogger::addLine(const std::string &line)
{
	const std::lock_guard<std::mutex> lock(_mutex);
	if (!_ready) {
		_logFile = std::ofstream("log.txt", std::ofstream::app);
		_ready = true;
	}
	_logFile << line << std::endl;
	_logFile.flush();
}
