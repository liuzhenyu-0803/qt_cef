#include "log.h"

std::mutex logMutex;

void log(const std::string &message)
{
    std::lock_guard<std::mutex> lock(logMutex);
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
    else {
        std::cerr << "Error: Unable to open log file." << std::endl;
    }
}
