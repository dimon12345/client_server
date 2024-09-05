#pragma once

#include <string>
#include <mutex>
#include <fstream>

class LineLogger
{
	std::mutex _mutex;
	std::ofstream _logFile;
	bool _ready;
public:
	LineLogger();
	void addLine(const std::string &line);
};
