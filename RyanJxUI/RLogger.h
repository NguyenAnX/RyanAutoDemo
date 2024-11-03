#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#pragma once

class RLogger
{
public:
	std::string logFile;

	RLogger();
	std::string getCurrentTimestamp();
	void writeLog(std::string message);
	void writeLog(int message);
};

