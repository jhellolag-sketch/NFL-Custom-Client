#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace Logger {

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
};

class LoggerImpl {
private:
    std::ofstream logFile;
    std::mutex logMutex;
    bool initialized = false;
    std::string logPath;

    std::string GetTimestamp() {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    std::string LogLevelToString(LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO:  return "INFO ";
            case WARN:  return "WARN ";
            case ERROR: return "ERROR";
            default:    return "?????";
        }
    }

public:
    bool Init() {
        std::lock_guard<std::mutex> lock(logMutex);
        
        if (initialized) return true;

        // Get user's Documents folder
        char path[MAX_PATH];
        if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path) != S_OK) {
            return false;
        }

        logPath = std::string(path) + "\\NFL-Custom-Client";
        
        // Create directory if it doesn't exist
        CreateDirectoryA(logPath.c_str(), NULL);
        
        logPath += "\\log.txt";
        
        logFile.open(logPath, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            return false;
        }

        initialized = true;
        Log("=== NFL Custom Client Logger Initialized ===", INFO);
        return true;
    }

    void Log(const std::string& message, LogLevel level = INFO) {
        if (!initialized) return;

        std::lock_guard<std::mutex> lock(logMutex);
        
        std::string logEntry = "[" + GetTimestamp() + "] [" + LogLevelToString(level) + "] " + message;
        
        logFile << logEntry << std::endl;
        logFile.flush();

        #ifdef _DEBUG
        OutputDebugStringA((logEntry + "\n").c_str());
        #endif
    }

    void Shutdown() {
        std::lock_guard<std::mutex> lock(logMutex);
        
        if (initialized) {
            Log("=== NFL Custom Client Logger Shutdown ===", INFO);
            logFile.close();
            initialized = false;
        }
    }
};

// Global logger instance
inline LoggerImpl& GetLogger() {
    static LoggerImpl logger;
    return logger;
}

// Convenience functions
inline bool Init() {
    return GetLogger().Init();
}

inline void Log(const std::string& message, LogLevel level = INFO) {
    GetLogger().Log(message, level);
}

inline void Shutdown() {
    GetLogger().Shutdown();
}

} // namespace Logger
