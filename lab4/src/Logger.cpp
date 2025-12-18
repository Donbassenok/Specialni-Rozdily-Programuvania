#include "Logger.hpp"
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : currentLevel(LogLevel::INFO) {
    std::string logPath;
#ifdef PROJECT_ROOT
    logPath = std::string(PROJECT_ROOT) + "application.log";
#else
    logPath = "application.log";
#endif

    logFile.open(logPath, std::ios::app);
    
    if (!logFile.is_open()) {
        std::cerr << "CRITICAL ERROR: Could not open log file at: " << logPath << std::endl;
    } else {
        std::cout << "[Logger] Writing logs to: " << logPath << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    currentLevel = level;
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < currentLevel) {
        return;
    }

    std::lock_guard<std::mutex> lock(logMutex);

    std::string timeStr = getCurrentTime();
    std::string levelStr = levelToString(level);
    
    std::stringstream ss;
    ss << "[" << timeStr << "] [" << levelStr << "] " << message;
    std::string finalLog = ss.str();

    std::cout << finalLog << std::endl;

    if (logFile.is_open()) {
        logFile << finalLog << std::endl;
        logFile.flush(); 
    }
}

void Logger::trace(const std::string& message) { log(LogLevel::TRACE, message); }
void Logger::debug(const std::string& message) { log(LogLevel::DEBUG, message); }
void Logger::info(const std::string& message)  { log(LogLevel::INFO, message); }
void Logger::warn(const std::string& message)  { log(LogLevel::WARN, message); }
void Logger::error(const std::string& message) { log(LogLevel::ERROR, message); }

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::tm tmStruct;
    
    #if defined(_WIN32) || defined(_WIN64)
        localtime_s(&tmStruct, &timeT);
    #else
        localtime_r(&timeT, &tmStruct);
    #endif

    std::stringstream ss;
    ss << std::put_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}