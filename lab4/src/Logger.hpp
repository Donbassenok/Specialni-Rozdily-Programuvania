#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <iostream>

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    static Logger& getInstance();

    void log(LogLevel level, const std::string& message);

    void trace(const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

    void setLevel(LogLevel level);

private:
    Logger();
    ~Logger();

    std::string getCurrentTime();

    std::string levelToString(LogLevel level);

    std::mutex logMutex;      
    std::ofstream logFile;    
    LogLevel currentLevel;    
};