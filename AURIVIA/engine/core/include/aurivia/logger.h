#pragma once

#include <string>
#include <iostream>

namespace Aurivia {

enum class LogLevel
{
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

/**
 * @brief Simple logging system
 */
class Logger
{
public:
    static void SetLevel(LogLevel level) { s_level = level; }
    
    template<typename... Args>
    static void Trace(const std::string& message)
    {
        if (s_level <= LogLevel::Trace)
            Log("[TRACE]", message);
    }
    
    template<typename... Args>
    static void Debug(const std::string& message)
    {
        if (s_level <= LogLevel::Debug)
            Log("[DEBUG]", message);
    }
    
    template<typename... Args>
    static void Info(const std::string& message)
    {
        if (s_level <= LogLevel::Info)
            Log("[INFO]", message);
    }
    
    template<typename... Args>
    static void Warning(const std::string& message)
    {
        if (s_level <= LogLevel::Warning)
            Log("[WARN]", message);
    }
    
    template<typename... Args>
    static void Error(const std::string& message)
    {
        if (s_level <= LogLevel::Error)
            Log("[ERROR]", message);
    }
    
    template<typename... Args>
    static void Critical(const std::string& message)
    {
        if (s_level <= LogLevel::Critical)
            Log("[CRITICAL]", message);
    }

private:
    static void Log(const std::string& level, const std::string& message)
    {
        std::cout << level << " " << message << std::endl;
    }
    
    static LogLevel s_level;
};

} // namespace Aurivia

#define AV_LOG_TRACE(msg) Aurivia::Logger::Trace(msg)
#define AV_LOG_DEBUG(msg) Aurivia::Logger::Debug(msg)
#define AV_LOG_INFO(msg) Aurivia::Logger::Info(msg)
#define AV_LOG_WARN(msg) Aurivia::Logger::Warning(msg)
#define AV_LOG_ERROR(msg) Aurivia::Logger::Error(msg)
#define AV_LOG_CRITICAL(msg) Aurivia::Logger::Critical(msg)
