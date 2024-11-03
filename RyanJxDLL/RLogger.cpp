#include "pch.h"
#include "RLogger.h"

RLogger::RLogger() {
	logFile = "C:\\Users\\nguye\\source\\debugging\\ryandll.log";
}

std::string RLogger::getCurrentTimestamp() {
	//// Get current time as a time_point
	auto now = std::chrono::system_clock::now();
	//// Convert to time_t for formatting
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	//// Convert to local time
#pragma warning(suppress : 4996)
	std::tm local_tm = *std::localtime(&now_c);

	//// Use stringstream to format the date and time
	std::ostringstream oss;
	oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");

	return oss.str();

	return "";
}

void RLogger::writeLog(std::string message) {
#pragma warning(suppress : 4996)
	FILE* f = freopen(this->logFile.c_str(), "a+", stdout);
	std::cout << this->getCurrentTimestamp() << " - " << message << std::endl;
	fclose(stdout);
}

void RLogger::writeLog(int message)
{
#pragma warning(suppress : 4996)
	FILE* f = freopen(this->logFile.c_str(), "a+", stdout);
	std::cout << this->getCurrentTimestamp() << " - " << std::to_string(message) << std::endl;
	fclose(stdout);
}

