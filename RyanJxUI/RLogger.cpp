#include "RLogger.h"

RLogger::RLogger() {
	logFile = "C:\\Users\\nguye\\source\\debugging\\ryandui.log";
}

std::string RLogger::getCurrentTimestamp() {
	//// Get current time as a time_point
	auto now = std::chrono::system_clock::now();
	//// Convert to time_t for formatting
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	//// Convert to local time
	std::tm local_tm = *std::localtime(&now_c);

	//// Use stringstream to format the date and time
	std::ostringstream oss;
	oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");

	return oss.str();

	return "";
}

void RLogger::writeLog(std::string message) {
	FILE* f = freopen(this->logFile.c_str(), "a+", stdout);
	std::cout << this->getCurrentTimestamp() << " - " << message << std::endl;
	fclose(stdout);
}

void RLogger::writeLog(int message)
{
	FILE* f = freopen(this->logFile.c_str(), "a+", stdout);
	std::cout << this->getCurrentTimestamp() << " - " << std::to_string(message) << std::endl;
	fclose(stdout);
}
